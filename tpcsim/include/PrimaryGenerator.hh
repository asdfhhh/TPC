#ifndef PrimaryGenerator_h
#define PrimaryGenerator_h 1

#include "G4VPrimaryGenerator.hh"
#include "TH1F.h"
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGenerator : public G4VPrimaryGenerator
{
  public:
    PrimaryGenerator();    
   ~PrimaryGenerator();

  public:
    virtual void GeneratePrimaryVertex(G4Event*);	
	TH1F*Gen_list;
	void InitialGenList();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
