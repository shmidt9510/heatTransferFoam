/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Application
heatTransferFoamAndPlasticAndThermoPlasticAndElasticAndMore42

Description
Simulate selective laser melting on the single layer with mechanical stresses properties calculation

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
// #include "dynamicFvMesh.H"
// #include "pisoControl.H"



#include "mathematicalConstants.H"
#include "functionsPhys.H"
#include "functionsMath.H"

//ELASTOTHERMOPLASTOTHING
// #include "constitutiveModel.H"
// #include "solidContactFvPatchVectorField.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"
// #include "createDynamicFvMesh.H"
// #include "createMesh.H"

//For dynamic mesh solver and checker
// pisoControl piso(mesh);

#include "readThermalProperties.H"
#include "readLaserProperties.H"
#include "readPowderProperties.H"
#include "readSystemProperties.H"
#include "readPowerStrategy.H"
#include "readMechanicalProperties.H"
#include "createFields.H"
#include "createPlasticFields.H"
//Adaptive mesh stuff
// #include "initContinuityErrs.H"
// #include "initTotalVolume.H"
// #include "createMeshFields.H"
// #include "createControls.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
coordX = mesh.C().component(vector::X);
coordY = mesh.C().component(vector::Y);
coordZ = mesh.C().component(vector::Z);

//initialPorosity here is for material conistensy after melting
if (powderDepth.value() != 0){
powderDepth = powderDepth*(scalar(1) - initialPorosity);
Info << "powderDepth " << powderDepth << endl;
porosityPrev = initialPorosity.value()*tanhSmooth(coordZ, powderDepth, -powderDepth/smootherPorosityFactor);
} else {
porosityPrev = initialPorosity.value()*tanhSmooth(coordZ, laserRadius, -laserRadius/smootherPorosityFactor)*0;
}
bool airIsOn = false;
if ((airDepth.value() > 0) && (powderDepth.value() > 0)){
  airIsOn = true;
porosityPrev = initialPorosity.value()*tanhSmooth(coordZ, airDepth + powderDepth, -powderDepth/smootherPorosityFactor);
airPart = tanhSmooth(coordZ, airDepth, -powderDepth/smootherAirFactor);
coordStart.replace(2, airDepth);
} else {
airPart = airPart*0;
}
T = T0;
//IC
// depth = laserStrategy - coordX;
// log_f = 3*LOG(pi/2)/2
// distribution = laser_distribution(x_surface, nlocal, dim-1)
// distribution = EXP((LOG(distribution) + log_f)*(1.0_pr - initial_pool_radius**-2) - log_f)
// lambda = laser_heat_flux(psi) * distribution / (initial_temp * k_0 * (1.0_pr - psi))
// temp = temp * EXP(-lambda*depth - (depth/initial_pool_radius)**2)
// point1 = laserStrategy[0]*convertToMetersTemp;
// T = T0 + T0*tempVar1*(gaussian(coordX, (point1[0]), laserRadius*tempVar2)*laserRadius/laserRadius.value())
//   *(gaussian(coordY, (point1[1]), laserRadius*tempVar2)*laserRadius/laserRadius.value())
//   *(gaussian(coordZ, (point1[2]), laserRadius*tempVar2)*laserRadius/laserRadius.value());

//For analytical problem
// dimensionedScalar Yh = max(coordY)/2;
// T = T0*(coordY/(2*Yh));
// T = T0*((scalar(1) - (coordY - Yh)/Yh)*((coordY - Yh)/Yh));
liquidFraction = tanhSmooth(T, (T_solidus + T_liquidus)/2, (T_liquidus - T_solidus)/2);
//Initial enthalpy
he = enthalpyCalc(T, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);

dimensionedScalar he_solidus = (0.5*T_solidus*(2*Cp_sol + dCp_sol*T_solidus));
dimensionedScalar he_liquidus = enthalpyFusion + 0.5*T_solidus*(2*Cp_sol + dCp_sol*T_solidus);
liquidFraction = tanhSmooth(he, (he_solidus + he_liquidus)/2, (he_liquidus - he_solidus)/2);
volScalarField Cp = FourParameterModel(liquidFraction, T, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T0);
volScalarField k = FourParameterModel(liquidFraction, T, k_sol, k_liq, dk_sol, dk_liq, T0);
volScalarField gradhe (Foam::mag(fvc::grad(he)));
dimensionedScalar deltaT (runTime.deltaT());

dimensionedScalar waitingTime = deltaT*0;
int firstIteration = 0;
// ***************** Check laser source energy ***************
dimensionedScalar liquidFractionVolume = fvc::domainIntegrate(liquidFraction);
volScalarField liquidFractionPrev = liquidFraction;
int lineAmount = lineAmountDim.value();
int strategyChoice = strategyChoiceDim.value();
double decreaseValue = decreaseValueDim.value();
dimensionedScalar liquidFractionWidth = laserRadius;
dimensionedScalar liquidFractionLength = laserRadius;
dimensionedScalar liquidFractionDepth = laserRadius;
dimensionedScalar maxTemperature = T0;
dimensionedScalar initialLaserPower = laserPower;
fileName outputFile("text.txt");
OFstream fileos(outputFile);
bool borderCheck = false;
bool convergedAdaptation = false;
bool startAdaptation = false;
double adaptPar = 0;
double prevAdaptPar = 0;
int timeIteration = 0;
int adaptationCounter = 0;
dimensionedScalar prevLaserPower = laserPower;
DEpsilonP = tensor::zero;
// dimensionedScalar hmin = pow(min(mesh.V()),1/3);
//
// dimensionedScalar cflLaser = mesh.deltatT()/hmin*laserSpeed;
// Info << "cfl laser" << cflLaser << nl << endl;

