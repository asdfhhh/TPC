/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified:	2018-12-07 14:28
* Filename:		DataBase.cc
* Description: 
*************************************************/
#include "DataBase.hh"

DataBase::DataBase(int Tname)
{
	printf("Initial data storage......\n");
	char name[100];

	//char bin_name[100];

//root file output
	sprintf(name,"Data_%d.root",Tname );
	//sprintf(bin_name,"Data_%d.bin",Tname );
	cout<<"the ROOT file: "<<name<<" constructed."<<endl;
	//cout<<"the binary file: "<<bin_name<<" constructed."<<endl;
//initial the file output
	hfile = new TFile(name,"RECREATE","ROOT file in Simulation");
	//bin_file.open(bin_name,ios_base::binary);

	printf(".......Initial complete!\n");
}

DataBase::~DataBase()
{
	hfile->cd();
	hfile->Write();
	//bin_file.close();
}

void DataBase::MakeTree()
{
	char Bname[12];
	//construct the tree
	t=new TTree("truth","Truth");
	t->Branch("E",&energy,"energy/D");
	t->Branch("x",&tx,"x/D");
	t->Branch("y",&ty,"y/D");
	t->Branch("z",&tz,"z/D");
        t->Branch("t",&incident_time,"t/D");
	t->Branch("code",&code,"code/I");
	t->Branch("event",&Eve_No,"Eve_No/I");


	d=new TTree("data","Data");
	d->Branch("ADC",&D_energy,"ADC/I");

	v=new TTree("vertex","vertex");
	v->Branch("v_energy",&v_energy,"v_energy/D");
	v->Branch("v_time",&v_time,"v_time/D");
	v->Branch("v_code",&v_code,"v_code/I");
}

 void DataBase::FillTrueth(double energy1,G4ThreeVector pos, int Event_No,double time1,int code1 )
{
	Eve_No=Event_No;
	energy=energy1;
	tx=pos.x();
	ty=pos.y();
	tz=pos.z();
	incident_time=time1;
	code=code1;
	
}

 void DataBase::SaveTrueth()
{
	t->Fill();
}

 void DataBase::FillData(int energy1)
{
	D_energy=energy1;
}

 void DataBase::SaveData()
{
	d->Fill();
}

 void DataBase::FillVertex(int code1,double energy1,double time1)
{
	v_code=code1;
	v_energy=energy1;
	v_time=time1;
}

 void DataBase::SaveVertex()
{
	v->Fill();
}



