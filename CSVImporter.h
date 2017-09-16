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
    Worksheet importSample(string str_path);
    bool isValidPath(string str_path);
    void setColumnProperties(Worksheet *wks);
    void deleteColumns(Worksheet *wks);
    void generateSample(Worksheet *wks);
    Worksheet createWorsheet();
};


#endif //USER_FILES_CSVIMPORTER_H
