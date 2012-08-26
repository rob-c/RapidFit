/**
 @class PDFConfigurator

 This is a class to contain configuration information for a PDF
 The information is taken from the XML  under the <PDF> tag
 Objects of this class are passed to PDF constructors to configure them

 @author Pete Clarke
 @date 2011-05-01
 */

#include "PDFConfigurator.h"
#include "StringProcessing.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using namespace::std;

///..........................................
//Default constructor & destructor
PDFConfigurator::PDFConfigurator() : defaultNames(), replacementNames(), configParameters(), configValues(), input_observable(), input_DataSet(NULL), fitFunction("[0]")
{
}

PDFConfigurator::PDFConfigurator( const PDFConfigurator& input ) :
	defaultNames( input.defaultNames ), replacementNames( input.replacementNames ), configParameters( input.configParameters ), configValues( input.configValues ),
	input_DataSet( input.input_DataSet ), fitFunction( input.fitFunction )
{
}

PDFConfigurator::~PDFConfigurator()
{
}

void PDFConfigurator::addObservableToModel( string inputObservable, IDataSet* inputDataSet )
{
	input_observable = inputObservable;
	input_DataSet = inputDataSet;
}

pair<string, IDataSet*> PDFConfigurator::getObservableToModel()
{
	return make_pair( input_observable, input_DataSet );
}

void PDFConfigurator::setFitFunc( string input )
{
	fitFunction = input;
}

string PDFConfigurator::getFitFunc()
{
	return fitFunction;
}

void PDFConfigurator::appendParameterNames( string names_list )
{
	vector<string> all_params = StringProcessing::SplitString( names_list, ':' );

	if( all_params.size() < 2 )
	{
		cerr << "Cannot Understand AppendParameterNames:\t" << names_list << endl;
		exit(-5434);
	}

	string suffix = all_params.back();

	for( unsigned int i=0; i< (all_params.size()-1); ++i )
	{
		string old_name = all_params[i];
		string new_name = old_name;
		new_name.append( suffix );
		string substitution = old_name;
		substitution.append(":");
		substitution.append( new_name );
		this->addParameterSubstitution( substitution );
	}
}

//...........................................
// Parameter substitution methods
// These allow you to configure a PDF with a substituttion of a default parameter name for another name
// Example :  substitute mass -> massBd

// Method to store a substitution
void PDFConfigurator::addParameterSubstitution( string substitution ) {

	// The string substitution is of the form defaultName:replacementName

	// Find position of ":" character
	size_t pos = substitution.find_first_of(":") ;
	if( pos == string::npos ) {
		cout << "  In PDFConfigurator::addParameterSubstitution : No separator found  in string : " << substitution << endl ;
		exit(1);
	}

	// Break into 2 strings
	string defaultName     =  substitution.substr( 0, pos ) ;
	string replacementName =  substitution.substr( pos+1, string::npos ) ;
	//cout << " In PDFConfigurator::addParameterSubstitution : storing substitution [" << defaultName << "--->" << replacementName << "]" << endl ;
	defaultNames.push_back( defaultName ) ;
	replacementNames.push_back( replacementName ) ;

	return ;
}

// Method to return a substitute name against an input default name.
// If no substitution then the input name is returned unchanged
string PDFConfigurator::getName( string defaultName ) {
	for( unsigned int ii=0; ii<defaultNames.size() ; ii++ ) {
		//cout << " Testing " << defaultName <<  "   against   " << defaultNames[ii] << endl ;
		if( defaultName == defaultNames[ii] ) {
			cout << " PDFConfigurator substituting [" << defaultName << "--->" << replacementNames[ii] << "]" << endl ;
			return replacementNames[ii] ;
		}
	}
	return defaultName ;
}


//............................................
// Configuration parameters

// Method to store a configuration parmeter
// The configuration parameter is of the form parameter:value
void PDFConfigurator::addConfigurationParameter( string configString ) {


	// Find position of ":" character
	size_t pos = configString.find_first_of(":") ;
	if( pos == string::npos ) {
		cout << "  In PDFConfigurator::addConfigurationParameter : No separator found  in string : " << configString << endl ;
		exit(1);
	}

	// Break into 2 strings
	string configParameter  =  configString.substr( 0, pos ) ;
	string configValue		=  configString.substr( pos+1, string::npos ) ;
	cout << " In PDFConfigurator::addConfigurationParameter : storing configParameter [" << configParameter << " : " << configValue << "]" << endl ;
	configParameters.push_back( configParameter ) ;
	configValues.push_back( configValue ) ;

	return ;
}


// Method to return a configuration parameter value
// If not found then returns " "
string PDFConfigurator::getConfigurationValue( string configParam ) {
	for( unsigned int ii=0; ii<configParameters.size() ; ii++ ) {
		//cout << " Testing " << configParam <<  "   against   " << configParameters[ii] << endl ;
		if( configParam == configParameters[ii] ) {
			//cout << " PDFConfiguratorgetConfigurationValue setting [" << configParam << "--->" << configValues[ii] << "]" << endl ;
			return configValues[ii] ;
		}
	}
	return string("") ;
}

// Method to check for a configuration parameter value
bool PDFConfigurator::hasConfigurationValue( string configParam, string paramValue ) {
	for( unsigned int ii=0; ii<configParameters.size() ; ii++ ) {
		//cout << " Testing " << configParam <<  "   against   " << configParameters[ii] << endl ;
		if( configParam == configParameters[ii] ) {
			cout << " PDFConfigurator::hasConfigurationValue found [" << configParam << " == " << configValues[ii] << "]" << endl ;
			return ( configValues[ii] == paramValue ) ;
		}
	}
	return false ;
}

// Method to check for a configuration parameter value boolean
bool PDFConfigurator::isTrue( string configParam ) {
	for( unsigned int ii=0; ii<configParameters.size() ; ii++ ) {
		//cout << " Testing " << configParam <<  "   against   " << configParameters[ii] << endl ;
		if( configParam == configParameters[ii] ) {
			bool returnValue =  ( strcasecmp( configValues[ii].c_str() , "TRUE" ) == 0 )  ;
			cout << " PDFConfigurator::isTrue found [" << configParam << " == " << returnValue << " ]" << endl ;
			return returnValue ;
		}
	}
	return false ;
}

string PDFConfigurator::XML() const
{
	stringstream xml;
	for( unsigned int i=0; i< configParameters.size(); ++i )
	{
		xml << "\t<ConfigurationParameter>" << configParameters[i] << ":" << configValues[i] << "</ConfigurationParameter>" << endl;
	}
	for( unsigned int i=0; i< defaultNames.size(); ++i )
	{
		xml << "\t<ParameterSubstitution>" << defaultNames[i] << ":" << replacementNames[i] << "</ParameterSubstitution>" << endl;
	}
	return xml.str();
}


