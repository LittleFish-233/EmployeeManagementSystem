#include "EmployeeStorage.h"



EmployeeStorage* EmployeeStorage_GetNewStorage()
{
	EmployeeStorage* temp = (EmployeeStorage*)malloc(sizeof(EmployeeStorage));
	if (temp == NULL)
	{
		return NULL;
	}
	temp->Head = NULL;
	temp->End = NULL;
	temp->Length = 0;
	temp->CurrentPrt = NULL;
	return temp;
}

//��ȡ�����нڵ����
int EmployeeStorage_Count(EmployeeStorage* list)
{
	return list->Length;
}

bool EmployeeStorage_Insert(EmployeeStorage* list, Employee* data)
{
	//�����ڴ�
	EmployeeNode* temp = (EmployeeNode*)malloc(sizeof(EmployeeNode));
	if (temp == NULL)
	{
		return false;
	}
	//��������
	temp->Date = data;
	temp->Next = NULL;

	//���ڵ���ӵ��б�β��
	if (list->End == NULL)
	{
		//���βָ��Ϊ�� ���б�Ϊ�� ��Ҫ����ͷָ��
		list->Head = temp;
		list->End = list->Head;
	}
	else
	{
		//��ԭβ�ڵ����һ�ڵ��޸�Ϊ��ǰ�ڵ�
		list->End->Next = temp;
		//�õ�ǰ�ڵ�����Ϊβ�ڵ�
		list->End = temp;
	}
	//������+1
	list->Length++;
	return true;
} 

const Employee* EmployeeStorage_IndexOf(EmployeeStorage* list,int index)
{
	//�ж��Ƿ��ڷ�Χ��
	if (index<0 || index>list->Length - 1)
	{
		return NULL;
	}
	//ͷָ�벻����Ϊ�� ���Ϊ�� ���������������
	//ѭ����ȡ��һ���ڵ�ֱ���ﵽָ���ڵ�
	EmployeeNode* temp = list->Head;
	int count = 0;
	while (count!=index)
	{
		temp = temp->Next;
		count++;
	}

	return temp->Date;
}

bool EmployeeStorage_Delete(EmployeeStorage* list,int index)
{
	//�ж��Ƿ��ڷ�Χ��
	if (index<0 || index>list->Length - 1)
	{
		return false;
	}

	//ͷָ�벻����Ϊ�� ���Ϊ�� ���������������
	//ѭ����ȡ��һ���ڵ�ֱ���ﵽָ���ڵ�
	EmployeeNode* last = NULL;
	EmployeeNode* current = list->Head;
	int count = 0;
	while (count != index)
	{
		last = current;
		current = current->Next;
		count++;
	}

	//�ҵ�ָ���ڵ�� ��ǰ�ڵ�ָ���ڵ�
	if (last == NULL)
	{
		if (current == NULL)
		{
			return false;
		}
		list->Head = current->Next;
	}
	else
	{
		last->Next = current->Next;
	}
	if (list->Length ==1)
	{
		//ɾ���������һ���ڵ�
		list->End = NULL;
	}

	//�ͷŵ�ǰ�ڵ��ڴ�
	DisposeEmployee(current->Date);
	free(current);
	//������-1
	list->Length--;

	return true;
}


//����ǰ�ڵ��Ϊͷ�ڵ�
bool EmployeeStorage_SetToHead(EmployeeStorage* list)
{
	list->CurrentPrt = list->Head;
	return true;
}

//����ǰ�ڵ��Ϊָ�������ڵ�
bool EmployeeStorage_SetToIndex(EmployeeStorage* list,int index)
{
	//�ж��Ƿ��ڷ�Χ��
	if (index<0 || index>list->Length - 1)
	{
		return false;
	}

	EmployeeStorage_SetToHead(list);

	for (int i = 0; i < index; i++)
	{
		EmployeeStorage_MoveToNext(list);
	}
	return true;
}


//�ƶ���ǰ�ڵ㵽��һ�ڵ�
bool EmployeeStorage_MoveToNext(EmployeeStorage* list)
{
	if (list->CurrentPrt == NULL)
	{
		return false;
	}
	if (list->CurrentPrt->Next==NULL)
	{
		return false;
	}
	list->CurrentPrt = list->CurrentPrt->Next;

	return true;
}

//��ȡ��ǰ�ڵ�����
const Employee* EmployeeStorage_GetCurrentNodeData(EmployeeStorage* list)
{
	if (list->CurrentPrt == NULL)
	{
		return NULL;
	}

	return  list->CurrentPrt->Date;
}

//����ָ���ڵ�˳�� ��װ����һ��ѭ�� �����Ҳ�����
bool EmployeeStorage_ExchangeNode(EmployeeStorage* list, int node1, int node2)
{
	//�ж��Ƿ��ڷ�Χ��
	if (node1<0 || node1>list->Length - 1)
	{
		return false;
	}
	if (node2<0 || node2>list->Length - 1)
	{
		return false;
	}
	if (node1 == node2)
	{
		return true;
	}
	//����node1<node2
	if (node1 > node2)
	{
		int temp = node1;
		node1 = node2;
		node2 = temp;
	}
	EmployeeNode* node1_pre_prt = NULL;
	EmployeeNode* node1_prt = NULL;
	EmployeeNode* node2_pre_prt = NULL;
	EmployeeNode* node2_prt = NULL;

	EmployeeNode* last = NULL;
	EmployeeNode* current = list->Head;

	int count = 0;
	while (count < list->Length)
	{
		//���ҵ�һ���ڵ�
		if (count == node1)
		{
			node1_pre_prt = last;
			node1_prt = current;
		}
		else if (count == node2)
		{
			node2_pre_prt = last;
			node2_prt = current;
			break;
		}


		last = current;
		current = current->Next;
		count++;
	}
	if (node1_prt == NULL || node2_prt == NULL || node2_pre_prt == NULL)
	{
		return false;
	}
	//���ҵ��ڵ���޸�ָ��ָ��
	//�������ڵ��������
	if (node1 + 1 == node2)
	{
		if (node1_pre_prt == NULL)
		{
			if (node2_prt->Next == NULL)
			{
				//node2��β�ڵ�
				list->End = node1_prt;
			}
			//node1��ͷ�ڵ�

			list->Head = node2_prt;
			node1_prt->Next = node2_prt->Next;
			node2_prt->Next = node1_prt;


			
		}
		else
		{
			if (node2_prt->Next == NULL)
			{
				//node2��β�ڵ�
				list->End = node1_prt;
			}
			node1_pre_prt->Next = node2_prt;
			node1_prt->Next = node2_prt->Next;
			node2_prt->Next = node1_prt;


		
		}
	}
	else
	{
		if (node1_pre_prt == NULL)
		{

			if (node2_prt->Next == NULL)
			{
				//node2��β�ڵ�
				list->End = node1_prt;
			}
			//node1��ͷ�ڵ�

			list->Head = node2_prt;
			node2_prt->Next = node1_prt->Next;
			node2_pre_prt->Next = node1_prt;
			node1_prt->Next = node2_prt->Next;

			
		}
		else
		{
			if (node2_prt->Next == NULL)
			{
				//node2��β�ڵ�
				list->End = node1_prt;
			}

			node1_pre_prt->Next = node2_prt;
			node2_prt->Next = node1_prt->Next;
			node2_pre_prt = node1_prt;
			node1_prt->Next = node2_prt->Next;

			
		}
	}




	return true;
}
