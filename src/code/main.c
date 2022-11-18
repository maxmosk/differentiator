#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "differentiator.h"


int main(void)
{
    char *exprstr = readline("Expression for differentiation: ");
    puts(exprstr);
    free(exprstr);
    return 0;
}
