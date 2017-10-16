//
// Created by Glassy on 16/09/2017.
//

#include "MathColumns.h"
MathColumns::MathColumns()
{

}

DataRange MathColumns::getDataRange(Worksheet wks, int x, int y)
{
    DataRange dr;
    if(wks)
    {
        dr.Add(wks,x,"X");
        dr.Add(wks,y,"Y");
    }
    return dr;
}

Worksheet MathColumns::linearFit(Worksheet wks, int x, int y)
{
    if(!wks)
        return NULL;
    WorksheetPage wp = wks.GetPage();
    DataRange dr;
    dr.Add(wks,0,"X");
    dr.Add(wks,3,"Y");
    vector vX;
    dr.GetData(&vX, 0);  // get data of x column to vector
    vector vY;
    dr.GetData(&vY, 1);  // get data of y column to vector
        // Prepare GUI tree to show fit options in GetN dialog
    GETN_TREE(trGUI)
    GETN_BEGIN_BRANCH(Fit, _L("Fit Options"))
    GETN_ID_BRANCH(IDST_LR_OPTIONS) GETN_OPTION_BRANCH(GETNBRANCH_OPEN)
    	GETN_CHECK(FixIntercept, _L("Fix Intercept"), 0)
    		GETN_ID(IDE_LR_FIX_INTCPT)
    	GETN_NUM(FixInterceptAt, _L("Fix Intercept at"), 0)
    		GETN_ID(IDE_LR_FIX_INTCPT_AT)
    	GETN_CHECK(FixSlope, _L("Fix Slope"), 0)
    		GETN_ID(IDE_LR_FIX_SLOPE)
    	GETN_NUM(FixSlopeAt, _L("Fix Slope at"), 1)
    		GETN_ID(IDE_LR_FIX_SLOPE_AT)
    	GETN_CHECK(UseReducedChiSq, STR_FITTING_CHECKBOX_USE_RED_CHI_SQR, 1)
    		GETN_ID(IDE_FIT_REDUCED_CHISQR)
    GETN_END_BRANCH(Fit)
    if( !GetNBox(trGUI) )
    {
    	return NULL; // clicked Cancel button
    }
    LROptions stLROptions;
    stLROptions = trGUI.Fit; // assign value from GUI tree to struct

    // Do linear fit with the above input dataset and fit option settings
    int nSize = vX.GetSize();  // data size
    FitParameter psFitParameter[4];  // two parameters
    RegStats stRegStats;  // regression statistics
    RegANOVA stRegANOVA;  // anova statistics

    int nRet = ocmath_linear_fit(vX, vY, nSize, psFitParameter, NULL,
                            0, &stLROptions, &stRegStats, &stRegANOVA);

    if(nRet != STATS_NO_ERROR)
    {
        out_str("Error");
        return NULL;
    }
    //output_to_tree_view_wks(wksPg, stRegStats);
    outputToWks(wp, &psFitParameter);

    XYRange iy(dr);

    Tree trDummy;
    ReportData rd(trDummy);
    WorksheetPage wksPage = wks.GetPage();
	int nLayer = wksPage.AddLayer();
	Worksheet wksReportData = wksPage.Layers(nLayer);
	rd.SetWorksheet(wksReportData);
    fitLinearReport(iy,rd,wksReportData);
    return wksReportData;
}


    void MathColumns::fitLinearReport(const XYRange& iy, ReportData& rd, Worksheet wks)
{
    // create report table
    ReportTable rt;
    rt = rd.CreateTable("ReportData", "Fitted Data", TABLE_ID);
    int nSubID = SUBNODE_ID_BEGIN;

    DWORD dwRules = DRR_GET_DEPENDENT | DRR_NO_FACTORS;
    int nNumData = iy.GetNumData(dwRules);

    for(int nRange = 0; nRange < nNumData; nRange++)
    {
         DataRange drOne;
         iy.GetSubRange(drOne, dwRules, nRange);

         vector vx, vy;
         drOne.GetData(dwRules, 0, NULL, NULL, &vy, &vx);

         // there are two parameters in linear fitting
         FitParameter sFitParameter[2];
         if( STATS_NO_ERROR == ocmath_linear_fit(vx, vy, vy.GetSize(), sFitParameter) )
         {
             // add fitted X data to report table
             string strName = "X" + (nRange+1);
             string strLongName = "X";
             rt.AddColumn(vx, strName, nSubID++, strLongName, OKDATAOBJ_DESIGNATION_X);

             // calculate fitted Y data
             double dIntercept = sFitParameter[0].Value;
             double dSlope = sFitParameter[1].Value;
             vector vFitY;
             vFitY = vx * dSlope + dIntercept;

             // add fitted Y data to report table
             strName = "Y" + (nRange+1);
             string strRange;
             strRange = drOne.GetDescription(GETLC_COL_LN_ONLY);
             strLongName = "Fitted data on " + strRange;
             rt.AddColumn(vFitY, strName, nSubID++, strLongName, OKDATAOBJ_DESIGNATION_Y);
             wks.SetReportTree(rt);
	         wks.AutoSize();

        }

	 }
}

