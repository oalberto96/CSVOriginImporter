//
// Created by Glassy on 03/09/2017.
//

#ifndef USER_FILES_CSVIMPORTER_H
#define USER_FILES_CSVIMPORTER_H
#include <origin.h>
class CSVImporter
{
private:
    bool baseline;
    bool new_format;
public:
    CSVImporter();
    void setNewFormat(bool has_new_format);
    bool hasNewFormat();
    int findWaveLength(Worksheet *wks,int user_input);
    void setBaseline(bool has_baseline);
    bool getBaseline();
    void deleteBaseline(Worksheet *wks);
    Worksheet importSample(string str_path);
    bool isValidPath(string str_path);
    void setColumnProperties(Worksheet *wks, int time_interval);
    void deleteColumns(Worksheet *wks);
    void plotWorksheet(Worksheet wks);
    void generateSample(Worksheet *wks, int user_row, int time_interval);
    Worksheet createWorsheet(int user_row);
    void cleanColumns(Worksheet *wks);

};


#endif //USER_FILES_CSVIMPORTER_H
