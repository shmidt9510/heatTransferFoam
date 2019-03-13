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
//
//
//     ///
//     dimensionedScalar initialPorosity
//     (
//         dimensionedScalar(thermalProperties.lookup("initialPorosity"))
//     );
//
//     dimensionedScalar absorptivity
//     (
//         dimensionedScalar(thermalProperties.lookup("absorptivity"))
//     );
// ////
//
//
//     dimensionedScalar laserPower
//     (
//         dimensionedScalar(thermalProperties.lookup("laserPower"))
//     );
//
//     dimensionedScalar laserSpeed
//     (
//         dimensionedScalar(thermalProperties.lookup("laserSpeed"))
//     );
//
//     dimensionedScalar laserRadius
//     (
//         dimensionedScalar(thermalProperties.lookup("laserRadius"))
//     );
//
//     dimensionedScalar coordStartX
//     (
//         dimensionedScalar(thermalProperties.lookup("coordStartX"))
//     );
//
//     dimensionedScalar coordStartY
//     (
//         dimensionedScalar(thermalProperties.lookup("coordStartY"))
//     );
//
//     dimensionedScalar coordStartZ
//     (
//         dimensionedScalar(thermalProperties.lookup("coordStartZ"))
//     );
