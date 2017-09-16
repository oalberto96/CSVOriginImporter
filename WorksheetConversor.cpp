//
// Created by Glassy on 12/09/2017.
//

#include "WorksheetConversor.h"


WorksheetConversor::WorksheetConversor()
{

}

void WorksheetConversor::generateTimeColumn(Column col)
{
    int limit = 13, range = 5, counter = 0;
    vector<double>& vec = col.GetDataObject();
    for(int i; i < limit; i++ )
    {
        vec.Add(counter);
        counter += range;
    }
}

void WorksheetConversor::RowtoColumn(Worksheet* wks, Column col, int rowIndex)
{
    vector<double>& vec = col.GetDataObject();
    foreach(Column column in wks->Columns)
    {
        vectorbase &column_data = column.GetDataObject();
        vec.Add(column_data[56]);
    }
}
