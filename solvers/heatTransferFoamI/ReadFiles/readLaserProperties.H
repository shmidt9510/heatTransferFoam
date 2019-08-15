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

    dimensionedVector coordStart
    (
        dimensionedVector(laserProperties.lookup("coordStart"))
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
    dimensionedVector point1("point1",dimLength,vector(0,0,0));
    dimensionedVector point2("point2",dimLength,vector(0,0,0));
    dimensionedVector travelLine = (point2 - point1);
    dimensionedScalar lineLength = sqrt(travelLine[0]*travelLine[0] +
    travelLine[1]*travelLine[1] + travelLine[2]*travelLine[2]);

    dimensionedScalar turnOnWidth
    (
        dimensionedScalar(laserProperties.lookup("turnOnWidth"))
    );

    dimensionedScalar turnOnShift
    (
        dimensionedScalar(laserProperties.lookup("turnOnShift"))
    );

    dimensionedScalar coolingTime
    (
        dimensionedScalar(laserProperties.lookup("coolingTime"))
    );

    dimensionedScalar E1
    (
        dimensionedScalar(laserProperties.lookup("E1"))
    );

    dimensionedScalar nu1
    (
        dimensionedScalar(laserProperties.lookup("nu1"))
    );

    dimensionedScalar hatchSpacing
    (
        dimensionedScalar(laserProperties.lookup("hatchSpacing"))
    );

    dimensionedScalar trackLength
    (
        dimensionedScalar(laserProperties.lookup("trackLength"))
    );

    dimensionedScalar lineAmountDim
    (
        dimensionedScalar(laserProperties.lookup("lineAmount"))
    );

    dimensionedScalar strategyChoiceDim
    (
        dimensionedScalar(laserProperties.lookup("strategyChoice"))
    );
