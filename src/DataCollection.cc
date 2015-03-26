#include "DataCollection.hh"
#include <math.h>

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

DataCollection::DataCollection() {
    Clear();
    results = new TTree("results", "Deposited energy");
    results->Branch("detector_up", &detector_up, "detector_up/D");
    results->Branch("detector_down", &detector_down, "detector_down/D");
    results->Branch("primary", &primary, "primary/D");
    results->Branch("foil", &foil, "foil/D");
    G4cout << "DataCollection OK" << G4endl;
}


DataCollection::~DataCollection() {
    delete results;
}


void
  DataCollection::Clear() {
    detector_up = 0;
    detector_down = 0;
    collimator_up = 0;
    collimator_down = 0;
    primary = 0;
    foil = 0;
}

void
  DataCollection::ClearSpectra() {
    results->Reset();
}

void
  DataCollection::FillEvent() {
    //only fill if one detector registered an event
    if((detector_up != 0) || (detector_down != 0))results->Fill();
    Clear();
}

void
  DataCollection::WriteToDisk(G4String RootFN) {
    RootFile = new TFile(RootFN, "RECREATE", "Results from two detectors", 9);
    if(RootFile->IsOpen()) {
        results->Write();
        RootFile->Close();
        ClearSpectra();
    } else {
        G4cerr << "Could not open ROOT file!" << G4endl;
    }
    RootFile->Close();
    delete RootFile;
}
