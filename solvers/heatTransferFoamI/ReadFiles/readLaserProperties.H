    Info<< "Reading laser properties\n" << endl;

    IOdictionary laserProperties
    (
        IOobject
        (
            "laserProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        )
    );

    dimensionedScalar laserPower
    (
        dimensionedScalar(laserProperties.lookup("laserPower"))
    );

    dimensionedScalar laserSpeed
    (
        dimensionedScalar(laserProperties.lookup("laserSpeed"))
    );

    dimensionedScalar laserRadius
    (
        dimensionedScalar(laserProperties.lookup("laserRadius"))
    );

    dimensionedScalar coordStartX
    (
        dimensionedScalar(laserProperties.lookup("coordStartX"))
    );

    dimensionedScalar coordStartY
    (
        dimensionedScalar(laserProperties.lookup("coordStartY"))
    );

    dimensionedScalar coordStartZ
    (
        dimensionedScalar(laserProperties.lookup("coordStartZ"))
    );

    dimensionedScalar timeStop
    (
        dimensionedScalar(laserProperties.lookup("timeStop"))
    );
