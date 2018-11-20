/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified:	2015-11-27 11:06
* Filename:		Target.cc
* Description: 
*************************************************/
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "Target.hh"
#include "DetSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
using namespace std;

Target::Target()
:  T1_tub(0),T2_tub(0),aTarget_tub(0),
T1_log(0),T2_log(0),aTarget_log(0),
T1_phys(0),T2_phys(0),aTarget_phys(0)
{
	d1=5*um;
	d2=100*um;
	R=4*cm;
	Target_len=2*d1+d2;
}

Target::~Target()
{ 
}

G4LogicalVolume* Target::Construct()
{ 
//materials
	G4double a;  // atomic mass
	G4double z;  // atomic number
	G4double density;
	G4String name, symbol;             // a=mass of a mole;
	G4Material* Vacuum ;
	G4int iz, n;
	G4int ncomponents, natoms;
	G4double abundance, fractionmass;
	G4double temperature, pressure;
	Vacuum=new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
	G4NistManager* man = G4NistManager::Instance();
	man->SetVerbose(0);
//construction G4_POLYETHYLENE
	G4Material* PE= man->FindOrBuildMaterial("G4_POLYETHYLENE");
	G4Material* M_substain= man->FindOrBuildMaterial("G4_MYLAR");
//add the Isotope Li
	G4Isotope*Li6=new G4Isotope(name="Li6", iz=3, n=6, a=6.015*g/mole);
	G4Isotope*Li7=new G4Isotope(name="Li7", iz=3, n=7, a=7.016*g/mole);
	G4Element* elLi  = new G4Element(name="element Li", symbol="Li", ncomponents=1);
	//elLi->AddIsotope(Li6, abundance= 7.59*perCent);
	//elLi->AddIsotope(Li7, abundance= 92.41*perCent);
	elLi->AddIsotope(Li6, abundance= 100*perCent);
	density = 0.534*g/cm3;
	G4Material* Li_t = new G4Material(name="target Li", density, ncomponents=1);
	Li_t->AddElement(elLi, 100.00*perCent);
//add the isotope Mg25
	G4Isotope*Mg25=new G4Isotope(name="Mg25", iz=12, n=25, a=24.985*g/mole);
	G4Element* elMg  = new G4Element(name="element Mg", symbol="Mg", ncomponents=1);
	elMg->AddIsotope(Mg25, abundance= 100*perCent);
	density = 1.738*g/cm3;
        G4Material* Mg_t = new G4Material(name="target Mg", density, ncomponents=1);
        Mg_t->AddElement(elMg, 100.00*perCent);
//add the isotope Fe56
        G4Isotope*Fe56=new G4Isotope(name="Fe56", iz=26, n=56, a=55.935*g/mole);
        G4Element* elFe  = new G4Element(name="element Fe", symbol="Fe", ncomponents=1);
	elFe->AddIsotope(Fe56, abundance= 100*perCent);
        density = 7.86*g/cm3;
	G4Material* Fe_t = new G4Material(name="target Fe", density, ncomponents=1);
	Fe_t->AddElement(elFe, 100.00*perCent);
//detector construction
	T1_tub=new G4Tubs("T1_tub",0,R,d1/2,0,2*pi);
	T2_tub=new G4Tubs("T2_tub",0,R,d2/2,0,2*pi);
	aTarget_tub=new G4Tubs("T_tub",0,R,Target_len/2,0,2*pi);
 
	T1_log=new G4LogicalVolume(T1_tub,Li_t,"target_log");
        T2_log=new G4LogicalVolume(T2_tub,Vacuum,"substain_log");
	aTarget_log=new G4LogicalVolume(aTarget_tub,Vacuum,"aTarget_log");

	new G4PVPlacement(0,G4ThreeVector(0,0,(d1+d2)/2),T1_log,"Target",aTarget_log,false,0);
	new G4PVPlacement(0,G4ThreeVector(0,0,0),T2_log,"substain",aTarget_log,false,0);
        new G4PVPlacement(0,G4ThreeVector(0,0,-(d1+d2)/2),T1_log,"Target",aTarget_log,false,0);

  
//set colour
	G4VisAttributes* VisAtt1= new G4VisAttributes(G4Colour(1,0,0));//red
	G4VisAttributes* VisAtt2= new G4VisAttributes(G4Colour(0,0,1));//blue


	T1_log->SetVisAttributes(VisAtt1);
	T2_log->SetVisAttributes(VisAtt2);
	aTarget_log->SetVisAttributes (G4VisAttributes::Invisible);
	return aTarget_log;
}
