#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <jni.h>

//Spielfeldgröße und benutzbare koordinaten für Auto koordinaten
#define XLENGTH 6
#define YLENGTH 6
int CarCordX = -1;
int CarCordY = -1;

//Node für linked List
typedef struct node {
    char val;
    struct node * next;
} node_t;

//Node für Trie
typedef struct trieNode {
    char pf[XLENGTH][YLENGTH];
    struct trieNode *prev;
    struct helpNode *helpnext;
} trieNode_t;

//Node für Helps
typedef struct helpNode{
    struct helpNode *next;
    struct trieNode *parent;
    struct trieNode *trienext;
} helpNode_t;

typedef struct saveNode{
    char save[XLENGTH][YLENGTH];
    struct saveNode *nextsave;
} saveNode_t;

typedef struct winNode{
    char winstep[XLENGTH][YLENGTH];
    struct winNode* nextwin;
    struct winNode* prevwin;
} winNode_t;

//Node für Pointer zu Nodes in List1
typedef struct list1Node{
    struct trieNode *list1node;
    struct list1Node *nextlist1;
} list1Node_t;

//Node für Pointer zu Nodes in List2
typedef struct list2Node{
    struct trieNode *list2node;
    struct list2Node *nextlist2;
} list2Node_t;

char board[XLENGTH][YLENGTH];

//prototypes
void draw(char field[XLENGTH][YLENGTH]);
void moveLeft(char Car, char field[XLENGTH][YLENGTH]);
void moveRight(char Car, char field[XLENGTH][YLENGTH]);
int checkCar(char Car, char field[XLENGTH][YLENGTH]);
int moveDown(char Car, char field[XLENGTH][YLENGTH]);
int moveUp(char Car, char field[XLENGTH][YLENGTH]);
int checkCars(char field[XLENGTH][YLENGTH]);
int checkPossibilitys(char field[XLENGTH][YLENGTH]);
int checkLeft(char Car, char field[XLENGTH][YLENGTH]);
int checkRight(char Car, char field[XLENGTH][YLENGTH]);
int checkUp(char Car, char field[XLENGTH][YLENGTH]);
int checkDown(char Car, char field[XLENGTH][YLENGTH]);
int carLength(char Car, char field[XLENGTH][YLENGTH]);
int solve(char Car, char field[XLENGTH][YLENGTH]);
bool isKnown(char field[XLENGTH][YLENGTH]);
int checkWin(char Car, char field[XLENGTH][YLENGTH]);
int WinSteps(trieNode_t* trieNode);
char* help (const char* input);

list1Node_t* list1start = NULL;
list1Node_t* currentlist1 = NULL;

list2Node_t* list2start = NULL;
list2Node_t* currentlist2 = NULL;

saveNode_t* start = NULL;
saveNode_t* currentSave = NULL;

node_t * head = NULL;
node_t* current = NULL;

trieNode_t* headNode = NULL;
trieNode_t* currentTrie = NULL;

helpNode_t* currentHelp = NULL;

winNode_t* winstart = NULL;
winNode_t* currentwin = NULL;

int depth = 0;
char *winarray = NULL;

JNIEXPORT jstring
JNICALL Java_rhp_rushhourproject_MainActivity_StringSolver(
        JNIEnv *env,
        jobject obj,
        jstring javaString)
{
    /*const char *nativeString = (*env)->GetStringUTFChars(env, javaString, 0);

    for(int i=0; i<XLENGTH; i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            board[i][j] = '\0';
        }
    }
    int g = 0;
    for(int i = 0; i < XLENGTH; i++)
    {
        for(int j = 0; j < YLENGTH; j++)
        {
            if(nativeString[g] != 'O')
            {
                board[i][j] = nativeString[g];
            }
            g++;
        }
    }
    draw(board);

    start = malloc(sizeof(saveNode_t));
    start->nextsave = NULL;
    currentSave = start;
    head = malloc(sizeof(node_t));
    head->next = NULL;
    depth++;
    printf("Depth is now: %i\n", depth);
    current = head;
    headNode = malloc(sizeof(trieNode_t));
    headNode->prev = NULL;
    currentTrie = headNode;
    currentHelp = currentTrie->helpnext;
    for(int i=0; i<XLENGTH; i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            start->save[i][j] = board[i][j];
        }
    }

    draw(board);
    checkPossibilitys(board);
    int h = 0;
    h = solve('R',board);
    jstring jstrBuf = (*env)->NewStringUTF(env, winarray);
    int length = (*env)->GetStringLength(env, jstrBuf);
    return jstrBuf;

    */
    const char* nativeString = (*env)->GetStringUTFChars(env, javaString, 0);
    printf("I gave %s\n",nativeString);

    char* h = "";
    h = help(nativeString);
    printf("I recevied %s\n",h);
    //jstring jstrBuf = (*env)->NewStringUTF(env, winarray);
    //int length = (*env)->GetStringLength(env, jstrBuf);
    //return jstrBuf;
    jstring jstrBuf = (*env)->NewStringUTF(env, winarray);
    //int length = (*env)->GetStringLength(env, jstrBuf);
    return jstrBuf;
    //return 0;
}

char* help(const char* input){

    //reset all to null
    list1start = NULL;
    currentlist1 = NULL;
    list2start = NULL;
    currentlist2 = NULL;
    start = NULL;
    currentSave = NULL;
    head = NULL;
    current = NULL;
    headNode = NULL;
    currentTrie = NULL;
    currentHelp = NULL;
    winstart = NULL;
    currentwin = NULL;
    depth = 0;
    winarray = NULL;

    for(int i=0; i<XLENGTH; i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            board[i][j] = '\0';
        }
    }
    int g = 0;
    for(int i = 0; i < XLENGTH; i++)
    {
        for(int j = 0; j < YLENGTH; j++)
        {
            if(input[g] != 'O')
            {
                board[i][j] = input[g];
            }
            g++;
        }
    }
    printf("I AM GIVING THIS!: %s\n", input);
    draw(board);

    start = malloc(sizeof(saveNode_t));
    start->nextsave = NULL;
    currentSave = start;
    head = malloc(sizeof(node_t));
    head->next = NULL;
    depth++;
    printf("Depth is now: %i\n", depth);
    current = head;
    headNode = malloc(sizeof(trieNode_t));
    headNode->prev = NULL;
    currentTrie = headNode;
    currentHelp = currentTrie->helpnext;
    for(int i=0; i<XLENGTH; i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            start->save[i][j] = board[i][j];
        }
    }
    winarray = "";
    draw(board);
    checkPossibilitys(board);
    int h = 0;
    h = solve('R',board);
    return winarray;
}

