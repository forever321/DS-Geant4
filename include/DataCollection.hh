#ifndef DataCollection_h
#define DataCollection_h 1

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"

#include "G4String.hh"
#include "G4Types.hh"

class DataCollection {


  private:
    G4double detector_up, detector_down;
    G4double collimator_up, collimator_down;
    G4double primary, foil;

    TFile *RootFile;
    TTree *results;

    void Clear();

  public:
      DataCollection();
     ~DataCollection();

    void AddDetector_up(G4double DE) {
	detector_up += DE;
    };
    void AddDetector_down(G4double DE) {
	detector_down += DE;
    };
    void AddColl_up(G4double CE) {
	collimator_up += CE;
    };
    void AddColl_down(G4double CE) {
	collimator_down += CE;
    };
    void SetPrimaryEnergy(G4double PE){
    primary = PE;
    };
    void AddFoilDep(G4double FE){
    foil += FE;
    };
    void FillEvent();
    void WriteToDisk(G4String);
    void ClearSpectra();

};

#endif
