//
// Created by Glassy on 26/09/2017.
//

#include "OriginPlot.h"

OriginPlot::OriginPlot()
{

}

void OriginPlot::plot(Worksheet *wks_sample, int x, int y)
{
    //Graph
    DataRange dr;
    dr.Add(*wks_sample, x, "X"); // 1st column for X data
    dr.Add(*wks_sample, y, "Y"); // 2nd column for Y data
    // Create a graph window
    GraphPage gp;
    gp.Create("Origin");
    GraphLayer gl = gp.Layers(); // Get active layer
    int nPlotIndex = gl.AddPlot(dr, IDM_PLOT_SCATTER);// Returns plot index (offset is 0), else return -1 for error
    if( nPlotIndex >= 0 )
    {
        gl.Rescale();
    }

}
