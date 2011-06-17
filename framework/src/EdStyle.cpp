// $Id: EdStyle.cpp,v 1.1 2009/11/10 10:35:46 gcowan Exp $
/**
  @class EdStyle

  Default style for RapidFit plots

  @author Greig A Cowan greig.alan.cowan@cern.ch
  @date 2009-10-02
 */

// Include files

//	ROOT Headers
#include "TLatex.h"
#include "TText.h"
#include "TPaveText.h"
#include "TROOT.h"
//	RapidFit Headers
#include "EdStyle.h"
//	System Headers
#include <iostream>
#include <string.h>

using namespace std;

//-----------------------------------------------------------------------------
// Implementation file for class : EdStyle
//
// 2007-12-07 : Greig Cowan
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

EdStyle::EdStyle( ) : edStyle(), icol(), font(), tsize()
{}

EdStyle::~EdStyle(){}

void EdStyle::SetStyle()
{

	// use helvetica-bold-r-normal, precision 2 (rotatable)
	Int_t lhcbFont = 62;
	// line thickness
	Width_t lhcbWidth = 2; //Width_t is a SHORT INT, not a double
	//Double_t lhcbWidth = 1.75;

	// use plain black on white colors
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetPalette(1);
	//gStyle->SetTitleColor(0);
	//gStyle->SetFillColor(0);

	// set the paper & margin sizes
	gStyle->SetPaperSize(Float_t(20),Float_t(26));
	gStyle->SetPadTopMargin(Float_t(0.05));
	gStyle->SetPadRightMargin(Float_t(0.05)); // increase for colz plots!!
	gStyle->SetPadBottomMargin(Float_t(0.16));
	gStyle->SetPadLeftMargin(Float_t(0.14));

	// use large fonts
	gStyle->SetTextFont(Font_t(lhcbFont));
	gStyle->SetTextSize(Float_t(0.08));
	gStyle->SetLabelFont(Style_t(lhcbFont),"x");
	gStyle->SetLabelFont(Style_t(lhcbFont),"y");
	gStyle->SetLabelFont(Style_t(lhcbFont),"z");
	gStyle->SetLabelSize(Float_t(0.05),"x");
	gStyle->SetLabelSize(Float_t(0.05),"y");
	gStyle->SetLabelSize(Float_t(0.05),"z");
	gStyle->SetTitleFont(Style_t(lhcbFont));
	gStyle->SetTitleSize(Float_t(0.05),"x");
	gStyle->SetTitleSize(Float_t(0.05),"y");
	gStyle->SetTitleSize(Float_t(0.05),"z");

	// use bold lines and markers
	gStyle->SetLineWidth(lhcbWidth);
	gStyle->SetFrameLineWidth(3);
	gStyle->SetHistLineWidth(lhcbWidth);
	gStyle->SetFuncWidth(lhcbWidth);
	gStyle->SetGridWidth(lhcbWidth);
	gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
	//gStyle->SetMarkerStyle(15);
	gStyle->SetMarkerStyle(20);
	gStyle->SetMarkerSize(1.5);

	// label offsets
	gStyle->SetLabelOffset(Float_t(0.015));

	// by default, do not display histogram decorations:
	gStyle->SetOptStat(0);
	gStyle->SetOptStat(1110);  // show only nent, mean, rms
	//gStyle->SetOptTitle(0);
	gStyle->SetOptFit(0);
	//gStyle->SetOptFit(1011); // show probability, parameters and errors

	// look of the statistics box:
	gStyle->SetStatBorderSize(1);
	gStyle->SetStatFont(Style_t(lhcbFont));
	gStyle->SetStatFontSize(Float_t(0.05));
	gStyle->SetStatX(Float_t(0.9));
	gStyle->SetStatY(Float_t(0.9));
	gStyle->SetStatW(Float_t(0.25));
	gStyle->SetStatH(Float_t(0.15));

	// put tick marks on top and RHS of plots
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);

	// histogram divisions: only 5 in x to avoid label overlaps
	gStyle->SetNdivisions(505,"x");
	gStyle->SetNdivisions(510,"y");

	TPaveText *lhcbName = new TPaveText(0.65,0.8,0.9,0.9,"BRNDC");
	lhcbName->SetFillColor(0);
	lhcbName->SetTextAlign(12);
	lhcbName->SetBorderSize(0);
	lhcbName->AddText("LHCb");

	TPaveText *lhcbPrelimR = new TPaveText(0.70 - gStyle->GetPadRightMargin(),
			0.80 - gStyle->GetPadTopMargin(),
			0.95 - gStyle->GetPadRightMargin(),
			0.85 - gStyle->GetPadTopMargin(),
			"BRNDC");
	lhcbPrelimR->SetFillColor(0);
	lhcbPrelimR->SetTextAlign(12);
	lhcbPrelimR->SetBorderSize(0);
	lhcbPrelimR->AddText("#splitline{LHCb}{#scale[1.0]{Preliminary}}");

	TPaveText *lhcbPrelimL = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
			0.87 - gStyle->GetPadTopMargin(),
			gStyle->GetPadLeftMargin() + 0.30,
			0.95 - gStyle->GetPadTopMargin(),
			"BRNDC");
	lhcbPrelimL->SetFillColor(0);
	lhcbPrelimL->SetTextAlign(12);
	lhcbPrelimL->SetBorderSize(0);
	lhcbPrelimL->AddText("#splitline{LHCb}{#scale[1.0]{Preliminary}}");

	/*
	TPaveText *lhcb7TeVPrelimR = new TPaveText(0.70 - gStyle->GetPadRightMargin(),
			0.75 - gStyle->SetPadTopMargin(0.05),
			0.95 - gStyle->GetPadRightMargin(),
			0.85 - gStyle->SetPadTopMargin(0.05),
			"BRNDC");
	lhcb7TeVPrelimR->SetFillColor(0);
	lhcb7TeVPrelimR->SetTextAlign(12);
	lhcb7TeVPrelimR->SetBorderSize(0);
	lhcb7TeVPrelimR->AddText("#splitline{#splitline{LHCb}{Preliminary}}{#scale[0.7]{#sqrt{s} = 7 TeV Data}}");

	TPaveText *lhcb7TeVPrelimL = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
			0.78 - gStyle->SetPadTopMargin(0.05),
			gStyle->GetPadLeftMargin() + 0.30,
			0.88 - gStyle->SetPadTopMargin(0.05),
			"BRNDC");
	lhcb7TeVPrelimL->SetFillColor(0);
	lhcb7TeVPrelimL->SetTextAlign(12);
	lhcb7TeVPrelimL->SetBorderSize(0);
	lhcb7TeVPrelimL->SetTextSize(0.06);
	lhcb7TeVPrelimL->AddText("#splitline{#splitline{LHCb}{Preliminary}}{#scale[0.7]{#sqrt{s} = 7 TeV Data}}");

	TPaveText *lhcb0_9TeVPrelimR = new TPaveText(0.70 - gStyle->GetPadRightMargin(),
			0.75 - gStyle->SetPadTopMargin(0.05),
			0.95 - gStyle->GetPadRightMargin(),
			0.85 - gStyle->SetPadTopMargin(0.05),
			"BRNDC");
	lhcb7TeVPrelimR->SetFillColor(0);
	lhcb7TeVPrelimR->SetTextAlign(12);
	lhcb7TeVPrelimR->SetBorderSize(0);
	lhcb7TeVPrelimR->AddText("#splitline{#splitline{LHCb}{Preliminary}}{#scale[0.7]{#sqrt{s} = 900 eV Data}}");

	TPaveText *lhcb0_9TeVPrelimL = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
			0.78 - gStyle->SetPadTopMargin(0.05),
			gStyle->GetPadLeftMargin() + 0.30,
			0.88 - gStyle->SetPadTopMargin(0.05),
			"BRNDC");
	lhcb0_9TeVPrelimL->SetFillColor(0);
	lhcb0_9TeVPrelimL->SetTextAlign(12);
	lhcb0_9TeVPrelimL->SetBorderSize(0);
	lhcb0_9TeVPrelimL->SetTextSize(0.06);
	lhcb0_9TeVPrelimL->AddText("#splitline{#splitline{LHCb}{Preliminary}}{#scale[0.7]{#sqrt{s} = 900 GeV Data}}");
	*/

	TText *lhcbLabel = new TText();
	lhcbLabel->SetTextFont(Font_t(lhcbFont));
	lhcbLabel->SetTextColor(1);
	lhcbLabel->SetTextSize(Float_t(0.04));
	lhcbLabel->SetTextAlign(12);

	TLatex *lhcbLatex = new TLatex();
	lhcbLatex->SetTextFont(Font_t(lhcbFont));
	lhcbLatex->SetTextColor(1);
	lhcbLatex->SetTextSize(Float_t(0.04));
	lhcbLatex->SetTextAlign(12);

	//gROOT->SetStyle("gStyle");
	//gROOT->ForceStyle();

}


