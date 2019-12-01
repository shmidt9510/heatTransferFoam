    Info<< "Reading displacement increment field DU\n" << endl;


    Info<< "Creating field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volVectorField Uold
    (
        IOobject
        (
            "Uold",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0,1,0,0,0,0,0)
    );

    volVectorField DU
    (
        IOobject
        (
            "DU",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0,1,0,0,0,0,0)
    );

    volTensorField gradU = fvc::grad(U);

    volTensorField gradDU = fvc::grad(DU);

    volTensorField epsilonT
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
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volTensorField DEpsilon
    (
        IOobject
        (
            "DEpsilon",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volTensorField DEpsilonT
    (
        IOobject
        (
            "DEpsilonT",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volTensorField DSigma
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
        dimForce/dimArea
    );

    volTensorField sigma
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
        dimForce/dimArea
    );

    volTensorField sigmaOld
    (
        IOobject
        (
            "sigmaOld",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimForce/dimArea
    );

    volScalarField sigmaYVol
    (
        IOobject
        (
            "sigmaYVol",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimForce/dimArea
    );
    sigmaYVol = sigmaY;

    volTensorField epsilon
    (
        IOobject
        (
            "epsilon",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volTensorField epsilonP
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
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volTensorField epsilonPold
    (
        IOobject
        (
            "epsilonPold",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    surfaceVectorField n = mesh.Sf()/mesh.magSf();

    dimensionedScalar sinkTerm("sinkTerm",dimensionSet(1, -3, -2, 0, 0, 0, 0),1000);


   // plastic strain increment
   // volTensorField DEpsilonP = rheology.DEpsilonP();
   // const volTensorField& DEpsilonP = rheology.DEpsilonP();
   volTensorField DEpsilonP
   (
    IOobject
    (
     "DEpsilonP",
     runTime.timeName(),
     mesh,
     IOobject::READ_IF_PRESENT,
     IOobject::NO_WRITE
     ),
    mesh,
    dimensionSet(0, 0, 0, 0, 0, 0, 0)
  );
