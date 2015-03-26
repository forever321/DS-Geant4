#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
//class EventAction;
//class RunAction;
class DataCollection;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction:public G4UserSteppingAction {
  public:
    SteppingAction(DetectorConstruction *);
    ~SteppingAction();

    void UserSteppingAction(const G4Step *);

  private:
      DataCollection * myDC;
    DetectorConstruction *detector;
    int MaxStepNumber;
    int MaxStepLength;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
