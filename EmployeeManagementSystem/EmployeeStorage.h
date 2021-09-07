#ifndef  __EMPLOYEESTORAGE_H__

#define   __EMPLOYEESTORAGE_H__

#include <stdlib.h>
#include "DataModel.h"

struct EmployeeNode
{
	EmployeeNode* Next = NULL;
	Employee* Date;
};

struct EmployeeStorage
{
	//ͷָ��
	EmployeeNode* Head = NULL;
	//βָ��
	EmployeeNode* End = NULL;

	int Length = 0;

	//ʹ�ñ���������ʱ ָ��ǰ�ڵ��ָ��
	EmployeeNode* CurrentPrt = NULL;

};

EmployeeStorage* EmployeeStorage_GetNewStorage();
int EmployeeStorage_Count(EmployeeStorage* list);
bool EmployeeStorage_Insert(EmployeeStorage* list, Employee* data);
const Employee* EmployeeStorage_IndexOf(EmployeeStorage* list, int index);
bool EmployeeStorage_Delete(EmployeeStorage* list, int index);
bool EmployeeStorage_SetToHead(EmployeeStorage* list);
bool EmployeeStorage_MoveToNext(EmployeeStorage* list);
const Employee* EmployeeStorage_GetCurrentNodeData(EmployeeStorage* list);
bool EmployeeStorage_ExchangeNode(EmployeeStorage* list, int node1, int node2);
bool EmployeeStorage_SetToIndex(EmployeeStorage* list, int index);



#endif

