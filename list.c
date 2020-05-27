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
    pNode AuxNode = ListToAddElem->pFirstNode;
    if (ListToAddElem->pFirstNode == NULL){ // if the list is empty add to the head of the list
        ListToAddElem->pFirstNode = NewNode;
        NewNode->pNext = NULL;
        return SUCCESS;
    }
    /* else - moving the iterator to the end of the linked list */
    while (AuxNode->pNext != NULL){
        AuxNode = AuxNode->pNext;
    }

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

    pNode AuxNode = ListToRemoveElem->pFirstNode;

    /* case is the first elem in the linked list */
    if (ListToRemoveElem->pCompareFunc(AuxNode->Elem, ElemToRemove)){
        ListToRemoveElem->pFirstNode = AuxNode->pNext;
        ListToRemoveElem->pDestroyFunc(AuxNode->Elem);
        free(AuxNode);
        return SUCCESS;
    }
    pNode BeforeAuxNode = ListToRemoveElem->pFirstNode;
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

    ListToGetItsFirstElem - pointer to head of the linked list we want to get its first element.

  Returns:

    pointer to the first element in the linked list.

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
    if (List1 == NULL && List2 == NULL){
        return TRUE;
    }
    if (List1 == NULL || List2 == NULL){
        return FALSE;
    }
    pNode AuxNodeList1 = List1->pFirstNode;
    pNode AuxNodeList2 = List2->pFirstNode;
    while(AuxNodeList1 != NULL && AuxNodeList2 != NULL){
        if (List1->pCompareFunc(AuxNodeList1->Elem, AuxNodeList2->Elem) &&
            List2->pCompareFunc(AuxNodeList1->Elem, AuxNodeList2->Elem)){
                AuxNodeList1 = AuxNodeList1->pNext;
                AuxNodeList2 = AuxNodeList2->pNext;
            continue;
        }
        return FALSE;
    }
    if (AuxNodeList1 == NULL && AuxNodeList2 == NULL){
        return TRUE;
    }
    return FALSE;
}

void ListPrint(PList ListToBePrinted){
    if (ListToBePrinted == NULL){
        printf("[]\n");
        return;
    }
    pNode AuxNode = ListToBePrinted->pFirstNode;
    while (AuxNode != NULL){
        printf("[");
        ListToBePrinted->pPrintFunc(AuxNode->Elem);
        printf("]\n");
        AuxNode = AuxNode->pNext;
    }
}

/* int User Functions*/
PElem Int_Copy (PElem Elem){
    if (Elem == NULL){
        return NULL;
    }
    int* New_int = (int*)malloc(sizeof(int));
    if (New_int==NULL){
        printf("MALLOC ERROR");
        return NULL;
    }
    *New_int = *(int*)Elem;
    return (PElem)New_int;
}


void Int_Delete (PElem Elem){
    if (Elem == NULL){
        return;
    }
    //free ((int*)Elem);
    free ((int*)Elem);
}


BOOL Int_Compare (PElem Elem_a, PElem Elem_b){
    if ( (Elem_a == NULL) || (Elem_b == NULL) ) {
        return FALSE;
    }
    int int_a = *(int*)Elem_a , int_b = *(int*)Elem_b;
    if (int_a == int_b){
        return TRUE;
    }
    return FALSE;
}


void Int_Print (PElem Elem){
    if (Elem == NULL){
        return;
    }
    printf("%d",*(int*)Elem);
}


/* string User Functions*/
PElem String_Copy (PElem Elem){
    if (Elem == NULL){
        return NULL;
    }
    char* Elem_char = (char*)Elem;
    int Elem_length = strlen(Elem_char);
    char* New_string = (char*)malloc(Elem_length+1);
    if (New_string==NULL){
        printf("MALLOC ERROR");
        return NULL;
    }
    strcpy(New_string,(char*)Elem);
    New_string[Elem_length]='\0';
    return (PElem)New_string;
}


void String_Delete (PElem Elem){
    if (Elem == NULL){
        return;
    }
    //free ((char*)Elem);
    free (Elem);
}


BOOL String_Compare (PElem Elem_a, PElem Elem_b){
    if ( (Elem_a == NULL) || (Elem_b == NULL) ) {
        return FALSE;
    }
    return !strcmp( (char*)Elem_a , (char*)Elem_b); //verify
}

void String_Print (PElem Elem){
    if (Elem == NULL){
        return;
    }
    printf("%s",(char*)Elem);
}

int main(){
    PList Int_List=ListCreate(Int_Copy,Int_Delete,Int_Compare,Int_Print);
    PList Int_List2=ListCreate(Int_Copy,Int_Delete,Int_Compare,Int_Print);



    /* int Test*/
    int X=5 , Y=2 , Z=6;
    ListAdd(Int_List,&X);
    ListAdd(Int_List,&Y);
    ListAdd(Int_List,&Z);
    ListPrint(Int_List);

    int* a = (int*)ListGetFirst(Int_List);
    int* b = (int*)ListGetFirst(Int_List);
    int* c = (int*)ListGetNext(Int_List);
    int* d = (int*)ListGetNext(Int_List);
    int* e = (int*)ListGetFirst(Int_List);
    int* f = (int*)ListGetNext(Int_List);
    int* g = (int*)ListGetNext(Int_List);
    //int* h = (int*)ListGetNext(Int_List);
    //int* i = (int*)List_Get_Next(Int_List);
    int i=100;
    int* j = (int*)ListGetFirst(Int_List);
    printf("%d %d %d %d %d %d %d %d %d\n",*a,*b,*c,*d,*e,*f,*g,i,*j);
    X=3;
    Y=2;
    ListRemove(Int_List,&X);
    ListRemove(Int_List,&Y);
    ListPrint(Int_List);
    Z=6;
    ListAdd(Int_List,&Z);
    ListAdd(Int_List,&Z);
    ListRemove(Int_List,&Z);
    ListPrint(Int_List);
    ListCompare(Int_List, Int_List2);
    ListDestroy(Int_List);
    ListDestroy(Int_List2);



    /* String test */
    PList String_List=ListCreate(String_Copy,String_Delete,String_Compare,String_Print);
    ListAdd(String_List,"yoav");
    ListAdd(String_List,"Tehila");
    ListAdd(String_List,"Alma");
    ListPrint(String_List);
    char* k = (char*)ListGetFirst(String_List);
    char* l = (char*)ListGetFirst(String_List);
    char* m = (char*)ListGetNext(String_List);
    char* n = (char*)ListGetNext(String_List);
    char* o = (char*)ListGetFirst(String_List);
    char* p = (char*)ListGetNext(String_List);
    char* q = (char*)ListGetNext(String_List);
    char* r = (char*)ListGetNext(String_List);
    char* s = (char*)ListGetNext(String_List);
    char* t = (char*)ListGetFirst(String_List);
    printf("%s %s %s %s %s %s %s %s %s %s\n",k,l,m,n,o,p,q,r,s,t);
    ListRemove(String_List,"yoav");
    ListRemove(String_List,"Alma");
    ListPrint(String_List);
    ListAdd(String_List,"rubin");
    ListAdd(String_List,"rubin");
    ListRemove(String_List,"rubin");
    ListPrint(String_List);
    ListDestroy(String_List);




    return 0;
}
