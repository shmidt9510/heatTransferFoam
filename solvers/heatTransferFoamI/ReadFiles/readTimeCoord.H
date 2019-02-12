
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
