#include "debug.h"
#include "differentiator.h"


/*(===========================================================================*/
static const treeData_t dummydata = {0};

static const char TeXdumpName[] = "texdump.tex";
/*)===========================================================================*/


/*(===========================================================================*/
static enum OP_CODE getopcode(const char opsign);

static void dump(const treeNode_t *node);

static void dumpLaTeX(FILE *file, const treeNode_t *node);
/*)===========================================================================*/


/*(===========================================================================*/
treeNode_t *differentiate(treeNode_t *expr)
{
    CHECK(NULL != expr, NULL);

    dump(expr);

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
        CHECK(TREE_SUCCESS == treeInsertLeft(dest, node, dummydata), NULL);
        CHECK(NULL != (src = exprparse(dest, node->left, src)), NULL);

        char sign = '\0';
        CHECK(1 == sscanf(src, " %c %n", &sign, &shift), NULL);
        src += shift;
        printf("Parsed signum: %c\n", sign);
        node->data.type = NODE_OP;
        CHECK(OP_ERROR != (node->data.opcode = getopcode(sign)), NULL);

        CHECK(TREE_SUCCESS == treeInsertRight(dest, node, dummydata), NULL);
        CHECK(NULL != (src = exprparse(dest, node->right, src)), NULL);

        shift = 0;
    }
    else if (1 == sscanf(src, " %lf %n", &num, &shift))
    {
        printf("Parsed number: %lg\n", num);
        node->data.type = NODE_NUM;
        node->data.num = num;
    }
    else if (1 == sscanf(src, " %c %n", &var, &shift))
    {
        printf("Parsed variable: %c\n", var);
        node->data.type = NODE_VAR;
        node->data.var = var;
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


/*(===========================================================================*/
static enum OP_CODE getopcode(const char opsign)
{
    switch (opsign)
    {
        case '+':
            return OP_ADD;
        case '-':
            return OP_SUB;
        case '*':
            return OP_MUL;
        case '/':
            return OP_DIV;

        default:
            return OP_ERROR;
    }
}

static void dump(const treeNode_t *node)
{
    FILE *outfile = fopen(TeXdumpName, "a");
    fprintf(outfile, "$$");
    dumpLaTeX(outfile, node);
    fprintf(outfile, "$$\n");
}

static void dumpLaTeX(FILE *file, const treeNode_t *node)
{
    CHECK(NULL != file, ;);
    CHECK(NULL != node, ;);

    switch (node->data.type)
    {
        case NODE_NUM:
            fprintf(file, "%lg", node->data.num);
            return;
        case NODE_VAR:
            fprintf(file, "%c", node->data.var);
            return;
        case NODE_OP:
            if ((NULL == node->left) || (NULL == node->right))
            {
                fprintf(file, "\\text{cringe}");
                return;    
            }
            fprintf(file, "(");
            switch (node->data.opcode)
            {
                case OP_ERROR:
                    fprintf(file, " \\text{cringe} ");
                    break;
                case OP_ADD:
                    dumpLaTeX(file, node->left);
                    fprintf(file, " + ");
                    dumpLaTeX(file, node->right);
                    break;
                case OP_SUB:
                    dumpLaTeX(file, node->left);
                    fprintf(file, " - ");
                    dumpLaTeX(file, node->right);
                    break;
                case OP_MUL:
                    dumpLaTeX(file, node->left);
                    fprintf(file, " \\cdot ");
                    dumpLaTeX(file, node->right);
                    break;
                case OP_DIV:
                    fprintf(file, " \\frac{ ");
                    dumpLaTeX(file, node->left);
                    fprintf(file, "}{");
                    dumpLaTeX(file, node->right);
                    fprintf(file, "} ");
                    break;

                default:
                    fprintf(file, "\\text{cringe}");
            }
            fprintf(file, ")");
            return;
        
        default:
            fprintf(file, "\\text{cringe}");
            return;
    }
}
/*)===========================================================================*/
