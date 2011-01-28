/** @class Bd2JpsiKstar_sWave Bd2JpsiKstar_sWave.cpp
 *
 *  RapidFit PDF for Bd2JpsiPhi with average angular acceptance input as a paramter
 *
 *  @author Ailsa Sparkes asparkes@cern.ch
 *  @date 2011-01-26
 */

#include "Bd2JpsiKstar_sWave.h"
#include "Mathematics.h"
#include <iostream>
#include "math.h"
#include "TMath.h"

//Constructor
Bd2JpsiKstar_sWave::Bd2JpsiKstar_sWave() :
	// Physics parameters
	gammaName     ( "gamma" )
	, deltaMName    ( "deltaM")
	, delta_paraName( "delta_para" )
	, delta_perpName( "delta_perp" )
	, delta_sName( "delta_s" )
	, Aperp_sqName  ( "Aperp_sq" )
	, Apara_sqName  ( "Apara_sq" )
	, As_sqName	( "As_sq" )
	, angAccI1Name	( "angAccI1" )
	, angAccI2Name	( "angAccI2" )
	, angAccI3Name	( "angAccI3" )
	, angAccI4Name	( "angAccI4" )
	, angAccI5Name	( "angAccI5" )
	, angAccI6Name	( "angAccI6" )
	, angAccI7Name  ( "angAccI7" )
	, angAccI8Name  ( "angAccI8" )
	, angAccI9Name  ( "angAccI9" )
	, angAccI10Name  ( "angAccI10" )
	, timeRes1Name	( "timeResolution1" )
	, timeRes2Name	( "timeResolution2" )
	, timeRes1FractionName	( "timeResolution1Fraction" )

	// Observables (What we want to gain from the pdf after inserting physics parameter values)
	, timeName	( "time" )
	, cosThetaName	( "cosTheta" )
	, phiName	( "phi" )
	, cosPsiName	( "cosPsi" )
	//, timeres	( "resolution" )
	, normalisationCacheValid(false)
, evaluationCacheValid(false)
{
	MakePrototypes();
}

//Make the data point and parameter set
void Bd2JpsiKstar_sWave::MakePrototypes()
{
	//Make the DataPoint prototype
	allObservables.push_back( timeName );
	allObservables.push_back( cosThetaName );
	allObservables.push_back( phiName );
	allObservables.push_back( cosPsiName );

	// Need to think about additional parameters like
	// event-by-event propertime resolution and acceptance.
	// This will require event-by-event PDF normalisation,
	// but we are already doing this for tagging.

	//Make the parameter set
	vector<string> parameterNames;
	parameterNames.push_back( gammaName );
	parameterNames.push_back( Apara_sqName );
	parameterNames.push_back( Aperp_sqName );
	parameterNames.push_back( As_sqName );
	parameterNames.push_back( delta_paraName );
	parameterNames.push_back( delta_perpName );
	parameterNames.push_back( deltaMName );
	parameterNames.push_back( delta_sName );
	parameterNames.push_back( timeRes1Name );
	parameterNames.push_back( timeRes2Name );
	parameterNames.push_back( timeRes1FractionName );
	parameterNames.push_back( angAccI1Name );
	parameterNames.push_back( angAccI2Name );
	parameterNames.push_back( angAccI3Name );
	parameterNames.push_back( angAccI4Name );
	parameterNames.push_back( angAccI5Name );
	parameterNames.push_back( angAccI6Name );
	parameterNames.push_back( angAccI7Name );
	parameterNames.push_back( angAccI8Name );
	parameterNames.push_back( angAccI9Name );
	parameterNames.push_back( angAccI10Name );
allParameters = *( new ParameterSet(parameterNames) );

	valid = true;
}

//Destructor
Bd2JpsiKstar_sWave::~Bd2JpsiKstar_sWave()
{
}

