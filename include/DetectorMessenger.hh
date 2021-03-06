#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWith3Vector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger:public G4UImessenger {
  public:
    DetectorMessenger(DetectorConstruction *);
    ~DetectorMessenger();

    void SetNewValue(G4UIcommand *, G4String);

  private:
      DetectorConstruction * Detector;

    G4UIdirectory *pipsDir;

    G4UIcmdWithoutParameter *UpdateCmd;
    G4UIcmdWithAString *SourceCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
