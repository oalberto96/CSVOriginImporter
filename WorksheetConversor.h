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
    Column RowtoColumn(Worksheet* wks, int rowIndex);
};


#endif //USER_FILES_CSVIMPORTER_H
