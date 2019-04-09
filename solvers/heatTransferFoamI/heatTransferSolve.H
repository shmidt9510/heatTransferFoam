#include "laserMovement.H"

porosity = max(scalar(0), min(porosityPrev, initialPorosity*(scalar(1) - liquidFraction)));

Cp = FourParameterModel(liquidFraction, T, Cp_sol, Cp_liq, dCp_sol, dCp_liq);
k = FourParameterModel(liquidFraction, T, k_sol, k_liq, dk_sol, dk_liq);

// TODO Conductivity is like hundred times less in powder.
// k = k*(scalar(1) - porosity/(initialPorosity + initialPorosity/10));

fusionTerm = (fvc::laplacian((scalar(1)-porosity)/(scalar(1)-initialPorosity)*k*enthalpyFusion/Cp, liquidFraction));

diffusivity = k/Cp *(scalar(1)-porosity)/(scalar(1)-initialPorosity);

  fvScalarMatrix TEqn
  (
      fvm::ddt(rho0, he)
      - fvm::laplacian(diffusivity, he)
      - laserDistribution / (scalar(1) - initialPorosity)
      + fusionTerm
  );

  TEqn.relax();

  TEqn.solve();

//Update variables for calculation T, next step and
liquidFraction = tanhSmooth(he, (he_solidus+he_liquidus)/2, (he_solidus-he_liquidus)/2);
T = temperatureCalc(he, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);
gradhe = Foam::mag(fvc::grad(he));
porosityPrev = porosity;

// ***************** Check laser source energy ***************
// volScalarField he_calc = enthalpyCalc(T, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);
// volScalarField qq = he-he_calc;
// Info<< "Sum of difference of he and enthalpyCalc(temeperatureCalc(he)) = " << sum(qq) << nl << endl;
// entSum= he;
// entSum.internalField() *= mesh.V();
// Info << "Here I am" << nl << endl;

// Info<< "Heat flux = " << (sum(entSum - entSumPrev))*rho0/deltaT*(scalar(1) - initialPorosity)  << nl << endl;
