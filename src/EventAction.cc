#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"

#include "RunAction.hh"
#include "G4RunManager.hh"



EventAction::EventAction() {
    G4cout << "EventAction OK!" << G4endl;
    dcoll = NULL;
}


EventAction::~EventAction() {
}


void
  EventAction::BeginOfEventAction(const G4Event *) {
}


void
  EventAction::EndOfEventAction(const G4Event * evt) {
    if(dcoll == NULL) {
        dcoll = ((RunAction *) (G4RunManager::GetRunManager()->GetUserRunAction()))->GetDataCollection();
    }
    //cout << "Filling"<<endl;

    dcoll->FillEvent();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
