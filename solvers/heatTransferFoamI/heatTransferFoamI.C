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
#include "dynamicFvMesh.H"
#include "pisoControl.H"



#include "mathematicalConstants.H"
#include "functionsPhys.H"
#include "functionsMath.H"

//ELASTOTHERMOPLASTOTHING
#include "constitutiveModel.H"
#include "solidContactFvPatchVectorField.H"


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
#include "createFields.H"
#include "readTimeCoord.H"

// Plastic stuff
#include "createPlasticFields.H"
#include "createHistory.H"
#include "readDivDSigmaExpMethod.H"
#include "readSolidMechanicsControls.H"
/*
ARSTOTZKA AND DYNAMIC MESH
*/
// #include "initContinuityErrs.H"
// #include "initTotalVolume.H"
// #include "createMeshFields.H"
// #include "createControls.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
coordX = mesh.C().component(vector::X);
coordY = mesh.C().component(vector::Y);
coordZ = mesh.C().component(vector::Z);
porosityPrev =  initialPorosity.value()*tanhSmooth(coordZ, powderDepth, powderDepth/smootherFactor);
liquidFraction = tanhSmooth(T, (T_solidus + T_liquidus)/2, (T_solidus - T_liquidus)/smootherFactor);
//Initial enthalpy
he = enthalpyCalc(T, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);

dimensionedScalar he_solidus = (0.5*T_solidus*(2*Cp_sol + dCp_sol*T_solidus));
dimensionedScalar he_liquidus = enthalpyFusion + 0.5*T_solidus*(2*Cp_sol + dCp_sol*T_solidus);
liquidFraction = tanhSmooth(he, (he_solidus + he_liquidus)/2, (he_solidus - he_liquidus)/smootherFactor);
volScalarField Cp = FourParameterModel(liquidFraction, T, Cp_sol, Cp_liq, dCp_sol, dCp_liq);
volScalarField k = FourParameterModel(liquidFraction, T, k_sol, k_liq, dk_sol, dk_liq);
volScalarField gradhe (Foam::mag(fvc::grad(he)));
dimensionedScalar deltaT (runTime.deltaT());
Info<< "Delta time= " << deltaT << nl << endl;

// ***************** Check laser source energy ***************
// dimensionedScalar liquidFractionVolume = fvc::domainIntegrate(liquidFraction);
// dimensionedScalar hmin = pow(min(mesh.V()),1/3);
//
// dimensionedScalar cflLaser = mesh.deltatT()/hmin*laserSpeed;
// Info << "cfl laser" << cflLaser << nl << endl;

// volScalarField entSumPrev = he;
// volScalarField entSum = he;
// entSumPrev.internalField() *= mesh.V();
// entSum.internalField() *= mesh.V();

// ***************** Check resolution ***************
volScalarField gausTest(
     gaussian(coordX, coordStartX, laserRadius)
    *gaussian(coordY, coordStartY, laserRadius)
    *gaussian(coordZ, coordStartZ, laserRadius));
    gausTest.internalField() *= mesh.V();
    Info << "Sum of gausian over mesh" << gSum(gausTest) << nl << endl;
    if (1-2*gSum(gausTest)>0.1)
    {
      FatalErrorIn(args.executable())
          << "Insufficent resolution or bad normalizatopn of gauss and stuff"
          << exit(FatalError);
    }

// ****************** MAIN LOOP *****************

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        //Dynamic mesh
// #       include "dynMeshFile.H"

        //Calculation of the heat distribution
#       include "heatTransferSolve.H"

        //Calculate stresses
#       include "elasticPlasticThermoSolidFoam.H"

        //Write everything
#       include "writeFields.H"

#       include "writeHistory.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}

// ************************************************************************* //