int solve(char Car, char field[XLENGTH][YLENGTH])
{
    if(list1start != NULL || list2start != NULL)
    {
        list1start = NULL;
        currentlist1 = NULL;

        list2start = NULL;
        currentlist2 = NULL;
        winstart = NULL;
        currentwin = NULL;
    }

    list1start = malloc(sizeof(list1Node_t));
    list1start->nextlist1 = NULL;
    currentlist1 = list1start;
    int isFirst = 1;
    currentlist2 = list2start;
    list2start = malloc(sizeof(list1Node_t));
    list2start->nextlist2 = NULL;
    currentlist2 = list2start;

    for(int i=0; i<XLENGTH; i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            start->save[i][j] = board[i][j];
        }
    }

    head->val = '\0';
    head->next = NULL;
    checkCars(field);
    current = head;
    //printf("\n");
    int d = 0;
    while(current != NULL)
    {
        current = current->next;
    }
    for(int i = 0; i<XLENGTH;i++)
    {
        for(int j=0; j<YLENGTH;j++)
        {
            if(isalpha(field[i][j]))
            {
                d = 1;
                while(current != NULL)
                {
                    if(field[i][j] == current->val)
                    {
                        d--;
                    }
                    current = current->next;
                }
                if(d == 0)
                {
                    current = head;
                    while(current->next != NULL)
                    {
                        current = current->next;
                    }
                    current->val = field[i][j];
                    current->next = malloc(sizeof(node_t));
                    current->next->val = '\0';
                    current->next->next = NULL;
                }
            }
        }
    }
    if(head->val == '\0')
    {
        winarray = "";
        return 11;
    }
    current = head;
    while(current != NULL)
    {
        current = current->next;
    }

    //printf("\n");
    for(int i = 0; i<XLENGTH;i++)
    {
        for(int j = 0; j<YLENGTH;j++)
        {
            headNode->pf[i][j] = field[i][j];
        }
    }
    char currentfield[XLENGTH][YLENGTH];
    for(int k = 0; k<XLENGTH;k++)
    {
        for(int l = 0; l<YLENGTH;l++)
        {
            currentfield[k][l] = currentTrie->pf[k][l];
        }
    }

    current = head;
    char currentfieldSave[XLENGTH][YLENGTH];
    for(int jk = 0; jk<XLENGTH;jk++)
    {
        for(int jl =0; jl<YLENGTH;jl++)
        {
            currentfieldSave[jk][jl] = currentfield[jk][jl];
        }
    }

    //int DEBUG = 0;

    while(current != NULL)
    {
        while(currentSave != NULL)
        {
            currentSave = currentSave->nextsave;
        }
        currentSave = start;

        //check ob es ein Auto ist
        if(isalpha(current->val))
        {
            for(int x=1; x<5;x++)
            {
                for(int jk = 0; jk<XLENGTH;jk++)
                {
                    for(int jl =0; jl<YLENGTH;jl++)
                    {
                        currentfield[jk][jl] = currentfieldSave[jk][jl];
                    }
                }
                //printf("x ist %i\n",x);
                if(x==1)
                {
                    for(int n=0;n<checkUp(current->val,currentfieldSave);n++)
                    {
                        moveUp(current->val, currentfield);
                        while(currentSave->nextsave != NULL)
                        {
                            currentSave = currentSave->nextsave;
                        }
                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                        for(int aa=0; aa<XLENGTH;aa++)
                        {
                            for(int bb=0; bb<YLENGTH;bb++)
                            {
                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                            }
                        }
                        currentSave->nextsave->nextsave= NULL;
                        currentSave = start;
                        currentHelp = malloc(sizeof(helpNode_t));
                        currentHelp->parent = currentTrie;
                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                        currentHelp->trienext->prev = currentTrie;

                        for(int ui =0; ui<XLENGTH; ui++)
                        {
                            for(int uo =0; uo<YLENGTH; uo++)
                            {
                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                            }
                        }
                        while(currentlist1->nextlist1 != NULL)
                        {
                            currentlist1 = currentlist1->nextlist1;
                        }
                        if(isFirst == 1)
                        {
                            isFirst = 0;
                            currentlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1 = NULL;
                        } else{
                            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
                            currentlist1->nextlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1->nextlist1 = NULL;
                        }
                        currentlist1 = list1start;
                        currentTrie = headNode;
                        currentHelp = currentHelp->next;
                    }
                }else if(x==2)
                {
                    for(int n=0;n<checkDown(current->val,currentfieldSave);n++)
                    {
                        moveDown(current->val, currentfield);
                        while(currentSave->nextsave != NULL)
                        {
                            currentSave = currentSave->nextsave;
                        }
                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                        for(int aa=0; aa<XLENGTH;aa++)
                        {
                            for(int bb=0; bb<YLENGTH;bb++)
                            {
                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                            }
                        }
                        currentSave->nextsave->nextsave= NULL;
                        currentSave = start;
                        currentHelp = malloc(sizeof(helpNode_t));
                        currentHelp->parent = currentTrie;
                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                        currentHelp->trienext->prev = currentTrie;

                        for(int ui =0; ui<XLENGTH; ui++)
                        {
                            for(int uo =0; uo<YLENGTH; uo++)
                            {
                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                            }
                        }
                        while(currentlist1->nextlist1 != NULL)
                        {
                            currentlist1 = currentlist1->nextlist1;
                        }
                        if(isFirst == 1)
                        {
                            isFirst = 0;
                            currentlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1 = NULL;
                        } else{
                            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
                            currentlist1->nextlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1->nextlist1 = NULL;
                        }
                        currentlist1 = list1start;
                        currentTrie = headNode;
                        currentHelp = currentHelp->next;
                    }
                }else if(x==3)
                {
                    for(int n=0;n<checkRight(current->val,currentfieldSave);n++)
                    {
                        moveRight(current->val, currentfield);
                        while(currentSave->nextsave != NULL)
                        {
                            currentSave = currentSave->nextsave;
                        }
                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                        for(int aa=0; aa<XLENGTH;aa++)
                        {
                            for(int bb=0; bb<YLENGTH;bb++)
                            {
                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                            }
                        }
                        currentSave->nextsave->nextsave= NULL;
                        currentSave = start;
                        currentHelp = malloc(sizeof(helpNode_t));
                        currentHelp->parent = currentTrie;
                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                        currentHelp->trienext->prev = currentTrie;

                        for(int ui =0; ui<XLENGTH; ui++)
                        {
                            for(int uo =0; uo<YLENGTH; uo++)
                            {
                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                            }
                        }
                        while(currentlist1->nextlist1 != NULL)
                        {
                            currentlist1 = currentlist1->nextlist1;
                        }
                        if(isFirst == 1)
                        {
                            isFirst = 0;
                            currentlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1 = NULL;
                        } else{
                            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
                            currentlist1->nextlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1->nextlist1 = NULL;
                        }
                        currentlist1 = list1start;
                        currentTrie = headNode;
                        currentHelp = currentHelp->next;
                    }
                }else if(x==4)
                {
                    for(int n=0;n<checkLeft(current->val,currentfieldSave);n++)
                    {
                        moveLeft(current->val, currentfield);
                        while(currentSave->nextsave != NULL)
                        {
                            currentSave = currentSave->nextsave;
                        }
                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                        for(int aa=0; aa<XLENGTH;aa++)
                        {
                            for(int bb=0; bb<YLENGTH;bb++)
                            {
                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                            }
                        }
                        currentSave->nextsave->nextsave= NULL;
                        currentSave = start;
                        currentHelp = malloc(sizeof(helpNode_t));
                        currentHelp->parent = currentTrie;
                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                        currentHelp->trienext->prev = currentTrie;

                        for(int ui =0; ui<XLENGTH; ui++)
                        {
                            for(int uo =0; uo<YLENGTH; uo++)
                            {
                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                            }
                        }
                        while(currentlist1->nextlist1 != NULL)
                        {
                            currentlist1 = currentlist1->nextlist1;
                        }
                        if(isFirst == 1)
                        {
                            isFirst = 0;
                            currentlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1 = NULL;
                        } else{
                            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
                            currentlist1->nextlist1->list1node = currentHelp->trienext;
                            currentlist1->nextlist1->nextlist1 = NULL;
                        }
                        currentlist1 = list1start;
                        currentTrie = headNode;
                        currentHelp = currentHelp->next;
                    }
                }
            }
        }
        current = current->next;
    }
    currentlist1 = list1start;
    isFirst = 1;
    while(currentlist1 != NULL)
    {
        if(currentlist1->list1node->pf[2][5] == Car)
        {
            winstart = malloc(sizeof(winNode_t));
            currentwin = winstart;
            winstart->prevwin = NULL;
            winstart->nextwin = NULL;
            for(int pp = 0; pp < XLENGTH; pp++)
            {
                for(int oo = 0; oo < YLENGTH; oo++)
                {
                    winstart->winstep[pp][oo] = currentfield[pp][oo];
                }
            }
            draw(currentlist1->list1node->pf);
            currentwin->nextwin = malloc(sizeof(winNode_t));
            currentwin->nextwin->prevwin = currentwin;
            currentwin = currentwin->nextwin;
            currentwin->nextwin = NULL;
            for(int pp = 0; pp < XLENGTH; pp++)
            {
                for(int oo = 0; oo < YLENGTH; oo++)
                {
                    currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                }
            }
            WinSteps(currentlist1->list1node);
            return 0;
        }
        if(currentlist1->list1node != NULL)
        {
            currentTrie = currentlist1->list1node;
            currentTrie->helpnext = malloc(sizeof(helpNode_t));
            currentHelp = currentTrie->helpnext;
            head->val = '\0';
            head->next = NULL;

            checkCars(currentTrie->pf);
            current = head;
            d = 0;
            while(current != NULL)
            {
                current = current->next;
            }
            for(int i = 0; i<XLENGTH;i++)
            {
                for(int j=0; j<YLENGTH;j++)
                {
                    if(isalpha(currentTrie->pf[i][j]))
                    {
                        d = 1;
                        while(current != NULL)
                        {
                            if(currentTrie->pf[i][j] == current->val)
                            {
                                d--;
                            }
                            current = current->next;
                        }
                        if(d == 0)
                        {
                            current = head;
                            while(current->next != NULL)
                            {
                                current = current->next;
                            }
                            current->val = currentTrie->pf[i][j];
                            current->next = malloc(sizeof(node_t));
                            current->next->val = '\0';
                            current->next->next = NULL;
                        }
                    }
                }
            }
            current = head;
            while(current != NULL)
            {
                if(isalpha(current->val))
                {
                    //printf("%c ", current->val);
                }
                current = current->next;
            }

            for(int k = 0; k<XLENGTH;k++)
            {
                for(int l = 0; l<YLENGTH;l++)
                {
                    currentfield[k][l] = currentTrie->pf[k][l];
                }
            }

            current = head;
            for(int jk = 0; jk<XLENGTH;jk++)
            {
                for(int jl =0; jl<YLENGTH;jl++)
                {
                    currentfieldSave[jk][jl] = currentfield[jk][jl];
                }
            }
            currentTrie = currentlist1->list1node;
            while(current != NULL)
            {
                while(currentSave != NULL)
                {
                    currentSave = currentSave->nextsave;
                }
                currentSave = start;

                //check ob es ein Auto ist
                if(isalpha(current->val))
                {
                    for(int x=1; x<5;x++)
                    {
                        for(int jk = 0; jk<XLENGTH;jk++)
                        {
                            for(int jl =0; jl<YLENGTH;jl++)
                            {
                                currentfield[jk][jl] = currentfieldSave[jk][jl];
                            }
                        }
                        if(x==1)
                        {
                            for(int n=0;n<checkUp(current->val,currentfieldSave);n++)
                            {
                                moveUp(current->val, currentfield);
                                if(currentfield[2][5] == Car)
                                {
                                    winstart = malloc(sizeof(winNode_t));
                                    currentwin = winstart;
                                    winstart->prevwin = NULL;
                                    winstart->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            winstart->winstep[pp][oo] = currentfield[pp][oo];
                                        }
                                    }
                                    draw(currentlist1->list1node->pf);
                                    currentwin->nextwin = malloc(sizeof(winNode_t));
                                    currentwin->nextwin->prevwin = currentwin;
                                    currentwin = currentwin->nextwin;
                                    currentwin->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                        }
                                    }
                                    WinSteps(currentlist1->list1node);
                                    return 1;
                                }
                                if(!isKnown(currentfield))
                                {
                                    while(currentSave->nextsave != NULL)
                                    {
                                        currentSave = currentSave->nextsave;
                                    }
                                    currentSave->nextsave = malloc(sizeof(saveNode_t));

                                    for(int aa=0; aa<XLENGTH;aa++)
                                    {
                                        for(int bb=0; bb<YLENGTH;bb++)
                                        {
                                            currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                        }
                                    }
                                    currentSave->nextsave->nextsave= NULL;
                                    currentSave = start;
                                    currentHelp = malloc(sizeof(helpNode_t));
                                    currentHelp->parent = currentTrie;
                                    currentHelp->trienext = malloc(sizeof(trieNode_t));
                                    currentHelp->trienext->prev = currentTrie;
                                    for(int ui =0; ui<XLENGTH; ui++)
                                    {
                                        for(int uo =0; uo<YLENGTH; uo++)
                                        {
                                            currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                        }
                                    }

                                    while(currentlist2->nextlist2 != NULL)
                                    {
                                        currentlist2 = currentlist2->nextlist2;
                                    }
                                    if(isFirst == 1)
                                    {
                                        isFirst = 0;
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2 = NULL;
                                    } else{
                                        currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                        currentlist2->nextlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2->nextlist2 = NULL;
                                    }
                                    currentHelp = currentTrie->helpnext;
                                    currentlist2 = list2start;
                                    currentHelp = currentHelp->next;

                                }
                            }
                        }else if(x==2)
                        {
                            for(int n=0;n<checkDown(current->val,currentfieldSave);n++)
                            {
                                moveDown(current->val, currentfield);
                                if(currentfield[2][5] == Car)
                                {
                                    winstart = malloc(sizeof(winNode_t));
                                    currentwin = winstart;
                                    winstart->prevwin = NULL;
                                    winstart->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            winstart->winstep[pp][oo] = currentfield[pp][oo];
                                        }
                                    }
                                    draw(currentlist1->list1node->pf);
                                    currentwin->nextwin = malloc(sizeof(winNode_t));
                                    currentwin->nextwin->prevwin = currentwin;
                                    currentwin = currentwin->nextwin;
                                    currentwin->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                        }
                                    }
                                    WinSteps(currentlist1->list1node);
                                    return 2;
                                }
                                if(!isKnown(currentfield))
                                {
                                    while(currentSave->nextsave != NULL)
                                    {
                                        currentSave = currentSave->nextsave;
                                    }
                                    currentSave->nextsave = malloc(sizeof(saveNode_t));

                                    for(int aa=0; aa<XLENGTH;aa++)
                                    {
                                        for(int bb=0; bb<YLENGTH;bb++)
                                        {
                                            currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                        }
                                    }
                                    currentSave->nextsave->nextsave= NULL;
                                    currentSave = start;
                                    currentHelp = malloc(sizeof(helpNode_t));
                                    currentHelp->parent = currentTrie;
                                    currentHelp->trienext = malloc(sizeof(trieNode_t));
                                    currentHelp->trienext->prev = currentTrie;
                                    for(int ui =0; ui<XLENGTH; ui++)
                                    {
                                        for(int uo =0; uo<YLENGTH; uo++)
                                        {
                                            currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                        }
                                    }

                                    while(currentlist2->nextlist2 != NULL)
                                    {
                                        currentlist2 = currentlist2->nextlist2;
                                    }
                                    if(isFirst == 1)
                                    {
                                        isFirst = 0;
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2 = NULL;
                                    } else{
                                        currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                        currentlist2->nextlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2->nextlist2 = NULL;
                                    }
                                    currentHelp = currentTrie->helpnext;
                                    currentlist2 = list2start;
                                    currentHelp = currentHelp->next;
                                }
                            }
                        }else if(x==3)
                        {
                            for(int n=0;n<checkRight(current->val,currentfieldSave);n++)
                            {
                                moveRight(current->val, currentfield);
                                if(currentfield[2][5] == Car)
                                {
                                    winstart = malloc(sizeof(winNode_t));
                                    currentwin = winstart;
                                    winstart->prevwin = NULL;
                                    winstart->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            winstart->winstep[pp][oo] = currentfield[pp][oo];
                                        }
                                    }
                                    draw(currentlist1->list1node->pf);
                                    currentwin->nextwin = malloc(sizeof(winNode_t));
                                    currentwin->nextwin->prevwin = currentwin;
                                    currentwin = currentwin->nextwin;
                                    currentwin->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                        }
                                    }
                                    WinSteps(currentlist1->list1node);
                                    return 3;
                                }
                                if(!isKnown(currentfield))
                                {
                                    while(currentSave->nextsave != NULL)
                                    {
                                        currentSave = currentSave->nextsave;
                                    }
                                    currentSave->nextsave = malloc(sizeof(saveNode_t));

                                    for(int aa=0; aa<XLENGTH;aa++)
                                    {
                                        for(int bb=0; bb<YLENGTH;bb++)
                                        {
                                            currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                        }
                                    }
                                    currentSave->nextsave->nextsave= NULL;
                                    currentSave = start;
                                    currentHelp = malloc(sizeof(helpNode_t));
                                    currentHelp->parent = currentTrie;
                                    currentHelp->trienext = malloc(sizeof(trieNode_t));
                                    currentHelp->trienext->prev = currentTrie;
                                    for(int ui =0; ui<XLENGTH; ui++)
                                    {
                                        for(int uo =0; uo<YLENGTH; uo++)
                                        {
                                            currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                        }
                                    }

                                    while(currentlist2->nextlist2 != NULL)
                                    {
                                        currentlist2 = currentlist2->nextlist2;
                                    }
                                    if(isFirst == 1)
                                    {
                                        isFirst = 0;
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2 = NULL;
                                    } else{
                                        currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                        currentlist2->nextlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2->nextlist2 = NULL;
                                    }
                                    currentHelp = currentTrie->helpnext;
                                    currentlist2 = list2start;
                                    currentHelp = currentHelp->next;
                                }
                            }
                        }else if(x==4)
                        {
                            for(int n=0;n<checkLeft(current->val,currentfieldSave);n++)
                            {
                                moveLeft(current->val, currentfield);
                                if(currentfield[2][5] == Car)
                                {
                                    winstart = malloc(sizeof(winNode_t));
                                    currentwin = winstart;
                                    winstart->prevwin = NULL;
                                    winstart->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            winstart->winstep[pp][oo] = currentfield[pp][oo];
                                        }
                                    }
                                    draw(currentlist1->list1node->pf);
                                    currentwin->nextwin = malloc(sizeof(winNode_t));
                                    currentwin->nextwin->prevwin = currentwin;
                                    currentwin = currentwin->nextwin;
                                    currentwin->nextwin = NULL;
                                    for(int pp = 0; pp < XLENGTH; pp++)
                                    {
                                        for(int oo = 0; oo < YLENGTH; oo++)
                                        {
                                            currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                        }
                                    }
                                    WinSteps(currentlist1->list1node);
                                    return 4;
                                }
                                if(!isKnown(currentfield))
                                {
                                    while(currentSave->nextsave != NULL)
                                    {
                                        currentSave = currentSave->nextsave;
                                    }
                                    currentSave->nextsave = malloc(sizeof(saveNode_t));

                                    for(int aa=0; aa<XLENGTH;aa++)
                                    {
                                        for(int bb=0; bb<YLENGTH;bb++)
                                        {
                                            currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                        }
                                    }
                                    currentSave->nextsave->nextsave= NULL;
                                    currentSave = start;
                                    currentHelp = malloc(sizeof(helpNode_t));
                                    currentHelp->parent = currentTrie;
                                    currentHelp->trienext = malloc(sizeof(trieNode_t));
                                    currentHelp->trienext->prev = currentTrie;
                                    for(int ui =0; ui<XLENGTH; ui++)
                                    {
                                        for(int uo =0; uo<YLENGTH; uo++)
                                        {
                                            currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                        }
                                    }

                                    while(currentlist2->nextlist2 != NULL)
                                    {
                                        currentlist2 = currentlist2->nextlist2;
                                    }
                                    if(isFirst == 1)
                                    {
                                        isFirst = 0;
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2 = NULL;
                                    } else{
                                        currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                        currentlist2->nextlist2->list2node = currentHelp->trienext;
                                        currentlist2->nextlist2->nextlist2 = NULL;
                                    }
                                    currentHelp = currentTrie->helpnext;
                                    currentlist2 = list2start;
                                    currentHelp = currentHelp->next;
                                }
                            }
                        }
                    }
                }
                current = current->next;
            }
        }
        currentlist1 = currentlist1->nextlist1;
    }

    currentlist1 = list1start;
    currentlist2 = list2start;
    list1start = NULL;
    list1start = malloc(sizeof(list1Node_t));
    currentlist1 = list1start;
    currentlist1->list1node = currentlist2->list2node;
    currentlist1->nextlist1 = NULL;
    currentlist2 = currentlist2->nextlist2;

    while(currentlist2 != NULL)
    {
        currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
        currentlist1->nextlist1->list1node = currentlist2->list2node;
        currentlist1 = currentlist1->nextlist1;
        currentlist1->nextlist1 = NULL;
        currentlist2 = currentlist2->nextlist2;
    }
    list2start = NULL;
    list2start = malloc(sizeof(list2Node_t));
    currentlist1 = list1start;
    currentlist2 = list2start;
    currentlist2->nextlist2 = NULL;
    currentlist2->list2node = NULL;

    while(true)
    {
        if(list1start->list1node == NULL)
        {
            winarray = "";
            return 15;
        }
        currentlist1 = list1start;
        currentlist2 = list2start;
        currentTrie = currentlist1->list1node;
        currentTrie->helpnext = malloc(sizeof(helpNode_t));
        currentHelp = currentTrie->helpnext;
        currentHelp->parent = currentTrie;
        if(currentTrie != NULL)
        {
            currentHelp = currentTrie->helpnext;
        }else
        {
            currentTrie->helpnext = malloc(sizeof(helpNode_t));
            currentHelp = currentTrie->helpnext;
        }
        currentHelp->parent = currentTrie;
        isFirst = 1;
        while(currentlist1 != NULL)
        {
            if(currentlist1->list1node != NULL)
            {
                currentTrie = currentlist1->list1node;

                current = head;
                for(int k = 0; k<XLENGTH;k++)
                {
                    for(int l = 0; l<YLENGTH;l++)
                    {
                        currentfield[k][l] = currentlist1->list1node->pf[k][l];
                    }
                }

                current = head;
                for(int jk = 0; jk<XLENGTH;jk++)
                {
                    for(int jl =0; jl<YLENGTH;jl++)
                    {
                        currentfieldSave[jk][jl] = currentfield[jk][jl];
                    }
                }
                if(currentlist1->list1node != NULL && checkWin(Car, currentlist1->list1node->pf))
                {
                    winstart = malloc(sizeof(winNode_t));
                    currentwin = winstart;
                    winstart->prevwin = NULL;
                    winstart->nextwin = NULL;
                    for(int pp = 0; pp < XLENGTH; pp++)
                    {
                        for(int oo = 0; oo < YLENGTH; oo++)
                        {
                            winstart->winstep[pp][oo] = currentfield[pp][oo];
                        }
                    }
                    draw(currentlist1->list1node->pf);
                    currentwin->nextwin = malloc(sizeof(winNode_t));
                    currentwin->nextwin->prevwin = currentwin;
                    currentwin = currentwin->nextwin;
                    currentwin->nextwin = NULL;
                    for(int pp = 0; pp < XLENGTH; pp++)
                    {
                        for(int oo = 0; oo < YLENGTH; oo++)
                        {
                            currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                        }
                    }
                    WinSteps(currentlist1->list1node);
                    return 1;
                }
                while(current != NULL)
                {
                    while(currentSave != NULL)
                    {
                        currentSave = currentSave->nextsave;
                    }
                    currentSave = start;

                    //check ob es ein Auto ist
                    if(isalpha(current->val))
                    {
                        for(int x=1; x<5;x++)
                        {
                            for(int jk = 0; jk<XLENGTH;jk++)
                            {
                                for(int jl =0; jl<YLENGTH;jl++)
                                {
                                    currentfield[jk][jl] = currentfieldSave[jk][jl];
                                }
                            }
                            if(x==1)
                            {
                                for(int n=0;n<checkUp(current->val,currentfieldSave);n++)
                                {
                                    moveUp(current->val, currentfield);
                                    if(currentfield[2][5] == Car)
                                    {
                                        winstart = malloc(sizeof(winNode_t));
                                        currentwin = winstart;
                                        winstart->prevwin = NULL;
                                        winstart->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                winstart->winstep[pp][oo] = currentfield[pp][oo];
                                            }
                                        }
                                        draw(currentlist1->list1node->pf);
                                        currentwin->nextwin = malloc(sizeof(winNode_t));
                                        currentwin->nextwin->prevwin = currentwin;
                                        currentwin = currentwin->nextwin;
                                        currentwin->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                            }
                                        }
                                        WinSteps(currentlist1->list1node);
                                        return 6;
                                    }
                                    if(!isKnown(currentfield))
                                    {
                                        while(currentSave->nextsave != NULL)
                                        {
                                            currentSave = currentSave->nextsave;
                                        }
                                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                                        for(int aa=0; aa<XLENGTH;aa++)
                                        {
                                            for(int bb=0; bb<YLENGTH;bb++)
                                            {
                                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                            }
                                        }
                                        currentSave->nextsave->nextsave= NULL;
                                        currentSave = start;

                                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                                        currentHelp->next = malloc(sizeof(helpNode_t));
                                        currentHelp->parent = currentTrie;
                                        currentHelp->trienext->prev = currentTrie;

                                        for(int ui =0; ui<XLENGTH; ui++)
                                        {
                                            for(int uo =0; uo<YLENGTH; uo++)
                                            {
                                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                            }
                                        }
                                        while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        if(isFirst == 1)
                                        {
                                            isFirst = 0;
                                            currentlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2 = NULL;
                                        } else{
                                            currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                            currentlist2->nextlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2->nextlist2 = NULL;
                                        }
                                        currentlist2 = list2start;
                                        /*while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        currentlist2->nextlist2 = malloc(sizeof(list2Node_t));
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2 = list2start;*/
                                        if(currentHelp->next)
                                        {
                                            currentHelp = currentHelp->next;
                                        }
                                    }
                                }
                            }else if(x==2)
                            {
                                for(int n=0;n<checkDown(current->val,currentfieldSave);n++)
                                {
                                    moveDown(current->val, currentfield);
                                    if(currentfield[2][5] == Car)
                                    {
                                        winstart = malloc(sizeof(winNode_t));
                                        currentwin = winstart;
                                        winstart->prevwin = NULL;
                                        winstart->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                winstart->winstep[pp][oo] = currentfield[pp][oo];
                                            }
                                        }
                                        draw(currentlist1->list1node->pf);
                                        currentwin->nextwin = malloc(sizeof(winNode_t));
                                        currentwin->nextwin->prevwin = currentwin;
                                        currentwin = currentwin->nextwin;
                                        currentwin->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                            }
                                        }
                                        WinSteps(currentlist1->list1node);
                                        return 6;
                                    }
                                    if(!isKnown(currentfield))
                                    {
                                        while(currentSave->nextsave != NULL)
                                        {
                                            currentSave = currentSave->nextsave;
                                        }
                                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                                        for(int aa=0; aa<XLENGTH;aa++)
                                        {
                                            for(int bb=0; bb<YLENGTH;bb++)
                                            {
                                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                            }
                                        }
                                        currentSave->nextsave->nextsave= NULL;
                                        currentSave = start;

                                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                                        currentHelp->next = malloc(sizeof(helpNode_t));
                                        currentHelp->parent = currentTrie;
                                        currentHelp->trienext->prev = currentTrie;

                                        for(int ui =0; ui<XLENGTH; ui++)
                                        {
                                            for(int uo =0; uo<YLENGTH; uo++)
                                            {
                                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                            }
                                        }
                                        while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        if(isFirst == 1)
                                        {
                                            isFirst = 0;
                                            currentlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2 = NULL;
                                        } else{
                                            currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                            currentlist2->nextlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2->nextlist2 = NULL;
                                        }
                                        currentlist2 = list2start;
                                        /*while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        currentlist2->nextlist2 = malloc(sizeof(list2Node_t));
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2 = list2start;*/
                                        if(currentHelp->next)
                                        {
                                            currentHelp = currentHelp->next;
                                        }
                                    }
                                }
                            }else if(x==3)
                            {
                                for(int n=0;n<checkRight(current->val,currentfieldSave);n++)
                                {
                                    moveRight(current->val, currentfield);
                                    if(currentfield[2][5] == Car)
                                    {
                                        winstart = malloc(sizeof(winNode_t));
                                        currentwin = winstart;
                                        winstart->prevwin = NULL;
                                        winstart->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                winstart->winstep[pp][oo] = currentfield[pp][oo];
                                            }
                                        }
                                        draw(currentlist1->list1node->pf);
                                        currentwin->nextwin = malloc(sizeof(winNode_t));
                                        currentwin->nextwin->prevwin = currentwin;
                                        currentwin = currentwin->nextwin;
                                        currentwin->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                            }
                                        }
                                        WinSteps(currentlist1->list1node);
                                        return 6;
                                    }
                                    if(!isKnown(currentfield))
                                    {
                                        while(currentSave->nextsave != NULL)
                                        {
                                            currentSave = currentSave->nextsave;
                                        }
                                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                                        for(int aa=0; aa<XLENGTH;aa++)
                                        {
                                            for(int bb=0; bb<YLENGTH;bb++)
                                            {
                                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                            }
                                        }
                                        currentSave->nextsave->nextsave= NULL;
                                        currentSave = start;

                                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                                        currentHelp->next = malloc(sizeof(helpNode_t));
                                        currentHelp->parent = currentTrie;
                                        currentHelp->trienext->prev = currentTrie;

                                        for(int ui =0; ui<XLENGTH; ui++)
                                        {
                                            for(int uo =0; uo<YLENGTH; uo++)
                                            {
                                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                            }
                                        }
                                        while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        if(isFirst == 1)
                                        {
                                            isFirst = 0;
                                            currentlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2 = NULL;
                                        } else{
                                            currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                            currentlist2->nextlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2->nextlist2 = NULL;
                                        }
                                        currentlist2 = list2start;
                                        /*while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        currentlist2->nextlist2 = malloc(sizeof(list2Node_t));
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2 = list2start;*/
                                        if(currentHelp->next)
                                        {
                                            currentHelp = currentHelp->next;
                                        }
                                    }
                                }
                            }else if(x==4)
                            {
                                for(int n=0;n<checkLeft(current->val,currentfieldSave);n++)
                                {
                                    moveLeft(current->val, currentfield);
                                    if(currentfield[2][5] == Car)
                                    {
                                        winstart = malloc(sizeof(winNode_t));
                                        currentwin = winstart;
                                        winstart->prevwin = NULL;
                                        winstart->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                winstart->winstep[pp][oo] = currentfield[pp][oo];
                                            }
                                        }
                                        draw(currentlist1->list1node->pf);
                                        currentwin->nextwin = malloc(sizeof(winNode_t));
                                        currentwin->nextwin->prevwin = currentwin;
                                        currentwin = currentwin->nextwin;
                                        currentwin->nextwin = NULL;
                                        for(int pp = 0; pp < XLENGTH; pp++)
                                        {
                                            for(int oo = 0; oo < YLENGTH; oo++)
                                            {
                                                currentwin->winstep[pp][oo] = currentlist1->list1node->pf[pp][oo];
                                            }
                                        }
                                        WinSteps(currentlist1->list1node);
                                        return 6;
                                    }
                                    if(!isKnown(currentfield))
                                    {
                                        while(currentSave->nextsave != NULL)
                                        {
                                            currentSave = currentSave->nextsave;
                                        }
                                        currentSave->nextsave = malloc(sizeof(saveNode_t));

                                        for(int aa=0; aa<XLENGTH;aa++)
                                        {
                                            for(int bb=0; bb<YLENGTH;bb++)
                                            {
                                                currentSave->nextsave->save[aa][bb] = currentfield[aa][bb];
                                            }
                                        }
                                        currentSave->nextsave->nextsave= NULL;
                                        currentSave = start;

                                        currentHelp->trienext = malloc(sizeof(trieNode_t));
                                        currentHelp->next = malloc(sizeof(helpNode_t));
                                        currentHelp->parent = currentTrie;
                                        currentHelp->trienext->prev = currentTrie;

                                        for(int ui =0; ui<XLENGTH; ui++)
                                        {
                                            for(int uo =0; uo<YLENGTH; uo++)
                                            {
                                                currentHelp->trienext->pf[ui][uo] = currentfield[ui][uo];
                                            }
                                        }
                                        while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        if(isFirst == 1)
                                        {
                                            isFirst = 0;
                                            currentlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2 = NULL;
                                        } else{
                                            currentlist2->nextlist2 = malloc(sizeof(list1Node_t));
                                            currentlist2->nextlist2->list2node = currentHelp->trienext;
                                            currentlist2->nextlist2->nextlist2 = NULL;
                                        }
                                        currentlist2 = list2start;
                                        /*while(currentlist2->nextlist2 != NULL)
                                        {
                                            currentlist2 = currentlist2->nextlist2;
                                        }
                                        currentlist2->nextlist2 = malloc(sizeof(list2Node_t));
                                        currentlist2->list2node = currentHelp->trienext;
                                        currentlist2 = list2start;*/
                                        if(currentHelp->next)
                                        {
                                            currentHelp = currentHelp->next;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    current = current->next;
                }
            }
            currentlist1 = currentlist1->nextlist1;
        }




        currentSave = start;

        /*
        currentlist1 = list1start;
        currentlist2 = list2start;

        currentlist1 = list1start;
        currentlist2 = list2start;

        list1start = NULL;

        list1start = malloc(sizeof(list1Node_t));
        currentlist1 = list1start;

        while(currentlist2 != NULL)
        {
            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
            currentlist1->nextlist1->nextlist1 = NULL;
            currentlist1->list1node = currentlist2->list2node;
            currentlist1 = currentlist1->nextlist1;
            currentlist2 = currentlist2->nextlist2;
        }
        currentlist1 = list1start;

        list2start = NULL;
        list2start = malloc(sizeof(list2Node_t));
        list2start->nextlist2 = NULL;
        list2start->list2node = NULL;
        currentlist2 = list2start;*/

        currentlist1 = list1start;
        currentlist2 = list2start;
        list1start = NULL;

        list1start = malloc(sizeof(list1Node_t));
        currentlist1 = list1start;
        currentlist1->list1node = currentlist2->list2node;
        currentlist1->nextlist1 = NULL;
        currentlist2 = currentlist2->nextlist2;

        while(currentlist2 != NULL)
        {
            currentlist1->nextlist1 = malloc(sizeof(list1Node_t));
            currentlist1->nextlist1->list1node = currentlist2->list2node;
            currentlist1 = currentlist1->nextlist1;
            currentlist1->nextlist1 = NULL;
            currentlist2 = currentlist2->nextlist2;
        }
        list2start = NULL;
        list2start = malloc(sizeof(list2Node_t));
        currentlist1 = list1start;
        currentlist2 = list2start;
        currentlist2->nextlist2 = NULL;
        currentlist2->list2node = NULL;

    }
    return 10;
}

