Making dependency list for source file heatTransferFoamI.C
g++ -std=c++11 -m64 -DOPENFOAM=1906 -DWM_DP -DWM_LABEL_SIZE=32 -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-attributes -Wno-unknown-pragmas -O3  -DNoRepository -ftemplate-depth-100 -IReadFiles -IdynMesh -IelasticPlasticSolid -IDynamicMesh -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/dynamicMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/meshTools/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/dynamicFvMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/finiteVolume/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/topoChangerFvMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/meshTools/lnInclude  -IlnInclude -I. -I/opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/OSspecific/POSIX/lnInclude   -fPIC -c heatTransferFoamI.C -o Make/linux64GccDPInt32Opt/heatTransferFoamI.o
In file included from heatTransferFoamI.C:61:0:
ReadFiles/readThermalProperties.H: In function 'int main(int, char**)':
ReadFiles/readThermalProperties.H:18:5: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
     );
     ^
ReadFiles/readThermalProperties.H:23:5: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
     );
     ^
ReadFiles/readThermalProperties.H:27:60: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("k_sol"))
                                                            ^
ReadFiles/readThermalProperties.H:32:61: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("dk_sol"))
                                                             ^
ReadFiles/readThermalProperties.H:36:60: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("k_liq"))
                                                            ^
ReadFiles/readThermalProperties.H:41:61: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("dk_liq"))
                                                             ^
ReadFiles/readThermalProperties.H:46:61: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("Cp_sol"))
                                                             ^
ReadFiles/readThermalProperties.H:51:62: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("dCp_sol"))
                                                              ^
ReadFiles/readThermalProperties.H:56:61: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("Cp_liq"))
                                                             ^
ReadFiles/readThermalProperties.H:61:62: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("dCp_liq"))
                                                              ^
ReadFiles/readThermalProperties.H:66:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("T_solidus"))
                                                                ^
ReadFiles/readThermalProperties.H:71:65: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("T_liquidus"))
                                                                 ^
ReadFiles/readThermalProperties.H:76:69: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("enthalpyFusion"))
                                                                     ^
ReadFiles/readThermalProperties.H:81:66: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("alphaLinear"))
                                                                  ^
ReadFiles/readThermalProperties.H:86:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("tempVar1"))
                                                               ^
ReadFiles/readThermalProperties.H:91:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(thermalProperties.lookup("tempVar2"))
                                                               ^
In file included from heatTransferFoamI.C:62:0:
ReadFiles/readLaserProperties.H:17:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("laserPower"))
                                                               ^
ReadFiles/readLaserProperties.H:22:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("laserSpeed"))
                                                               ^
ReadFiles/readLaserProperties.H:27:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("laserRadius"))
                                                                ^
ReadFiles/readLaserProperties.H:32:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = Foam::Vector<double>]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedVector(laserProperties.lookup("coordStart"))
                                                               ^
ReadFiles/readLaserProperties.H:37:61: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("timeStop"))
                                                             ^
ReadFiles/readLaserProperties.H:42:72: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("convertToMetersTemp"))
                                                                        ^
ReadFiles/readLaserProperties.H:59:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("turnOnWidth"))
                                                                ^
ReadFiles/readLaserProperties.H:64:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("turnOnShift"))
                                                                ^
ReadFiles/readLaserProperties.H:69:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("coolingTime"))
                                                                ^
ReadFiles/readLaserProperties.H:74:55: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("E1"))
                                                       ^
ReadFiles/readLaserProperties.H:79:56: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("nu1"))
                                                        ^
ReadFiles/readLaserProperties.H:84:65: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("hatchSpacing"))
                                                                 ^
ReadFiles/readLaserProperties.H:89:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("trackLength"))
                                                                ^
ReadFiles/readLaserProperties.H:94:63: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("lineAmount"))
                                                               ^
ReadFiles/readLaserProperties.H:99:67: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("strategyChoice"))
                                                                   ^
In file included from heatTransferFoamI.C:63:0:
ReadFiles/readPowderProperties.H:18:69: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("initialPorosity"))
                                                                     ^
ReadFiles/readPowderProperties.H:23:66: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("absorptivity"))
                                                                  ^
ReadFiles/readPowderProperties.H:28:65: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("powderDepth"))
                                                                 ^
ReadFiles/readPowderProperties.H:33:62: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("airDepth"))
                                                              ^
ReadFiles/readPowderProperties.H:38:69: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("airConductivity"))
                                                                     ^
ReadFiles/readPowderProperties.H:43:65: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("airCapacity"))
                                                                 ^
ReadFiles/readPowderProperties.H:48:64: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(powderProperties.lookup("airDensity"))
                                                                ^
In file included from heatTransferFoamI.C:64:0:
ReadFiles/readSystemProperties.H:18:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:23:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:28:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:33:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:38:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:43:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:48:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:53:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:57:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:62:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:66:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:70:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:75:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:80:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
ReadFiles/readSystemProperties.H:84:1: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
 );
 ^
In file included from heatTransferFoamI.C:66:0:
ReadFiles/readMechanicalProperties.H:17:54: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("E"))
                                                      ^
ReadFiles/readMechanicalProperties.H:22:55: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("nu"))
                                                       ^
ReadFiles/readMechanicalProperties.H:27:59: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("sigmaY"))
                                                           ^
ReadFiles/readMechanicalProperties.H:32:55: warning: 'Foam::dimensioned<Type>::dimensioned(Foam::Istream&) [with Type = double]' is deprecated (declared at /opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude/dimensionedType.C:235): Since 2018-11 [-Wdeprecated-declarations]
         dimensionedScalar(laserProperties.lookup("Ep"))
                                                       ^
heatTransferFoamI.C:142:6: warning: unused variable 'borderCheck' [-Wunused-variable]
 bool borderCheck = false;
      ^
g++ -std=c++11 -m64 -DOPENFOAM=1906 -DWM_DP -DWM_LABEL_SIZE=32 -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-attributes -Wno-unknown-pragmas -O3  -DNoRepository -ftemplate-depth-100 -IReadFiles -IdynMesh -IelasticPlasticSolid -IDynamicMesh -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/dynamicMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/meshTools/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/dynamicFvMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/finiteVolume/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/dynamicMesh/topoChangerFvMesh/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/meshTools/lnInclude  -IlnInclude -I. -I/opt/OpenFOAM/OpenFOAM-v1906/src/OpenFOAM/lnInclude -I/opt/OpenFOAM/OpenFOAM-v1906/src/OSspecific/POSIX/lnInclude   -fPIC -Xlinker --add-needed -Xlinker --no-as-needed Make/linux64GccDPInt32Opt/heatTransferFoamI.o -L/opt/OpenFOAM/OpenFOAM-v1906/platforms/linux64GccDPInt32Opt/lib \
    -lfiniteVolume -ldynamicMesh -lmeshTools -ldynamicFvMesh -ltopoChangerFvMesh -lmeshTools -ltopoChangerFvMesh -L -lmesquite -L/home/ofuser/OpenFOAM/ofuser-v1906/platforms/linux64GccDPInt32Opt/lib  -lOpenFOAM -ldl  \
     -lm -o /home/ofuser/OpenFOAM/ofuser-v1906/platforms/linux64GccDPInt32Opt/bin/heatTransferFoamI