/*
   EdStyle::EdStyle(  ) {
//
// based on a style file from BaBar
//

//..BABAR style from RooLogon.C in workdir

// use plain black on white colors
Int_t icol=0;
gStyle->SetFrameBorderMode(icol);
gStyle->SetCanvasBorderMode(icol);
gStyle->SetPadBorderMode(icol);
gStyle->SetPadColor(icol);
gStyle->SetCanvasColor(icol);
gStyle->SetStatColor(icol);
//gStyle->SetFillColor(icol);

// set the paper & margin sizes
//   gStyle->SetPaperSize(20,26);
//   gStyle->SetPadTopMargin(0.05);
//   gStyle->SetPadRightMargin(0.05);
//   gStyle->SetPadBottomMargin(0.16);
//   gStyle->SetPadLeftMargin(0.12);

// use large fonts
//Int_t font=72;
Int_t font=42;
Double_t tsize=0.045;
gStyle->SetTextFont(font);
gStyle->SetTextSize(tsize);
gStyle->SetLabelFont(font,"x");
gStyle->SetTitleFont(font,"x");
gStyle->SetLabelFont(font,"y");
gStyle->SetTitleFont(font,"y");
gStyle->SetLabelFont(font,"z");
gStyle->SetTitleFont(font,"z");

gStyle->SetLabelSize(tsize,"x");
gStyle->SetTitleSize(tsize,"x");
gStyle->SetLabelSize(tsize,"y");
gStyle->SetTitleSize(tsize,"y");
gStyle->SetLabelSize(tsize,"z");
gStyle->SetTitleSize(tsize,"z");
gStyle->SetTitleSize(0.05);


//use bold lines and markers
gStyle->SetMarkerStyle(20);
gStyle->SetMarkerSize(1.2);
gStyle->SetHistLineWidth(2.0);
gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

//get rid of X error bars and y error bar caps
//gStyle->SetErrorX(0.001);

//do not display any of the standard histogram decorations
gStyle->SetOptTitle(0);

gStyle->SetOptStat(0);

gStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);

//   gROOT->SetStyle("GREIG");

//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);
 */
