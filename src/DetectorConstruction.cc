#include "DetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "DetectorMessenger.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Polycone.hh"
#include "G4RunManager.hh"

DetectorConstruction::~DetectorConstruction() {
    G4cout << "\n Deleting DetectorConstruction..." << G4endl;
}

G4VPhysicalVolume *
DetectorConstruction::Construct() {
    PrintInfo();
    return ConstructCalorimeter();
}

void
  DetectorConstruction::PrintInfo() {
    cout << "\n********* Information about the geometrical setup *********";
    cout << "\nSource: " << SourceName<<G4endl;
}

DetectorConstruction::DetectorConstruction() {
    G4cout << "Constructing DetectorConstruction" << G4endl;
    //Detector Messenger
    detectorMessenger = new DetectorMessenger(this);
    
    MacroGap = 0.01*mm;
    MicroGap = 0.0001*mm;

    //Here we define the materials:
    G4NistManager *man = G4NistManager::Instance();
    man->SetVerbose(1);

    vacuum = man->FindOrBuildMaterial("G4_Galactic");

    //Initialize the variables:
    G4Element *elCu = man->FindOrBuildElement("Cu");
    G4Element *elZn = man->FindOrBuildElement("Zn");
    G4Material *Brass = new G4Material("Brass", 8.55 * g / cm3, 2);
    Brass->AddElement(elCu, 65 * perCent);
    Brass->AddElement(elZn, 35 * perCent);
    
    //Detector - Source distance
    DetSourceDist = 3.5*mm;
    DetYOffset = 49.5*mm;

    //Detector Mount Platform
    DetMountPlatDiameter = 190*mm;
    DetMountPlatThickness = 5*mm;
    DetMountPlatMaterial = Brass;

    //detector support plate
    SupportPlateThickness = 3. * mm;
    SupportPlateDiameter = 44. * mm;
    SupportPlateMaterial = man->FindOrBuildMaterial("G4_Al");
    CutSize = 9*mm+MacroGap; //the cut is much more complicated. However, the material 
    //of the detector holder is very similar -> Al vs. AlO, so from scatterin 
    //point of view there is no difference. So, first approximation, the hole is 9x9 mm
    //cutXSize = 14.7 * mm;
    //cutYSize = 12.9 * mm;

    //Detector
    DetectorXSize = DetectorYSize = 9.0 * mm;
    //total thickness is 0.5 mm
    DepletionLayerThickness = 0.4694 * mm;      // from the Hamamatsu information (rear dead layer is min. 30 mum)
    FrontDeadLayerThickness = 0.0006 * mm;      // front dead layer from the article
    RearDeadLayerThickness = 0.03 * mm;
    
    FrontDeadLayerMaterial = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    DetectorMaterial = man->FindOrBuildMaterial("G4_Si");

    //CeramicSupportXSize = 14.5 * mm;
    //CeramicSupportYSize = 12.7 * mm;  
    CeramicSupportXSize = 9*mm; //see the comments about the hole in the detector support
    CeramicSupportYSize = 9*mm;
    CeramicSupportThickness = 1.28 * mm;
    CeramicSupportMaterial = man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");


    //source platform
    SourcePlatfMaterial = Brass;

    //207Bi source
    BiSourceMaterial = man->FindOrBuildMaterial("G4_Al");
    TiWindowMaterial = man->FindOrBuildMaterial("G4_Ti");

    TiWindowDiameter = 15 * mm;
    TiWindowThickness = 2. * 0.005325 * mm;
    
    //45Ca source
    CaHoleDiameter = 15 * mm;
    CaRingMaterial = man->FindOrBuildMaterial("G4_Al");;
    
    CaSmallRingDiameter = 22.5 * mm - MacroGap;
    CaSmallRingThickness = 1.6 * mm;
    
    CaKaptonFoilDiameter = 22.5 * mm - MacroGap;
    CaKaptonFoilThickness = 0.04 * mm; 
    CaKaptonFoilMaterial = man->FindOrBuildMaterial("G4_KAPTON");
    
    SourceName = "Ca";
}

