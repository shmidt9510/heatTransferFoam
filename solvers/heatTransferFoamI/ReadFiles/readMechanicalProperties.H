Info<< "Reading mechanical properties\n" << endl;

    IOdictionary mechanicalProperties
    (
        IOobject
        (
            "mechanicalProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        )
    );

    dimensionedScalar E
    (
        dimensionedScalar(mechanicalProperties.lookup("E"))
    );

    dimensionedScalar nu
    (
        dimensionedScalar(mechanicalProperties.lookup("nu"))
    );

    dimensionedScalar sigmaY
    (
        dimensionedScalar(mechanicalProperties.lookup("sigmaY"))
    );

    dimensionedScalar Ep
    (
        dimensionedScalar(mechanicalProperties.lookup("Ep"))
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
        E/(2*(1 + nu))
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
      E*nu/((1 + nu)*(1 - 2*nu))
    );

    Info << " mu 0 "<< max(mu) << " lambda 0 " << max(lambda) << endl;



    double solidSmoothWidth = readScalar(mechanicalProperties.lookup("solidSmoothWidth"));
    double solidSmoothAmplitude = readScalar(mechanicalProperties.lookup("solidSmoothAmplitude"));

    surfaceScalarField muf = fvc::interpolate(mu, "mu");
    surfaceScalarField lambdaf = fvc::interpolate(lambda, "lambda");
    surfaceScalarField muf0 = muf;
    surfaceScalarField lambdaf0 = lambdaf;
    volScalarField mu0 = mu;
    volScalarField lambda0 = lambda;
    // volScalarField mu;
    // mu =  E/(2*(1 + nu));
    // volScalarField lambda = E*nu/((1 + nu)*(1 - 2*nu));
    // surfaceScalarField muf = fvc::interpolate(mu, "mu");
    // surfaceScalarField lambdaf = fvc::interpolate(lambda, "lambda");
