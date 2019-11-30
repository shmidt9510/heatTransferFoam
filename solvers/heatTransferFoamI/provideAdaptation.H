// Input something for parameterChoice
// Output new power
convergedAdaptation = false;
prevAdaptPar = adaptPar;
if (parameterChoice.value() == 0){
  adaptPar = maxTemperature.value() - borderValue.value();
} else if (parameterChoice.value() == 1) {
  adaptPar = liquidFractionVolume.value() - borderValue.value();
} else if (parameterChoice.value() == 2) {
  adaptPar = liquidFractionDepth.value() - borderValue.value();
} else if (parameterChoice.value() == 3) {
  adaptPar = integratedTemperature.value() - borderValue.value();
}
Info << "Liquid fraction depth " << liquidFractionDepth << endl;
//******Check parameter and decrease power********//
if ((mag(adaptPar) < borderValue.value()*adaptationRegion.value()) || ((laserPower.value() == initialLaserPower.value())
  && (adaptationCounter > 1))) {
  convergedAdaptation = true;
  Info << "Magic happens and it converged, new value is == "<< laserPower.value() << endl;
}

prevLaserPower.value() = laserPower.value();
if (!convergedAdaptation){ if (adaptPar > 0){
    laserPower.value() *= (scalar(1 - decreaseValue));
    Info << "Decrease power!! Your new power is " << laserPower.value() << " :)" << endl;
}  else {
      laserPower.value() *= (scalar(1 + decreaseValue));
      Info << "Increase power!! Your new power is " << laserPower.value() << " :8" << endl;

}}
if ((sign(adaptPar) != sign(prevAdaptPar)) && (adaptationCounter > 1) && (!convergedAdaptation)){
  Info << "Integrating over three infinite dimensional Hilbert-Kalabi space" << endl;
  laserPower.value() = (mag((prevLaserPower - laserPower)*
    ((- adaptPar)/(prevAdaptPar - adaptPar) + laserPower/(prevLaserPower - laserPower)))).value();
  Info<< "Hooray, we have linear interpolation and stuff, new laser power == " << laserPower.value() << endl;
}
if (laserPower > initialLaserPower){
  laserPower.value() = initialLaserPower.value();
  Info << "Laser power is soooo huge so I stop this celebration of life, lp == " << laserPower << endl;
  }
if (!convergedAdaptation){
  he = he.prevIter();
Info << "Time to step to the timestep back" << endl;
}
Info << "Some adaptation is provided, new laser power is == " << laserPower << endl;
