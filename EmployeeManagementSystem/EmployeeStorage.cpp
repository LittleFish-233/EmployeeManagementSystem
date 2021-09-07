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

//获取链表中节点个数
int EmployeeStorage_Count(EmployeeStorage* list)
{
	return list->Length;
}

bool EmployeeStorage_Insert(EmployeeStorage* list, Employee* data)
{
	//分配内存
	EmployeeNode* temp = (EmployeeNode*)malloc(sizeof(EmployeeNode));
	if (temp == NULL)
	{
		return false;
	}
	//复制数据
	temp->Date = data;
	temp->Next = NULL;

	//将节点添加到列表尾部
	if (list->End == NULL)
	{
		//如果尾指针为空 则列表为空 需要设置头指针
		list->Head = temp;
		list->End = list->Head;
	}
	else
	{
		//将原尾节点的下一节点修改为当前节点
		list->End->Next = temp;
		//用当前节点设置为尾节点
		list->End = temp;
	}
	//链表长度+1
	list->Length++;
	return true;
} 

const Employee* EmployeeStorage_IndexOf(EmployeeStorage* list,int index)
{
	//判断是否在范围内
	if (index<0 || index>list->Length - 1)
	{
		return NULL;
	}
	//头指针不可能为空 如果为空 其他代码出现问题
	//循环读取下一个节点直到达到指定节点
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
	//判断是否在范围内
	if (index<0 || index>list->Length - 1)
	{
		return false;
	}

	//头指针不可能为空 如果为空 其他代码出现问题
	//循环读取下一个节点直到达到指定节点
	EmployeeNode* last = NULL;
	EmployeeNode* current = list->Head;
	int count = 0;
	while (count != index)
	{
		last = current;
		current = current->Next;
		count++;
	}

	//找到指定节点后 将前节点指向后节点
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
		//删除的是最后一个节点
		list->End = NULL;
	}

	//释放当前节点内存
	DisposeEmployee(current->Date);
	free(current);
	//链表长度-1
	list->Length--;

	return true;
}


//将当前节点改为头节点
bool EmployeeStorage_SetToHead(EmployeeStorage* list)
{
	list->CurrentPrt = list->Head;
	return true;
}

//将当前节点改为指定索引节点
bool EmployeeStorage_SetToIndex(EmployeeStorage* list,int index)
{
	//判断是否在范围内
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


//移动当前节点到下一节点
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

//获取当前节点数据
const Employee* EmployeeStorage_GetCurrentNodeData(EmployeeStorage* list)
{
	if (list->CurrentPrt == NULL)
	{
		return NULL;
	}

	return  list->CurrentPrt->Date;
}

//交换指定节点顺序 封装后会多一层循环 但是我不关心
bool EmployeeStorage_ExchangeNode(EmployeeStorage* list, int node1, int node2)
{
	//判断是否在范围内
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
	//设置node1<node2
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
		//查找第一个节点
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
	//查找到节点后修改指针指向
	//处理相邻的特殊情况
	if (node1 + 1 == node2)
	{
		if (node1_pre_prt == NULL)
		{
			if (node2_prt->Next == NULL)
			{
				//node2是尾节点
				list->End = node1_prt;
			}
			//node1是头节点

			list->Head = node2_prt;
			node1_prt->Next = node2_prt->Next;
			node2_prt->Next = node1_prt;


			
		}
		else
		{
			if (node2_prt->Next == NULL)
			{
				//node2是尾节点
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
				//node2是尾节点
				list->End = node1_prt;
			}
			//node1是头节点

			list->Head = node2_prt;
			node2_prt->Next = node1_prt->Next;
			node2_pre_prt->Next = node1_prt;
			node1_prt->Next = node2_prt->Next;

			
		}
		else
		{
			if (node2_prt->Next == NULL)
			{
				//node2是尾节点
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