//kontrolliert ob sich das gewünschte Auto am Ziel befindet
int checkWin(char Car, char field[XLENGTH][YLENGTH])
{
    if(field[2][5] == Car)
    {
        return 1;
    }else
    {
        return 0;
    }
}

void draw(char field[XLENGTH][YLENGTH])
{
    printf("_________________\n");
    for(int i = 0; i<XLENGTH; i++)
    {
        for(int j = 0; j<YLENGTH; j++)
        {
            if(isalpha(field[i][j]))
            {
                printf(" %c ",field[i][j]);
            }
            else
            {
                printf(" O ");
            }

        }
        printf("\n");
    }
}

void moveLeft(char Car, char field[XLENGTH][YLENGTH])
{
    checkCar(Car, field);
    if(CarCordY+1 <= YLENGTH && field[CarCordX][CarCordY+1] == Car)
    {
        if(CarCordY-1 > -1 && !isalpha(field[CarCordX][CarCordY-1]))
        {
            field[CarCordX][CarCordY-1] = field[CarCordX][CarCordY];

            field[CarCordX][CarCordY] = field[CarCordX][CarCordY+1];
            if(CarCordY+2 < YLENGTH && field[CarCordX][CarCordY+2] == Car)
            {
                field[CarCordX][CarCordY+1] = field[CarCordX][CarCordY+2];
                field[CarCordX][CarCordY+2] = '\0';
            }
            else
            {
                field[CarCordX][CarCordY+1] = '\0';
            }
        }
    }
}

