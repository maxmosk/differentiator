#ifndef DIFFERENTIATOR_NODES_H_INCLUDED__
#define DIFFERENTIATOR_NODES_H_INCLUDED__


enum NODE_TYPE
{
    NODE_NUM = 0,
    NODE_VAR = 1,
    NODE_OP  = 2
};

enum OP_CODE
{
    OP_ERROR = -1,
    OP_ADD   = 0,
    OP_SUB   = 1,
    OP_MUL   = 2,
    OP_DIV   = 3
};


#endif /* DIFFERENTIATOR_NODES_H_INCLUDED__ */
