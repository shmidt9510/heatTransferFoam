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
    volVectorField Udisp
    (
        IOobject
        (
            "Udisp",
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

    constitutiveModel rheology(sigma, DU);

    volScalarField rho = rheology.rho();
    volScalarField mu = rheology.mu();
    volScalarField lambda = rheology.lambda();
    surfaceScalarField muf = fvc::interpolate(mu, "mu");//tanhSmooth(liquidFraction, 0.5, 0.5)

    surfaceScalarField lambdaf = fvc::interpolate(lambda, "lambda");//tanhSmooth(liquidFraction, 0.5, 0.5)


    surfaceVectorField n = mesh.Sf()/mesh.magSf();

   // plastic strain increment
   const volSymmTensorField& DEpsilonP = rheology.DEpsilonP();

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