G4VPhysicalVolume *
DetectorConstruction::ConstructCalorimeter() {
    //put some colors
    G4VisAttributes *green = new G4VisAttributes(G4Colour(0., 1., 0.));
    G4VisAttributes *blue = new G4VisAttributes(G4Colour(0., 0., 1.));
    G4VisAttributes *red = new G4VisAttributes(G4Colour(1., 0., 0.));

    //small gaps to make space between the volumes
    G4double MacroGap = 1 * um;
    G4double MicroGap = 5 * nm;

    //WORLD:
    G4double worldx = 0.5 * m;
    G4double worldy = 0.5 * m;
    G4double worldz = 0.5 * m;
    G4Box *world = new G4Box("world_box", worldx, worldy, worldz);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(world, vacuum, "world_log", 0, 0, 0);
    logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
    G4VPhysicalVolume *physical_world = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "world_phys", 0, false, 0);
        
    //brass plates - Detector Mount Platform
    G4Tubs* baseDetMountPlat = new G4Tubs("DetMountPlat",0,DetMountPlatDiameter/2,DetMountPlatThickness/2,0,twopi);
    G4Tubs* DrillTube1 = new G4Tubs("DrillTube1",0,49.5*mm/2,2*mm,0,twopi);
    G4SubtractionSolid* tempsol_up = new G4SubtractionSolid("tempsol_up",baseDetMountPlat,DrillTube1,0,G4ThreeVector(0,DetYOffset,-DetMountPlatThickness/2));
    G4Tubs* DrillTube2 = new G4Tubs("DrillTube2",0,30*mm/2,3*mm,0,twopi);

    solidDetMountPlat = new G4SubtractionSolid("DetMountPlat", tempsol_up, DrillTube2,0,G4ThreeVector(0,DetYOffset,DetMountPlatThickness/2));
    logicDetMountPlat = new G4LogicalVolume(solidDetMountPlat, DetMountPlatMaterial,"DetMountPlat_up");
    logicDetMountPlat->SetVisAttributes(green);
    //logicDetMountPlat->SetVisAttributes (G4VisAttributes::Invisible); 
    physiDetMountPlat_up = new G4PVPlacement(0,G4ThreeVector(0,0, DetSourceDist+1*mm+DetMountPlatThickness/2),logicDetMountPlat, "DetMountPlat_up",logicWorld,false,0);

    G4SubtractionSolid* tempsol_down = new G4SubtractionSolid("tempsol_down",baseDetMountPlat,DrillTube1,0,G4ThreeVector(0,DetYOffset,DetMountPlatThickness/2));
    solidDetMountPlat_down = new G4SubtractionSolid("DetMountPlat", tempsol_down, DrillTube2,0,G4ThreeVector(0,DetYOffset,-DetMountPlatThickness/2));
    logicDetMountPlat_down = new G4LogicalVolume(solidDetMountPlat_down, DetMountPlatMaterial,"DetMountPlat_down");
    logicDetMountPlat_down->SetVisAttributes(green); 
    //logicDetMountPlat_down->SetVisAttributes (G4VisAttributes::Invisible); 
    physiDetMountPlat_down = new G4PVPlacement(0,G4ThreeVector(0,0, -(DetSourceDist+1*mm+DetMountPlatThickness/2)),logicDetMountPlat_down, "DetMountPlat_down",logicWorld,false,0);

    // detector support plate
    roundPlate = new G4Tubs("roundPlate", 0, SupportPlateDiameter / 2., SupportPlateThickness / 2., 0. * deg, 360. * deg);
    squareCut = new G4Box("squareCut", CutSize / 2., CutSize / 2., 50*mm); //the Z dimension is irrelevant, as long as it is larger than the thickness of the support plate
    roundPlateWithACut = new G4SubtractionSolid("RPWAC", roundPlate, squareCut);
    logicRPWAC = new G4LogicalVolume(roundPlateWithACut, SupportPlateMaterial, "RPWAC");    
    logicRPWAC->SetVisAttributes(red);
    physiRPWAC_up = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, DetSourceDist+SupportPlateThickness/2), logicRPWAC, "RPWAC_up", logicWorld, false, 0);
    physiRPWAC_down = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, -(DetSourceDist+SupportPlateThickness/2)), logicRPWAC, "RPWAC_down", logicWorld, false, 0);
    
    //detector
    //front dead layer
    solidFrontDeadLayer = new G4Box("FrontDeadLayer", DetectorXSize / 2., DetectorYSize / 2., FrontDeadLayerThickness / 2.);
    logicFrontDeadLayer = new G4LogicalVolume(solidFrontDeadLayer, FrontDeadLayerMaterial, "FrontDeadLayer");
    G4double ZPos = DetSourceDist+0.5*mm+FrontDeadLayerThickness/2.+MacroGap;
    physiFrontDeadLayer_up = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, ZPos), logicFrontDeadLayer, "FrontDeadLayer_up", logicWorld, false, 0);    
    physiFrontDeadLayer_down = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, -ZPos), logicFrontDeadLayer, "FrontDeadLayer_down", logicWorld, false, 0);    
    
    ZPos+=FrontDeadLayerThickness/2+DepletionLayerThickness/2;

    //sensitive volume, we need 2 logical volumes because the energy deposit is tied to the logical volumes
    solidDetector = new G4Box("Detector", DetectorXSize / 2., DetectorYSize / 2., DepletionLayerThickness / 2.);
    logicDetector_up = new G4LogicalVolume(solidDetector, DetectorMaterial, "Detector");
    logicDetector_down = new G4LogicalVolume(solidDetector, DetectorMaterial, "Detector");
    physiDetector_up = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, ZPos), logicDetector_up, "Detector_up", logicWorld, false, 0);
    physiDetector_down = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, -ZPos), logicDetector_down, "Detector_down", logicWorld, false, 0);

    ZPos+=DepletionLayerThickness/2+RearDeadLayerThickness/2;

    
    //read dead layer
    solidRearDeadLayer = new G4Box("RearDeadLayer", DetectorXSize / 2., DetectorYSize / 2., RearDeadLayerThickness / 2.);
    logicRearDeadLayer = new G4LogicalVolume(solidRearDeadLayer, DetectorMaterial, "RearDeadLayer");
    physiRearDeadLayer_up = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, ZPos), logicRearDeadLayer, "RearDeadLayer_up", logicWorld, false, 0);
    physiRearDeadLayer_down = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, -ZPos), logicRearDeadLayer, "RearDeadLayer_down", logicWorld, false, 0);
    
    ZPos+=RearDeadLayerThickness/2+CeramicSupportThickness/2;
    
    //ceramic support of the detector's chip
    solidCeramicSupport = new G4Box("CeramicSupport", CeramicSupportXSize / 2., CeramicSupportYSize / 2., CeramicSupportThickness / 2.);
    logicCeramicSupport = new G4LogicalVolume(solidCeramicSupport, CeramicSupportMaterial, "CeramicSupport");
    physiCeramicSupport_up = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, ZPos), logicCeramicSupport, "CeramicSupport_up", logicWorld, false, 0);
    physiCeramicSupport_down = new G4PVPlacement(0, G4ThreeVector(0, DetYOffset, -ZPos), logicCeramicSupport, "CeramicSupport_down", logicWorld, false, 0);
    
    
    
    //Source platform - a square with a round hole in the middle
    G4Box* solidSourcePlatf_o = new G4Box("SourcePlatf_o", 40*mm/2, 135*mm/2, 2*mm/2);
    G4double CutDiamL,CutDiamS;
    if(SourceName=="Ca"){
        CutDiamL = 30.2 * mm;
        CutDiamS = 25 * mm;
    }
    G4Tubs* solidCutSourcePlatfL = new G4Tubs("CutSourcePlatf",0,CutDiamL/2,1*mm,0,twopi);
    G4Tubs* solidCutSourcePlatfS = new G4Tubs("CutSourcePlatf",0,CutDiamS/2,1*mm,0,twopi);
    
    
    G4SubtractionSolid* tempsol_src = new G4SubtractionSolid("SourcePlatf_temp",solidSourcePlatf_o, solidCutSourcePlatfL,0,G4ThreeVector(0,DetYOffset,1*mm));
    solidSourcePlatf = new G4SubtractionSolid("SourcePlatf_temp1",tempsol_src, solidCutSourcePlatfS,0,G4ThreeVector(0,DetYOffset,-1*mm));
    
    logicSourcePlatf = new G4LogicalVolume(solidSourcePlatf, SourcePlatfMaterial,"SourcePlatf");
    logicSourcePlatf->SetVisAttributes(red);
    physiSourcePlatf = new G4PVPlacement(0,G4ThreeVector(0,0, -1*mm),logicSourcePlatf, "SourcePlatf",logicWorld,false,0);    
    
    
    //45Ca source
    const G4double CaBRInner[] = { 7.5 * mm, 7.5 * mm, 11.25 * mm, 11.25 * mm };
    const G4double CaBROuter[] = { 15. * mm, 15. * mm, 15. * mm, 15. * mm };
    const G4double CaBRzPlane[] = { 0. * mm, 1.0 * mm, 1.0 * mm, 2.6 * mm };
    solidCaBigRing = new G4Polycone("solidCaBigRing", 0. * deg, 360. * deg, 4, CaBRzPlane, CaBRInner, CaBROuter); 
    logicCaBigRing = new G4LogicalVolume(solidCaBigRing, CaRingMaterial,"CaBigRing");

    solidCaSmallRing = new G4Tubs("CaSmallRing",CaHoleDiameter/2,CaSmallRingDiameter/2,CaSmallRingThickness/2,0,twopi);
    logicCaSmallRing = new G4LogicalVolume(solidCaSmallRing, CaRingMaterial,"CaSmallRing");

    solidCaKaptonFoil = new G4Tubs("CaKaptonFoil",0,CaKaptonFoilDiameter/2,CaKaptonFoilThickness/2,0,twopi);
    logicCaKaptonFoil = new G4LogicalVolume(solidCaKaptonFoil, CaKaptonFoilMaterial,"CaKaptonFoil");

    
    if(SourceName=="Ca"){
        ZPos = -1 * mm;
        physiCaBigRing = new G4PVPlacement(0,G4ThreeVector(0,DetYOffset, ZPos),logicCaBigRing, "CaBigRing",logicWorld,false,0);
        ZPos += 1 * mm + MacroGap; //1 mm for the inner thickness of the Ca Big Ring
        physiCaKaptonFoil = new G4PVPlacement(0,G4ThreeVector(0,DetYOffset, ZPos + CaKaptonFoilThickness/2),logicCaKaptonFoil, "CaKaptonFoil",logicWorld,false,0);
        cout << "Ca source position: " << (ZPos + CaKaptonFoilThickness/2)/mm << endl;
        ZPos += CaKaptonFoilThickness + MacroGap;
        physiCaSmallRing = new G4PVPlacement(0,G4ThreeVector(0,DetYOffset, ZPos + CaSmallRingThickness/2),logicCaSmallRing, "CaSmallRing",logicWorld,false,0);
    }
