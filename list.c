
//
// Created by Shlomi Shitrit on 26/05/2020.
//

/*

  File: list.c

  Abstract:

    linked list handling with ADT

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

/* interface functions */

/*

  Function: ListCreate

  Abstract:

    Create new linked list of ADT.

  Parameters: pointers to user functions

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

    pNode AuxNode = ListToDestroy->pFirstNode;

    while(AuxNode != NULL){
        pNode BeforeAuxNode = AuxNode;
        AuxNode = AuxNode->pNext;
        ListToDestroy->pDestroyFunc(BeforeAuxNode->Elem);
        free(BeforeAuxNode);
    }
    free(ListToDestroy);
}


/*

  Function: ListAdd

  Abstract:

    Add Element to the end of the linked list.

  Parameters:

    ListToAddElem - pointer to head of the linked list we want to add in an element.
    ElemToAddIn   - pointer to an element to add to the end of the list.


  Returns:

    RESULT - FAIL or SUCCESS if add

*/

Result ListAdd(PList ListToAddElem, PElem ElemToAddIn){
    if (ListToAddElem == NULL || ElemToAddIn == NULL){
        return FAIL;
    }

    /* allocating memory to the new Node */
    pNode NewNode = (pNode)malloc(sizeof(Node));
    if (NewNode == NULL){
        return FAIL;
    }
    /* creating new element by cloning */
    PElem NewElem = ListToAddElem->pCloneFunc(ElemToAddIn);
    if (NewElem == NULL){
        return FAIL;
    }
    NewNode->Elem = NewElem;

    /* add in the new element to the list */
    pNode AuxNode = ListToAddElem->pFirstNode; // aux node for iterating
    if (ListToAddElem->pFirstNode == NULL){ // if the list is empty add to the head of the list
        ListToAddElem->pFirstNode = NewNode;
        NewNode->pNext = NULL;
        return SUCCESS;
    }
    /* else - moving the iterator to the end of the linked list */
    while (AuxNode->pNext != NULL){
        AuxNode = AuxNode->pNext;
    }
    /* insert the new node to the end of the list */
    AuxNode->pNext = NewNode;
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


  Returns:

    RESULT - FAIL or SUCCESS if removed

*/

Result ListRemove(PList ListToRemoveElem, PElem ElemToRemove){
    if (ListToRemoveElem == NULL || ElemToRemove == NULL){
        return FAIL;
    }

    pNode AuxNode = ListToRemoveElem->pFirstNode; // aux node for iterating

    /* case is the first elem in the linked list */
    if (ListToRemoveElem->pCompareFunc(AuxNode->Elem, ElemToRemove)){
        ListToRemoveElem->pFirstNode = AuxNode->pNext;
        ListToRemoveElem->pDestroyFunc(AuxNode->Elem);
        free(AuxNode);
        return SUCCESS;
    }

    pNode BeforeAuxNode = ListToRemoveElem->pFirstNode; // another aux node to save the node before
    AuxNode = AuxNode->pNext;
    while (AuxNode != NULL){
        if (ListToRemoveElem->pCompareFunc(AuxNode->Elem, ElemToRemove)){
            if (AuxNode->pNext == NULL){ // case is the last element in the linked list
                BeforeAuxNode->pNext = NULL;
                ListToRemoveElem->pDestroyFunc(AuxNode->Elem);
                free(AuxNode);
                return SUCCESS;
            }
            /* case in the middle of the linked list */
            BeforeAuxNode->pNext = AuxNode->pNext;
            ListToRemoveElem->pDestroyFunc(AuxNode->Elem);
            free(AuxNode);
            return SUCCESS;
        }
        AuxNode = AuxNode->pNext;
        BeforeAuxNode = BeforeAuxNode->pNext;
    }
    return FAIL;
}


/*

  Function: ListGetFirst

  Abstract:

    Returns a pointer to the first element in the linked list.

  Parameters:

    ListToGetItsFirstElem - pointer to head of the linked list we want to get its first element.

  Returns:

    pointer to the first element in the linked list.

*/

PElem ListGetFirst(PList ListToGetItsFirstElem){
    if (ListToGetItsFirstElem == NULL){
        return NULL;
    }
    ListToGetItsFirstElem->Iterator = ListToGetItsFirstElem->pFirstNode;
    return ListToGetItsFirstElem->Iterator->Elem;
}


/*

  Function: ListGetNext

  Abstract:

    Returns a pointer to the Next element in the linked list.

  Parameters:

    ListToGetItsIteratorValue - pointer to the linked list we want to get its iterator element value after iterating.

  Returns:

    pointer to the iterator element in the linked list after iterating once.

*/

PElem ListGetNext(PList ListToGetItsIteratorValue){
    if (ListToGetItsIteratorValue == NULL){
        return NULL;
    }

    if (ListToGetItsIteratorValue->Iterator == NULL){
        return NULL;
    }
    ListToGetItsIteratorValue->Iterator = ListToGetItsIteratorValue->Iterator->pNext;

    if (ListToGetItsIteratorValue->Iterator == NULL){
        return NULL;
    }
    return ListToGetItsIteratorValue->Iterator->Elem;
}

/*

  Function: ListCompare

  Abstract:

    Compare between two lists

  Parameters:

    List1 - pointer to head of the linked 1st list we want to compare.
    List2 - pointer to head of the linked 2nd list we want to compare.

  Returns:

    BOOL - TRUE or FALSE if similar list.

*/

BOOL ListCompare(PList List1, PList List2){
    if (List1 == NULL && List2 == NULL){ // case both empty
        return TRUE;
    }
    if (List1 == NULL || List2 == NULL){ // case only one of them empty
        return FALSE;
    }
    pNode AuxNodeList1 = List1->pFirstNode; // aux node for iterating list1
    pNode AuxNodeList2 = List2->pFirstNode; // aux node for iterating list2
    while(AuxNodeList1 != NULL && AuxNodeList2 != NULL){
        if (List1->pCompareFunc(AuxNodeList1->Elem, AuxNodeList2->Elem) &&
            List2->pCompareFunc(AuxNodeList1->Elem, AuxNodeList2->Elem)){
                AuxNodeList1 = AuxNodeList1->pNext;
                AuxNodeList2 = AuxNodeList2->pNext;
            continue;
        }
        return FALSE;
    }
    /* finished iterating - case both get to the end */
    if (AuxNodeList1 == NULL && AuxNodeList2 == NULL){
        return TRUE;
    }
    return FALSE;
}

/*

  Function: ListPrint

  Abstract:

    prints the linked list elements

  Parameters:

    ListToBePrinted - pointer to the linked list we want to print

  Returns: --

*/

void ListPrint(PList ListToBePrinted){
    if (ListToBePrinted == NULL){ //case of empty list
        printf("[]\n");
        return;
    }
    pNode AuxNode = ListToBePrinted->pFirstNode; // iterator for printing
    printf("[");
    while (AuxNode != NULL){
        ListToBePrinted->pPrintFunc(AuxNode->Elem);
        AuxNode = AuxNode->pNext;
    }
    printf("]\n");
}




/*
  Function: ListCpy
  Abstract:
    Copies a List
  Parameters:
    ListToCpy - pointer to the linked list we want to copy
  Returns: 
    pointer to the new List
*/

PList ListCpy(PList ListToCpy) {
    if (!ListToCpy)
        return NULL;

    // create new empty List
    PList NewList = ListCreate(ListToCpy->pCloneFunc, ListToCpy->pDestroyFunc, ListToCpy->pCompareFunc, ListToCpy->pPrintFunc);
    if (!NewList)
        return NULL;
    
    // preserve the Iterator of the List to be copied
    pNode originalNode = ListToCpy->Iterator;
    
    // copy the first List element
    PElem tmpElem = ListGetFirst(ListToCpy);
    if (!ListAdd(NewList, tmpElem))
        return NewList;
    
    // copy the rest of the List elements
    while (( tmpElem = ListGetNext(ListToCpy) )) {
        if (!ListAdd(NewList, tmpElem))
            break;
    }

    ListToCpy->Iterator = originalNode;

    return NewList;
}
