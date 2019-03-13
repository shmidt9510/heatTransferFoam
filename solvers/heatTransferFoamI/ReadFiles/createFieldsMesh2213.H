// uniformDimensionedVectorField g
uniformDimensionedVectorField g
(
    IOobject
    (
        "g",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

volScalarField pd
(
    IOobject
    (
        "pd",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

surfaceScalarField phi
(
    IOobject
    (
        "phi",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    linearInterpolate(U) & mesh.Sf()
);


wordList pcorrTypes
(
    pd.boundaryField().size(),
    zeroGradientFvPatchScalarField::typeName
);

for (label i = 0; i < pd.boundaryField().size(); i++)
{
    if (pd.boundaryField()[i].fixesValue())
    {
        pcorrTypes[i] = fixedValueFvPatchScalarField::typeName;
    }
}


volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    pd + rho0*(g & mesh.C())
);


label pdRefCell = 0;
scalar pdRefValue = 0.0;
setRefCell(pd, pimple.dict(), pdRefCell, pdRefValue);
mesh.schemesDict().setFluxRequired(pd.name());

scalar pRefValue = 0.0;

if (pd.needReference())
{
    pRefValue = readScalar(pimple.dict().lookup("pRefValue"));

    p += dimensionedScalar
    (
        "p",
        p.dimensions(),
        pRefValue - getRefCellValue(p, pdRefCell)
    );
}
