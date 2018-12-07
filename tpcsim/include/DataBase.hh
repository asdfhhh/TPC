/************************************************
* Author: Fan Ruirui
* email:fanrr@ihep.ac.cn
* Last modified:	2018-12-07 14:28
* Filename:		DataBase.hh
* Description: 
*************************************************/
#ifndef DataBase_h
#define DataBase_h 1
#include "globals.hh"
#include "G4UnitsTable.hh"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TTree.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class DataBase
{
public:
	DataBase(int Run_No);
	~DataBase();

	void MakeTree(int Det_NUM);
	void FillTrueth(double delta_energy,G4ThreeVector pos, int Event_No, int Det_ID);
	void FillData(int total_energy,int Det_ID);

	void SaveData();
	void SaveTrueth();

private: 
	TTree*t;
	TTree*d;
	char Hname[100];
	TFile* hfile;
	double *energy;
	double *tx;
	double *ty;
	double *tz;
	int Eve_No;
	int *D_energy;
	ofstream bin_file;
};

#endif /*DataBase_h*/

