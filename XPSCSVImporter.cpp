/*------------------------------------------------------------------------------*
 * File Name:				 													*
 * Creation: 03/09/2017 														*
 * Purpose: OriginC Source C file												*
 * Copyright (c) ABCD Corp.	2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010		*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////

#include <Origin.h>
#include "WorksheetConversor.h"
#include "CSVImporter.h"

////////////////////////////////////////////////////////////////////////////////////

//#pragma labtalk(0) // to disable OC functions for LT calling.

////////////////////////////////////////////////////////////////////////////////////
// Include your own header files here.


////////////////////////////////////////////////////////////////////////////////////
// Start your functions here.
main()
{
    string strFile = GetOpenBox("*.csv");
    CSVImporter csv_importer();
    Worksheet wks;
    wks = csv_importer.importSample(strFile);
    wks.AutoSize(AS_SELECTION);
	csv_importer.deleteColumns(&wks);
    csv_importer.setColumnProperties(&wks);
}
