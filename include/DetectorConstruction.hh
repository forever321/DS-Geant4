//preprocessor directives to prevent multiple includes of the same file
#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh 1

//preprocessor directive to include the header file for the base class
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "DetectorMessenger.hh"

using namespace std;


//class declaration, we don't need to tell the compiler how big it is, yet
class G4VPhysicalVolume;
class G4Box;
class G4Tubs;
class G4Sphere;
class G4LogicalVolume;
class G4SubtractionSolid;
class G4UnionSolid;
class G4Material;
class G4Polycone;
class G4Region;

//this is the user defined class that inherits behaviour from the virtual base class of the geant4 toolkit
class DetectorConstruction:public G4VUserDetectorConstruction {

  public:
//declare the constructor for this class
    DetectorConstruction();
//declare the destructor of this class
    ~DetectorConstruction();

//the one method that MUST be defined in this class, it is called "Construct", takes no arguments, and returns a pointer to an object of type G4VPhysicalVolume
    G4VPhysicalVolume *Construct();

    G4VPhysicalVolume *GetDetVol_up() {
	return physiDetector_up;
    };

    G4VPhysicalVolume *GetDetVol_down() {
	return physiDetector_down;
    };

    G4VPhysicalVolume *GetFoilVol();

    void SetSource(G4String ns);
    G4int GetSourceInd(){return SourceInd;};
    void UpdateGeometry();

  private:
    G4double MacroGap, MicroGap;
  
    G4VPhysicalVolume *ConstructCalorimeter();
    DetectorMessenger *detectorMessenger;

    G4Box *solidWorld;		//pointer to the solid World 
    G4LogicalVolume *logicWorld;	//pointer to the logical World
    G4VPhysicalVolume *physiWorld;	//pointer to the physical World

    G4Material *vacuum;

    // Detector mount platform
    G4double DetMountPlatDiameter;
    G4double DetMountPlatThickness;
    G4SubtractionSolid* solidDetMountPlat;
    G4SubtractionSolid* solidDetMountPlat_down;
    G4LogicalVolume* logicDetMountPlat;
    G4LogicalVolume* logicDetMountPlat_down;
    G4VPhysicalVolume* physiDetMountPlat_up;
    G4VPhysicalVolume* physiDetMountPlat_down;
    G4Material* DetMountPlatMaterial;

    //detector support plate
    G4Tubs *roundPlate;
    G4Box *squareCut;
    G4SubtractionSolid *roundPlateWithACut;

    G4LogicalVolume *logicRPWAC;
    G4VPhysicalVolume *physiRPWAC_up;
    G4VPhysicalVolume *physiRPWAC_down;
    G4Material *SupportPlateMaterial;
    G4double SupportPlateThickness;
    G4double SupportPlateDiameter;
    G4double CutSize;
    //G4double cutXSize;
    //G4double cutYSize;

    //detector
    G4double DetSourceDist;
    G4double DetYOffset;
    
    G4String DetectorName;
    G4double DetectorXSize, DetectorYSize;

    G4Box *solidDetector;
    G4LogicalVolume *logicDetector_up;
    G4LogicalVolume *logicDetector_down;
    G4VPhysicalVolume *physiDetector_up;
    G4VPhysicalVolume *physiDetector_down;
    G4Material *DetectorMaterial;
    G4double DepletionLayerThickness;

    G4Box *solidFrontDeadLayer;
    G4LogicalVolume *logicFrontDeadLayer;
    G4VPhysicalVolume *physiFrontDeadLayer_up;
    G4VPhysicalVolume *physiFrontDeadLayer_down;
    G4Material *FrontDeadLayerMaterial;
    G4double FrontDeadLayerThickness;

    G4Box *solidRearDeadLayer;
    G4LogicalVolume *logicRearDeadLayer;
    G4VPhysicalVolume *physiRearDeadLayer_up;
    G4VPhysicalVolume *physiRearDeadLayer_down;
    G4double RearDeadLayerThickness;

    G4Box *solidCeramicSupport;
    G4LogicalVolume *logicCeramicSupport;
    G4VPhysicalVolume *physiCeramicSupport_up;
    G4VPhysicalVolume *physiCeramicSupport_down;
    G4Material *CeramicSupportMaterial;
    G4double CeramicSupportXSize, CeramicSupportYSize, CeramicSupportThickness;
    
    


    //Source variable
    G4String SourceName;
    G4int SourceInd;
    
    G4SubtractionSolid* solidSourcePlatf;
    G4LogicalVolume* logicSourcePlatf;
    G4VPhysicalVolume* physiSourcePlatf;
    G4Material* SourcePlatfMaterial;

    

    //source holder (for Bi)
    G4Polycone *solidBiSource;
    G4LogicalVolume *logicBiSource;
    G4VPhysicalVolume *physiBiSource;
    G4Material *BiSourceMaterial;

    G4double TiWindowDiameter;
    G4double TiWindowThickness;
    G4Tubs *solidTiWindow;
    G4LogicalVolume *logicTiWindow;
    G4VPhysicalVolume *physiTiWindow;
    G4Material *TiWindowMaterial;

    //45Ca source
    G4double CaHoleDiameter;
    G4Material* CaRingMaterial;
    
    G4Polycone* solidCaBigRing;
    G4LogicalVolume* logicCaBigRing;
    G4VPhysicalVolume* physiCaBigRing;
    G4Material* CaBigRingMaterial;

    G4double CaSmallRingDiameter;
    G4double CaSmallRingThickness;
    G4Tubs* solidCaSmallRing;
    G4LogicalVolume* logicCaSmallRing;
    G4VPhysicalVolume* physiCaSmallRing;
    
    G4double CaKaptonFoilDiameter;
    G4double CaKaptonFoilThickness;
    G4Tubs* solidCaKaptonFoil;
    G4LogicalVolume* logicCaKaptonFoil;
    G4VPhysicalVolume* physiCaKaptonFoil;
    G4Material* CaKaptonFoilMaterial;

    //133Ba source
    G4double BaHoleDiameter;
    G4Material* BaRingMaterial;

    G4Polycone* solidBaBigRing;
    G4LogicalVolume* logicBaBigRing;
    G4VPhysicalVolume* physiBaBigRing;

    G4double BaSmallRingDiameter;
    G4double BaSmallRingThickness;
    G4Tubs* solidBaSmallRing;
    G4LogicalVolume* logicBaSmallRing;
    G4VPhysicalVolume* physiBaSmallRing;

    G4double BaKaptonFoilDiameter;
    G4double BaKaptonFoilThickness;
    G4Tubs* solidBaKaptonFoil;
    G4LogicalVolume* logicBaKaptonFoil;
    G4VPhysicalVolume* physiBaKaptonFoil;
    G4Material* BaKaptonFoilMaterial;
    
    
    
    void PrintInfo();
};
#endif
