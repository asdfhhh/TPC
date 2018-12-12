
#include "PrimaryGenerator.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::~PrimaryGenerator()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{	
	//vertex A first pulse
	G4double x = 0;
	G4double y = 0;
	G4double z = 55*m;  //z uniform in (-zmax, +zmax)
	G4ThreeVector positionA(x,y,z);
  	G4double timeA = 0*s;
  	// 
  	G4PrimaryVertex* vertexA = new G4PrimaryVertex(positionA, timeA);
  	//generate particles
  	//white neutrons
  	const G4int N_num=10;
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particleDefinition= particleTable->FindParticle(particleName="neutron");
	G4PrimaryParticle* particle1[N_num];
	for(int i=0;i<N_num;i++)
	{
		particle1[i]= new G4PrimaryParticle(particleDefinition);	
		particle1[i]->SetMomentumDirection(G4ThreeVector(0,0,-1));	
		particle1[i]->SetKineticEnergy(Gen_list->GetRandom()*keV);
		//particle1[i]->SetKineticEnergy(1*keV);
		vertexA->SetPrimary(particle1[i]);
	}
	//gamma flash
  	const G4int G_num=10;
	particleDefinition= particleTable->FindParticle(particleName="gamma");
	G4PrimaryParticle* particle2[G_num];
	for(int i=0;i<G_num;i++)
	{
		particle2[i]= new G4PrimaryParticle(particleDefinition);	
		particle2[i]->SetMomentumDirection(G4ThreeVector(0,0,-1));	
		particle2[i]->SetKineticEnergy(1000*keV);
		vertexA->SetPrimary(particle2[i]);
	}
	//generate a vertex	
	event->AddPrimaryVertex(vertexA);
	
		//vertex A second pulse
	G4ThreeVector positionB(x,y,z);
  	G4double timeB = 410*ns;
  	// 
  	G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, timeB);
  	//generate particles
  	//white neutrons
	particleDefinition= particleTable->FindParticle(particleName="neutron");
	G4PrimaryParticle* particle3[N_num];
	for(int i=0;i<N_num;i++)
	{
		particle3[i]= new G4PrimaryParticle(particleDefinition);	
		particle3[i]->SetMomentumDirection(G4ThreeVector(0,0,-1));	
		particle3[i]->SetKineticEnergy(Gen_list->GetRandom()*keV);
		vertexB->SetPrimary(particle3[i]);
	}
	//gamma flash
	particleDefinition= particleTable->FindParticle(particleName="gamma");
	G4PrimaryParticle* particle4[G_num];
	for(int i=0;i<G_num;i++)
	{
		particle4[i]= new G4PrimaryParticle(particleDefinition);	
		particle4[i]->SetMomentumDirection(G4ThreeVector(0,0,-1));	
		particle4[i]->SetKineticEnergy(1000*keV);
		vertexB->SetPrimary(particle4[i]);
	}
	//generate a vertex	
	event->AddPrimaryVertex(vertexB);
}
void PrimaryGenerator::InitialGenList()
{
	//create the neutron list histogram
	Gen_list = new TH1F("nlist", "the neutron spectrum in keV", 200, 0, 450000);
	ifstream file_in("n_list.txt");
	float energy;
	double number;
	while (!file_in.eof())
	{
		file_in >> energy;
		file_in >> number;
		Gen_list->Fill(energy, number);
	}
	file_in.close();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
