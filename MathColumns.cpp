//
// Created by Glassy on 16/09/2017.
//

#include "MathColumns.h"

MathColumns::MathColumns()
{

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
