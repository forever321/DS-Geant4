#include "G4RunManager.hh"
#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh" 
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DataCollection.hh"

int main(int argc, char** argv)
{ 
  DataCollection* DataColl = new DataCollection();
  G4RunManager* runManager = new G4RunManager();
  
  DetectorConstruction* detector;
  PrimaryGeneratorAction* primary;
  PhysicsList* physics;
  EventAction* evtact;
  SteppingAction* stepact;
  
  runManager->SetUserInitialization(detector = new DetectorConstruction);
  runManager->SetUserInitialization(physics=new PhysicsList());
  runManager->SetUserAction(primary = new PrimaryGeneratorAction(physics->GetSpectrumGenerator(),detector,DataColl));
  runManager->SetUserAction(stepact = new SteppingAction(detector));

  runManager->SetUserAction(evtact = new EventAction());
   
  G4UImanager * UI = G4UImanager::GetUIpointer();  // get the pointer to the User Interface manager
  G4VisManager* visManager = new G4VisExecutive();  visManager->Initialize();
  
  // set user action classes
  RunAction* ra; 
  runManager->SetUserAction(ra = new RunAction(detector,primary,physics,DataColl));   //runManager->Initialize();
  if(argc == 1)   // define UI terminal for interactive mode:
  {	G4UIsession* session = new G4UIterminal(new G4UItcsh); 
	session->SessionStart();
	delete session;
  }
  else            // batch mode:
  { G4String command = "/control/execute ";	G4String fileName = argv[1];
    if(argc<3){
      G4cout << "No random seed has been provided"<<G4endl;
      delete runManager;
      return 0;
    }
    CLHEP::HepRandom::setTheEngine(new CLHEP::HepJamesRandom);
    G4int randseed = atoi(argv[2]);
    CLHEP::HepRandom::setTheSeed(randseed);
  	G4cout << "Setting the Random seed: "<<randseed<<G4endl;

    UI->ApplyCommand(command+fileName);
  }
  // job termination
  delete runManager;
  return 0;
}
