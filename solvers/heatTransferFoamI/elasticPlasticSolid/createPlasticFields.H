    Info<< "Reading displacement increment field DU\n" << endl;
    volVectorField DU
    (
        IOobject
        (
            "DU",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volTensorField gradDU = fvc::grad(DU);

    Info<< "Creating field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimensionSet(0,1,0,0,0,0,0), vector::zero)
    );

    volSymmTensorField DEpsilon
    (
        IOobject
        (
            "DEpsilon",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    volSymmTensorField epsilonT
    (
        IOobject
        (
            "epsilonT",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    volSymmTensorField DepsilonT
    (
        IOobject
        (
            "DepsilonT",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    volTensorField gradU
    (
        IOobject
        (
            "grad(U)",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedTensor("zero", dimless, tensor::zero)
    );
    volSymmTensorField DSigma
    (
        IOobject
        (
            "DSigma",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
    );

    volSymmTensorField sigma
    (
        IOobject
        (
            "sigma",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
    );

    volSymmTensorField epsilon
    (
        IOobject
        (
            "epsilon",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    volSymmTensorField epsilonP
    (
        IOobject
        (
            "epsilonP",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );


    volVectorField divDSigmaExp
    (
        IOobject
        (
            "divDSigmaExp",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimensionSet(1,-2,-2,0,0,0,0), vector::zero)
    );

    volVectorField divDSigmaNonLinExp
    (
        IOobject
        (
            "divDSigmaNonLinExp",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimensionSet(1,-2,-2,0,0,0,0), vector::zero)
    );
    volScalarField mu_
    (
        IOobject
        (
            "mu_",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        E1/(2.0+2.0*nu1)
    );

    volScalarField lambda_
    (
        IOobject
        (
            "lambda_",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        E1*nu1/((1+nu1)*(1-2*nu1))
    );

    volScalarField mu
    (
        IOobject
        (
            "mu",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        E1
    );

    volScalarField lambda
    (
        IOobject
        (
            "lambda",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        E1
    );

    constitutiveModel rheology(sigma, DU);
    volScalarField rho = rheology.rho();
    mu = mu_;
    lambda = lambda_;
    // volScalarField mu = rheology.mu();
    // volScalarField lambda = rheology.lambda();
    surfaceScalarField muf = fvc::interpolate(mu, "mu");
    surfaceScalarField lambdaf = fvc::interpolate(lambda, "lambda");
    surfaceScalarField muf_ = fvc::interpolate(mu_, "mu_");
    surfaceScalarField lambdaf_ = fvc::interpolate(lambda_, "lambda_");

    surfaceVectorField n = mesh.Sf()/mesh.magSf();

   // plastic strain increment
   // volSymmTensorField DEpsilonP = rheology.DEpsilonP();
   // const volSymmTensorField& DEpsilonP = rheology.DEpsilonP();
   volSymmTensorField DEpsilonP
   (
    IOobject
    (
     "DEpsilonP",
     runTime.timeName(),
     mesh,
     IOobject::NO_READ,
     IOobject::NO_WRITE
     ),
    mesh,
    dimensionedSymmTensor("0", dimless, symmTensor::zero)
  );

    // for aitken relaxation
    volVectorField aitkenDelta
    (
        IOobject
        (
            "aitkenDelta",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimLength, vector::zero)
   );

   scalar aitkenInitialRes = 1.0;
   scalar aitkenTheta = 0.1;


   volScalarField ytemp = rheology.sigmaY();


   volScalarField sigmaY1
   (
       IOobject
       (
           "sigmaY1",
           runTime.timeName(),
           mesh,
           IOobject::NO_READ,
           IOobject::AUTO_WRITE
       ),
       ytemp
   );

   volSymmTensorField sigma_
   (
       IOobject
       (
           "sigma_",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::NO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );

   volSymmTensorField epsilon_
   (
       IOobject
       (
           "epsilon_",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::NO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimless, symmTensor::zero)
   );

   volSymmTensorField fullPlastic
   (
       IOobject
       (
           "fullPlastic",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::AUTO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );

   volSymmTensorField fullThermal
   (
       IOobject
       (
           "fullThermal",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::AUTO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );

   volSymmTensorField fullStress
   (
       IOobject
       (
           "fullStress",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::NO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );

   volSymmTensorField DPlastic
   (
       IOobject
       (
           "DPlastic",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::NO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );

   volSymmTensorField DThermal
   (
       IOobject
       (
           "DThermal",
           runTime.timeName(),
           mesh,
           IOobject::READ_IF_PRESENT,
           IOobject::NO_WRITE
       ),
       mesh,
       dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
   );
   //***************************************//

   // scalar LoopTol_ = 1e-8;
   // label MaxNewtonIter_ = 1000;

   volScalarField sigmaY_
   (
    IOobject
    (
     "sigmaY",
     runTime.timeName(),
     mesh,
     IOobject::READ_IF_PRESENT,
     IOobject::AUTO_WRITE
     ),
    sigmaY1
  );

   volScalarField DSigmaY_
   (
    IOobject
    (
     "DSigmaY_",
     runTime.timeName(),
     mesh,
     IOobject::NO_READ,
     IOobject::NO_WRITE
     ),
    mesh,
    dimensionedScalar("0", dimPressure, 0.0)
  );
   volSymmTensorField DEpsilonP_
   (
    IOobject
    (
     "DEpsilonP_",
     runTime.timeName(),
     mesh,
     IOobject::READ_IF_PRESENT,
     IOobject::NO_WRITE
     ),
    mesh,
    dimensionedSymmTensor("0", dimless, symmTensor::zero)
  );
   volScalarField DEpsilonPEq_
   (
    IOobject
    (
     "DEpsilonPEq_",
     runTime.timeName(),
     mesh,
     IOobject::READ_IF_PRESENT,
     IOobject::AUTO_WRITE
     ),
    mesh,
    dimensionedScalar("0", dimless, 0.0)
  );
   volScalarField activeYield_
   (
    IOobject
    (
     "activeYield_",
     runTime.timeName(),
     mesh,
     IOobject::READ_IF_PRESENT,
     IOobject::AUTO_WRITE
     ),
    mesh,
    dimensionedScalar("0", dimless, 0)
  );
  volSymmTensorField  plasticN_
   (
    IOobject
    (
     "plasticN_",
     runTime.timeName(),
     mesh,
     IOobject::NO_READ,
     IOobject::NO_WRITE
     ),
    mesh,
    dimensionedSymmTensor("zero", dimless, symmTensor::zero)
  );

  volVectorField DULiquid
  (
      IOobject
      (
          "DULiquid",
          runTime.timeName(),
          mesh,
          IOobject::NO_READ,
          IOobject::AUTO_WRITE
      ),
      mesh,
      dimensionedVector("zero", dimensionSet(0,1,0,0,0,0,0), vector::zero)
  );

   // volTensorField SigmaTensor
   // (
   //    IOobject
   //    (
   //        "Srate",
   //        runTime.timeName(),
   //        mesh,
   //        IOobject::NO_READ,
   //        IOobject::NO_WRITE
   //    ),
   //    mesh
   // );

   // volTensorField Srate
   // (
   //    IOobject
   //    (
   //       "Srate",
   //       runTime.timeName(),
   //       mesh,
   //       IOobject::NO_READ,
   //       IOobject::AUTO_WRITE
   //     ),
   //     mesh
   //  );
