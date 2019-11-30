    Info<< "Reading displacement increment field DU\n" << endl;


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
    
    volTensorField DEpsilon
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
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
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
        dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
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
        dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
    );

    volTensorField epsilon
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
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    surfaceVectorField n = mesh.Sf()/mesh.magSf();

   // plastic strain increment
   // volSymmTensorField DEpsilonP = rheology.DEpsilonP();
   // const volSymmTensorField& DEpsilonP = rheology.DEpsilonP();
   volTensorField DEpsilonP
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
    dimensionedSymmTensor("zero", dimless, symmTensor::zero)
  );
