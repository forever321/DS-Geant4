//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: PhysicsList.cc,v 1.39 2010-06-04 15:42:23 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "MySpectrumGenerator.hh"

#include "PhysListEmStandard.hh"
#include "PhysListEmStandardSS.hh"
#include "PhysListEmStandardGS.hh"
#include "PhysListEmStandardWVI.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4DecayPhysics.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronQElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"

#include "G4LossTableManager.hh"
#include "G4EmConfigurator.hh"
#include "G4UnitsTable.hh"

#include "G4ProcessManager.hh"
#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4BraggIonGasModel.hh"
#include "G4BetheBlochIonGasModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList():G4VModularPhysicsList() {
    G4LossTableManager::Instance();
    defaultCutValue = 1. * um;
    cutForGamma = defaultCutValue;
    cutForElectron = defaultCutValue;
    cutForPositron = defaultCutValue;

    helIsRegisted = false;
    bicIsRegisted = false;
    biciIsRegisted = false;

    pMessenger = new PhysicsListMessenger(this);

    SetVerboseLevel(1);

    // EM physics
    emName = G4String("emstandard_opt3");
    emPhysicsList = new G4EmStandardPhysics(1);

    // Deacy physics and all particles
    decPhysicsList = new G4DecayPhysics();

    spectGen = new MySpectrumGenerator();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList() {
    delete pMessenger;
    delete emPhysicsList;
    delete decPhysicsList;
    for(size_t i = 0; i < hadronPhys.size(); i++) {
        delete hadronPhys[i];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::ConstructParticle() {
    decPhysicsList->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::ConstructProcess() {
    // transportation
    //
    AddTransportation();

    // electromagnetic physics list
    //
    emPhysicsList->ConstructProcess();

    // decay physics list
    //
    decPhysicsList->ConstructProcess();

    // hadronic physics lists
    for(size_t i = 0; i < hadronPhys.size(); i++) {
        hadronPhys[i]->ConstructProcess();
    }

    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    radioactiveDecay->SetHLThreshold(-1.*s);
    radioactiveDecay->SetICM(true);               //Internal Conversion
    radioactiveDecay->SetARM(true);              //Atomic Rearangement
              
    G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager();  
    pmanager->AddProcess(radioactiveDecay, 0, -1, 1);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::AddPhysicsList(const G4String & name) {
    if(verboseLevel > 1) {
        G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
    }

    if(name == emName)
        return;

    if(name == "local") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new PhysListEmStandard(name);

    } else if(name == "emstandard_opt0") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmStandardPhysics(1);

    } else if(name == "emstandard_opt1") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmStandardPhysics_option1();

    } else if(name == "emstandard_opt2") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmStandardPhysics_option2();

    } else if(name == "emstandard_opt3") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmStandardPhysics_option3();

    } else if(name == "standardSS") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new PhysListEmStandardSS(name);
    } else if(name == "standardWVI") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new PhysListEmStandardWVI(name);

    } else if(name == "standardGS") {

        emName = name;
        delete emPhysicsList;
        emPhysicsList = new PhysListEmStandardGS(name);

    } else if(name == "ionGasModels") {

        AddPhysicsList("emstandard_opt0");
        emName = name;
        AddIonGasModels();

    } else if(name == "emlivermore") {
        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmLivermorePhysics();

    } else if(name == "empenelope") {
        emName = name;
        delete emPhysicsList;
        emPhysicsList = new G4EmPenelopePhysics();

    } else if(name == "elastic" && !helIsRegisted) {
        hadronPhys.push_back(new G4HadronElasticPhysics());
        helIsRegisted = true;

    } else if(name == "DElastic" && !helIsRegisted) {
        hadronPhys.push_back(new G4HadronDElasticPhysics());
        helIsRegisted = true;

    } else if(name == "HElastic" && !helIsRegisted) {
        hadronPhys.push_back(new G4HadronHElasticPhysics());
        helIsRegisted = true;

    } else if(name == "QElastic" && !helIsRegisted) {
        hadronPhys.push_back(new G4HadronQElasticPhysics());
        helIsRegisted = true;

    } else if(name == "binary" && !bicIsRegisted) {
        hadronPhys.push_back(new G4HadronInelasticQBBC());
        bicIsRegisted = true;

    } else if(name == "binary_ion" && !biciIsRegisted) {
        hadronPhys.push_back(new G4IonBinaryCascadePhysics());
        biciIsRegisted = true;

    } else {

        G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << " is not defined" << G4endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void
  PhysicsList::SetCuts() {
    if(verboseLevel > 0) {
        G4cout << "PhysicsList::SetCuts:";
        G4cout << "CutLength : " << G4BestUnit(defaultCutValue, "Length") << G4endl;
    }
    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma
    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");

    if(verboseLevel > 0)
        DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::SetCutForGamma(G4double cut) {
    cutForGamma = cut;
    G4cout << "Setting cut for gamma " << G4BestUnit(cut, "Length") << G4endl;
    SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::SetCutForElectron(G4double cut) {
    cutForElectron = cut;
    G4cout << "Setting cut for electron " << G4BestUnit(cut, "Length") << G4endl;
    SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::SetCutForPositron(G4double cut) {
    cutForPositron = cut;
    G4cout << "Setting cut for positron " << G4BestUnit(cut, "Length") << G4endl;
    SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
  PhysicsList::AddIonGasModels() {
    G4EmConfigurator *
        em_config = G4LossTableManager::Instance()->EmConfigurator();
    theParticleIterator->reset();
    while((*theParticleIterator) ()) {
        G4ParticleDefinition *
            particle = theParticleIterator->value();
        G4String partname = particle->GetParticleName();
        if(partname == "alpha" || partname == "He3" || partname == "GenericIon") {
            G4BraggIonGasModel *
                mod1 = new G4BraggIonGasModel();
            G4BetheBlochIonGasModel *
                mod2 = new G4BetheBlochIonGasModel();
            G4double eth = 2. * MeV * particle->GetPDGMass() / proton_mass_c2;
            em_config->SetExtraEmModel(partname, "ionIoni", mod1, "", 0.0, eth, new G4IonFluctuations());
            em_config->SetExtraEmModel(partname, "ionIoni", mod2, "", eth, 100 * TeV, new G4UniversalFluctuation());

        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
