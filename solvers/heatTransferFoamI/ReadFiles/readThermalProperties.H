    Info<< "Reading thermal properties\n" << endl;

    IOdictionary thermalProperties
    (
        IOobject
        (
            "thermalProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        )
    );

    dimensionedScalar rho0
    (
        thermalProperties.lookup("rho0")
    );

    dimensionedScalar T0
    (
        thermalProperties.lookup("T0")
    );

    dimensionedScalar k_sol
    (
        dimensionedScalar(thermalProperties.lookup("k_sol"))
    );

    dimensionedScalar dk_sol
    (
        dimensionedScalar(thermalProperties.lookup("dk_sol"))
    );
    dimensionedScalar k_liq
    (
        dimensionedScalar(thermalProperties.lookup("k_liq"))
    );

    dimensionedScalar dk_liq
    (
        dimensionedScalar(thermalProperties.lookup("dk_liq"))
    );

    dimensionedScalar Cp_sol
    (
        dimensionedScalar(thermalProperties.lookup("Cp_sol"))
    );

    dimensionedScalar dCp_sol
    (
        dimensionedScalar(thermalProperties.lookup("dCp_sol"))
    );

    dimensionedScalar Cp_liq
    (
        dimensionedScalar(thermalProperties.lookup("Cp_liq"))
    );

    dimensionedScalar dCp_liq
    (
        dimensionedScalar(thermalProperties.lookup("dCp_liq"))
    );

    dimensionedScalar T_solidus
    (
        dimensionedScalar(thermalProperties.lookup("T_solidus"))
    );

    dimensionedScalar T_liquidus
    (
        dimensionedScalar(thermalProperties.lookup("T_liquidus"))
    );

    dimensionedScalar enthalpyFusion
    (
        dimensionedScalar(thermalProperties.lookup("enthalpyFusion"))
    );

    dimensionedScalar alphaLinear
    (
        dimensionedScalar(thermalProperties.lookup("alphaLinear"))
    );

    dimensionedScalar tempVar1
    (
        dimensionedScalar(thermalProperties.lookup("tempVar1"))
    );

    dimensionedScalar tempVar2
    (
        dimensionedScalar(thermalProperties.lookup("tempVar2"))
    );
