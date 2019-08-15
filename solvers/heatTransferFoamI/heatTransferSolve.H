#include "laserMovement.H"

porosity = max(scalar(0), min(porosityPrev, initialPorosity*(scalar(1) - liquidFraction)));

Cp = FourParameterModel(liquidFraction, T, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T0);
k = FourParameterModel(liquidFraction, T, k_sol, k_liq, dk_sol, dk_liq, T0);

// An Experimental Determination of the Thermal Conductivity of a 304L Stainless Steel Powder Metallurgy Material
// Consider porosity couldn't be lesser than 0.5
if (initialPorosity.value() != 0){
k = k*(scalar(1) - 1.6*porosity);
//linear decrease
Cp = Cp*(scalar(1) - porosity);
rho = rho*(scalar(1) - porosity);
}
if (airDepth.value() != 0){
  k = k*(scalar(1) - airPart) + airConductivity;
  rho = rho*(scalar(1) - airPart) + airDensity;
  Cp = Cp*(scalar(1) - airPart) + airCapacity;
}
fusionTerm = (fvc::laplacian(k*enthalpyFusion/Cp, liquidFraction));

diffusivity = k/Cp;

  fvScalarMatrix TEqn
  (
      fvm::ddt(rho0, he)
      - fvm::laplacian(diffusivity, he)
      - laserDistribution
      + fusionTerm
  );

  TEqn.relax();

  TEqn.solve();
//Update variables for calculation T, next step and
liquidFraction = tanhSmooth(he, (he_solidus + he_liquidus)/2, (he_liquidus - he_solidus)/2);
Info << "Max liquidFraction = " << max(liquidFraction) << endl;
dimensionedScalar liquidFractionVolume = fvc::domainIntegrate(liquidFraction*(scalar(1) - airPart));
Info << "Liquid Fraction Volume = " << liquidFractionVolume << endl;
liquidFractionDepth = laserRadius*0;
liquidFractionWidth = laserRadius*0;
liquidFractionLength = laserRadius*0;
dimensionedScalar integratedTemperature = fvc::domainIntegrate(T);
maxTemperature = max(T);

forAll (liquidFraction.internalField(), cellI)
    {
      if((mag(liquidFraction[cellI] - scalar(0.5)) < 0.1)
        && (mag(coordZ[cellI] - coordStart[2].value()) > liquidFractionDepth.value()) )
      {
         liquidFractionDepth = mag(coordZ[cellI] - coordStart[2].value())*laserRadius/laserRadius.value();
      }
      if((mag(liquidFraction[cellI] - scalar(0.5)) < 0.1)
          && (mag(coordY[cellI] - coordStart[1].value()) > liquidFractionWidth.value()))
      {
         liquidFractionWidth = mag(coordY[cellI] - coordStart[1].value())*laserRadius/laserRadius.value();
      }
    }
liquidFractionDepth *= 1000000;
liquidFractionWidth *= 2000000;
if (turnOnDebug.value() == 1){
Info << "Params " << (max(mag((laserCoordinate[1] - coordY)*liquidFraction))).value() << " "
     << (mag(max((coordY - laserCoordinate[1])*liquidFraction))).value() << " "
     << (max(mag((laserCoordinate[1] - coordY)*liquidFraction))).value() << " "
     << (mag(max((coordY - laserCoordinate[1])*liquidFraction))).value() << endl;
 }
fileos << mesh.time().value() <<"  "<< liquidFractionVolume.value() << "  " << maxTemperature.value() <<
  "  " << integratedTemperature.value() << "  " << liquidFractionDepth.value() << " " << liquidFractionWidth.value() << endl;

T = temperatureCalc(he, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);
gradhe = Foam::mag(fvc::grad(he));
trackHistory += (linecounter + scalar(2))/2*max(scalar(0), liquidFraction - liquidFractionPrev);
trackHistory = min(trackHistory,(linecounter+scalar(2))/2);
liquidFractionPrev = liquidFraction;
porosityPrev = porosity;

// ***************** Check laser source energy ***************
if (turnOnDebug.value() == 1){
  entSum= he;
  entSum.internalField() *= mesh.V();
  Info << "Heat flux calculated = " << ((sum(entSum*rho - entSumPrev*rho))/deltaT).value() << endl;
  Info << "Heat flux from laser = " << absorptivity*laserPower.value() << endl;
  entSumPrev = entSum;
}
