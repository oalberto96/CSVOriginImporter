//
// Created by Glassy on 16/09/2017.
//

#ifndef USER_FILES_MATHCOLUMNS_H
#define USER_FILES_MATHCOLUMNS_H
#include <origin.h>
#include <ReportTree.h>
#include <GetNBox.h>
#include	<XFbase.h>

#define TABLE_ID 1
#define SUBNODE_ID_BEGIN 1000

class MathColumns
{
public:
    MathColumns();
    DataRange getDataRange(Worksheet wks, int x, int y);
    columnDivide(Column result_col);
    columnLn(Column col);
    Worksheet linearFit(Worksheet wks, int x, int y);

    fitLinearReport(const XYRange& iy, ReportData& rd, Worksheet wks);
    outputToWks(WorksheetPage wp, const FitParameter* psFitParameter);
    output_to_tree_view_wks(WorksheetPage& wp, const RegStats& stRegStats);

};


#endif //USER_FILES_MATHCOLUMNS_H
