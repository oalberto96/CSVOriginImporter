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
    bool valid_input = true;
    int row_number;
    string strFile = GetOpenBox("*.csv");
    CSVImporter csv_importer();
    if (strFile != "" && csv_importer.isValidPath(strFile))
    {
        Worksheet wks;
        wks = csv_importer.importSample(strFile);
        if (wks)
        {
            wks.AutoSize(AS_SELECTION);
            csv_importer.deleteColumns(&wks);
            if (csv_importer.getBaseline()) {
                csv_importer.deleteBaseline(&wks);
            }
            csv_importer.setColumnProperties(&wks);
            csv_importer.cleanColumns(&wks);
            while (valid_input)
            {
                string str_row = InputBox("Ingrese valor de longitud de onda", "");
                if (str_row == "NANUM")
                {
                    valid_input = false;
                    continue;
                }
                int wl_input_user =  atoi(str_row);
                row_number = csv_importer.findWaveLength(&wks,wl_input_user);
                csv_importer.generateSample(&wks,row_number);
                valid_input = false;
            }

        }
    }
    else
    {
        out_str("Accion cancelada por el usuario");
    }


}
