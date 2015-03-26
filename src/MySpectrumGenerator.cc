#include "MySpectrumGenerator.hh"
#include "Randomize.hh"

MySpectrumGenerator::MySpectrumGenerator():MAX_SPECTRUM(5000) {

}

void
  MySpectrumGenerator::Initialize(G4String fname) {
    std::ifstream ispectr(fname.c_str(), std::ifstream::in);
    if(!ispectr.is_open()){
        cerr<<"Error opening " << fname << endl;
        return;
    }
    
    //the first 14 lines is the decay information, write it to the screen!
    char info[100];
    for(int i=0;i<14;i++){
        ispectr.getline(info,100);
        //ispectr >> info;
        cout << info << endl;
    }

    G4int i=1; //counter
    float dummy,val; /// temporary variable for sscanf
    while(ispectr >> dummy >> val){
        spectr[i]=val;
        i++;
        if(val > spectr_maximum)spectr_maximum = val;        
    }

    spectr[0]=spectr[1]; //the beta spectrum formulas don't work for 0 energy
    spectr_maximum *= 1.01; //increase it a bit for numerical safety!
    EndPointEnergy = (i-1)/10.0;
    cout << "EndPointEnergy " << EndPointEnergy << endl;

    for(int j = i - 1; j < MAX_SPECTRUM; j++) {
        spectr[j] = 0;
    }
    /*
    for(int j = 0; j < MAX_SPECTRUM; j++) {
        cout << j << ": " << spectr[j] << endl;
    }
    */
}

MySpectrumGenerator::~MySpectrumGenerator() {
}

G4double
MySpectrumGenerator::GetRandomEnergy() {
    G4double RandomEnergy, RandomOrdinate;
    //std::cout << "Max En: "<< EndPointEnergy<<endl;
    do {
        RandomEnergy = G4UniformRand() * EndPointEnergy;
        RandomOrdinate = G4UniformRand() * spectr_maximum;
    } while(RandomOrdinate > spectr[(int) round(RandomEnergy*10)]);
    return RandomEnergy;        //this is just a number. one should multiply it with keV
}

