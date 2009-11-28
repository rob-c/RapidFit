/**
  @class Minuit2Wrapper

  A wrapper for Minuit2, implementing IMinimiser

  @author Benjamin M Wynne bwynne@cern.ch
  @date 2009-10-02
 */

#include "Minuit2Wrapper.h"
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnContours.h"
#include <iostream>
#include <limits>
#include "ResultParameterSet.h"
#include <ctime>
#include "StringProcessing.h"

const double MAXIMUM_MINIMISATION_STEPS = 800.0;
const double FINAL_GRADIENT_TOLERANCE = 0.001;
const double STEP_SIZE = 0.01;
const int MINUIT_QUALITY = 2;

//Default constructor
Minuit2Wrapper::Minuit2Wrapper()
{
}

//Destructor
Minuit2Wrapper::~Minuit2Wrapper()
{
}

//Use Migrad to minimise the given function
void Minuit2Wrapper::Minimise( FitFunction * NewFunction )
{
	//Make a wrapper for the function
	function = new Minuit2Function( NewFunction );

	//Minimise the wrapped function
	MnMigrad mig( *function, *( function->GetMnUserParameters() ), MINUIT_QUALITY );

	//Retrieve the result of the fit
	FunctionMinimum minimum = mig( (int)MAXIMUM_MINIMISATION_STEPS, FINAL_GRADIENT_TOLERANCE );

	//Output time information
	time_t timeNow;
	time(&timeNow);
	cout << "Minuit2 finished: " << ctime( &timeNow ) << endl;

	//Make a set of the fitted parameters
	const MnUserParameters * minimisedParameters = &minimum.UserParameters();
	ParameterSet * newParameters = NewFunction->GetParameterSet();
	vector<string> allNames = newParameters->GetAllNames();
	ResultParameterSet * fittedParameters = new ResultParameterSet( allNames );
	for (int nameIndex = 0; nameIndex < allNames.size(); nameIndex++)
	{
		string parameterName = allNames[nameIndex];
		PhysicsParameter * oldParameter = newParameters->GetPhysicsParameter( parameterName );
		double parameterValue = minimisedParameters->Value( parameterName.c_str() );
		double parameterError = minimisedParameters->Error( parameterName.c_str() );

		fittedParameters->SetResultParameter( parameterName, parameterValue, oldParameter->GetOriginalValue(), parameterError,
				-numeric_limits<double>::max(), numeric_limits<double>::max(),
				oldParameter->GetType(), oldParameter->GetUnit() );
	}

	// Get the covariance matrix. Stored as an n*(n+1)/2 vector
	const MnUserCovariance * covMatrix = &minimum.UserCovariance();
	vector<double> covData = covMatrix->Data();	

	//Make the contour plots
	vector< FunctionContour* > allContours;
	const MnContours contoursFromMinuit = MnContours( *function, minimum );
	for ( int plotIndex = 0; plotIndex < contours.size(); plotIndex++ )
	{
		//Find the index (in Minuit) of the parameter names requested for the plot
		int xParameterIndex = StringProcessing::VectorContains( &allNames, &( contours[plotIndex].first ) );
		int yParameterIndex = StringProcessing::VectorContains( &allNames, &( contours[plotIndex].second ) );
		if ( xParameterIndex == -1 )
		{
			cerr << "Contour plotting failed: parameter \"" << contours[plotIndex].first << "\" not found" << endl;
		}
		else if ( yParameterIndex == -1 )
		{
			cerr << "Contour plotting failed: parameter \"" << contours[plotIndex].second << "\" not found" << endl;
		}
		else
		{
			//If the parameters have valid indices, ask minuit to plot them
			int numberOfPoints = 4;
			int iErrf;
			double xCoordinates1[numberOfPoints], yCoordinates1[numberOfPoints];
			double xCoordinates2[numberOfPoints], yCoordinates2[numberOfPoints];

			//One sigma contour
			function->SetSigma(1);
			vector< pair< double, double> > oneSigmaContour = contoursFromMinuit( xParameterIndex, yParameterIndex, numberOfPoints );	

			//Two sigma contour
			function->SetSigma(2);
			vector< pair< double, double> > twoSigmaContour = contoursFromMinuit( xParameterIndex, yParameterIndex, numberOfPoints );	

			//Store the contours
			FunctionContour * newContour = new FunctionContour( contours[plotIndex].first, contours[plotIndex].second, 2 );
			newContour->SetPlot( 1, oneSigmaContour );
			newContour->SetPlot( 2, twoSigmaContour );
			allContours.push_back(newContour);
		}
	}

	//Work out the fit status - possibly dodgy
	int fitStatus;
	if ( !minimum.HasCovariance() )
	{
		fitStatus = 0;
	}
	else if ( !minimum.HasAccurateCovar() )
	{
		fitStatus = 1;
	}
	else if ( minimum.HasMadePosDefCovar() )
	{
		fitStatus = 2;
	}
	else
	{
		fitStatus = 3;
	}

	fitResult = new FitResult( minimum.Fval(), fittedParameters, fitStatus, *( NewFunction->GetPhysicsBottle() ), covData, allContours );
}

//Return the result of minimisation
FitResult * Minuit2Wrapper::GetFitResult()
{
	return fitResult;
}

//Request contour plots
void Minuit2Wrapper::ContourPlots( vector< pair< string, string > > ContourParameters )
{
	contours = ContourParameters;
}