void moveRight(char Car, char field[XLENGTH][YLENGTH])
{
    checkCar(Car, field);
    int d = carLength(Car, field);
    if(CarCordY+d <= YLENGTH && field[CarCordX][CarCordY+1] == Car)
    {
        if(CarCordY+1 < YLENGTH && !isalpha(field[CarCordX][CarCordY+d]))
        {
            while(d>0)
            {
                field[CarCordX][CarCordY+d] = field[CarCordX][CarCordY+d-1];
                field[CarCordX][CarCordY+d-1] = '\0';
                d--;
            }
        }
    }
}

int moveDown(char Car, char field[XLENGTH][YLENGTH])
{
    checkCar(Car, field);
    int d = carLength(Car, field);
    if(field[CarCordX+1][CarCordY] == Car && CarCordX+1 <= XLENGTH)
    {
        if(CarCordX+d+1 <= XLENGTH && !isalpha(field[CarCordX+d][CarCordY]))
        {
            while(d>0)
            {
                field[CarCordX+d][CarCordY] = field[CarCordX+d-1][CarCordY];
                field[CarCordX+d-1][CarCordY] = '\0';
                d--;
            }
        }
    }
    return 1;
}

int moveUp(char Car, char field[XLENGTH][YLENGTH])
{
    checkCar(Car, field);
    if(CarCordX-1 > -1 && field[CarCordX+1][CarCordY] == Car && CarCordX+carLength(Car,field) <= XLENGTH)
    {
        if(!isalpha(field[CarCordX-1][CarCordY]) && CarCordX-1 > -1)
        {
            field[CarCordX-1][CarCordY] = field[CarCordX][CarCordY];

            field[CarCordX][CarCordY] = field[CarCordX+1][CarCordY];
            if(CarCordX+2 < XLENGTH && field[CarCordX+2][CarCordY] == Car)
            {
                field[CarCordX+1][CarCordY] = field[CarCordX+2][CarCordY];
                field[CarCordX+2][CarCordY] = '\0';
            }
            else
            {
                field[CarCordX+1][CarCordY] = '\0';
            }
        }
    }
    return 1;
}

