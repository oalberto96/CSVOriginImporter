//
// Created by Glassy on 15/09/2017.
//

#ifndef USER_FILES_CSVPARSER_H
#define USER_FILES_CSVPARSER_H
#define COMMA 1
#define SEMICOLON 2
#include <origin.h>

class CSVParser
{
public:
    CSVParser();
    bool findBaseline(string str_path);
    string createCopy(string str_path,int mode);
    string loadTextFile(string str_path);
    string replaceComas(string str_path_temp, int mode);
};


#endif //USER_FILES_CSVPARSER_H
