IOdictionary powerStrategy1
(
    IOobject
    (
        "powerStrategy1",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

List<scalar> powerStrategy(
        List<scalar> (powerStrategy1.lookup("powerStrategy"))
);