int checkCar(char Car, char field[XLENGTH][YLENGTH])
{
    for(int i = 0; i<XLENGTH; i++)
    {
        for(int j = 0; j<YLENGTH; j++)
        {
            if(field[i][j] == Car)
            {
                CarCordX = i;
                CarCordY = j;
                return 0;
            }
        }
    }
    return 0;
}

int checkCars(char field[XLENGTH][YLENGTH])
{
    int cars = 0;
    int f = 0;
    head = malloc(sizeof(node_t));
    head->val = '\0';
    head->next = NULL;
    current = head;
    for(int i = 0; i<XLENGTH; i++)
    {
        for(int j =0; j<YLENGTH; j++)
        {
            if(isalpha(field[i][j]))
            {
                while (current != NULL && current->next != NULL)
                {
                    if(current->val == field[i][j])
                    {
                        f++;
                    }
                    current = current->next;
                }
                if(f == 0)
                {
                    while (current->next != NULL)
                    {
                        current = current->next;
                    }
                    current->val = field[i][j];
                    current->next = malloc(sizeof(node_t));
                    current->next->val = '\0';
                    current->next->next = NULL;
                    cars++;
                }
                current = head;
                f = 0;
            }
        }
    }
    return cars;
}

int checkPossibilitys(char field[XLENGTH][YLENGTH])
{
    int possibilitys = 0;
    checkCars(field);
    current = head;
    for(int i = 0; i<XLENGTH; i++)
    {
        for(int j = 0; j<YLENGTH; j++)
        {
            if(field[i][j] == current->val && isalpha(field[i][j]))
            {
                possibilitys = possibilitys+checkLeft(field[i][j], field)+checkRight(field[i][j], field)+checkUp(field[i][j], field)+checkDown(field[i][j], field);
                if(current->next != NULL)
                {
                    current = current->next;
                }
            }
        }
    }
    return possibilitys;
}

