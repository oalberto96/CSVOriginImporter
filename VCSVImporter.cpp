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
            csv_importer.setColumnProperties(&wks);
            csv_importer.cleanColumns(&wks);
            while (valid_input)
            {
                string str_row = InputBox("Ingrese el numero de columna a importar", "");
                if (str_row == "NANUM")
                {
                    valid_input = false;
                    continue;
                }
                int row_number =  atoi(str_row);
                if (row_number>0)
                {
                    csv_importer.generateSample(&wks,row_number);
                    valid_input = false;
                }
                else
                {
                    out_str("Ingrese un numero valido");
                }
            }

        }
    }
    else
    {
        out_str("Accion cancelada por el usuario");
    }


}
