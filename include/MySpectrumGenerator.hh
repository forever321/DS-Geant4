#ifndef MySpectrumGenerator_h
#define MySpectrumGenerator_h 1

#include "globals.hh" 
#include <iostream>
#include <string>
#include <vector>

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
    vector<G4double> CESpectr;
    vector<G4double> CEIntensities;
    G4double totalIntensity;
    G4bool isContinuous;

};

#endif
