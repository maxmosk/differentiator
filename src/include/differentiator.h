#ifndef DIFFERENTIATOR_H_INCLUDED__
#define DIFFERENTIATOR_H_INCLUDED__


#include <math.h>
#include <stddef.h>
#include "bintree.h"
#include "differentiator_nodes.h"


treeNode_t *differentiate(treeNode_t *expr);

const char *exprparse(tree_t *dest, treeNode_t *node, const char *src);


#endif /* DIFFERENTIATOR_H_INCLUDED__ */
