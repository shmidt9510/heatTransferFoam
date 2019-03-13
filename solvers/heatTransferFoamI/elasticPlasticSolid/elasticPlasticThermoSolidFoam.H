
Info<< "Solve elastoplasticthermonanosolid"<< endl;

        int iCorr = 0;
        lduSolverPerformance solverPerf;
        scalar initialResidual = 1.0;
        scalar relativeResidual = 1.0;
        scalar plasticResidual = 1.0;
        lduMatrix::debug = 0;
        scalar relResT = 1.0;



        // dimensionedScalar threeK = E/(rho0*(1 - 2*nu));
        volScalarField threeKalpha = rheology.threeK()*rho*alphaLinear;
        surfaceScalarField threeKalphaf =
            fvc::interpolate(threeKalpha, "threeKalpha");
        // volScalarField threeKalpha = threeK*rho0*alphaLinear;
        // surfaceScalarField threeKalphaf =
        //     fvc::interpolate(threeKalpha, "threeKalpha");
        volScalarField dT = T-T.oldTime();
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
                fvm::laplacian(2*muf + lambdaf, DU, "laplacian(DDU,DU)")
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

        Udisp += DU*(scalar(1) - liquidFraction);
        epsilon += DEpsilon*(scalar(1) - liquidFraction);
        epsilonP += rheology.DEpsilonP()*(scalar(1) - liquidFraction);
        sigma += DSigma*(scalar(1) - liquidFraction);
        Udisp *= (scalar(1) - liquidFraction);
        epsilon *= (scalar(1) - liquidFraction);
        epsilonP *= (scalar(1) - liquidFraction);
        sigma *= (scalar(1) - liquidFraction);


        // Update yields stresses
        rheology.updateYieldStress();
        // volScalarField  yieldstressstress = rheology.sigmaY();
// #       include "writeFields.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;





  Info<< "End elastic plastic thermal nano uber cancer two pi power one over exponent calculation\n" << endl;


// ************************************************************************* //
