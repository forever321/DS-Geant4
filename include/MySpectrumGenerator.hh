#ifndef MySpectrumGenerator_h
#define MySpectrumGenerator_h 1

#include "globals.hh" 
#include <iostream>
#include <string>

using namespace std;

class MySpectrumGenerator {

  public:

    MySpectrumGenerator();
    ~MySpectrumGenerator();

    G4double GetRandomEnergy();
    void Initialize(G4String fname);

  private:
    const G4int MAX_SPECTRUM; 
    G4double spectr[5000]; //array which holds the spectrum shape
    G4double spectr_maximum;
    G4double EndPointEnergy;

};

#endif
