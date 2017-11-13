//
// Created by Glassy on 15/09/2017.
//

#include "CSVParser.h"

CSVParser::CSVParser()
{

}

bool CSVParser::findBaseline(string str_path)
{
    bool has_baseline = false;
    string temp_content;
    temp_content = loadTextFile(str_path);
    temp_content = temp_content.Left(400);
    int result = temp_content.Find("Baseline",0,FALSE);
    if(result>=0)
    {
        has_baseline = true;
    }
    return has_baseline;
}

string CSVParser::createCopy(string str_path)
{
    string temp_str_patch = str_path;
    string temp_content;
    temp_str_patch.Replace(".csv","temporal.csv");
    temp_content = loadTextFile(str_path);
    temp_content = replaceComas(temp_content);
    out_str(temp_str_patch);
    stdioFile ff(temp_str_patch, file::modeCreate | file::modeWrite);
    ff.WriteString(temp_content);
    str_path = temp_str_patch;
    return str_path;
}

string CSVParser::loadTextFile(string str_path)
{
    string content_file;
    LoadTextFile(content_file, str_path);
    return content_file;
}

string CSVParser::replaceComas(string str_content_file)
{
    String temp_content;
    temp_content = str_content_file.Left(400);
    int result = temp_content.Find(";",0,FALSE);
    if(result>=0)
    {
        str_content_file.Replace(";"," ");
    }
    else
    {
        str_content_file.Replace(","," ");
    }
    str_content_file.Replace(".",",");
    return str_content_file;
}
