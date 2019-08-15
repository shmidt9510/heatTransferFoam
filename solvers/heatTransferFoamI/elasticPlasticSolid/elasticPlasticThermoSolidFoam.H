
Info<< "Solve elastoplasticthermonanosolid"<< endl;

#       include "readSolidMechanicsControls.H"

        int iCorr = 0;
        lduSolverPerformance solverPerf;
        scalar initialResidual = 1.0;
        scalar relativeResidual = 1.0;
        scalar plasticResidual = 1.0;
        lduMatrix::debug = 0;
        scalar relResT = 1.0;

        // HOW TO EXCLUDE LIQUID PART
        T.storePrevIter();
        //TODO RECHECK
        // solidSmooth = tanhSmooth(-T, T_solidus/1.5, T_solidus/tempVar2)*tempVar1 + scalar(1) - tempVar1;
        if (youngDependence.value() == 1){
          solidSmooth = max((T_solidus - T)/(T_solidus - T0), 1e-6);
        } else {
          solidSmooth = scalar(1);
        }
        //
        // tempSmooth = max((T_solidus - T)/(T_solidus - T0), scalar(0));
        // solidSmooth = (scalar(1) - liquidFraction*0.99999);
        // if (initialPorosity.value() > 0){
        //   solidSmooth *= (scalar(1) - porosity/initialPorosity*0.9999);
        // }
        surfaceScalarField solidSmoothf = fvc::interpolate(solidSmooth, "solidSmooth");
        muf = muf_*solidSmoothf;
        lambdaf = lambdaf_*solidSmoothf;
        mu = mu_*solidSmooth;
        lambda = lambda_*solidSmooth;
        muf.correctBoundaryConditions();
        lambdaf.correctBoundaryConditions();
        mu.correctBoundaryConditions();
        lambda.correctBoundaryConditions();
        mu.write();
        // mu.write();
        // lambda.write();
        // Info << min(muf) << " " << min(mu) << " " << min(lambdaf) << " " << min(lambda) << endl;
        // Info << min(solidSmooth) <<" "<< max(liquidFraction) << " "<< max(porosity/initialPorosity) <<endl ;
         // dimensionedScalar threeK = E/(rho0*(1 - 2*nu));

        // TforSolid = T;
        // TforSolidOld = T.oldTime();
        // if (mesh.time().value() == runTime.deltaTValue()){
        //   TforSolidOld = T0;
        // }
        // forAll (TforSolid.internalField(), cellI)
        //     {
        //       if (TforSolid.internalField()[cellI]>= T_solidus.value()){
        //         TforSolid.internalField()[cellI] = T_solidus.value();
        //       }
        //       if (TforSolidOld.internalField()[cellI] >= T_solidus.value()){
        //         TforSolidOld.internalField()[cellI] = T_solidus.value();
        //       }
        //     }
        //
        //   forAll(mesh.boundary(), patchID)
        //   {
        //     forAll (mesh.boundary()[patchID],facei)
        //     {
        //     if (TforSolid.boundaryField()[patchID][facei]>= T_solidus.value()){
        //       TforSolid.boundaryField()[patchID][facei] = T_solidus.value();
        //     }
        //     if (TforSolidOld.boundaryField()[patchID][facei] >= T_solidus.value()){
        //       TforSolidOld.boundaryField()[patchID][facei] = T_solidus.value();
        //     }
        //   }
        // }
        // // Useless with upper forAll lopp
        // TforSolid.correctBoundaryConditions();
        // TforSolidOld.correctBoundaryConditions();
        // threeKalpha = rheology.threeK()*rho*alphaLinear;
        threeKalpha = (2*mu+3*lambda)*alphaLinear;
        // Info << threeKalpha -
        // threeKalpha.write();
        surfaceScalarField threeKalphaf =
            fvc::interpolate(threeKalpha, "threeKalpha");
        // volScalarField threeKalpha = threeK*rho0*alphaLinear;
        // surfaceScalarField threeKalphaf =
        //     fvc::interpolate(threeKalpha, "threeKalpha");
        // TforSolidOld = T.oldTime();
        // if (mesh.time().value() == runTime.deltaTValue()){
        //   TforSolidOld = T0;
        // }
         dT = T - T.oldTime();;

         if (mesh.time().value() == runTime.deltaTValue()){
           dT = T - T0;
         } else {
           dT = T - T.oldTime();
         }
         // TforSolidOld = T;
        iCorr = 0;

        volVectorField gradThreeKalphaDeltaT =
            fvc::grad(threeKalpha*(dT), "grad(threeKalphaDeltaT)");
        surfaceVectorField threeKalphaDeltaTf =
            mesh.Sf()*threeKalphaf*fvc::interpolate(dT, "deltaT");
        // #       include "calculateCourant.H"
        temp1 = gradThreeKalphaDeltaT;
        DThermal = (sigma - sigma) + I*threeKalpha*(dT);
        epsilonT = (epsilon-epsilon) + I*alphaLinear*(T - T0);
        DepsilonT = (epsilon-epsilon) +I*alphaLinear*(dT);
        DEpsilonP *= 0;
        sigma = 2*mu*(epsilon - epsilonP - epsilonT)
               + lambda*(I*tr(epsilon - epsilonP - epsilonT)) ;
        do
        {
            DU.storePrevIter();
#           include "calculateDivDSigmaExp.H"
// #           include "calculateDivDSigmaNonLinExp.H"

            // Incremental form of the
            // linear momentum conservation
            // ensuring conservation of total momentum
            // fvVectorMatrix DUEqn
            // (
            //     fvm::d2dt2(rho, DU)
            //  ==
            //     fvm::laplacian(2*muf + lambdaf, DU, "laplacian(DDU,DU)")
            //   + divDSigmaExp
            //   + divDSigmaNonLinExp
            // //- fvc::div(2*mu*DEpsilonP, "div(sigma)")
            //   - fvc::div
            //     (
            //         2*muf*(mesh.Sf() & fvc::interpolate(DEpsilonP))
            //     )
            // );

            fvVectorMatrix DUEqn
            (
                rho*fvm::d2dt2(DU)
             ==
            fvm::laplacian((2*muf + lambdaf), DU, "laplacian(DDU,DU)")
              + divDSigmaExp
              - fvc::div(2*muf*(mesh.Sf() & fvc::interpolate(DEpsilonP)) +
                         lambdaf*(mesh.Sf() & fvc::interpolate(tr(DEpsilonP)*I)))
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
            // DULiquid = DU*solidSmooth;
            // gradDU = fvc::grad(DU);
            gradDU = fvc::grad(DU);
            // Increment of Green finite strain tensor
            //
            // correct plasticty term
            DEpsilon = symm(gradDU);
            DEpsilon.correctBoundaryConditions();
            // rheology.update();
// #           include "rheologyUpdate2.H"


            // rheology.correct();
            // Info << "And something goes wrong" << endl;
            // Increment of Green finite strain tensor
            // DEpsilon = symm(gradDU);
            // DSigma = 2*mu*(DEpsilon)
            //        + lambda*(I*tr(DEpsilon)) - DThermal;
           DSigma = 2*mu*(DEpsilon - DEpsilonP)
                  + lambda*(I*tr(DEpsilon - DEpsilonP)) - DThermal;
            DSigma.correctBoundaryConditions();
// #           include "calculateDEpsilonDSigma.H"

#           include "calculateRelativeResidual.H"
            Info << "How stress is changing " << max(sqrt((3.0/2.0)*magSqr(dev(DSigma)))) << endl;
            // Info << "How XX " << max((DSigma.component(tensor::XX))) << endl;
            //
            // Info << "How YY " << max((DSigma.component(tensor::YY))) << endl;
            //
            // Info << "How ZZ " << max((DSigma.component(tensor::ZZ))) << endl;
            //
            Info << "How Plastic " << max(DEpsilonP) << endl;

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
        // if (max(liquidFraction).value() > 0.99){
        // if (!wasAdapted){
        //   if (solverPerf.nIterations() == 0){
        //     if (adaptCounter == 0){
        //       adaptTime = 1;
        //       adaptCounter = 5;
        //     } else if (iCorr < 50) {adaptCounter--;}
        //   }
        // } else {
        //   if (solverPerf.nIterations() != 0){
        //     adaptTime = 1;
        //     badTime = 1;
        //     adaptCounter = 10;
        //     wasAdapted = 0;
        //   } else {
        //     wasAdapted = 0;
        //   }
        // }
        // }
        // Update total quantities
        // U += DULiquid;
        U += DU;
        gradU += gradDU;
        epsilon += DEpsilon;
        epsilonP += DEpsilonP;
        sigma += DSigma;
        Info << max(sigma) << endl;

        fullStress = 2*mu*(epsilon) + lambda*(I*tr(epsilon));
        fullPlastic = 2*mu*(epsilonP) + lambda*I*tr(epsilonP);
        DPlastic = 2*mu*DEpsilonP + lambda*I*tr(DEpsilonP);
        fullThermal = (sigma - sigma) + I*threeKalpha*(T - T0);
        DThermal = (sigma - sigma) + I*threeKalpha*(dT);
        // U = solidSmooth;
        // epsilon *= solidSmooth;
        // epsilonP *= solidSmooth;
        // sigma *= solidSmooth;


        // Update yields stresses
        // rheology.updateYieldStress();
// #        include "updateStress.H"
        // volScalarField  yieldstressstress = rheology.sigmaY();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;





  Info<< "End elastic plastic thermal nano uber cancer two pi power one over exponent calculation\n" << endl;


// ************************************************************************* //
