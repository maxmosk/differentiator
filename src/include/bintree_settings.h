#ifndef BINTREE_SETTINGS_H_INCLUDED__
#define BINTREE_SETTINGS_H_INCLUDED__


#include <ctype.h>
#include "differentiator_nodes.h"


typedef struct
{
    enum NODE_TYPE type;
    union
    {
        enum OP_CODE opcode;
        char var;
        double num;
    };
} treeData_t;


#endif /* BINTREE_SETTINGS_H_INCLUDED__ */

