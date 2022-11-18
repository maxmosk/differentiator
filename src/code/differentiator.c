#include "debug.h"
#include "differentiator.h"


/*(===========================================================================*/
treeNode_t *differentiate(treeNode_t *expr)
{
    CHECK(NULL != expr, NULL);
    return (treeNode_t *) NULL;
}

const char *exprparse(tree_t *dest, treeNode_t *node, const char *src)
{
    CHECK(NULL != dest, NULL);
    CHECK(NULL != node, NULL);
    CHECK(NULL != src,  NULL);

    int shift = 0;
    CHECK(0 == sscanf(src, " ( %n", &shift), NULL);
    src += shift;

    double num = NAN;
    char var = '\0';
    if ('(' == *src)
    {
        //CHECK(TREE_SUCCESS == treeInsertLeft(dest));
        CHECK(NULL != (src = exprparse(dest, node, src)), NULL);

        char sign = '\0';
        CHECK(1 == sscanf(src, " %c %n", &sign, &shift), NULL);
        src += shift;
        printf("Parsed signum: %c\n", sign);

        CHECK(NULL != (src = exprparse(dest, node, src)), NULL);

        shift = 0;
    }
    else if (1 == sscanf(src, " %lf %n", &num, &shift))
    {
        printf("Parsed number: %lg\n", num);
    }
    else if (1 == sscanf(src, " %c %n", &var, &shift))
    {
        printf("Parsed variable: %c\n", var);
    }
    else
    {
        return NULL;
    }
    src += shift;
    CHECK(0 == sscanf(src, " ) %n", &shift), NULL);
    src += shift;

    return src;
}
/*)===========================================================================*/
