    Info << "Reading field T\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
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
            IOobject::AUTO_WRITE
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

    volScalarField TforSolid
    (
        IOobject
      (
        "TforSolid",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 1, 0, 0, 0)
    );

    volScalarField TforSolidOld
    (
        IOobject
      (
        "TforSolidOld",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 1, 0, 0, 0)
    );

    volScalarField solidSmooth
    (
        IOobject
      (
        "solidSmooth",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volScalarField tempSmooth
    (
        IOobject
      (
        "tempSmooth",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volVectorField temp1
    (
        IOobject
      (
        "temp1",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimensionSet(1,-2,-2,0,0,0,0), vector::zero)
    );
    volScalarField dT
    (
        IOobject
      (
        "dT",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 1, 0, 0, 0)
    );


    volScalarField airPart
    (
        IOobject
      (
        "airPart",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, 0, 0, 0, 0)
    );

    volScalarField threeKalpha
    (
        IOobject
      (
        "threeKalpha",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(1, -1, -2, -1, 0, 0, 0)
    );

    volScalarField alphaLinearForLib
    (
        IOobject
      (
        "alphaLinearForLib",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionSet(0, 0, 0, -1, 0, 0, 0)
    );
    alphaLinearForLib = alphaLinear;


      volScalarField beta_
      (
       IOobject
       (
        "beta_",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
        ),
       mesh,
       dimensionedScalar("0", dimless, 0)
     );


     volScalarField coordX
     (
         IOobject
         (
             "coordX",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionSet(0, 1, 0, 0, 0, 0, 0)
     );

     volScalarField coordY
     (
         IOobject
         (
             "coordY",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionSet(0, 1, 0, 0, 0, 0, 0)
     );

     volScalarField coordZ
     (
         IOobject
         (
             "coordZ",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionSet(0, 1, 0, 0, 0, 0, 0)
     );

     volScalarField trackHistory
     (
         IOobject
         (
             "trackHistory",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::AUTO_WRITE
         ),
         mesh,
         dimensionSet(0, 0, 0, 0, 0, 0, 0)
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
