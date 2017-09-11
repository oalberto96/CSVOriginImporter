//
// Created by Glassy on 03/09/2017.
//

#ifndef USER_FILES_CSVIMPORTER_H
#define USER_FILES_CSVIMPORTER_H
#include <origin.h>
class CSVImporter
{
public:
    CSVImporter();
    string createCopy(string str_path);
    string loadTextFile(string str_path);
    string replaceComas(string str_path_temp);
    Worksheet importSample(string str_path);
    bool isValidPath(string str_path);
    WorksheetPage generateWoorkBook();
};


#endif //USER_FILES_CSVIMPORTER_H
