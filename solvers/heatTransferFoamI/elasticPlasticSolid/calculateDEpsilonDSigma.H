// Increment of Green finite strain tensor
DEpsilon = symm(gradDU);
// DEpsilon = symm(gradDU);
// //
DSigma = 2*mu*(DEpsilon - DEpsilonP)
       + lambda*(I*tr(DEpsilon - DEpsilonP)) - DThermal;


//NonLinTotalLagrangian



// Increment of second Piola-Kirchhoff stress tensor
// DSigma = 2*mu*(DEpsilon - DEpsilonP) + lambda*(I*tr(DEpsilon)) - I*threeKalpha*(dT);
