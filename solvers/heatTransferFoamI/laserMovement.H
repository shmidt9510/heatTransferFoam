dimensionedScalar localTime = mesh.time();
//Read strategy
if (strategyChoice == 0){
if (linecounter < laserStrategy.size()){
  Info << "Strategy choice first" << endl;
  point1 = laserStrategy[linecounter]*convertToMetersTemp;
  point2 = laserStrategy[linecounter + 1]*convertToMetersTemp;
}
} else if (strategyChoice == 1){
  Info << "Second strategy choice" << endl;
  // point11.replace(0, coordStart[2]);//+hatchSpacing*linecounter/2*v2 + LayerNumber*powderDepth*v3;
  // point21 = coordStart;//+hatchSpacing*linecounter/2*v2 + LayerNumber*powderDepth*v3 + lineLength*v1;
  // dimensionedScalar point1x = coordStart[0] + trackLength*((linecounter/2)%2 - lineAmount*LayerNumber);
  // dimensionedScalar point2x = coordStart[0] + trackLength*((linecounter/2+1)%2 - lineAmount*LayerNumber);
  // dimensionedScalar point1y = coordStart[1] + hatchSpacing*(linecounter - lineAmount*LayerNumber)/2;
  // dimensionedScalar point1z = coordStart[2] + LayerNumber*powderDepth;
  // dimensionedScalar point2y = coordStart[1] + hatchSpacing*(linecounter - lineAmount*LayerNumber)/2;
  // dimensionedScalar point2z = coordStart[2] + LayerNumber*powderDepth;
  // dimensionedVector vector1("v1",dimLength,vector(point1x.value(),point1y.value(),point1z.value()));
  // dimensionedVector vector2("v2",dimLength,vector(point2x.value(),point2y.value(),point2z.value()));
  // point1 = vector1;
  // point2 = vector2;
   point1.replace(0, coordStart[0] + trackLength*((linecounter/2 - lineAmount*LayerNumber)%2));
   point2.replace(0, coordStart[0] + trackLength*((linecounter/2 + 1 - lineAmount*LayerNumber)%2));
   point1.replace(1, coordStart[1] + hatchSpacing*(linecounter - lineAmount*LayerNumber)/2);
   point2.replace(1, coordStart[1] + hatchSpacing*(linecounter - lineAmount*LayerNumber)/2);
   point1.replace(2, coordStart[2] - LayerNumber*powderDepth);
   point2.replace(2, coordStart[2] - LayerNumber*powderDepth);
}
if (turnOnDebug.value() == 1){
  Info << "linecounter " << linecounter << endl;
  Info << "coordStart " << coordStart << endl;
  Info << "point1 = " << point1 << endl;
  Info << "point2 = " << point2 << endl;
  Info << "LayerNumber = " << LayerNumber << endl;
}
travelLine = (point2 - point1);
lineLength = sqrt(travelLine[0]*travelLine[0] + travelLine[1]*travelLine[1] + travelLine[2]*travelLine[2]);

dimensionedVector speedVector = laserSpeed*travelLine/lineLength;
//Local time starts from 0 for every line
if((mesh.time() > waitingTime)){
  localTime = mesh.time() - laserSumTime;
} else {
  localTime *= 0;
}
dimensionedVector laserCoordinate ("laserCoordinate",dimLength,
  vector((point1[0] + speedVector[0]*localTime).value(),(point1[1] + speedVector[1]*localTime).value()
  ,(point1[2] + speedVector[2]*localTime).value()));

if (mag(localTime*laserSpeed) > lineLength){
Info << "One more line is done" <<  endl;
fileos << "New line # " << linecounter/2 <<  endl;
  linecounter = linecounter + 2;
  laserSumTime = laserSumTime + localTime;
  bool strategyNewLayer1 = (( laserStrategy[linecounter-2](2) != laserStrategy[linecounter](2)) && (strategyChoice == 0));
  bool strategyNewLayer2 = (((linecounter/2)%lineAmount) == 0) && (linecounter != 0) && (strategyChoice == 1);
  if (turnOnDebug.value() == 1){
  Info << "WTF with layers " << strategyNewLayer1 << strategyNewLayer2 << endl;
  }
  if ((strategyNewLayer1) || (strategyNewLayer2)){
    Info<< "Starting new layer" << " flag 1 " << strategyNewLayer1 << " flag 2 " << strategyNewLayer2 << endl;
    if (coolingTime.value() > 0){
    waitingTime = mesh.time() + coolingTime;
    }
    laserSumTime += coolingTime;

    airDepth = airDepth - powderDepth;
    airPart = tanhSmooth(coordZ, airDepth, -powderDepth/smootherAirFactor);
    LayerNumber++;
  }
}
bool strategyChoiceStop1 = ((strategyChoice == 0) && (linecounter >= laserStrategy.size())) || (mesh.time() > timeStop);
bool strategyChoiceStop2 = (strategyChoice == 1) && (linecounter/2 > lineAmount*10);
Info << "line Number = " << linecounter/2 << endl;
if ((strategyChoiceStop1) || (strategyChoiceStop2) || (mesh.time() < waitingTime))
{
  if (turnOnDebug.value() == 1) {
    Info << (linecounter >= laserStrategy.size()) << " " <<(mesh.time() > timeStop) << " " << (mesh.time() < waitingTime) << endl;
  }
  Info << "Laser is off" << " flag 1 " << strategyChoiceStop1 << " flag 2 " << strategyChoiceStop2 << endl;
  laserDistribution *= 0;
} else {
laserDistribution = 2*absorptivity*laserPower*
  gaussian(coordX, laserCoordinate[0], laserRadius)*
  gaussian(coordY, laserCoordinate[1], laserRadius)*
  gaussian(coordZ, laserCoordinate[2], laserRadius)*
  (scalar(1) - airPart);
}
// Info >> "Power Sum " >> fvc::domainIntegrate(laserDistribution) >> endl;
