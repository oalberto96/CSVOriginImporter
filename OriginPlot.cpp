//
// Created by Glassy on 26/09/2017.
//

#include "OriginPlot.h"

OriginPlot::OriginPlot()
{

}

/*void OriginPlot::linearFitPlot(){
    GraphPage grPg("Graph1");
    if (grPg)
    {
        GraphLayer g2 = grPg.Layers(0);
        if (g2.IsValid() )
        {
            DataRange graphDataRange;
            graphDataRange = getDataRange(wks,0,1);
            g2.AddPlot(graphDataRange, IDM_PLOT_LINE);
            g2.Rescale();
        }
    }
    else
    {
        out_str("Error al graficar");
    }
}*/

void OriginPlot::plot(Worksheet *wks_sample, int x, int y, string graph_name)
{
    //Graph
    DataRange dr;
    dr.Add(*wks_sample, x, "X"); // 1st column for X data
    dr.Add(*wks_sample, y, "Y"); // 2nd column for Y data
    // Create a graph window
    GraphPage gp;
    gp.Create("Origin");
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
        gp.Create("Origin");
        gp.SetName(graph_name);
    }
    GraphLayer gl = gp.Layers(); // Get active layer
    int nPlotIndex = gl.AddPlot(data_range, nplotid);// Returns plot index (offset is 0), else return -1 for error
    if( nPlotIndex >= 0 )
    {
        gl.Rescale();
    }
}
