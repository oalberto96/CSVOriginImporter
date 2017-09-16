//
// Created by Glassy on 03/09/2017.
//

#include "CSVImporter.h"
#include "WorksheetConversor.h"

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

Worksheet CSVImporter::createWorsheet()
{
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    int index = wksPage.AddLayer("New Sheet");
    Worksheet wks = wksPage.Layers(index);
    wks.Show = true;
    return wks;
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

void CSVImporter::generateSample(Worksheet *wks)
{
	int user_row = 57;
    WorksheetConversor wks_conversor();
    Worksheet wks_sample;
    wks_sample = createWorsheet();
    wks_sample.AddCol("s", "s"); //Add column AA0
    wks_sample.AddCol("s", "s");// Add column LnAA0
    //Column Time
    Column col_time(wks_sample,0);
    wks_conversor.generateTimeColumn(col_time);
    col_time.SetName("Time");
    //Column A(Y)
    Column col(wks_sample, 1);
    wks_conversor.RowtoColumn(wks,col,user_row);
    col.SetName("A");
    //Column AA0
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
