//
// Created by Glassy on 15/09/2017.
//

#include "CSVParser.h"

CSVParser::CSVParser()
{

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