//Not only set the physics parameters, but indicate that the cache is no longer valid
bool Bd2JpsiKstar_sWave::SetPhysicsParameters( ParameterSet * NewParameterSet )
{
	normalisationCacheValid = false;
	evaluationCacheValid = false;
	bool isOK = allParameters.SetPhysicsParameters(NewParameterSet);
        // Physics parameters (the stuff you want to extract from the physics model by plugging in the experimental measurements)
        gamma      = allParameters.GetPhysicsParameter( gammaName )->GetValue();
        deltaMs    = allParameters.GetPhysicsParameter( deltaMName )->GetValue();
        Aperp_sq   = allParameters.GetPhysicsParameter( Aperp_sqName )->GetValue();
        Apara_sq   = allParameters.GetPhysicsParameter( Apara_sqName )->GetValue();
	As_sq   = allParameters.GetPhysicsParameter( As_sqName )->GetValue();
	delta_para = allParameters.GetPhysicsParameter( delta_paraName )->GetValue();
	delta_perp = allParameters.GetPhysicsParameter( delta_perpName )->GetValue();
	delta_s = allParameters.GetPhysicsParameter( delta_sName )->GetValue();
        timeRes1 = allParameters.GetPhysicsParameter( timeRes1Name )->GetValue();
        timeRes2 = allParameters.GetPhysicsParameter( timeRes2Name )->GetValue();
        timeRes1Frac = allParameters.GetPhysicsParameter( timeRes1FractionName )->GetValue();
        angAccI1 = allParameters.GetPhysicsParameter( angAccI1Name )->GetValue();
        angAccI2 = allParameters.GetPhysicsParameter( angAccI2Name )->GetValue();
        angAccI3 = allParameters.GetPhysicsParameter( angAccI3Name )->GetValue();
        angAccI4 = allParameters.GetPhysicsParameter( angAccI4Name )->GetValue();
        angAccI5 = allParameters.GetPhysicsParameter( angAccI5Name )->GetValue();
        angAccI6 = allParameters.GetPhysicsParameter( angAccI6Name )->GetValue();
	angAccI7 = allParameters.GetPhysicsParameter( angAccI7Name )->GetValue();
	angAccI8 = allParameters.GetPhysicsParameter( angAccI8Name )->GetValue();
	angAccI9 = allParameters.GetPhysicsParameter( angAccI9Name )->GetValue();
	angAccI10 = allParameters.GetPhysicsParameter( angAccI10Name )->GetValue();

Azero_sq = 1 - Aperp_sq - Apara_sq;
		AparaAperp = sqrt(Apara_sq)*sqrt(Aperp_sq);
        	AzeroApara = sqrt(Azero_sq)*sqrt(Apara_sq);
        	AzeroAperp = sqrt(Azero_sq)*sqrt(Aperp_sq);
		AparaAs    = sqrt(Apara_sq)*sqrt(As_sq);
		AperpAs	   = sqrt(Aperp_sq)*sqrt(As_sq);
		AzeroAs    = sqrt(Azero_sq)*sqrt(As_sq);

	return isOK;
}

//Return a list of parameters not to be integrated
vector<string> Bd2JpsiKstar_sWave::GetDoNotIntegrateList()
{
	vector<string> doNotIntList;
	return doNotIntList;
}

//Calculate the function value
double Bd2JpsiKstar_sWave::Evaluate(DataPoint * measurement)
{
	time = measurement->GetObservable( timeName )->GetValue();
        cosTheta = measurement->GetObservable( cosThetaName )->GetValue();
        phi      = measurement->GetObservable( phiName )->GetValue();
        cosPsi   = measurement->GetObservable( cosPsiName )->GetValue();

	//cout << gamma << " " << Aperp_sq << " " << Azero_sq << endl;

        if(timeRes1Frac >= 0.9999)
	{
                // Set the member variable for time resolution to the first value and calculate
                timeRes = timeRes1;
                return buildPDFnumerator();
        }
        else
	{
                // Set the member variable for time resolution to the first value and calculate
                timeRes = timeRes1;
                double val1 = buildPDFnumerator();
                // Set the member variable for time resolution to the second value and calculate
                timeRes = timeRes2;
                double val2 = buildPDFnumerator();
                return timeRes1Frac*val1 + (1. - timeRes1Frac)*val2;
        }
}

