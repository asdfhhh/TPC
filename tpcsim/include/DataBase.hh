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

	void MakeTree();
	void FillTrueth(double energy1,G4ThreeVector pos, int Event_No,double time1,int code1 );
	void FillData(int total_energy);
	void FillVertex(int code,double energy,double time) ;

	void SaveData();
	void SaveTrueth();	
	void SaveVertex();

private: 
	TTree*t;
	TTree*d;
	TTree*v;
	TFile* hfile;
	double energy;
	double tx;
	double ty;
	double tz;
	int Eve_No;
	int D_energy;
	int code;	
	ofstream bin_file;	
	double incident_time;
	double v_energy;
	double v_time;	
	int v_code;

};

#endif /*DataBase_h*/

