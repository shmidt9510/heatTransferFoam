    Info<< "Reading powder properties\n" << endl;

    IOdictionary powderProperties
    (
        IOobject
        (
            "powderProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        )
    );


    dimensionedScalar initialPorosity
    (
        dimensionedScalar(powderProperties.lookup("initialPorosity"))
    );

    dimensionedScalar absorptivity
    (
        dimensionedScalar(powderProperties.lookup("absorptivity"))
    );

    dimensionedScalar powderDepth
    (
        dimensionedScalar(powderProperties.lookup("powderDepth"))
    );
