//
// Created by Glassy on 16/09/2017.
//

#ifndef USER_FILES_MATHCOLUMNS_H
#define USER_FILES_MATHCOLUMNS_H
#include <origin.h>
#include <ReportTree.h>
#include <GetNBox.h>
#define TABLE_ID 1
#define SUBNODE_ID_BEGIN 1000

class MathColumns
{
public:
    MathColumns();
    columnDivide(Column result_col);
    columnLn(Column col);
    fitLinearReport(const XYRange& iy, ReportData& rd);
    linearFit(Worksheet wks, int x, int y);
    outputToWks(WorksheetPage wp, const FitParameter* psFitParameter);
    output_to_tree_view_wks(WorksheetPage& wp, const RegStats& stRegStats);

};


#endif //USER_FILES_MATHCOLUMNS_H
