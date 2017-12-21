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
    this->new_format = false;
    this->baseline = false;
    this->project_name = "";
}

void CSVImporter::setProjectName(string project_name)
{
    this->project_name = project_name;
}

string CSVImporter::getProjectName()
{
    return this->project_name;
}

string CSVImporter::extractProjectName(string project_path)
{
    string aux;
    int index;
    index = project_path.Find(".csv");
    aux = project_path.Left(index);
    index = aux.ReverseFind('\\');
    aux = project_path.Right(index);
    out_str("Hi!" + aux);
    return aux;
}

void CSVImporter::setBaseline(bool has_baseline)
{
    this->baseline = has_baseline;
}

bool CSVImporter::getBaseline()
{
    return this->baseline
}

void CSVImporter::setNewFormat(bool has_new_format)
{
    this->new_format = has_new_format;
}

bool CSVImporter::hasNewFormat()
{
    return this->new_format
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
    bool has_new_format = false;
    setProjectName(extractProjectName(str_path));

    setNewFormat(csv_parser.findNewFormat(str_path));

    if(AscImpReadFileStruct(str_path, &ascii_importer) != 0)
    {
    	string str_temp = str_path;
        out_str("Error al importar el archivo, creando archivo temporal ,...");
        setNewFormat(csv_parser.findNewFormat(str_path));
        has_new_format = hasNewFormat();
        str_path = csv_parser.createCopy(str_temp,COMMA,has_new_format);
        if(AscImpReadFileStruct(str_path, &ascii_importer) != 0)
        {
            str_path = csv_parser.createCopy(str_temp,SEMICOLON,has_new_format);
            if(AscImpReadFileStruct(str_path, &ascii_importer) != 0)
            {
                out_str("Error al cargar el archivo, creando archivo temporal ;...");
            }
            else
            {
                setNewFormat(false);
            }
        }
        else
        {
            setNewFormat(false);
        }
    }

    setBaseline(csv_parser.findBaseline(str_path));
    out_str(str_path);
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    wksPage.SetLongName(getProjectName());
    Folder fld = wksPage.GetFolder();
    fld.Rename(getProjectName());
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
    if (hasNewFormat())
    {
         wks.DeleteRow(0);
         wks.DeleteRow(0);
         out_str("Borrado exitoso");
    }
    wks.Show = true;
    out_str("Archivo importado con exito");
    wks.AutoSizeRow(RCLT_COMMENT,1);
    return wks;
}

int CSVImporter::findWaveLength(Worksheet *wks,double user_input)
{
    int row = -1;
    int i, j = 0;
    double aux1, aux2, aux3;
    Column col = wks->Columns(0);
    vectorbase &data_column = col.GetDataObject();

    if(user_input > data_column[0])
    {
        row = 0;
    }
    else if (user_input < data_column.GetSize() - 1)
    {
        row = data_column.GetSize() -1
    }
    else
    {
        for (i = 0; i < data_column.GetSize(); i++)
        {
            if(user_input >= data_column[i])
            {
                row = i;
                break;
            }
        }
        if(row == 0)
        {

        }
        else if (row == data_column.GetSize() - 1)
        {
            aux1 = abs(user_input - data_column[row - 1 ]);
            aux2 = abs(user_input - data_column[row]);
            if (aux1 < aux2)
            {
                row = row - 1;
            }
        }
        else
        {
            aux1 = abs(user_input - data_column[row - 1 ]);
            aux2 = abs(user_input - data_column[row]);
            aux3 = abs(user_input - data_column[row + 1]);

            if (aux1 < aux2)
            {
                if (aux1 < aux3)
                {
                    row = row - 1;
                }
                else
                {
                    row = row + 1;
                }
            }
            else
            {
                if (aux3 < aux2)
                {
                    row = row + 1;
                }
            }
        }
    }
    return row;
}

void CSVImporter::plotWorksheet(Worksheet wks)
{
    OriginPlot o_plot();
    o_plot.plot_worksheet(wks, "Todos");

}

void CSVImporter::generateSample(Worksheet *wks, int user_row, int time_interval)
{

    WorksheetConversor wks_conversor();
    MathColumns column_operator();
    OriginPlot o_plot();
    Worksheet wks_sample;
    wks_sample = createWorsheet(user_row);
    wks_sample.AddCol(); //Add column AA0
    wks_sample.AddCol();// Add column LnAA0
    //Column Time
    Column col_time(wks_sample,0);
    wks_conversor.generateTimeColumn(col_time, time_interval, wks->GetNumCols());
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
    Column col1(*wks, 0), colx(*wks, 3);
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

void CSVImporter::setColumnProperties(Worksheet *wks, int time_interval)
{
    int i = 0;
    string name = "mins", aux_name;
    int column_counter = 0;
    foreach(Column column in wks->Columns)
    {
        if (column_counter != 0)
        {
            aux_name = "" + i + name ;
            i += time_interval;
            column.SetName(aux_name);
            column.SetLongName("");
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
