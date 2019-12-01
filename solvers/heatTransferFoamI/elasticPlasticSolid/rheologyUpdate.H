DU = U - Uold;
gradDU = fvc::grad(DU);
DEpsilon = 0.5*(gradDU + gradDU.T());
//Full sigma with termal plastic and elastic part
sigma += 2.0*mu*gradDU + lambda*I*tr(gradDU);

if (mechanicalTest == 1){
  Info << "max DU " << max(DU) << endl;
  Info << "Max sigma" << max(sigma) << endl;
}
volScalarField sqrtJ2 = sqrt((3.0/2.0)*magSqr(dev(sigma)));

volScalarField fac = sqrtJ2/sigmaYVol;
//Still no boundary after
fac.correctBoundaryConditions();
forAll(fac, celli)
  {
  if (fac[celli] > 1.0) //Plasticity occurs
    {
      // New sigma with direction. Don't sure if it must be here.
      sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
      tensor dsigma = sigma[celli] - sigmaOld[celli];
      tensor DEpsE = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
        + dev(dsigma)/(2.0*mu[celli]);
      DEpsilonP[celli] = DEpsilon[celli] - DEpsE - DEpsilonT[celli];
    }
  else // only elasticity
  {
    DEpsilonP[celli] *= 0;
  }
}

if (mechanicalTest == 1){
  fac.write();
  sqrtJ2.write();
  Info << "max sqrtJ2 " << max(sqrtJ2) << endl;
  Info << "Is there any plasticity " <<  max(fac) << endl;
}


// TODO change boundary Field
// forAll(mesh.boundary(), patchID)
// {
//     forAll (mesh.boundary()[patchID],facei)
//     {
//     if (fac.boundaryField()[patchID][facei] > 1.0) //Plasticity occurs
//       {
//         // sigma[celli] = 1.0/3.0*I*tr(sigma[celli]) + dev(sigma[celli])/fac[celli];
//         // tensor dsigma = sigma[celli] - sigma_old[celli];
//         // tensor deps_e = 1.0/3.0*I*tr(dsigma)/(3.0*lambda[celli]+2.0*mu[celli])
//         // + dev(dsigma)/(2.0*mu[celli]);
//         // DEpsilonP.boundaryFieldRef()[patchID][facei] = DEpsilon.boundaryFieldRef()[patchID][facei] - deps_e - DEpsilonT[celli];
//       }
//     else // only elasticity
//     {
//       DEpsilonP.boundaryFieldRef()[patchID][facei] = 0.0;
//     }
//   }
// }
//
// DEpsilonP.correctBoundaryConditions();
epsilonP += DEpsilonP;
Info << "How Plastic " << max(DEpsilonP) << endl;
