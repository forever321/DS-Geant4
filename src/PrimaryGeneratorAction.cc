#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RandomDirection.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(MySpectrumGenerator * ms, DetectorConstruction * dc, DataCollection *datc):Spectrum(ms), currdc(dc), DataColl(datc) {
    //particleGun = new G4GeneralParticleSource(); //initialize the ParticleGun
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
    particleGun->SetParticleDefinition(particleTable->FindParticle("e-"));
    messenger = new PrimaryMessenger(this);
    ResetGammas();
    ResetCE();

    ShootBetas = true;
    ShootGammas = false;
    ShootCE = false;

    G4cout << "PrimaryGenerator OK!" << G4endl;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete particleGun;
}



void
  PrimaryGeneratorAction::GeneratePrimaries(G4Event * anEvent) {
    
    //only do 45Ca;

    //set the position
    const G4double PosZ = 0.02 * mm; //half of the Kapton foil thickness

    G4double PosX, PosY;
    G4double SpotDiam = 2 * mm;
    G4double SpotRadius2 = SpotDiam * SpotDiam / 4.;
    do {
        PosY = (G4UniformRand() - 0.5) * SpotDiam;
        PosX = (G4UniformRand() - 0.5) * SpotDiam;
    } while((PosY * PosY + PosX * PosX) > SpotRadius2);
    
    PosY+=49.5*mm; // DetYOffset
    particleGun->SetParticlePosition(G4ThreeVector(PosX, PosY, PosZ));
    
    G4double RandomEnergy = (Spectrum->GetRandomEnergy()) * keV;
    DataColl->SetPrimaryEnergy(RandomEnergy);
    particleGun->SetParticleEnergy(RandomEnergy);
    particleGun->SetParticleMomentumDirection(G4RandomDirection());
    particleGun->GeneratePrimaryVertex(anEvent); 

    if((anEvent->GetEventID() % 1000000) == 0) {
        G4cout << "Event: " << anEvent->GetEventID() << G4endl;
    }
}

void
  PrimaryGeneratorAction::SetGammaEnergy(G4double En) {
    GammaEnergies[GammaCounter] = En;
    GammaCounter++;
}

void
  PrimaryGeneratorAction::ResetGammas() {
    GammaCounter = 0;
    for(G4int i = 0; i < NUM_OF_GAMMAS; i++) {
        GammaEnergies[i] = 0;
    }
}

void
  PrimaryGeneratorAction::SetCEEnergy(G4double En) {
    CEEnergies[CECounter] = En;
    CECounter++;
}

void
  PrimaryGeneratorAction::ResetCE() {
    CECounter = 0;
    for(G4int i = 0; i < NUM_OF_GAMMAS; i++) {
        CEEnergies[i] = 0;
    }
}
