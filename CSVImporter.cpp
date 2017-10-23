//
// Created by Glassy on 03/09/2017.
//

#include "CSVImporter.h"
#include "WorksheetConversor.h"
#include "MathColumns.h"
#include "OriginPlot.h"
#include "CSVParser.h"

CSVImporter::CSVImporter()
{
    this->baseline = false;
}

void CSVImporter::setBaseline(bool has_baseline)
{
    this->baseline = has_baseline;
}

bool CSVImporter::getBaseline()
{
    return this->baseline
}

void CSVImporter::deleteBaseline(Worksheet *wks)
{
    wks->DeleteCol(1);
}

bool CSVImporter::isValidPath(string str_path)
{
    if (str_path.IsFile() && str_path.Match("*.csv"))
        return true;
    else
		return false;
}

Worksheet CSVImporter::createWorsheet(int user_row)
{
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    wksPage.SetName("Muestra" + user_row);
    int index = wksPage.AddLayer("New Sheet");
    Worksheet wks = wksPage.Layers(index);
    Worksheet tmp = wksPage.Layers(0);
    tmp.Destroy();
    wks.Show = true;
    return wks;
}

Worksheet CSVImporter::importSample(string str_path)
{
    ASCIMP ascii_importer;
    CSVParser csv_parser();
    if(AscImpReadFileStruct(str_path, &ascii_importer) != 0)
    {
        str_path = csv_parser.createCopy(str_path);
        out_str("Error al cargar el archivo, creando archivo temporal...");
    }
    setBaseline(csv_parser.findBaseline(str_path));
    out_str(str_path);
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    int index = wksPage.AddLayer("New Sheet");
    Worksheet wks = wksPage.Layers(index);
    Worksheet tmp = wksPage.Layers(0);
    tmp.Destroy();
    if (wks.ImportASCII(str_path, ascii_importer) != 0)
    {
        wksPage.Destroy();
        out_str("Error al cargar el archivo");
        return NULL;
    }
    wks.Show = true;
    out_str("Archivo importado con exito");
    wks.AutoSizeRow(RCLT_COMMENT,1);
    return wks;
}

void CSVImporter::generateSample(Worksheet *wks,int user_row)
{
    WorksheetConversor wks_conversor();
    MathColumns column_operator();
    OriginPlot o_plot();
    Worksheet wks_sample;
    wks_sample = createWorsheet(user_row);
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
    Column col_AA0(wks_sample, 2);
    column_operator.columnDivide(col_AA0);
    col_AA0.SetName("AA0");
    //Column LnAA0
    Column col_LnAA0(wks_sample, 3);
    column_operator.columnLn(col_LnAA0);
    col_LnAA0.SetName("LnAA0");
    //plot
    string graph_name = "GraficaMuestra" + user_row;
    DataRange data_range;
    data_range = column_operator.getDataRange(wks_sample,0,3);
    o_plot.plot(data_range,graph_name,IDM_PLOT_LINESYMB);
    Worksheet wks_linearfit = column_operator.linearFit(wks_sample,0,3);
    data_range = column_operator.getDataRange(wks_linearfit,0,1);
    o_plot.plot(data_range,graph_name,IDM_PLOT_LINE);
}

void CSVImporter::cleanColumns(Worksheet *wks)
{
    Column col1(*wks, 0), colx(*wks, 8);
    int nblank_rows = col1.GetNumRows();
    int n_rows = colx.GetUpperIndex()+1;
    for (int i = n_rows; i < nblank_rows; i++) {
        wks->DeleteRow(n_rows);
    }
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
