    Info << "Reading field T\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volScalarField he
    (
        IOobject
        (
            "he",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
        // dimensionSet(0, 2, -2, 0, 0, 0, 0)
    );

    volScalarField heStar
    (
        IOobject
      (
        "heStar",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 2, -2, 0, 0, 0, 0)
    );

    volScalarField laserDistribution
    (
        IOobject
      (
        "laserDistribution",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(1, -1, -3, 0, 0, 0, 0) //1 -1 -3
    );

    volScalarField liquidFraction
    (
        IOobject
      (
        "liquidFraction",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volScalarField porosity
    (
        IOobject
      (
        "porosity",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volScalarField porosityPrev
    (
        IOobject
      (
        "porosity",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volScalarField fusionTerm
    (
        IOobject
      (
        "fusionTerm",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(1, -1, -3, 0, 0, 0, 0)
    );

    volScalarField diffusivity
    (
        IOobject
      (
        "diffusivity",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(1, -1, -1, 0, 0, 0, 0)
    );

    // volSymmTensorField epsilonP
    // (
    //     IOobject
    //     (
    //         "epsilonP",
    //         runTime.timeName(),
    //         mesh,
    //         IOobject::READ_IF_PRESENT,
    //         IOobject::AUTO_WRITE
    //     ),
    //     mesh,
    //     dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    // );
    //
    //
    // volVectorField divDSigmaExp
    // (
    //     IOobject
    //     (
    //         "divDSigmaExp",
    //         runTime.timeName(),
    //         mesh,
    //         IOobject::NO_READ,
    //         IOobject::NO_WRITE
    //     ),
    //     mesh,
    //     dimensionedVector("zero", dimensionSet(1,-2,-2,0,0,0,0), vector::zero)
    // );

// #   include "createPhi.H"
//
//     label pRefCell = 0;
//     scalar pRefValue = 0.0;
//     setRefCell(p, piso.dict(), pRefCell, pRefValue);
//     mesh.schemesDict().setFluxRequired(p.name());
//
//     Info<< "Reading/calculating field rho\n" << endl;
//     volScalarField rho
//     (
//         IOobject
//         (
//             "rho",
//             runTime.timeName(),
//             mesh,
//             IOobject::READ_IF_PRESENT,
//             IOobject::AUTO_WRITE
//         ),
//         rho0*(scalar(1) - beta*(T - T0))
//     );
