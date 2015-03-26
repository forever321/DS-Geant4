#ifndef PRIMARYMESSENGER_HH
#define PRIMARYMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

class PrimaryGeneratorAction;

class PrimaryMessenger:public G4UImessenger {

  private:
    G4UIcmdWithABool * pGammaCmd;
    G4UIcmdWithADoubleAndUnit *pGammaEnCmd;
    G4UIcmdWithoutParameter *pResetGammaCmd;
    G4UIcmdWithABool *pCECmd;
    G4UIcmdWithABool *pBetaCmd;
    G4UIcmdWithADoubleAndUnit *pCEEnCmd;
    G4UIcmdWithoutParameter *pResetCECmd;
    PrimaryGeneratorAction *PrimGen;

  public:
      PrimaryMessenger(PrimaryGeneratorAction *);
     ~PrimaryMessenger();
    void SetNewValue(G4UIcommand *, G4String);

};

#endif
