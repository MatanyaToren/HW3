//
// Created by Shlomi Shitrit on 26/05/2020.
//

/*

  File: list.c

  Abstract:

    linked list with ADT

*/

/* includes */

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

/*

  Function: ListCreate

  Abstract:

    Create new linked list of ADT.

  Parameters: user functions

    pClone_Func   - pointer to function that clone an element
    pDestroy_Func - pointer to function that destroy an element
    pCompare_Fun  - pointer to function that compare between 2 elements
    pPrint_Func   -  pointer to function that print an element

  Returns:

    Pointer to head of a new linked list

*/

PList ListCreate(pCloneElemFunc pClone_Func, pDestroyElemFunc pDestroy_Func,
                 pCompareElemsFunc pCompare_Func, pPrintElemFunc pPrint_Func){
    if(pClone_Func == NULL || pDestroy_Func == NULL || pCompare_Func == NULL || pPrint_Func == NULL){
        return NULL;
    }
    /* allocating memory for the new linked list */
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

/*

  Function: ListDestroy

  Abstract:

    Destroy linked list of ADT.

  Parameters:

    ListToDestroy - pointer to head of the linked list we want to destroy.

  Returns: --

*/

void ListDestroy(PList ListToDestroy){
    if (ListToDestroy == NULL){
        return;
    }

    ListToDestroy->Iterator = ListToDestroy->pFirstNode;

    while(ListToDestroy->Iterator != NULL){
        ListToDestroy->pDestroyFunc(ListToDestroy->Iterator->Elem);
        free(ListToDestroy->Iterator);
        ListToDestroy->Iterator = ListToDestroy->Iterator->pNext;
    }
}


/*

  Function: ListAdd

  Abstract:

    Add Element to the end of the linked list.

  Parameters:

    ListToAddElem - pointer to head of the linked list we want to add in an element.
    ElemToAddIn   - pointer to an element to add to the end of the list.


  Returns: RESULT - FAIL or SUCCESS if add

*/

Result ListAdd(PList ListToAddElem, PElem ElemToAddIn){
    if (ListToAddElem == NULL || ElemToAddIn == NULL){
        return FAIL;
    }
    /* moving the iterator to the end of the linked list */
    while (ListToAddElem->Iterator->pNext != NULL){
        ListToAddElem->Iterator = ListToAddElem->Iterator->pNext;
    }
    /* allocating memory to the new Node */
    pNode NewNode = (pNode)malloc(sizeof(Node));
    if (NewNode == NULL){
        return FAIL;
    }
    /* add in the new element */
    PElem NewElem = ListToAddElem->pCloneFunc(ElemToAddIn);
    NewNode->Elem = NewElem;
    ListToAddElem->Iterator->pNext = NewNode;
    NewNode->pNext = NULL;
    return SUCCESS;
}

/*

  Function: ListRemove

  Abstract:

    Remove Element if exist in the linked list.

  Parameters:

    ListToRemoveElem - pointer to head of the linked list we want to remove an element.
    ElemToRemove     - pointer to an element to remove from the list.


  Returns: RESULT - FAIL or SUCCESS if removed

*/

Result ListRemove(PList ListToRemoveElem, PElem ElemToRemove){

}