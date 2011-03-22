#ifndef RAPIDRUN_H
#define RAPIDRUN_H

#include "main.h"
#include "TList.h"
#include "TObject.h"
#include "TObjString.h"
#include "TString.h"

#include <memory>

class RapidRun : public TObject {

public:
	RapidRun(){}//needed by Root IO
	RapidRun( TList* );
	int run();

private:

	std::auto_ptr<TList> args;
	ClassDef( RapidRun, 1 )//Needed for Cint
};

#endif