double Bd2JpsiKstar_sWave::buildPDFnumerator()
{
	// The angular functions f1->f6 as defined in roadmap Table 1.(same for Kstar)
	double f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
	Mathematics::getBs2JpsiPhiAngularFunctionsWithSwave( f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, cosTheta, phi, cosPsi );

	// The time dependent amplitudes as defined in roadmap Eqns 48 -> 59  //No tagging so only need 2 (h± pg 72)
	// First for the B
	double AzeroAzeroB, AparaAparaB, AperpAperpB, AsAsB;
	double ImAparaAperpB, ReAzeroAparaB, ImAzeroAperpB;
	double ReAparaAsB, ImAperpAsB, ReAzeroAs;

	getTimeDependentAmplitudes( AzeroAzeroB, AparaAparaB, AperpAperpB
			, ImAparaAperpB, ReAzeroAparaB, ImAzeroAperpB
			, AsAsB, ReAparaAsB, ImAperpAsB, ReAzeroAs
							   );


	double v1 = f1 * AzeroAzeroB
		+ f2 * AparaAparaB
		+ f3 * AperpAperpB
		+ f4 * ImAparaAperpB
		+ f5 * ReAzeroAparaB
		+ f6 * ImAzeroAperpB
		+ f7 * AsAsB
		+ f8 * ReAparaAsB
		+ f9 * ImAperpAsB
		+ f10 * ReAzeroAs;

	/*
	if (isnan(v1))
	{
		cout << f1 << " " << f2 << " " << f3 << " " <<f4 << " " << f5 << " " << f6 << endl;
			cout << AzeroAzeroB << " " << AperpAperpB << " " << AparaAparaB << " " << ImAparaAperpB << " " << ReAzeroAparaB << " " << ImAzeroAperpB << endl;
	}
	 */
		return v1;
}


double Bd2JpsiKstar_sWave::Normalisation(DataPoint * measurement, PhaseSpaceBoundary * boundary)
{

	IConstraint * timeBound = boundary->GetConstraint("time");
	if ( timeBound->GetUnit() == "NameNotFoundError" )
	{
		cerr << "Bound on time not provided" << endl;
		return -1.;
	}
	else
	{
		tlow = timeBound->GetMinimum();
		thigh = timeBound->GetMaximum();
	}


        if(timeRes1Frac >= 0.9999)
        {
                // Set the member variable for time resolution to the first value and calculate
                timeRes = timeRes1;
                return buildPDFdenominator();
        }
        else
        {
                // Set the member variable for time resolution to the first value and calculate
                timeRes = timeRes1;
                double val1 = buildPDFdenominator();
                // Set the member variable for time resolution to the second value and calculate
                timeRes = timeRes2;
                double val2 = buildPDFdenominator();
                return timeRes1Frac*val1 + (1. - timeRes1Frac)*val2;
        }
}

double Bd2JpsiKstar_sWave::buildPDFdenominator()
{

	if (!normalisationCacheValid)
	{
		// The integrals of the time dependent amplitudes as defined in roadmap Eqns 48 -> 59
		getTimeAmplitudeIntegrals(  cachedAzeroAzeroIntB
				, cachedAparaAparaIntB
				, cachedAperpAperpIntB
				, cachedAparaAperpIntB
				, cachedAzeroAparaIntB
				, cachedAzeroAperpIntB
				, cachedAsAsIntB
				, cachedAparaAsIntB
				, cachedAperpAsIntB
				, cachedAzeroAsIntB
						);


		normalisationCacheValid = true;
	}

	//cout << gamma << endl;

	double v1 = cachedAzeroAzeroIntB * angAccI1
		+ cachedAparaAparaIntB * angAccI2
		+ cachedAperpAperpIntB * angAccI3
		+ cachedAparaAperpIntB * angAccI4
		+ cachedAzeroAparaIntB * angAccI5
		+ cachedAzeroAperpIntB * angAccI6
		+ cachedAsAsIntB * angAccI7
		+ cachedAparaAsIntB * angAccI8
		+ cachedAperpAsIntB * angAccI9
		+ cachedAzeroAsIntB * angAccI10;

	return v1;
}

