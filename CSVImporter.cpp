//
// Created by Glassy on 03/09/2017.
//

#include "CSVImporter.h"

CSVImporter::CSVImporter()
{

}

bool CSVImporter::isValidPath(string str_path)
{
    if (str_path.IsFile() && str_path.Match("*.csv"))
        return true;
    else
		return false;
}

Worksheet CSVImporter::importSample(string str_path)
{
    int column_number = 57;
    ASCIMP ascii_importer;
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    int index = wksPage.AddLayer("New Sheet");
    Worksheet wks = wksPage.Layers(index);
    if(AscImpReadFileStruct(str_path, &ascii_importer) == 0)
    {
        wks.ImportASCII(str_path, ascii_importer);
        wks.Show = true;
        out_str("Archivo importado con exito");
    }
    else
    {
        out_str("Error al cargar el archivo: importSample");
    }
    return wks;
}

void CSVImporter::deleteColumns(Worksheet *wks)
{
    int i;
    int num_col = wks->GetNumCols();
    for (i=2;i<num_col;i++)
    {
    	wks->DeleteCol(i);
    }
}

void CSVImporter::setColumnProperties(Worksheet *wks)
{
    int i = 0;
    string name = "mins", aux_name;
    int column_counter = 0;
    foreach(Column column in wks->Columns)
    {
        if (column_counter != 0)
        {
            aux_name = "" + i + name ;
            i +=5;
            column.SetName(aux_name);
            column.SetUnits("Abs");
        }
        else
        {
            column.SetName("Wavelength");
            column.SetUnits("Wavelength (nm)");
        }
        column_counter++;
    }
}
