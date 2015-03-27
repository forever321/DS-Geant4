#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * HPGeDet):
Detector(HPGeDet) {

    pipsDir = new G4UIdirectory("/twodets/geometry/");
    pipsDir->SetGuidance("control of the set-up geometry");

    SourceCmd = new G4UIcmdWithAString("/twodets/geometry/SelectSource", this);
    SourceCmd->SetGuidance("Select the source.");
    SourceCmd->SetParameterName("Choice of Source", false);
    SourceCmd->SetCandidates("Ca Bi Ba");
    SourceCmd->AvailableForStates(G4State_PreInit);

    UpdateCmd = new G4UIcmdWithoutParameter("/twodets/geometry/update", this);
    UpdateCmd->SetGuidance("Update calorimeter geometry.");
    UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
    UpdateCmd->SetGuidance("if you changed geometrical value(s).");
    UpdateCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger() {
    delete UpdateCmd;
    delete SourceCmd;
    delete pipsDir;

    G4cout << "deleting DetectorMessenger" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  DetectorMessenger::SetNewValue(G4UIcommand * command, G4String newValues) {
    if(command == SourceCmd)
        Detector->SetSource(newValues);
    if(command == UpdateCmd)
        Detector->UpdateGeometry();

}
