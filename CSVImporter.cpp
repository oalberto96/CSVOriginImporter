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

WorksheetPage CSVImporter::generateWoorkBook()
{
	WorksheetPage wsp;
	return wsp
}

string CSVImporter::createCopy(string str_path)
{
    string temp_str_patch = str_path;
    temp_str_patch.Replace(".csv",".temp");
    if(!CopyFile(str_path, temp_str_patch))
    {
        return NULL;
    }
    return temp_str_patch;
}

string CSVImporter::loadTextFile(string str_path)
{
    string content_file;
    LoadTextFile(content_file, str_path);
    return content_file;
}

string CSVImporter::replaceComas(string str_content_file)
{
    str_content_file.Replace(","," ");
    str_content_file.Replace(".",",");
    return str_content_file;
}


void CSVImporter::importSample(string str_path)
{
    int column_number = 57;
    ASCIMP ascii_importer;
    WorksheetPage wksPage;
    wksPage.Create("STAT", CREATE_VISIBLE );
    if(AscImpReadFileStruct(str_path, &ascii_importer) == 0)
    {
        int index = wksPage.AddLayer("New Sheet");
        Worksheet wks = wksPage.Layers(index);
        wks.ImportASCII(str_path, ascii_importer);
        wks.Show = true;

        out_str("Archivo importado con exito");
    }
    else
    {
        out_str("Error al cargar el archivo: importSample");
    }

}
