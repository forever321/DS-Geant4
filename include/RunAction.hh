#ifndef RunAction_hh
#define RunAction_hh 1

#include "G4UserRunAction.hh"
#include "DataCollection.hh"
#include "RunMessenger.hh"

#include "TROOT.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TFile.h"

//using namespace std;         //needed for using standard libraries

class DetectorConstruction;	//declare the DetectorConstruction class as we will define a pointer to it later
class PrimaryGeneratorAction;
class PhysicsList;
//Run action class, carries out tasks at the begin and end of each run.
//The concept of a run incorporates a fixed geometry, fixed beam conditions, simulation of number of primaries.
//Begins with /run/beamOn command and finishes with tracking of last secondary to zero energy: 
class RunAction:public G4UserRunAction {
  public:
    //Run action class needs a pointer of the detector construction class in order to get details of the readout geometry.
    //Accepts pointer to detector construction class:
    RunAction(DetectorConstruction *, PrimaryGeneratorAction *, PhysicsList *, DataCollection* );
    ~RunAction();

    void BeginOfRunAction(const G4Run *);
    void EndOfRunAction(const G4Run *);
    void SetOutputFileName(G4String fn) {
	OutputFileName = fn;
    };
    DataCollection *GetDataCollection() {
	return DataColl;
    };

  private:
    DetectorConstruction * myDC;	//local pointer for detector construction class
    PrimaryGeneratorAction *primary;
    PhysicsList *myPhysicsList;
    DataCollection *DataColl;
    G4String OutputFileName;
    RunMessenger *messenger;
};

#endif
