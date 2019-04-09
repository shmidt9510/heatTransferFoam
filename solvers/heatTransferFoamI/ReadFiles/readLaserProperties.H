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

    dimensionedScalar convertToMetersTemp
    (
        dimensionedScalar(laserProperties.lookup("convertToMetersTemp"))
    );

    List<vector> laserStrategy(
            List<vector>(laserProperties.lookup("laserStrategy"))
    );
    int linecounter = 0;
    dimensionedScalar laserSumTime = mesh.time()*0;
    dimensionedScalar localTime = mesh.time()*0;
    dimensionedVector point1 = laserStrategy[0]*convertToMetersTemp;
    dimensionedVector point2 = laserStrategy[1]*convertToMetersTemp;
    dimensionedVector travelLine = (point2 - point1);
    dimensionedScalar lineLength = sqrt(travelLine[0]*travelLine[0] +
    travelLine[1]*travelLine[1] + travelLine[2]*travelLine[2]);
