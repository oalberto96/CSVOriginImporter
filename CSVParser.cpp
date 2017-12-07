//
// Created by Glassy on 15/09/2017.
//

#include "CSVParser.h"

CSVParser::CSVParser()
{

}

bool CSVParser::findNewFormat(string str_path)
{
    bool has_new_format = false;
    string temp_content;
    temp_content = loadTextFile(str_path);
    temp_content = temp_content.Left(3);
    int result = temp_content.Find("0,,",0,FALSE);
    if(result>=0)
    {
        has_new_format = true;
    }
    return has_new_format;
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

string CSVParser::createCopy(string str_path, int mode, bool has_new_format)
{
    int index=0;
    string temp_str_patch = str_path;
    string temp_content;
    temp_str_patch.Replace(".csv","temporal.csv");
    temp_content = loadTextFile(str_path);
    index = temp_content.Find("\n");
    if (has_new_format) {
        while ( index >= temp_content.Find("\n") ) {
            temp_content.Delete(0,1);
        }
    }
    switch (mode) {
        case COMMA:
            temp_content = replaceComas(temp_content,COMMA);
            break;
        case SEMICOLON:
            temp_content = replaceComas(temp_content,SEMICOLON);
            break;
    }
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

string CSVParser::replaceComas(string str_content_file, int mode)
{
    switch (mode) {
        case COMMA:
            str_content_file.Replace(",",".");
            str_content_file.Replace(";",",");
            break;
        case SEMICOLON:
            str_content_file.Replace(",",";");
            str_content_file.Replace(".",",");
            break;
    }
    return str_content_file;
}
