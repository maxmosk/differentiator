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
    char buf = '\0';
    sscanf(src, " %c %n", &buf, &shift);



    return src;
}
/*)===========================================================================*/
