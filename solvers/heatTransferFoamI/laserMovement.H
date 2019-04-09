dimensionedScalar localTime = mesh.time();

//Read strategy
if (linecounter < laserStrategy.size()){
  point1 = laserStrategy[linecounter]*convertToMetersTemp;
  point2 = laserStrategy[linecounter + 1]*convertToMetersTemp;
  travelLine = (point2 - point1);
  lineLength = sqrt(travelLine[0]*travelLine[0] +
  travelLine[1]*travelLine[1] + travelLine[2]*travelLine[2]);
}

// Minus here is a small bug
dimensionedVector speedVector = -laserSpeed*travelLine/lineLength;
localTime = mesh.time() - laserSumTime;
if (mag(localTime*laserSpeed) > lineLength){
Info << "One more line is done" << endl;
  linecounter = linecounter + 2;
  laserSumTime = laserSumTime + localTime;
  if (linecounter >= laserStrategy.size()){
    timeStop = mesh.time();
  }
}

if (linecounter >= laserStrategy.size())
{
  Info << "Laser is off" << endl;
  laserDistribution *= 0;
} else {
laserDistribution = 2*absorptivity*laserPower*
  gaussian(coordX, (point1[0]) - speedVector[0]*localTime, laserRadius)*
  gaussian(coordY, (point1[1]) - speedVector[1]*localTime, laserRadius)*
  gaussian(coordZ, (point1[2]) - speedVector[2]*localTime, laserRadius);
}
