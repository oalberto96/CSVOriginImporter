//
// Created by Glassy on 12/09/2017.
//

#ifndef USER_FILES_WORKSHEETCONVERSOR_H
#define USER_FILES_WORKSHEETCONVERSOR_H
#include <origin.h>

class WorksheetConversor
{
public:
    WorksheetConversor();
    void RowtoColumn(Worksheet* wks,Column col,int rowIndex);
    void generateTimeColumn(Column col, int time_interval, int columns);
};


#endif //USER_FILES_CSVIMPORTER_H
