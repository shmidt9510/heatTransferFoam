gradDU = fvc::grad(DU);
DEpsilon = 0.5*(gradDU + gradDU.T());
sigma += 2.0*mu*DEpsilon + lambda*I*tr(DEpsilon);
if (mechanicalTest == 1){
  Info << "max DU " << max(DU) << endl;
  Info << "Max sigma" << max(sigma) << endl;
}
volScalarField sqrtJ2 = sqrt((1.0/2.0)*magSqr(dev(sigma)));

volScalarField fac = sqrtJ2/sigmaYVol;
fac.correctBoundaryConditions();
if (mechanicalTest == 1){
  Info << "max sqrtJ2 " << max(sqrtJ2) << endl;
  Info << "Is there any plasticity " <<  max(fac) << endl;
}
forAll(fac, celli)
  {
  if (fac[celli] > 1.0) //Plasticity occurs
    {
      sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
      tensor dsigma = sigma[celli] - sigma_old[celli];
      tensor deps_e = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
      + dev(dsigma)/(2.0*mu[celli]);
      DEpsilonP[celli] = DEpsilon[celli] - deps_e - DEpsilonT[celli];
    }
  else // only elasticity
  {
    DEpsilonP[celli] *= 0;
  }
}

forAll(mesh.boundary(), patchID)
{
    forAll (mesh.boundary()[patchID],facei)
    {
    if (fac.boundaryField()[patchID][facei] > 1.0) //Plasticity occurs
      {
        // sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
        // tensor dsigma = sigma[celli] - sigma_old[celli];
        // tensor deps_e = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
        // + dev(dsigma)/(2.0*mu[celli]);
        // DEpsilonP[celli] = DEpsilon[celli] - deps_e - DEpsilonT[celli];
      }
    else // only elasticity
    {
      DEpsilonP.boundaryField()[patchID][facei] = 0.0;
    }
  }
}
