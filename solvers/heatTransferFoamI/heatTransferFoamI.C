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


Description


\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#include "pimpleControl.H"

// #include "pisoControl.H"
#include "simpleControl.H"
#include "dynamicFvMesh.H"
// #include "MULES.H"
// #include "subCycle.H"
// SOLID STUFF
// #include "constitutiveModel.H"
// #include "thermalModel.H"

//

#include "mathematicalConstants.H"
#include "functionsPhys.H"
#include "functionsMath.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#include "setRootCase.H"
#include "createTime.H"
#include "createDynamicFvMesh.H"

// #include "createMesh.H"

// pisoControl piso(mesh);
// pimpleControl pimple(mesh);

#include "initContinuityErrs.H"
simpleControl simple(mesh);
//TODO Create object of properties onedat
#include "readThermalProperties.H"
#include "readLaserProperties.H"
#include "readPowderProperties.H"
#include "createFields.H"
#include "readTimeCoord.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
coordX = mesh.C().component(vector::X);
coordY = mesh.C().component(vector::Y);
coordZ = mesh.C().component(vector::Z);
porosityPrev =  initialPorosity.value()*tanhSmooth(coordZ, powderDepth, powderDepth/100);
liquidFraction = tanhSmooth(T, (T_solidus+T_liquidus)/2, (T_solidus-T_liquidus)/2);
//Initial enthalpy
he = enthalpyCalc(T, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);

dimensionedScalar he_solidus =(0.5*T_solidus*(2*Cp_sol+dCp_sol*T_solidus));
dimensionedScalar he_liquidus = enthalpyFusion + 0.5*T_solidus*(2*Cp_sol+dCp_sol*T_solidus);
liquidFraction = tanhSmooth(he, (he_solidus+he_liquidus)/2, (he_solidus-he_liquidus)/2);
volScalarField gradhe = Foam::mag(fvc::grad(he));
dimensionedScalar deltaT = runTime.deltaT();
Info<< "Delta time= " << deltaT << nl << endl;


// volScalarField entSumPrev = he;
// volScalarField entSum = he;
// entSumPrev.internalField() *= mesh.V();
// entSum.internalField() *= mesh.V();

//Check resolution
volScalarField gausTest =
     gaussian(coordX, coordStartX, laserRadius)
    *gaussian(coordY, coordStartY, laserRadius)
    *gaussian(coordZ, coordStartZ, laserRadius);
    gausTest.internalField() *= mesh.V();
    Info << "Sum of gausian over mesh" << gSum(gausTest) << nl << endl;
    if (1-2*gSum(gausTest)>0.1)
    {
      FatalErrorIn(args.executable())
          << "Insufficent resolution or bad normalizatopn of gauss and stuff"
          << exit(FatalError);
    }
//


    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;




        bool meshChanged = mesh.update();
        reduce(meshChanged, orOp<bool>());

#       include "volContinuity.H"  //Do I need it? (DynMesh case)




        dimensionedScalar localTime = mesh.time();
        // Info<< "Time = " << localTime.dimensions() << nl << endl;
        //
        laserDistribution = 2*absorptivity*laserPower*
        gaussian(coordX, coordStartX-laserSpeed*localTime, laserRadius)*
        gaussian(coordY, coordStartY, laserRadius)*
        gaussian(coordZ, coordStartZ, laserRadius);


        // Info<< "laserDistribution max = " << max(laserDistribution) << nl << endl;
        // volScalarField laserDistStat = laserDistribution;
        // laserDistStat.internalField() *= mesh.V();
        // Info<< "laserDistribution sum = " << sum(laserDistStat) << nl << endl;

        porosity = max(scalar(0), min(porosityPrev, initialPorosity*(scalar(1) - liquidFraction)));

        // Info<< "porositymin= " << min(porosity) << nl << endl;
        // Info<< "porositymax= " << max(porosity) << nl << endl;
        // Info<< "enthalpymin= " << min(he) << nl << endl;
        // Info<< "enthalpymax= " << max(he) << nl << endl;

        volScalarField Cp = FourParameterModel(liquidFraction, T, Cp_sol, Cp_liq, dCp_sol, dCp_liq);
        volScalarField k = FourParameterModel(liquidFraction, T, k_sol, k_liq, dk_sol, dk_liq);
        // Conductivity is like hundred times less in powder.
        // k = k*(scalar(1)-porosity);

        fusionTerm = fvc::laplacian((scalar(1)-porosity)/(scalar(1)-initialPorosity)*k*enthalpyFusion/Cp, liquidFraction);
        // Info<< "liquidFraction min = " << min(liquidFraction) << nl << endl;
        // Info<< "liquidFraction max = " << max(liquidFraction) << nl << endl;

        // entSumPrev = he;
        // entSumPrev.internalField() *= mesh.V();

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
        // enthalpySum =  (he)*mesh.V();

        // Info<< "6 = " << enthalpySum-enthalpySumPrev << nl << endl;
        //Update variables for calculation T, next step and
        liquidFraction = tanhSmooth(he, (he_solidus+he_liquidus)/2, (he_solidus-he_liquidus)/2);
        T = temperatureCalc(he, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);
        // gradhe = Foam::mag(fvc::grad(he));
        // volScalarField he_calc = enthalpyCalc(T, liquidFraction, Cp_sol, Cp_liq, dCp_sol, dCp_liq, T_solidus, T_liquidus, enthalpyFusion);
        // volScalarField qq = he-he_calc;
        // Info<< "Sum of difference of he and enthalpyCalc(temeperatureCalc(he)) = " << sum(qq) << nl << endl;
        // entSum= he;
        // entSum.internalField() *= mesh.V();
        // Info << "Here I am" << nl << endl;

        // Info<< "Heat flux = " << (sum(entSum - entSumPrev))*rho0/deltaT*(scalar(1) - initialPorosity)  << nl << endl;
        porosityPrev = porosity;
        if(runTime.outputTime())
          {
            T.write();
            liquidFraction.write();
            porosity.write();
            laserDistribution.write();
            he.write();
            gradhe.write();
          }

// #include "thermalStress.H"



        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}

// ************************************************************************* //
