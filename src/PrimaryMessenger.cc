#include "PrimaryGeneratorAction.hh"

PrimaryMessenger::PrimaryMessenger(PrimaryGeneratorAction * pg):PrimGen(pg) {
    pGammaCmd = new G4UIcmdWithABool("/twodets/phys/SetShootGammas", this);
    pGammaCmd->SetGuidance("If true it will also generate (isotropic) gamma rays");
    pGammaCmd->SetParameterName("sgamma", false);
    pGammaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGammaEnCmd = new G4UIcmdWithADoubleAndUnit("/twodets/phys/SetGammaEnergy", this);
    pGammaEnCmd->SetGuidance("Set the gamma energy");
    pGammaEnCmd->SetParameterName("GammaEn", false);
    pGammaEnCmd->SetUnitCandidates("keV MeV");
    pGammaEnCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pResetGammaCmd = new G4UIcmdWithoutParameter("/twodets/phys/ResetGammas", this);
    pResetGammaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pCECmd = new G4UIcmdWithABool("/twodets/phys/SetShootCE", this);
    pCECmd->SetGuidance("If true it will also generate (isotropic) conversion electrons");
    pCECmd->SetParameterName("sce", false);
    pCECmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pBetaCmd = new G4UIcmdWithABool("/twodets/phys/SetShootBetas", this);
    pBetaCmd->SetGuidance("If true it will generate (isotropic) betas");
    pBetaCmd->SetParameterName("sbeta", false);
    pBetaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pCEEnCmd = new G4UIcmdWithADoubleAndUnit("/twodets/phys/SetCEEnergy", this);
    pCEEnCmd->SetGuidance("Set the conversion electron energy");
    pCEEnCmd->SetParameterName("CEEn", false);
    pCEEnCmd->SetUnitCandidates("keV MeV");
    pCEEnCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pResetCECmd = new G4UIcmdWithoutParameter("/twodets/phys/ResetCE", this);
    pResetCECmd->AvailableForStates(G4State_PreInit, G4State_Idle);

}

PrimaryMessenger::~PrimaryMessenger() {
    delete pGammaCmd;
    delete pGammaEnCmd;
    delete pResetGammaCmd;
    delete pCECmd;
    delete pBetaCmd;
    delete pCEEnCmd;
    delete pResetCECmd;
}

void
  PrimaryMessenger::SetNewValue(G4UIcommand * command, G4String newValue) {
    if(command == pGammaCmd) {
        PrimGen->SetGammas(pGammaCmd->GetNewBoolValue(newValue));
    }
    if(command == pBetaCmd) {
        PrimGen->SetBetas(pBetaCmd->GetNewBoolValue(newValue));
    }
    if(command == pGammaEnCmd) {
        PrimGen->SetGammaEnergy(pGammaEnCmd->GetNewDoubleValue(newValue));
    }
    if(command == pResetGammaCmd) {
        PrimGen->ResetGammas();
    }
    if(command == pCECmd) {
        PrimGen->SetCE(pCECmd->GetNewBoolValue(newValue));
    }
    if(command == pCEEnCmd) {
        PrimGen->SetCEEnergy(pCEEnCmd->GetNewDoubleValue(newValue));
    }
    if(command == pResetCECmd) {
        PrimGen->ResetCE();
    }
}
