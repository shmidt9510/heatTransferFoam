Info<< "Reading system controls\n" << endl;

IOdictionary systemProperties
(
    IOobject
    (
        "systemProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    )
);

dimensionedScalar turnOnDebug
(
    systemProperties.lookup("turnOnDebug")
);

dimensionedScalar thermalOn
(
    systemProperties.lookup("thermalOn")
);

dimensionedScalar mechanicalOn
(
    systemProperties.lookup("mechanicalOn")
);

dimensionedScalar adaptiveOn
(
    systemProperties.lookup("adaptiveOn")
);

dimensionedScalar youngDependence
(
    systemProperties.lookup("youngDependence")
);

dimensionedScalar smootherAirFactor
(
    systemProperties.lookup("smootherAirFactor")
);

dimensionedScalar smootherPorosityFactor
(
    systemProperties.lookup("smootherPorosityFactor")
);

dimensionedScalar borderValue
(
    systemProperties.lookup("borderValue")
);
dimensionedScalar decreaseValueDim
(
    systemProperties.lookup("decreaseValueDim")
);

dimensionedScalar parameterChoice
(
    systemProperties.lookup("parameterChoice")
);
dimensionedScalar adaptationRegion
(
    systemProperties.lookup("adaptationRegion")
);
dimensionedScalar onlySingleTrack
(
    systemProperties.lookup("onlySingleTrack")
);

dimensionedScalar temporal1
(
    systemProperties.lookup("temporal1")
);

dimensionedScalar temporal2
(
    systemProperties.lookup("temporal2")
);
dimensionedScalar temporal3
(
    systemProperties.lookup("temporal3")
);

double mechanicalTest = readScalar(systemProperties.lookup("mechanicalTest"));
