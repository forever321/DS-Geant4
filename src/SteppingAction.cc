#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"

#include "G4RunManager.hh"
#include "RunAction.hh"

SteppingAction::SteppingAction(DetectorConstruction * DC):detector(DC) {
    myDC = NULL;
    MaxStepNumber = 500000;
    MaxStepLength = 1000;       //in meters
}


SteppingAction::~SteppingAction() {
}


void
  SteppingAction::UserSteppingAction(const G4Step * aStep) {
    if(myDC == NULL)
        myDC = ((RunAction *) (G4RunManager::GetRunManager()->GetUserRunAction()))->GetDataCollection();
    /*
       G4Track* aTrack = aStep->GetTrack();
       Int_t stepn = aTrack->GetCurrentStepNumber();
       if((stepn>MaxStepNumber)||(aTrack->GetTrackLength()/m>MaxStepLength)){
       aTrack->SetTrackStatus(fStopAndKill);
       cout << "Killing track: ";
       if(stepn>MaxStepNumber){cout<<"It has too many steps"<<G4endl;}else{cout<<"It is too long"<<G4endl;}
       }
    */

    G4VPhysicalVolume *
        pVol = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    if(pVol == detector->GetDetVol_up())
        myDC->AddDetector_up(aStep->GetTotalEnergyDeposit());
    if(pVol == detector->GetDetVol_down())
        myDC->AddDetector_down(aStep->GetTotalEnergyDeposit());
    if(pVol == detector->GetFoilVol())
        myDC->AddFoilDep(aStep->GetTotalEnergyDeposit());

}
