//
// Created by Glassy on 12/09/2017.
//

#include "WorksheetConversor.h"


WorksheetConversor::WorksheetConversor()
{

}

void WorksheetConversor::generateTimeColumn(Column col, int time_interval, int columns)
{
    int counter = 0;
    vector<double>& vec = col.GetDataObject();
    for(int i; i < columns-1; i++ )
    {
        vec.Add(counter);
        counter += time_interval;
    }
}

void WorksheetConversor::RowtoColumn(Worksheet* wks, Column col, int rowIndex)
{
    vector<double>& vec = col.GetDataObject();
    bool first_column = true;
    foreach(Column column in wks->Columns)
    {
        if(first_column)
        {
            first_column = false;
            continue;
        }
        vectorbase &column_data = column.GetDataObject();
        vec.Add(column_data[rowIndex]);
    }
}