void MathColumns::outputToWks(WorksheetPage wp, const FitParameter* psFitParameter)
{
    // prepare report tree
    int nID = 100; // Each node must have node ID and node ID must be unique
    Tree tr;
    tr.Report.ID = nID++;
    TreeNode trReport = tr.Report;
    trReport.SetAttribute(TREE_Table, GETNBRANCH_TRANSPOSE);

    // column 1
    trReport.P1.ID = nID++;
    trReport.P1.SetAttribute(STR_LABEL_ATTRIB, "Parameter"); // column label
    trReport.P1.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);

    // column 2
    trReport.P2.ID = nID++;
    trReport.P2.SetAttribute(STR_LABEL_ATTRIB, "Value"); // column label
    trReport.P2.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);

    // column 3
    trReport.P3.ID = nID++;
    trReport.P3.SetAttribute(STR_LABEL_ATTRIB, "Prob>|t|"); // column label
    trReport.P3.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);

    // prepare the vectors to show in the table
    vector<string> vsParamNames = {"Intercept", "Slope"};  // parameter name
    vector vValues, vProbs;  // parameter value and prob
    for(int nParam = 0; nParam < vsParamNames.GetSize(); nParam++)
    {
        vValues.Add(psFitParameter[nParam].Value);
        vProbs.Add(psFitParameter[nParam].Prob);
    }

    // assign the vectors to tree node
    trReport.P1.strVals = vsParamNames;
    trReport.P2.dVals = vValues;
    trReport.P3.dVals = vProbs;

    // report tree to worksheet
    int iLayer = wp.AddLayer("Linear Fit Params");
    Worksheet wksResult = wp.Layers(iLayer);
    if(!wksResult.IsValid() || wksResult.SetReportTree(trReport) < 0)
    {
        printf("Fail to set report tree. \n");
        return;
    }
    wksResult.AutoSize();
}


void MathColumns::output_to_tree_view_wks(WorksheetPage& wp, const RegStats& stRegStats)
{
	Tree tr;
	int nID = 100; // Each node must have node ID and node ID must be unique
	uint nTableFormat = GETNBRANCH_OPEN
						| GETNBRANCH_HIDE_COL_HEADINGS
						| GETNBRANCH_HIDE_ROW_HEADINGS
						| GETNBRANCH_FIT_COL_WIDTH
						| GETNBRANCH_FIT_ROW_HEIGHT;

	// prepare root table node
	tr.Report.ID = nID++; // add Report treenode and assign node id
	TreeNode trReport = tr.Report;
	// need set table attribute for table node
	trReport.SetAttribute(TREE_Table, nTableFormat);
	// the title of root table
	trReport.SetAttribute(STR_LABEL_ATTRIB, "Linear Fit Stats");

	// prepare stats table node
	trReport.Table.ID = nID++; // add Table treenode and assign node id
	TreeNode trTable = trReport.Table;
	// need set table attribute for table node
	trTable.SetAttribute(TREE_Table, nTableFormat|GETNBRANCH_TRANSPOSE);
	// the title of stats table
	trTable.SetAttribute(STR_LABEL_ATTRIB, "Regression Statistics");

	// prepare result node
	trTable.Stats.ID = nID++; // add Stats treenode and assign node id
	TreeNode trStats = trTable.Stats;
	trStats += stRegStats; // support adding result from sturct to treenode

	// set label, those text will show in row header in table
	trStats.N.SetAttribute(STR_LABEL_ATTRIB, "Number of Points");
	trStats.DOF.SetAttribute(STR_LABEL_ATTRIB, "Degrees of Freedom");
	trStats.SSR.SetAttribute(STR_LABEL_ATTRIB, "Residual Sum of Squares");
	trStats.AdjRSq.SetAttribute(STR_LABEL_ATTRIB, "Adj. R-Square");

	// to hide other nodes
	trStats.ReducedChiSq.Show = false;
	trStats.Correlation.Show = false;
	trStats.Rvalue.Show = false;
	trStats.RSqCOD.Show = false;
	trStats.RMSESD.Show = false;
	trStats.NormResiduals.Show = false;

	// the bits to control the newly created worksheet as hierarchy format
	DWORD   dwOptions = WP_SHEET_HIERARCHY | CREATE_NO_DEFAULT_TEMPLATE;
	int iLayer = wp.AddLayer("Linear Fit Stats", dwOptions);

	Worksheet wksResult = wp.Layers(iLayer);
	if(!wksResult.IsValid() || wksResult.SetReportTree(trReport) < 0)
	{
	    printf("Fail to set report tree.\n");
	    return;
	}
	wksResult.AutoSize();
}

void MathColumns::columnDivide(Column result_col)
{
    result_col.SetFormula("col(A)/col(A)[1]");
    result_col.ExecuteFormula();
}

void MathColumns::columnLn(Column col)
{
    col.SetFormula("Ln(col(AA0))");
    col.ExecuteFormula();
}
