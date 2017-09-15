//
// Created by Glassy on 15/09/2017.
//

#ifndef USER_FILES_CSVPARSER_H
#define USER_FILES_CSVPARSER_H
#include <origin.h>

class CSVParser
{
public:
    CSVParser();
    string createCopy(string str_path);
    string loadTextFile(string str_path);
    string replaceComas(string str_path_temp);
};


#endif //USER_FILES_CSVPARSER_H