int checkLeft(char Car, char field[XLENGTH][YLENGTH])
{
    int space = 0;
    for(int i =0; i<XLENGTH;i++)
    {
        for(int j = 0; j<YLENGTH;j++)
        {
            if(j+1 < YLENGTH && j-1 > -1 && field[i][j] == Car && field[i][j+1] == Car)
            {
                int d = 1;
                while(j-d > -1 && !isalpha(field[i][j-d]))
                {
                    space++;
                    d++;
                }
            }
        }
    }
    return space;
}

int checkRight(char Car, char field[XLENGTH][YLENGTH])
{
    int space = 0;
    int length = carLength(Car, field);
    for(int i = 0; i<XLENGTH; i++)
    {
        for(int j = 0; j<YLENGTH; j++)
        {
            if(j+length < YLENGTH && j+length > -1 && j+length-1 > -1 && field[i][j] == Car && field[i][j+length-1] == Car)
            {
                int d = 0;
                while(j+length+d < YLENGTH && j+d > -1 && !isalpha(field[i][j+length+d]))
                {
                    space++;
                    d++;
                }
            }
        }
    }
    return space;
}

int checkUp(char Car, char field[XLENGTH][YLENGTH])
{
    int space = 0;
    for(int i = 0; i<XLENGTH;i++)
    {
        for(int j = 0; j<YLENGTH;j++)
        {
            if(i+1 < XLENGTH && i-1 > -1 && field[i][j] == Car && field[i+1][j] == Car)
            {
                int d = 1;
                while(i-d > -1 && !isalpha(field[i-d][j]))
                {
                    space++;
                    d++;
                }
            }
        }
    }
    return space;
}