/*
    //Bi-207 source
   
    //source
    const G4double rInnerb[] = { 9.25 * mm, 7.5 * mm, 9.25 * mm };      //blijkbaar moet ik die hier def ?
    const G4double rOuterb[] = { 12.5 * mm, 12.5 * mm, 12.5 * mm, 12.5 * mm };
    const G4double zPlaneb[] = { 0. * mm, 1.5 * mm, (3. - 0.0001) * mm };
    solidBiSource = new G4Polycone("BiSource", 0. * deg, 360. * deg, 3, zPlaneb, rInnerb, rOuterb);
    logicBiSource = new G4LogicalVolume(solidBiSource, BiSourceMaterial, "BiSource");
    logicBiSource->SetVisAttributes(green);

    //Ti window of the Bi209 Source *************
    solidTiWindow = new G4Tubs("TiWindow", 0., TiWindowDiameter / 2. - MacroGap, TiWindowThickness / 2., 0. * deg, 360. * deg);
    logicTiWindow = new G4LogicalVolume(solidTiWindow, TiWindowMaterial, "TiWindow");
    logicTiWindow->SetVisAttributes(green);

    if(SourceName == "Bi") {
        ZDist = SourcePlatfPos + 1 * mm + MacroGap;
        physiBiSource = new G4PVPlacement(0, G4ThreeVector(0, 0, ZDist), logicBiSource, "BiSource", logicWorld, false, 0);
        physiTiWindow = new G4PVPlacement(0, G4ThreeVector(0, 0, ZDist + 1.5*mm), logicTiWindow, "TiWindow", logicWorld, false, 0);
    }
    */
    G4cout << "DetectorConstruction OK!" << G4endl;
    return physical_world;
}

void
  DetectorConstruction::UpdateGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(ConstructCalorimeter());
    G4cout << G4endl << "****** Geometry updated ****** " << G4endl << G4endl;
}


void DetectorConstruction::SetSource(G4String ns){
	SourceName=ns;
	if(SourceName=="Ca"){SourceInd=1;};
	if(SourceName=="Bi"){SourceInd=2;};
}

G4VPhysicalVolume* DetectorConstruction::GetFoilVol(){
    if(SourceInd==1){ //it's the Ca source
        return physiCaKaptonFoil;
    }else{
        return physiTiWindow;
    }
}


