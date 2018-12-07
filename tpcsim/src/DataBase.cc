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
	delete energy;
	delete D_energy;
}

void DataBase::MakeTree(int det_num)
{
	int ch_num=det_num;
	energy=new double[ch_num];
	tx=new double[ch_num];
	ty=new double[ch_num];
	tz=new double[ch_num];
	D_energy=new int[ch_num];
	char Bname[12];
	//construct the tree
	t=new TTree("truth","Truth");
	for (int i= 0; i< ch_num; i++)
	{
		sprintf(Hname,"t_Ch%d",i+1); 
		sprintf(Bname,"energy%d/D",i+1);
		t->Branch(Hname,&energy[i],Bname);
		sprintf(Hname,"x%d",i+1); 
		sprintf(Bname,"x%d/D",i+1);
		t->Branch(Hname,&tx[i],Bname);
		sprintf(Hname,"y%d",i+1); 
		sprintf(Bname,"y%d/D",i+1);
		t->Branch(Hname,&ty[i],Bname);
		sprintf(Hname,"z%d",i+1); 
		sprintf(Bname,"z%d/D",i+1);
		t->Branch(Hname,&tz[i],Bname);
	}
	t->Branch("event",&Eve_No,"Eve_No/I");


	d=new TTree("data","Data");
	for (int i= 0; i< ch_num; i++)
	{
		sprintf(Hname,"d_Ch%d",i+1);
		sprintf(Bname,"D_energy%d/I",i+1);
		d->Branch(Hname,&D_energy[i],Bname);
	}
}

 void DataBase::FillTrueth(double energy1,G4ThreeVector pos, int Event_No, int D_id1)
{
	Eve_No=Event_No;
	energy[D_id1]=energy1;
	tx[D_id1]=pos.x();
	ty[D_id1]=pos.y();
	tz[D_id1]=pos.z();
}

 void DataBase::SaveTrueth()
{
	t->Fill();
}

 void DataBase::FillData(int energy1,int D_id1)
{
	D_energy[D_id1]=energy1;
}

 void DataBase::SaveData()
{
	d->Fill();
}





