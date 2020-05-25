#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_* PList;
typedef void* PElem;


/*User functions*/
typedef PElem (*pCloneElemFunc)(PElem Elem);
typedef PElem (*pDestroyElemFunc)(PElem ElemToDestroy);
typedef BOOL (*pCompareElemsFunc)(PElem Elem1, PElem Elem2);
typedef void (*pPrintElemFunc)(PElem Elem);


/*Interface functions*/
PList ListCreate(pCloneElemFunc pClone_Func, pDestroyElemFunc pDestroy_Func,
                pCompareElemsFunc pCompare_Func, pPrintElemFunc pPrint_Func);
void ListDestroy(PList ListToDestroy);
Result ListAdd(PList ListToAddElem, PElem ElemToAddIn);
Result ListRemove(PList ListToRemoveElem, PElem ElemToRemove);
PElem ListGetFirst(PList ListToGetItsFirstElem);
PElem ListGetNext(PList ListToGetItsIteratorValue);
BOOL ListCompare(PList List1, PList List2); /* Compare between List1 and List2 */
void ListPrint(PList ListToBePrinted);

#endif
