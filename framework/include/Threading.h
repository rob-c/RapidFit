//	Class designed to contain common structs/functions required for multi-threading the fits in RapidFit

#ifndef RAPIDFIT_THREADING_H
#define RAPIDFIT_THREADING_H

#include "DataPoint.h"
#include "IDataSet.h"
#include "IPDF.h"
#include "RapidFitIntegrator.h"

#include <vector>
#include <string>

//      Threading Struct which contains all of the objects required for running multiple concurrent fits to data subsets
//	This object is useful as multiple bits of information need to be provided to the running thread
struct Fitting_Thread{
	explicit Fitting_Thread() : dataSubSet(), fittingPDF(NULL), useWeights(false), weightName(), dataPoint_Result(), FitBoundary(NULL), ResultIntegrator(NULL) {}
	vector<DataPoint*> dataSubSet;
	IPDF* fittingPDF;
	bool useWeights;
	string weightName;
	vector<double> dataPoint_Result;
	PhaseSpaceBoundary* FitBoundary;
	RapidFitIntegrator* ResultIntegrator;
	private:
		Fitting_Thread(const Fitting_Thread&);
		Fitting_Thread& operator=(const Fitting_Thread&);
};

class Threading
{
	public:
		//	Number of cores on machine this is compiled for
		static int numCores();

		//	Split the data into subset(s) with a safe default
		static vector<vector<DataPoint*> > divideData( IDataSet*, int=1 );
	private:
		Threading();
};

#endif