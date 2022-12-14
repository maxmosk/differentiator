#include "bintree.h"
#include "debug.h"


/*(===========================================================================*/
const size_t stackInitSize = 10;

static const char gvizbuf[] = "gvizbuffer";
/*)===========================================================================*/


/*(===========================================================================*/
#ifndef NDEBUG
static void treeGraph(const tree_t *tree, const char *filename);

static void treeGraphAddNode(const treeNode_t *node, FILE *file);
#endif /* NDEBUG */
/*)===========================================================================*/


/*(===========================================================================*/
enum TREE_CODES treeCtor(tree_t *tree)
{
    CHECK(NULL != tree, TREE_NULLPTR);

    tree->root = NULL;

    return TREE_SUCCESS;
}

bool treeEmpty(const tree_t *tree)
{
    enum TREE_CODES verify = TREE_ERROR;
    CHECK(TREE_SUCCESS == (verify = treeVerify(tree)), false);

    return NULL == tree->root;
}

enum TREE_CODES treeInsertRoot(tree_t *tree, const treeData_t elem)
{
    enum TREE_CODES verify = TREE_ERROR;
    CHECK(TREE_SUCCESS == (verify = treeVerify(tree)), verify);

    CHECK(treeEmpty(tree), TREE_ERROR);

    treeNode_t *newnode = treeNodeCtor(elem);
    CHECK(NULL != newnode, TREE_NOMEM);

    tree->root = newnode;

    return TREE_SUCCESS;
}

enum TREE_CODES treeInsertLeft(tree_t *tree, treeNode_t *node, const treeData_t elem)
{
    enum TREE_CODES verify = TREE_ERROR;
    CHECK(TREE_SUCCESS == (verify = treeVerify(tree)), verify);
    CHECK(NULL != node, TREE_NULLPTR);

    treeNode_t *newnode = treeNodeCtor(elem);
    CHECK(NULL != newnode, TREE_NOMEM);
    
    node->left = newnode;

    return TREE_SUCCESS;
}

enum TREE_CODES treeInsertRight(tree_t *tree, treeNode_t *node, const treeData_t elem)
{
    enum TREE_CODES verify = TREE_ERROR;
    CHECK(TREE_SUCCESS == (verify = treeVerify(tree)), verify);
    CHECK(NULL != node, TREE_NULLPTR);

    treeNode_t *newnode = treeNodeCtor(elem);
    CHECK(NULL != newnode, TREE_NOMEM);

    node->right = newnode;

    return TREE_SUCCESS;
}

enum TREE_CODES treeVerify(const tree_t *tree)
{
    CHECK(NULL != tree, TREE_NULLPTR);

#ifndef NDEBUG
    static size_t ngraphs = 0;
    char namebuf[64] = "";
    sprintf(namebuf, "graph%zu.jpg", ngraphs++);

    LOGOPEN("tree.html");
    LOGPRINTF("<pre>\n");
    LOGPRINTF("tree_t [%p]\n", (const void *) tree);
    LOGPRINTF("{\n");
    LOGPRINTF("    root = %p\n", (void *) tree->root);
    LOGPRINTF("}\n");

    treeGraph(tree, namebuf);
    LOGPRINTF("<img src=\"%s\">\n", namebuf);
    LOGPRINTF("</pre>\n");
    LOGCLOSE();
#endif /* NDEBUG */

    return TREE_SUCCESS;
}

enum TREE_CODES treeDtor(tree_t *tree)
{
    enum TREE_CODES verify = TREE_ERROR;
    CHECK(TREE_SUCCESS == (verify = treeVerify(tree)), verify);
   
    treeNodeDtor(tree->root);
    tree->root = NULL;

    return TREE_SUCCESS;
}

treeNode_t *treeNodeCtor(const treeData_t elem)
{
    treeNode_t *node = calloc(1, sizeof *node);
    CHECK(NULL != node, NULL);

    node->right = node->left = NULL;
    node->data = elem;

    return node;
}

void treeNodeDtor(treeNode_t *node)
{
    if (NULL == node)
    {
        return;
    }

    treeNodeDtor(node->right);
    treeNodeDtor(node->left);
    free(node);
}
/*)===========================================================================*/


/*(===========================================================================*/
#ifndef NDEBUG
static void treeGraph(const tree_t *tree, const char *filename)
{
    CHECK(NULL != tree, ;);
    CHECK(NULL != filename, ;);

    FILE *dotfile = fopen(gvizbuf, "w");
    CHECK(NULL != dotfile, ;);

    fprintf(dotfile, "digraph\n");
    fprintf(dotfile, "{\n");

    if (NULL != tree->root)
    {
        fprintf(dotfile, "root->NODE%p\n", (const void *) tree->root);
        treeGraphAddNode(tree->root, dotfile);
    }

    fprintf(dotfile, "}\n");
    fclose(dotfile);

    char cmdbuf[128] = "";
    sprintf(cmdbuf, "dot %s -o %s -Tjpg", gvizbuf, filename);
    CHECK(0 == system(cmdbuf), ;);
}

static void treeGraphAddNode(const treeNode_t *node, FILE *file)
{
    if (NULL == node)
    {
        return;
    }
    else
    {
        fprintf(file,   "NODE%p[style=\"rounded\",shape=record,color=\"blue\",label="
                        "\"{"
                        " { type=%u | opcode=%d | num=%lg | var=%c } | "
                        "{ <left> left=%p | <right> right=%p } "
                        "}\"];\n",
                        (const void *) node,
                        node->data.type, node->data.opcode, node->data.num,
                        isprint(node->data.var) ? node->data.var : '%',
                        (const void *) node->left, (const void *) node->right);

        if (NULL != node->left)
        {
            fprintf(file, "NODE%p:left->NODE%p[color=\"blue\"];\n", (const void *) node,
                                                (const void *) node->left);
        }

        if (NULL != node->right)
        {
            fprintf(file, "NODE%p:right->NODE%p[color=\"red\"];\n", (const void *) node,
                                                (const void *) node->right);
        }
    }

    treeGraphAddNode(node->left, file);
    treeGraphAddNode(node->right, file);
}
#endif /* NDEBUG */
/*)===========================================================================*/
