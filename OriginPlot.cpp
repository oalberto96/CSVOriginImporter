//
// Created by Glassy on 26/09/2017.
//

#include "OriginPlot.h"

OriginPlot::OriginPlot()
{

}

void OriginPlot::plot_worksheet(Worksheet wks, string graph_name)
{
    DataRange dr;
    dr.Add(wks, 0, "X");
    for (int i = 1; i < wks.GetNumCols(); i++)
    {
        dr.Add(wks,i,"Y");
    }
    GraphPage gp;
    gp.Create("Absorbance");
    gp.SetName(graph_name);
    GraphLayer gl = gp.Layers();
    int plot_index = gl.AddPlot(dr, IDM_PLOT_LINE);
    if( plot_index >= 0 )
    {
        gl.Rescale();
    }


}

void OriginPlot::plot(Worksheet *wks_sample, int x, int y, string graph_name)
{
    //Graph
    DataRange dr;
    dr.Add(*wks_sample, x, "X"); // 1st column for X data
    dr.Add(*wks_sample, y, "Y"); // 2nd column for Y data
    // Create a graph window
    GraphPage gp;
    gp.Create("LnAA0");
    gp.SetName(graph_name);
    GraphLayer gl = gp.Layers(); // Get active layer
    int nPlotIndex = gl.AddPlot(dr, IDM_PLOT_LINESYMB);// Returns plot index (offset is 0), else return -1 for error
    if( nPlotIndex >= 0 )
    {
        gl.Rescale();
    }
}

void OriginPlot::plot(DataRange data_range, string graph_name,int nplotid)
{
    GraphPage gp(graph_name);
    if (!gp) {
        gp.Create("LnAA0");
        gp.SetName(graph_name);
    }
    GraphLayer gl = gp.Layers(); // Get active layer
    int nPlotIndex = gl.AddPlot(data_range, nplotid);// Returns plot index (offset is 0), else return -1 for error
    if( nPlotIndex >= 0 )
    {
        gl.Rescale();
    }
}