void Bd2JpsiKstar_sWave::getTimeDependentAmplitudes(
		  double & AzeroAzero
		, double & AparaApara
		, double & AperpAperp
		, double & ImAparaAperp
		, double & ReAzeroApara
		, double & ImAzeroAperp
		, double & AsAs
		, double & ReAparaAs
		, double & ImAperpAs
		, double & ReAzeroAs
		)
{
	// Quantities depending only on physics parameters can be cached
	if ( !evaluationCacheValid )
	{
		cachedAzero = sqrt( Azero_sq );
		cachedApara = sqrt( Apara_sq );
		cachedAperp = sqrt( Aperp_sq );
		cachedAs = sqrt (As_sq);

		cachedSinDeltaPerpPara	= sin( delta_perp - delta_para );
		cachedCosDeltaPara	= cos( delta_para );
		cachedSinDeltaPerp	= sin( delta_perp );
		cachedCosDeltaParaS	= cos( delta_para - delta_s );
		cachedSinDeltaPerpS 	= sin( delta_perp - delta_s );
		cachedCosDeltaS		= cos( delta_s);

		evaluationCacheValid = true;
	}


	//cout << gamma << " " << deltaGamma << " " << Azero_sq << " " << Aperp_sq << endl;

	//cout << cachedExpCosh << " " << cachedExpSinh << " " << cachedExpCos << " " << cachedExpSin << endl;


	// Now calculate the amplitudes

	double Exp = Mathematics::Exp(time, gamma, timeRes);

	AzeroAzero = Azero_sq * Exp;  // changed- see note 2009-015 eq 11-13
        AparaApara = Apara_sq * Exp;  //
        AperpAperp = Aperp_sq * Exp;  //
	AzeroAzero = Azero_sq * Exp;

        ImAparaAperp = cachedApara*cachedAperp * cachedSinDeltaPerpPara * Exp;    //See http://indico.cern.ch/getFile.py/access?contribId=4&resId=0&materialId=slides&confId=33933 page14

	ReAzeroApara = cachedAzero*cachedApara * cachedCosDeltaPara * Exp;

        ImAzeroAperp = cachedAzero*cachedAperp * cachedSinDeltaPerp * Exp;

	ReAparaAs = cachedApara*cachedAs * cachedCosDeltaParaS * Exp; //AILSA_ NOT SURE

	ImAperpAs = cachedAperp*cachedAs * cachedSinDeltaPerpS * Exp; //AILSA

	ReAzeroAs = cachedAzero*cachedAs * cachedCosDeltaS * Exp; //AILSA

	//if ( isnan(ImAparaAperp)) cout << Azero_sq << " " << Apara_sq << " " << Aperp_sq << " " << Exp << endl;

	return;
}

void Bd2JpsiKstar_sWave::getTimeAmplitudeIntegrals(
		  double & AzeroAzeroInt
		, double & AparaAparaInt
		, double & AperpAperpInt
		, double & AparaAperpInt
		, double & AzeroAparaInt
		, double & AzeroAperpInt
		, double & AsAsInt
		, double & AparaAsInt
		, double & AperpAsInt
		, double & AzeroAsInt
	)
{

	double ExpInt = Mathematics::ExpInt(tlow, thigh, gamma, timeRes);

		AzeroAzeroInt = Azero_sq * ExpInt;
	        AparaAparaInt = Apara_sq  * ExpInt;
       		AperpAperpInt = Aperp_sq * ExpInt;
		AsAsInt = As_sq * ExpInt;

		AparaAperpInt = AparaAperp * cachedSinDeltaPerpPara * ExpInt;

		AzeroAparaInt = AzeroApara * cachedCosDeltaPara * ExpInt;

		AzeroAperpInt = AzeroAperp * cachedSinDeltaPerp * ExpInt;

		AparaAsInt = AparaAs * cachedCosDeltaParaS * ExpInt;

		AperpAsInt = AperpAs * cachedSinDeltaPerpS * ExpInt;

		AzeroAsInt = AzeroAs * cachedCosDeltaS * ExpInt;

	return;
}