#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


const char *s = NULL;

int getG(const char *str);

int getP(void);

int getN(void);

int getE(void);

int getT(void);


int main(void)
{
    char *exprstr = readline("Mathematical expression: ");
    printf("%d\n", getG(exprstr));

    free(exprstr);
    return EXIT_SUCCESS;
}


int getG(const char *str)
{
    s = str;

    int val = getE();
    assert(*s == '\0');

    return val;
}

int getP()
{
    int val = 0;
    
    if (*s == '(')
    {
        s++;
        val = getE();
        
        assert(*s == ')');
        s++;
    }
    else
    {
        val = getN();
    }

    return val;
}

int getN()
{
    int val = 0;
    const char *old_s = s;

    while ((*s <= '9') && (*s >= '0'))
    {
        val = 10 * val + (*s - '0');
        s++;
    }

    assert(s != old_s);
    return val;
}

int getE(void)
{
    int val = getT();

    while ((*s == '+') || (*s == '-'))
    {
        char op = *s;
        *s++;

        int val_2 = getT();
        if (op == '+')
        {
            val += val_2;
        }
        else
        {
            val -= val_2;
        }
    }

    return val;
}

int getT(void)
{
    int val = getP();

    while ((*s == '*') || (*s == '/'))
    {
        char op = *s;
        *s++;

        int val_2 = getP();
        if (op == '*')
        {
            val *= val_2;
        }
        else
        {
            val /= val_2;
        }
    }

    return val;
}

