/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified:	2015-08-10 11:05
* Filename:		DetectorConstruction.hh
* Description: 
*************************************************/

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1
#include "globals.hh"
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "Target.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
 
	inline G4double GetTPCR(){return TPC_r;}
	inline G4double GetTPCL(){return TPC_l;}
  private:
 
    // solid volumes
    //
    G4Box* experimentalHall_box;
    G4Tubs* detector_tub;
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* detector_log;
	G4LogicalVolume* target_log;
    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
	G4VPhysicalVolume* detector_phys;
	//TPC parameters
	G4double TPC_r;
	G4double TPC_l;
	Target *atarget;
    G4VPhysicalVolume* target_phys;
};

#endif

