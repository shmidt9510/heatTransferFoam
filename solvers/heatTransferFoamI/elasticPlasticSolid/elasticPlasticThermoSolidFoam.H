
Info<< "Solve elastoplasticthermonanosolid"<< endl;

        int iCorr = 0;
        // lduSolverPerformance solverPerf;
        Vector<double> initialResidual = vector(0,0,0);
        double relativeResidual = 1.0;
        double plasticResidual = 1.0;
        lduMatrix::debug = 0;
        // HOW TO EXCLUDE LIQUID PART
        solidSmooth = -tanhSmooth((T - T0), T_solidus/2, T_solidus/solidSmoothWidth)*solidSmoothAmplitude + scalar(1);

        // (scalar(1) - liquidFraction*0.9);
        // if (initialPorosity.value() > 0){
        //   solidSmooth *=(scalar(1) - porosity/initialPorosity*0.9);
        // }
        surfaceScalarField solidSmoothf = fvc::interpolate(solidSmooth, "solidSmooth");
        muf = muf0*solidSmoothf;
        lambdaf = lambdaf0*solidSmoothf;
        mu = mu0*solidSmooth;
        lambda = lambda0*solidSmooth;
        if (mechanicalTest == 1){
          Info << "Max mu "<< max(mu) << " Max lambda " << max(lambda) << endl;
                  mu.write();
                  lambda.write();
        }

        sigmaYVol = sigmaY*max((T_solidus - T)/(T_solidus - T0), 0.1);
        sigmaYVol.write();
        TforSolidOld = T.oldTime();
        if (mesh.time().value() == runTime.deltaTValue()){
          TforSolidOld = T0;
        }
        dT = T - TforSolidOld;


        volScalarField threeKalpha = (2*mu+3*lambda)*alphaLinear*(scalar(1) - liquidFraction);
        volVectorField gradThreeKalphaDeltaT =
          fvc::grad(threeKalpha*(T), "grad(threeKalphaDeltaT)");
        DEpsilonT = tensor::one*alphaLinear*T*(scalar(1) - liquidFraction);


                  if (mechanicalTest == 1){
                    solidSmooth.write();
                    Info << "Max DEpsilonT" << max(DEpsilonT) << endl;
                    Info << "Maximum threekapa is "<< max(gradThreeKalphaDeltaT) << endl;
                    gradThreeKalphaDeltaT.write();
                    }

//************************************ START OF MECHANICAL PART ***************************//
        iCorr = 0;
        Uold = U.oldTime();
        epsilonPold = epsilonP.oldTime();
        sigmaOld = sigma.oldTime();
        if (mesh.time().value() == runTime.deltaTValue()){
          Uold = U*0;
          epsilonPold = tensor::zero;
          sigmaOld = sigma*0;
        }
        gradU = fvc::grad(U);
        DEpsilonP = tensor::zero;
        do
        {
          sigma = sigmaOld;
          epsilonP = epsilonPold;
            U.storePrevIter();
            fvVectorMatrix UEqn
            (
                rho*fvm::d2dt2(U)
             ==
            fvm::laplacian((2*muf + lambdaf), U, "laplacian(DDU,DU)")
              +    fvc::div
                (
                    mu*gradU.T() + lambda*(I*tr(gradU)) - (mu + lambda)*gradU,
                    "div(sigma)"
                )
                - fvc::div(2*muf*(mesh.Sf() & fvc::interpolate(epsilonP)) +
                         lambdaf*(mesh.Sf() & fvc::interpolate(tr(epsilonP)*I)))
                - gradThreeKalphaDeltaT
            );

            // DUEqn.solve();
            initialResidual = UEqn.solve().initialResidual();
            if ((initialResidual[0] > initialResidual[1]) && (initialResidual[0] > initialResidual[2])){
              relativeResidual = initialResidual[0];
            } else if (initialResidual[1] > initialResidual[2]) {
              relativeResidual = initialResidual[1];
            } else {
              relativeResidual = initialResidual[2];
            }
            // relativeResidual = max(initialResidual[1],initialResidual[2],initialResidual[3]);
            if (mechanicalTest == 1){
              Info << "Init res" << initialResidual << endl;
            }
            U.relax();

#           include "rheologyUpdate.H"
            if (iCorr % 1 == 0)
            {
                Info<< "\tTime " << runTime.value()
                    << ", Corr " << iCorr
                    << ", Solving for " << U.name()
                    // << " using " << solverPerf.solverName()
                    // << ", res = " << solverPerf.initialResidual()
                    << ", rel res = " << relativeResidual
                    << ", plastic res = " << plasticResidual << endl;

                // Info<< ", inner iters = " << solverPerf.nIterations() << endl;
            }
        }
        while
        (
            iCorr++ < 2
            ||
            (
                //solverPerf.initialResidual() > convergenceTolerance
                // relativeResidual > convergenceTolerance
                relativeResidual > 1e-1
             && iCorr < 2000
            )
        );

        Info<< nl << "Time " << runTime.value() << ", Solving for " << DU.name()
            << ", Initial residual = " << initialResidual
            // << ", Final residual = " << solverPerf.initialRefsidual()
            << ", Final rel residual = " << relativeResidual
            << ", No outer iterations " << iCorr << endl;

        // Update total quantities
        Info << "Maximum DU = " << max(DU) << endl;
        DSigma = 2*mu*(DEpsilon - DEpsilonP - DEpsilonT) + lambda*(I*tr(DEpsilon - DEpsilonP - DEpsilonT));
        // U += DU;
        // gradU = fvc::grad(U);
        epsilon = 0.5*(gradU + gradU.T());
        // epsilonP += DEpsilonP;
        sigma = sigmaOld + DSigma;
        Info << "Maximum Eqsigma = " << max(sqrt((3.0/2.0)*magSqr(dev(sigma)))) << endl;
        // epsilon += DEpsilon;
        // sigma += DSigma;

        // U *= solidSmooth;
        // epsilon *= solidSmooth;
        // epsilonP *= solidSmooth;
        // sigma *= solidSmooth;


        // Update yields stresses

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;





  Info<< "End elastic plastic thermal nano uber cancer two pi power one over exponent calculation\n" << endl;


// ************************************************************************* //
