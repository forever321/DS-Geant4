#include "RunAction.hh"
#include "G4Run.hh"
#include "Randomize.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunMessenger.hh"

RunAction::RunAction(DetectorConstruction * DC, PrimaryGeneratorAction * pg, PhysicsList * phys, DataCollection* datc){
    primary = pg;
    DataColl = datc;
    OutputFileName = "results.root";
    messenger = new RunMessenger(this);

    G4cout << "Creating RunAction" << G4endl;
}


RunAction::~RunAction() {
    delete DataColl;
}


void
  RunAction::BeginOfRunAction(const G4Run * aRun) {
    CLHEP::HepRandom::showEngineStatus();

    G4cout << "Starting run " << aRun->GetRunID() << G4endl;
    time_t CurrentTime;
    tm *
        ptm;
    time(&CurrentTime);
    ptm = localtime(&CurrentTime);
    G4cout << "Time: " << asctime(ptm) << G4endl;
}


void
  RunAction::EndOfRunAction(const G4Run * aRun) {

    DataColl->WriteToDisk(OutputFileName);

    G4cout << "End of run OK!" << G4endl;
    time_t CurrentTime;
    tm *
        ptm;
    time(&CurrentTime);
    ptm = localtime(&CurrentTime);
    G4cout << "Simulation finished." << G4endl << "Time: " << asctime(ptm) << G4endl;
    CLHEP::HepRandom::showEngineStatus();

}
