/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified: 2015-08-10 11:03
* Filename: SteppingAction.cc
* Description: 
*************************************************/
#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(RunAction*rct)                                         
{
	aRun=rct;	

 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	DataBase*aData=aRun->GetDataBase();
	G4String PreV=aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName();
	if(PreV!="det")return;
	G4String PostV=aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();
	if(PostV!="Target")return;
	G4Track*aTrack=aStep->GetTrack();
	if(aTrack->GetParentID() == 0)
	{
		int code=aTrack->GetParticleDefinition()->GetPDGEncoding();
		double energy=(aTrack->GetVertexKineticEnergy())/keV;
		double time=(aStep->GetPostStepPoint()->GetGlobalTime())/ns;
		aData->FillVertex(code,energy,time);
		aData->SaveVertex();
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
