#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "differentiator.h"


int main(void)
{
    tree_t expr = {0};
    treeCtor(&expr);
    treeData_t dummydata = {0};
    treeInsertRoot(&expr, dummydata);

    char *exprstr = readline("Expression for differentiation: ");
    exprparse(&expr, expr.root, exprstr);
    free(exprstr);

    treeDtor(&expr);
    return 0;
}
