
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
          solidSmooth.write();
        }

        TforSolid = T;
        TforSolidOld = T.oldTime();
        if (mesh.time().value() == runTime.deltaTValue()){
          TforSolidOld = T0;
        }
        sigmaYVol *= max((T_solidus - T)/(T_solidus - T0), 0.1);
        Info << "Min sigmaY Vol"<< min(sigmaYVol) << endl;

        dT = TforSolid - TforSolidOld;
        volScalarField threeKalpha = (2*mu+3*lambda)*alphaLinear*(scalar(1) - liquidFraction);
        volVectorField gradThreeKalphaDeltaT =
          fvc::grad(threeKalpha*(T), "grad(threeKalphaDeltaT)");
        DEpsilonT = tensor::one*alphaLinear*T*(scalar(1) - liquidFraction);
        if (mechanicalTest == 1){
          Info << "Max DEpsilonT" << max(DEpsilonT) << endl;
          Info << "Maximum threekapa is "<< max(gradThreeKalphaDeltaT) << endl;
          volVectorField threeKgrad = fvc::grad((threeKalpha), "grad(three)*T")*T;
          volVectorField threeTgrad = fvc::grad((T), "grad(T)*three")*threeKalpha;
          threeKgrad.write();
          threeTgrad.write();
          gradThreeKalphaDeltaT.write();
        }

        iCorr = 0;
        volTensorField sigma_old = sigma;
        if (mechanicalTest == 1){
          Info << "All baragos with temperature is done" << endl;
        }

//************************************ START OF MECHANICAL PART ***************************//
// fvm::laplacian((2*muf + lambdaf), DU, "laplacian(DDU,DU)")
        gradDU = fvc::grad(DU);
        DEpsilonP = tensor::zero;
        do
        {
          sigma = sigma_old;
            DU.storePrevIter();
            if (mechanicalTest == 1){
              Info << "Old DU is stored" << endl;
            }


            fvVectorMatrix DUEqn
            (
                rho*fvm::d2dt2(DU)
             ==
            fvm::laplacian((2*muf + lambdaf), DU, "laplacian(DDU,DU)")
              +    fvc::div
                (
                    mu*gradDU.T() + lambda*(I*tr(gradDU)) - (mu + lambda)*gradDU,
                    "div(sigma)"
                )
              // - sinkTerm*DU*(liquidFraction)/((scalar(1) - liquidFraction) + SMALL)
                - fvc::div(2*muf*(mesh.Sf() & fvc::interpolate(DEpsilonP)) +
                         lambdaf*(mesh.Sf() & fvc::interpolate(tr(DEpsilonP)*I)))
                         - gradThreeKalphaDeltaT
            );

            if (mechanicalTest == 1){
              Info << "Matrix is a good matrix" << endl;
            }

            // DUEqn.solve();
            initialResidual = DUEqn.solve().initialResidual();
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
            DU.relax();

            gradDU = fvc::grad(DU);
            DEpsilon = 0.5*(gradDU + gradDU.T());
            sigma += 2.0*mu*gradDU + lambda*I*tr(gradDU);
            if (mechanicalTest == 1){
              Info << "max DU " << max(DU) << endl;
              Info << "Max sigma" << max(sigma) << endl;
            }
            volScalarField sqrtJ2 = sqrt((1.0/2.0)*magSqr(dev(sigma)));

            volScalarField fac = sqrtJ2/sigmaYVol;
            fac.correctBoundaryConditions();
            if (mechanicalTest == 1){
              Info << "max sqrtJ2 " << max(sqrtJ2) << endl;
              Info << "Is there any plasticity " <<  max(fac) << endl;
            }
            forAll(fac, celli)
              {
              if (fac[celli] > 1.0) //Plasticity occurs
                {
                  sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
                  tensor dsigma = sigma[celli] - sigma_old[celli];
                  tensor deps_e = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
                  + dev(dsigma)/(2.0*mu[celli]);
                  DEpsilonP[celli] = DEpsilon[celli] - deps_e - DEpsilonT[celli];
                }
              else // only elasticity
              {
                DEpsilonP[celli] *= 0;
              }
            }
// TODO change boundary Field
            // forAll(mesh.boundary(), patchID)
            // {
            //     forAll (mesh.boundary()[patchID],facei)
            //     {
            //     if (fac.boundaryField()[patchID][facei] > 1.0) //Plasticity occurs
            //       {
            //         // sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
            //         // tensor dsigma = sigma[celli] - sigma_old[celli];
            //         // tensor deps_e = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
            //         // + dev(dsigma)/(2.0*mu[celli]);
            //         // DEpsilonP.boundaryFieldRef()[patchID][facei] = DEpsilon.boundaryFieldRef()[patchID][facei] - deps_e - DEpsilonT[celli];
            //       }
            //     else // only elasticity
            //     {
            //       DEpsilonP.boundaryFieldRef()[patchID][facei] = 0.0;
            //     }
            //   }
            // }
            //
            // DEpsilonP.correctBoundaryConditions();

            Info << "How Plastic " << max(DEpsilonP) << endl;

            if (iCorr % 1 == 0)
            {
                Info<< "\tTime " << runTime.value()
                    << ", Corr " << iCorr
                    << ", Solving for " << DU.name()
                    // << " using " << solverPerf.solverName()
                    // << ", res = " << solverPerf.initialResidual()
                    << ", rel res = " << relativeResidual
                    << ", plastic res = " << plasticResidual;

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
        U += DU;
        gradU = fvc::grad(U);
        epsilon = 0.5*(gradU + gradU.T());
        epsilonP += DEpsilonP;
        sigma = sigma_old + DSigma;
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
