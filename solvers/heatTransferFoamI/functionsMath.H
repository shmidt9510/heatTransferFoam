volScalarField gaussian (const volScalarField& x, dimensionedScalar x0, dimensionedScalar sigma)
{
return (exp(-2*Foam::pow((x - x0)/(sigma),2.0))/(Foam::pow(3.1415f/2, 0.5f)*sigma));
}

volScalarField tanhSmooth (const volScalarField& x, const dimensionedScalar& shift, const dimensionedScalar& width)
{
return (0.5*tanh((x-shift)/width)+0.5);
}

dimensionedScalar tanhSmooth (const dimensionedScalar& x, const dimensionedScalar& shift, const dimensionedScalar& width)
{
return (0.5*tanh((x-shift)/width)+0.5);
}

double calculatePower(double t, double a, double b, double c, double x1, double x0)
{
  if (x1 > x0){
    return 100;
  }
  if (t < x0){
    return 1;
  } else {
    return (a* Foam::pow(((t - x1)),b) + c);
  }
}
