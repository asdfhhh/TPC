/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified:	2015-12-24 14:46
* Filename:		PrimaryGeneratorAction.hh
* Description: 
*************************************************/

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "TH1F.h"


class G4VPrimaryGenerator;
class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction();
	void GeneratePrimaries(G4Event* anEvent);
private:
	G4ParticleGun* particleGun;
	TH1F*Gen_list;
	void InitialGenList();
};
#endif