//gStyle->SetOptStat(1111);
/* 
   gStyle->SetOptFit(1111);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1.);
   }
 */


//  These functions are not guaranteed correct but will people please add to them
//  it can save time in editing tables out of RapidFit if we can at least call one standard function for things like this
//	This could be cleaner but given where this occurs in the program I officially cba

TString EdStyle::GetParamRootUnit( string Param_Unit )
{
	if( Param_Unit == "ps^{-1}" ){
		return TString( Param_Unit );
	} else if ( Param_Unit == "MeV/c^{2}" ) {
		return TString( "MeV{c}^{-2}" );
	} else if ( Param_Unit == "ps" ) {
		return TString( Param_Unit );
	} else {
		return TString( "" );
	}
}

TString EdStyle::GetParamLatexUnit( string Param_Unit )
{
	TString Unit("$");
	if( Param_Unit == "ps^{-1}" ){
                Unit.Append( Param_Unit );
        } else if ( Param_Unit == "MeV/c^{2}" ) {
                Unit.Append( "MeV{c}^{-2}" );
	} else if ( Param_Unit == "ps" ) {
		Unit.Append( Param_Unit );
	} else {
		return TString( "" );
	}
	Unit.Append("$");
	return Unit;
}

TString EdStyle::GetParamRootName( string Param_Name )
{
	if( Param_Name == "LLscan" ) {

		return  TString("#Delta LL");
	}
	if( Param_Name == "gamma" ) {

		return  TString("#Gamma");

	} else if ( Param_Name == "deltaGamma" ) {

		return  TString("#Delta#Gamma" );

	} else if ( Param_Name == "Azero_sq" ) {

		return TString("A_{0}^{2}");

	} else if ( Param_Name == "Aperp_sq" ) {

		return TString("A_{#perp}^{2}");

        } else if ( Param_Name == "Apara_sq" ) {

                return TString("A_{#parallel}^{2}");

	} else if ( Param_Name == "delta_para" ) {

		return TString("#delta_{#parallel}");

	} else if ( Param_Name == "delta_perp" ) {

		return TString("#delta_{#perp}");

	} else if ( Param_Name == "Phi_s" ) {

		return TString("#phi_{s}");

        } else if ( Param_Name == "m_Bs" ) {

                return TString("m_{B_s}");

        } else if (Param_Name == "sigma_m1" ) {

                return TString("{#sigma_{m}}^1");

        } else if (Param_Name == "sigma_m2" ) {

                return TString("{#sigma_{m}}^2");

        } else if (Param_Name == "f_sig_m1" ) {

                return TString("f_{{#sigma_{m}}^1}");

	} else if (Param_Name == "mistag" ) {

                return TString("#omega");

        } else if (Param_Name == "angAccI1" ) {

                return TString("#zeta_{1}");

        } else if (Param_Name == "angAccI2" ) {

                return TString("#zeta_{2}");
        
        } else if (Param_Name == "angAccI3" ) {

                return TString("#zeta_{3}");
        
        } else if (Param_Name == "angAccI4" ) {

                return TString("#zeta_{4}");
        
        } else if (Param_Name == "angAccI5" ) {

                return TString("#zeta_{5}");
        
        } else if (Param_Name == "angAccI6" ) {

                return TString("#zeta_{6}");
        
        } else if (Param_Name == "angAccI7" ) {

                return TString("#zeta_{7}");
        
        } else if (Param_Name == "angAccI8" ) {

                return TString("#zeta_{8}");
        
        } else if (Param_Name == "angAccI9" ) {

                return TString("#zeta_{9}");

	} else if (Param_Name =="deltaM" ) {

		return TString( "#Delta{m_{s}}" );

	} else if (Param_Name =="delta_zero") {

		return TString("#delta_{0}");

        } else {

		return TString(Param_Name);
	}

}