int checkDown(char Car, char field[XLENGTH][YLENGTH])
{
    int space = 0;
    int length = carLength(Car, field);
    for(int i =0; i<XLENGTH;i++)
    {
        for(int j = 0; j<YLENGTH;j++)
        {
            if(i+length-1 > -1 && i+length < XLENGTH && field[i][j] == Car && field[i+length-1][j] == Car)
            {
                int d = 0;
                while(i+length+d < XLENGTH && !isalpha(field[i+length+d][j]))
                {
                    space++;
                    d++;
                }
            }
        }
    }
    return space;
}

int carLength(char Car, char field[XLENGTH][YLENGTH])
{
    int length = 0;
    checkCar(Car, field);
    if(CarCordY+1 < YLENGTH && field[CarCordX][CarCordY+1] == Car)
    {
        int d = 0;
        while(CarCordY+d < YLENGTH && field[CarCordX][CarCordY+d] == Car)
        {
            length++;
            d++;
        }
    }else if(field[CarCordX+1][CarCordY] == Car)
    {
        int d = 0;
        while(CarCordX+d < XLENGTH && field[CarCordX+d][CarCordY] == Car)
        {
            length++;
            d++;
        }
    }
    return length;
}

bool isKnown(char field[XLENGTH][YLENGTH])
{
    int h;
    bool similar = false;
    currentSave = start;
    while(currentSave != NULL)
    {
        h=0;
        for(int o=0; o<XLENGTH;o++)
        {
            for(int q=0; q<YLENGTH;q++)
            {
                if(currentSave->save[o][q] != field[o][q])
                {
                    h++;
                }
            }
        }
        if(h == 0)
        {
            similar = true;
        }
        currentSave = currentSave->nextsave;
    }

    if(similar == false)
    {
        currentSave = start;
        return false;
    }else
    {
        currentSave = start;
        return true;
    }
}