volScalarField entSumPrev = he;
volScalarField entSum = he;
// entSumPrev = entSumPrev*mesh.V();
// entSum = entSum*mesh.V();
int LayerNumber = 0;
//****************** Single track flag *******************
if (onlySingleTrack.value() == 1){
runTime.setDeltaT(trackLength/(laserSpeed*50));
runTime.setEndTime(runTime.value()+runTime.deltaT().value()*50);
}
// ***************** Check resolution ***************
// volScalarField gausTest(
//      gaussian(coordX, coordStartX, laserRadius)
//     *gaussian(coordY, coordStartY, laserRadius)
//     *gaussian(coordZ, coordStartZ, laserRadius));
//     gausTest.internalField() *= mesh.V();
//     Info << "Sum of gausian over mesh" << gSum(gausTest) << nl << endl;
//     if (1-2*gSum(gausTest)>0.1)
//     {
//       FatalErrorIn(args.executable())
//           << "Insufficient resolution or bad normalizatopn of gauss and stuff"
//           << exit(FatalError);
//     }

// ****************** MAIN LOOP *****************
    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        //Dynamic mesh
//         if (adaptiveOn.value() == 1){
// #       include "dynMeshFile.H"
//         }
        //Calculation of the heat distribution
        he.storePrevIter();
        if (thermalOn.value() == 1){
          if ((adaptiveOn.value() == 1) && startAdaptation){
            while (!convergedAdaptation){
              adaptationCounter++;
              Info << "Adaptation iteration # " << adaptationCounter<< endl;
#             include "heatTransferSolve.H"
            }
            convergedAdaptation = false;
          } else if (adaptiveOn.value() == 2) {
            laserPower = powerStrategy[timeIteration]*laserPower/laserPower.value();;
#           include "heatTransferSolve.H"
          } else if (adaptiveOn.value() == 3) {
            laserPower = initialLaserPower*calculatePower(mesh.time().value(),a,b,c,x1,x0);
            Info << "POOOOOOOOWEERRRRR" << laserPower << endl;
#           include "heatTransferSolve.H"
          } else {
#           include "heatTransferSolve.H"
          }
          if (firstIteration == 1){
            while (!convergedAdaptation){
              adaptationCounter++;
              Info << "Adaptation iteration # " << adaptationCounter<< endl;
  #             include "heatTransferSolve.H"
            }
            convergedAdaptation = false;
            firstIteration = 2;
          }
          if (convergedAdaptation){
            he.prevIter();
#           include "heatTransferSolve.H"
          }

        adaptationCounter = 0;
        }

//        Calculate stresses
        if (mechanicalOn.value() == 1){

        Info << "Solve plastic" << endl;
#       include "elasticPlasticThermoSolidFoam.H"
        }

        //Write everything
        if (runTime.outputTime())
        {
          runTime.write();
          liquidFraction.write();
          DEpsilonP.write();
          epsilonP.write();
          DEpsilonT.write();

                  volScalarField epsilonEq
          (
              IOobject
              (
                  "epsilonEq",
                  runTime.timeName(),
                  mesh,
                  IOobject::NO_READ,
                  IOobject::AUTO_WRITE
              ),
              sqrt((2.0/3.0)*magSqr(dev(epsilon)))
          );

          Info<< "Max epsilonEq = " << max(epsilonEq).value() << endl;

          volScalarField epsilonPEq
          (
              IOobject
              (
                  "epsilonPEq",
                  runTime.timeName(),
                  mesh,
                  IOobject::NO_READ,
                  IOobject::AUTO_WRITE
              ),
              sqrt((2.0/3.0)*magSqr(dev(epsilonP)))
          );

          Info<< "Max epsilonPEq = " << max(epsilonPEq).value() << endl;

          volScalarField sigmaEq
          (
              IOobject
              (
                  "sigmaEq",
                  runTime.timeName(),
                  mesh,
                  IOobject::NO_READ,
                  IOobject::AUTO_WRITE
              ),
              sqrt((3.0/2.0)*magSqr(dev(sigma)))
          );

                    Info<< "Max sigmaEq = " << max(sigmaEq).value() << endl;

                    volScalarField sigmaHyd
                    (
                        IOobject
                        (
                            "sigmaHyd",
                            runTime.timeName(),
                            mesh,
                            IOobject::NO_READ,
                            IOobject::AUTO_WRITE
                        ),
                        (
                            sigma.component(symmTensor::XX)
                          + sigma.component(symmTensor::YY)
                          + sigma.component(symmTensor::ZZ)
                        )/3
                    );
            Info<< "Max sigmaHyd = " << max(sigmaHyd).value() << endl <<
             "Xx " << max(sigma.component(symmTensor::XX)).value() << endl <<
             "Yy " << max(sigma.component(symmTensor::YY)).value() << endl <<
             "Zz " << max(sigma.component(symmTensor::ZZ)).value() << endl;



        }
// #       include "writeFields.H"
//
// #       include "writeHistory.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
        timeIteration ++;
    }

    Info<< "End\n" << endl;

    return(0);
}
