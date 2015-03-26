#ifndef EventAction_hh
#define EventAction_hh 1

#include "G4UserEventAction.hh"
#include "DataCollection.hh"


class G4Event;

class EventAction:public G4UserEventAction {
  public:
    EventAction();
    ~EventAction();

  public:
    void BeginOfEventAction(const G4Event *);
    void EndOfEventAction(const G4Event *);


  private:
      DataCollection * dcoll;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
