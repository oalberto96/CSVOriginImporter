//
// Created by Glassy on 26/09/2017.
//

#ifndef USER_FILES_ORIGINPLOT_H
#define USER_FILES_ORIGINPLOT_H
#include <origin.h>


class OriginPlot
{
public:
    OriginPlot();
    void plot_worksheet(Worksheet wks, string graph_name);
    void plot(Worksheet *wks_sample, int x, int y, string graph_name);
    void plot(DataRange data_range, string graph_name,int nplotid);
    void linearFit(Worksheet wks, int x, int y);
    void outputToWks(WorksheetPage wp, const FitParameter* psFitParameter);
};


#endif //USER_FILES_ORIGINPLOT_H
