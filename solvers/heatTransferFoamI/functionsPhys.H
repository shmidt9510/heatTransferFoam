volScalarField FourParameterModel (const volScalarField& phi, const volScalarField& T,
dimensionedScalar A_sol, dimensionedScalar A_liq,
dimensionedScalar dA_sol, dimensionedScalar dA_liq)
{
return (A_sol+dA_sol*T)+phi*((A_liq-A_sol)+(dA_liq-dA_sol)*T);
}

volScalarField enthalpyCalc (const volScalarField& T, const volScalarField& phi,
dimensionedScalar Cp_sol, dimensionedScalar Cp_liq,
dimensionedScalar dCp_sol, dimensionedScalar dCp_liq,
dimensionedScalar T_solidus, dimensionedScalar T_liquidus,
dimensionedScalar enthalpyFusion)
{
  return ((0.5*T*(2*Cp_sol+dCp_sol*T))*(scalar(1)-phi)
  + phi*(0.5*(T-T_liquidus)*(2*Cp_liq+dCp_liq*(T)) + enthalpyFusion + 0.5*T_solidus*(2*Cp_sol+dCp_sol*T_solidus)));
}

volScalarField temperatureCalc (const volScalarField& he, const volScalarField& phi,
dimensionedScalar Cp_sol, dimensionedScalar Cp_liq,
dimensionedScalar dCp_sol, dimensionedScalar dCp_liq,
dimensionedScalar T_solidus, dimensionedScalar T_liquidus,
dimensionedScalar enthalpyFusion)
{
  volScalarField c (phi*(enthalpyFusion + 0.5*T_solidus*(2*Cp_sol + dCp_sol*T_solidus)
                                 - T_liquidus*Cp_liq) - he);
  volScalarField b (phi*(Cp_liq - (T_liquidus*dCp_liq)/2) - Cp_sol*(phi - 1));
  volScalarField a (((dCp_liq*phi)/2 - (dCp_sol*(phi - 1))/2));
  volScalarField D (b*b - 4*a*c);
  volScalarField ans ((-b+Foam::sqrt(D))/(2*a));
  return ans;
}
