//
// Created by Glassy on 15/09/2017.
//

#include "CSVParser.h"

CSVParser::CSVParser()
{

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
    str_content_file.Replace(","," ");
    str_content_file.Replace(".",",");
    return str_content_file;
}
