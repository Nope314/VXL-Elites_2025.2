#include "app.h"
#include "common.h"

// MORSE TREE

typedef struct _node
{
    char character;

    struct _node* dot;

    struct _node* dash;

} _node;


//==================================================
// LEVEL 6 (SPECIAL SYMBOL)
//==================================================

// '='  -> -...-
static _node node_EQUAL = {'=', NULL, NULL};

// '+'  -> .-.-.
static _node node_PLUS = {'+', NULL, NULL};

// '/'  -> -..-.
static _node node_SLASH = {'/', NULL, NULL};


//==================================================
// LEVEL 5 (NUMBER)
//==================================================

static _node node_5 = {'5', NULL, NULL};

static _node node_4 = {'4', NULL, NULL};

static _node node_3 = {'3', NULL, NULL};

static _node node_2 = {'2', &node_PLUS, NULL};

static _node node_1 = {'1', NULL, NULL};

static _node node_6 = {'6', NULL, NULL};

static _node node_7 = {'7', NULL, NULL};

static _node node_8 = {'8', NULL, &node_SLASH};

static _node node_9 = {'9', NULL, NULL};

static _node node_0 = {'0', NULL, NULL};


//==================================================
// LEVEL 4
//==================================================

static _node node_H = {'H', &node_5, &node_4};

static _node node_V = {'V', NULL, &node_3};

static _node node_F = {'F', NULL, &node_2};

static _node node_L = {'L', NULL, NULL};

static _node node_P = {'P', NULL, &node_1};

static _node node_J = {'J', NULL, NULL};

static _node node_B = {'B', &node_6, &node_EQUAL};

static _node node_X = {'X', NULL, NULL};

static _node node_C = {'C', NULL, NULL};

static _node node_Y = {'Y', NULL, NULL};

static _node node_Z = {'Z', &node_7, NULL};

static _node node_Q = {'Q', NULL, &node_0};


//==================================================
// LEVEL 3
//==================================================

static _node node_S = {'S', &node_H, &node_V};

static _node node_U = {'U', &node_F, NULL};

static _node node_R = {'R', &node_L, NULL};

static _node node_W = {'W', &node_P, &node_J};

static _node node_D = {'D', &node_B, &node_X};

static _node node_K = {'K', &node_C, &node_Y};

static _node node_G = {'G', &node_Z, &node_Q};

static _node node_O = {'O', &node_8, &node_9};


//==================================================
// LEVEL 2
//==================================================

static _node node_I = {'I', &node_S, &node_U};

static _node node_A = {'A', &node_R, &node_W};

static _node node_N = {'N', &node_D, &node_K};

static _node node_M = {'M', &node_G, &node_O};


//==================================================
// LEVEL 1
//==================================================

static _node node_E = {'E', &node_I, &node_A};

static _node node_T = {'T', &node_N, &node_M};


//==================================================
// ROOT
//==================================================

static _node root = {'\0', &node_E, &node_T};

static _node* cur;


//==================================================
// INIT
//==================================================

void logic_init(void)
{
    cur = &root;
}


//==================================================
// INPUT
//==================================================

void morse_input(char symbol)
{
    if(symbol == '.')
    {
        if(cur->dot != NULL)
        {
            cur = cur->dot;
        }
    }
    else if(symbol == '-')
    {
        if(cur->dash != NULL)
        {
            cur = cur->dash;
        }
    }
}


//==================================================
// COMMIT
//==================================================

char morse_commit(void)
{
    char c = cur->character;

    cur = &root;

    return c;
}


//==================================================
// CHECK DATA
//==================================================

uint8_t morse_has_data(void)
{
    return (cur != &root);
}
