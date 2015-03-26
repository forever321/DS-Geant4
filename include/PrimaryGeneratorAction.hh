#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Navigator.hh"
#include "DetectorConstruction.hh"
#include "G4ParticleTable.hh"
#include "PrimaryMessenger.hh"
#include "MySpectrumGenerator.hh"
#include "G4GeneralParticleSource.hh"

#include "DataCollection.hh"

class G4Event;			//geant4 class which represents an event, ie. particle history


class PrimaryGeneratorAction:public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction(MySpectrumGenerator *, DetectorConstruction *, DataCollection *);
    ~PrimaryGeneratorAction();

    //you must define this method, it is called by the G4RunManager
    //run manager passes the pointer to an event object, it will be given attributes from the Particle Gun
    void GeneratePrimaries(G4Event *);
    //G4GeneralParticleSource* GetParticleGun() {return particleGun;};
    G4ParticleGun *GetParticleGun() {
	return particleGun;
    };
    void SetGammas(G4bool sg) {
	ShootGammas = sg;
    };
    void SetGammaEnergy(G4double);
    void ResetGammas();
    void SetCE(G4bool sce) {
	ShootCE = sce;
    };
    void SetBetas(G4bool sb){ShootBetas=sb;};
    void SetCEEnergy(G4double);
    void ResetCE();

  private:
    #define NUM_OF_GAMMAS 20
    G4double GammaEnergies[NUM_OF_GAMMAS];
    G4double CEEnergies[NUM_OF_GAMMAS];
    G4int GammaCounter;
    G4int CECounter;
    G4bool ShootGammas;
    G4bool ShootCE;
    G4bool ShootBetas;

    G4GeneralParticleSource *gpsGun;
    G4ParticleGun *particleGun;
    G4ParticleTable *particleTable;

    PrimaryMessenger *messenger;

    MySpectrumGenerator *Spectrum;
    DetectorConstruction *currdc;
    DataCollection *DataColl;

};

#endif
