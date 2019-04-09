
Info<< "Solve elastoplasticthermonanosolid"<< endl;

        int iCorr = 0;
        lduSolverPerformance solverPerf;
        scalar initialResidual = 1.0;
        scalar relativeResidual = 1.0;
        scalar plasticResidual = 1.0;
        lduMatrix::debug = 0;
        scalar relResT = 1.0;

        // HOW TO EXCLUDE LIQUID PART
        // volScalarField solidSmooth = mag((T_liquidus + T_liquidus/20 - T)/T_liquidus)*
        // volScalarField solidSmooth = tanhSmooth(T, T_solidus/1.2, T_solidus/10);
        // (scalar(1) - liquidFraction*0.9);
        // if (initialPorosity.value() > 0){
        //   solidSmooth *=(scalar(1) - porosity/initialPorosity*0.9);
        // }
        // surfaceScalarField solidSmoothf = fvc::interpolate(solidSmooth, "solidSmooth");
        // muf *= solidSmoothf;
        // lambdaf *= solidSmoothf;
        // mu *= solidSmooth;
        // lambda *= solidSmooth;
        // Info << min(muf) << " " << min(mu) << " " << min(lambdaf) << " " << min(lambda) << endl;
        // Info << min(solidSmooth) <<" "<< max(liquidFraction) << " "<< max(porosity/initialPorosity) <<endl ;
         // dimensionedScalar threeK = E/(rho0*(1 - 2*nu));


        volScalarField threeKalpha = rheology.threeK()*rho*alphaLinear;
        surfaceScalarField threeKalphaf =
            fvc::interpolate(threeKalpha, "threeKalpha");
        // volScalarField threeKalpha = threeK*rho0*alphaLinear;
        // surfaceScalarField threeKalphaf =
        //     fvc::interpolate(threeKalpha, "threeKalpha");

        TforSolid = T;
        TforSolidOld = T.oldTime();
        if (mesh.time().value() == runTime.deltaTValue()){
          TforSolidOld *= 0;
        }

        forAll (TforSolid.internalField(), cellI)
            {
              if (TforSolid.internalField()[cellI]>= T_solidus.value()){
                TforSolid.internalField()[cellI] = T_solidus.value();
              }
              if (TforSolidOld.internalField()[cellI] >= T_solidus.value()){
                TforSolidOld.internalField()[cellI] = T_solidus.value();
              }
            }

          forAll(mesh.boundary(), patchID)
          {
            forAll (mesh.boundary()[patchID],facei)
            {
            if (TforSolid.boundaryField()[patchID][facei]>= T_solidus.value()){
              TforSolid.boundaryField()[patchID][facei] = T_solidus.value();
            }
            if (TforSolidOld.boundaryField()[patchID][facei] >= T_solidus.value()){
              TforSolidOld.boundaryField()[patchID][facei] = T_solidus.value();
            }
          }
        }
        // Useless with upper forAll lopp
        TforSolid.correctBoundaryConditions();
        TforSolidOld.correctBoundaryConditions();

        volScalarField dT = TforSolid - TforSolidOld;
        TforSolidOld = TforSolid;
        // volScalarField dT = T-T.oldTime();

        iCorr = 0;
        volVectorField gradThreeKalphaDeltaT =
            fvc::grad(threeKalpha*(dT), "grad(threeKalphaDeltaT)");
        surfaceVectorField threeKalphaDeltaTf =
            mesh.Sf()*threeKalphaf*fvc::interpolate(dT, "deltaT");

        do
        {
            DU.storePrevIter();
#           include "calculateDivDSigmaExp.H"
            fvVectorMatrix DUEqn
            (
                rho*fvm::d2dt2(DU)
             ==
                fvm::laplacian((2*muf + lambdaf), DU, "laplacian(DDU,DU)")
              + divDSigmaExp
              - fvc::div(2*muf*(mesh.Sf() & fvc::interpolate(DEpsilonP)))
            );

            solverPerf = DUEqn.solve();

            if (iCorr == 0)
            {
                initialResidual = solverPerf.initialResidual();
            }

            if (aitkenRelax)
            {
#               include "aitkenRelaxation.H"
            }
            else
            {

                DU.relax();
            }

            gradDU = fvc::grad(DU);

#           include "calculateRelativeResidual.H"
#           include "calculateDEpsilonDSigma.H"

            // correct plastic strain increment
            rheology.correct();

#           include "calculatePlasticResidual.H"

            if (iCorr % infoFrequency == 0)
            {
                Info<< "\tTime " << runTime.value()
                    << ", Corr " << iCorr
                    << ", Solving for " << DU.name()
                    << " using " << solverPerf.solverName()
                    << ", res = " << solverPerf.initialResidual()
                    << ", rel res = " << relativeResidual
                    << ", plastic res = " << plasticResidual;
                if (aitkenRelax)
                {
                    Info<< ", aitken = " << aitkenTheta;
                }
                Info<< ", inner iters = " << solverPerf.nIterations() << endl;
            }
        }
        while
        (
            iCorr++ < 2
            ||
            (
                //solverPerf.initialResidual() > convergenceTolerance
                relativeResidual > convergenceTolerance
             && iCorr < nCorr
            )
        );

        Info<< nl << "Time " << runTime.value() << ", Solving for " << DU.name()
            << ", Initial residual = " << initialResidual
            << ", Final residual = " << solverPerf.initialResidual()
            << ", Final rel residual = " << relativeResidual
            << ", No outer iterations " << iCorr << endl;

        // Update total quantities
        U += DU;
        epsilon += DEpsilon;
        epsilonP += rheology.DEpsilonP();
        sigma += DSigma;

        // U *= solidFraction;
        // epsilon *= solidFraction;
        // epsilonP *= solidFraction;
        // sigma *= solidFraction;


        // Update yields stresses
        rheology.updateYieldStress();
        // volScalarField  yieldstressstress = rheology.sigmaY();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;





  Info<< "End elastic plastic thermal nano uber cancer two pi power one over exponent calculation\n" << endl;


// ************************************************************************* //