int WinSteps(trieNode_t* trieNode)
{
    int winsteps = 1;
    while(trieNode->prev != NULL)
    {
        winsteps++;
        printf("Winsteps = %i\n", winsteps);
        trieNode = trieNode->prev;
        draw(trieNode->pf);
        currentwin->nextwin = malloc(sizeof(winNode_t));
        currentwin->nextwin->prevwin = currentwin;
        currentwin = currentwin->nextwin;
        currentwin->nextwin = NULL;
        for(int pp = 0; pp < XLENGTH; pp++)
        {
            for(int oo = 0; oo < YLENGTH; oo++)
            {
                currentwin->winstep[pp][oo] = trieNode->pf[pp][oo];
            }
        }
    }
    printf("Ende Winsteps = %i\n", winsteps);

    printf("ALLE IN WINSTEPS-LINKED LIST\n");
    currentwin = winstart;
    while(currentwin->nextwin != NULL)
    {
        currentwin = currentwin->nextwin;
    }
    int h = 0;
    while(currentwin != NULL)
    {
        for(int ii = 0; ii < XLENGTH; ii++)
        {
            for(int uu = 0; uu < YLENGTH; uu++)
            {
                h++;
            }
        }
        currentwin = currentwin->prevwin;
    }
    winarray = malloc(h * 4);
    for(int ar = 0; ar < h; ar++)
    {
        winarray[ar] = '\0';
    }
    currentwin = winstart;
    while(currentwin->nextwin != NULL)
    {
        currentwin = currentwin->nextwin;
    }

    int p = 0;
    while(currentwin != NULL)
    {
        //draw(currentwin->winstep);
        for(int ii = 0; ii < XLENGTH; ii++)
        {
            for(int uu = 0; uu < YLENGTH; uu++)
            {
                if(currentwin->winstep[ii][uu] == '\0')
                {
                    winarray[p] =  'O';
                    p++;
                }else {
                    char currchar = currentwin->winstep[ii][uu];
                    winarray[p] = currchar;
                    p++;
                }
            }
        }
        currentwin = currentwin->prevwin;
    }
    //printf("Winarray: %s\n", winarray);
    return 1;
}