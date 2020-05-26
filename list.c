//
// Created by Shlomi Shitrit on 26/05/2020.
//

/*

  File: list.c

  Abstract:

    linked list with ADT

*/

/* includes */

#include "defs.h"
#include "list.h"

/* typedefs */

typedef struct Node{PElem Elem; struct Node* pNext;} Node;
typedef Node* pNode;
typedef struct List_{pNode pFirstNode;
                    pNode Iterator;
                    pCloneElemFunc pCloneFunc;
                    pDestroyElemFunc pDestroyFunc;
                    pCompareElemsFunc pCompareFunc;
                    pPrintElemFunc pPrintFunc;} List;

/* statics */


/* interface functions */
PList ListCreate(pCloneElemFunc pClone_Func, pDestroyElemFunc pDestroy_Func,
                 pCompareElemsFunc pCompare_Func, pPrintElemFunc pPrint_Func){
    if(pClone_Func == NULL || pDestroy_Func == NULL || pCompare_Func == NULL || pPrint_Func == NULL){
        return NULL;
    }
    PList NewList = (PList)malloc(sizeof(List));
    if (NewList == NULL){
        return NULL;
    }

    NewList->pFirstNode = NULL; // pointer to the first node.
    NewList->Iterator = NULL; // Iterator.
    /* pointers to user Functions */
    NewList->pCloneFunc = pClone_Func;
    NewList->pDestroyFunc = pDestroy_Func;
    NewList->pCompareFunc = pCompare_Func;
    NewList->pPrintFunc = pPrint_Func;

    return NewList;
}