TString EdStyle::GetParamLatexName( string Param_Name )
{
	TString Name("$");
        if( Param_Name == "LLscan" ) {

                Name.Append("\\Delta\\text{LL}");
        }
        if( Param_Name == "gamma" ) {

                Name.Append("\\Gamma");

        } else if ( Param_Name == "deltaGamma" ) {

                Name.Append("\\Delta\\Gamma" );

        } else if ( Param_Name == "Azero_sq" ) {

                Name.Append("{A_0}^2");

        } else if ( Param_Name == "Aperp_sq" ) {

                Name.Append("{A_\\perp}^2");

        } else if ( Param_Name == "Apara_sq" ) {

                Name.Append("{A_\\parallel}^2");

        } else if ( Param_Name == "delta_para" ) {

                Name.Append("\\delta_\\parallel");

        } else if ( Param_Name == "delta_perp" ) {

                Name.Append("\\delta_\\perp");

        } else if ( Param_Name == "Phi_s" ) {

                Name.Append("\\phi_s");

        } else if ( Param_Name == "m_Bs" ) {

		Name.Append("m_{B_s}");

	} else if (Param_Name == "sigma_m1" ) {

		Name.Append("{\\sigma_m}^1");

	} else if (Param_Name == "sigma_m2" ) {

                Name.Append("{\\sigma_m}^2");

	} else if (Param_Name == "f_sig_m1" ) {

		Name.Append("f_{{\\sigma_m}^1}");

	} else if (Param_Name == "timeOffset" ) {

		Name.Append("\\tau_{Offset}");

	} else if (Param_Name == "timeResolution1" ) {

		Name.Append("\\tau_1");

	} else if (Param_Name == "timeResolution2" ) {

		Name.Append("\\tau_2");

	} else if (Param_Name == "timeResolution1Fraction" ) {

		Name.Append("f_{\\tau_1}");

	} else if (Param_Name == "mistag" ) {

		Name.Append("\\omega");

	} else if (Param_Name == "angAccI1" ) {

		Name.Append("\\zeta_1");

	} else if (Param_Name == "angAccI2" ) {

                Name.Append("\\zeta_2");

        } else if (Param_Name == "angAccI3" ) {

                Name.Append("\\zeta_3");

        } else if (Param_Name == "angAccI4" ) {

                Name.Append("\\zeta_4");

        } else if (Param_Name == "angAccI5" ) {

                Name.Append("\\zeta_5");

        } else if (Param_Name == "angAccI6" ) {

                Name.Append("\\zeta_6");

        } else if (Param_Name == "angAccI7" ) {

                Name.Append("\\zeta_7");

        } else if (Param_Name == "angAccI8" ) {

                Name.Append("\\zeta_8");

        } else if (Param_Name == "angAccI9" ) {

                Name.Append("\\zeta_9");

	} else if (Param_Name == "angAccI10" ) {

                Name.Append("\\zeta_10");

	} else if (Param_Name =="deltaM" ) {

                Name.Append( "\\Delta{M_s}" );

        } else if (Param_Name =="delta_zero") {

                Name.Append("\\delta_0");

	} else if (Param_Name == "SignalFractionUBT") {
	
		Name.Append("{f_{UB}}^T");
	
	} else if (Param_Name == "SignalFractionUBU") {
	
		Name.Append("{f_{UB}}^{UT}");
	
	} else if (Param_Name == "SignalFractionBT") {
	
		Name.Append("{f_{B}}^T");
	
	} else if (Param_Name == "SignalFractionBU") {
	
		Name.Append("{f_{B}}^{UT}");
	
	} else if (Param_Name == "mistagOffset") {
	
		Name.Append("\\omega_{Offset}");
	
	} else if (Param_Name == "mistagScale") {
	
		Name.Append("\\omega_{Scale}");
	
	} else if (Param_Name == "timeResLL1Frac") {
	
		Name.Append("f_{\\tau_{LL1}}");
	
	} else if (Param_Name == "As_sq") {
	
		Name.Append("{A_s}^2");
	
	} else if (Param_Name == "sigma_LL1") {
	
		Name.Append("\\sigma_{LL1}");
	
	} else if (Param_Name == "sigma_LL2") {
	
		Name.Append("\\sigma_{LL2}");
	
	} else if (Param_Name == "tau_LL1") {
	
		Name.Append("\\tau_{LL1}");
	
	} else if (Param_Name == "tau_LL2") {
	
		Name.Append("\\tau_{LL2}");
	
	} else if (Param_Name == "alphaM_pr") {
	
		Name.Append("\\alpha M_{pr}");
	
	}  else if (Param_Name == "delta_s") {
	
		Name.Append("\\delta_s");
	
	}  else if (Param_Name == "f_LL1") {
	
		Name.Append("f_{LL1}");
	
	} else {
		Name.Append("\\text(");
		Name.Append(Param_Name);
		Name.Append(")");
	}

	Name.Append("$");
	return Name;
}


//	Wrapper functions
TString EdStyle::GetParamLatexUnit( TString arg )
{
	return GetParamLatexUnit( string( arg.Data() ) );
}
TString EdStyle::GetParamRootUnit( TString arg )
{
	return GetParamRootUnit( string( arg.Data() ) );
}
TString EdStyle::GetParamLatexName( TString arg )
{
	return GetParamLatexName( string( arg.Data() ) );
} 
TString EdStyle::GetParamRootName( TString arg )
{
	return GetParamRootName( string( arg.Data() ) );
}
