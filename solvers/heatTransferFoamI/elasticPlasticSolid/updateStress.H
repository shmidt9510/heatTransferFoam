
  Info << nl << "Updating the yield stress" << endl;
  sigmaY_ += DSigmaY_;
  sigmaY_.correctBoundaryConditions();

  // count cells actively yielding
  int numCellsYielding = 0;
  forAll(activeYield_.internalField(), celli)
    {
      if (DEpsilonPEq_.internalField()[celli] > SMALL)
    {
      activeYield_.internalField()[celli] = 1.0;
      numCellsYielding++;
    }
      else
    {
      activeYield_.internalField()[celli] = 0.0;
    }
    }
  reduce(numCellsYielding, sumOp<int>());
  forAll(activeYield_.boundaryField(), patchi)
    {
      if (!activeYield_.boundaryField()[patchi].coupled())
    {
      forAll(activeYield_.boundaryField()[patchi], facei)
        {
          if (DEpsilonPEq_.boundaryField()[patchi][facei] > SMALL)
        {
          activeYield_.boundaryField()[patchi][facei] = 1.0;
        }
          else
        {
          activeYield_.boundaryField()[patchi][facei] = 0.0;
        }
        }
    }
    }
  Info << "\t" << numCellsYielding << " cells are actively yielding"
       << nl << endl;


  Info << "\tMax DEpsilonPEq is " << gMax(DEpsilonPEq_) << nl << endl;
