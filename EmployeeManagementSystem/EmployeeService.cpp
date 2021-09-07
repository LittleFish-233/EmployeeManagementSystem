#include "EmployeeService.h"

//初始化
EmployeeService* EmployeeService_GetNewService()
{
	EmployeeService* temp = (EmployeeService*)malloc(sizeof(EmployeeService));
	if (temp == NULL)
	{
		return NULL;
	}
	
	temp->EmployeeStorage = EmployeeStorage_GetNewStorage();
	return temp;
}
//获取链表中节点个数
int EmployeeService_Count(EmployeeService* service)
{
	return EmployeeStorage_Count(service->EmployeeStorage);
}

//添加员工
bool  EmployeeService_Add(EmployeeService* service, Employee* item)
{
	return EmployeeStorage_Insert(service->EmployeeStorage, item);
}

//获取所有职工信息 按现有排序获取
const struct Employee** EmployeeService_GetAll(EmployeeService* service)
{
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return NULL;
	}
	//为保存结果的指针数组分配内存
    const struct Employee** result = (const struct Employee**)malloc(sizeof( Employee*) * count);
	if (result == NULL)
	{
		return NULL;
	}
	EmployeeStorage_SetToHead(service->EmployeeStorage);
	do
	{
		*result = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);
		result++;
	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	//将结果指针复位
	result -= count;
	return result;
}

//获取指定姓名的职工
const struct Employee* EmployeeService_FindByName(EmployeeService* service,const char* name)
{
	//检查是否为空
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return NULL;
	}

	EmployeeStorage_SetToHead(service->EmployeeStorage);
	do
	{
		const struct Employee* temp = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);
		if (strcmp(temp->Name,name) == 0)
		{
			//相同则返回
			return temp;
		}

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	return NULL;
}

//获取指定职工号的职工
const struct Employee* EmployeeService_FindById(EmployeeService* service, long long id)
{
	//检查是否为空
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return NULL;
	}

	EmployeeStorage_SetToHead(service->EmployeeStorage);
	do
	{
		const struct Employee* temp = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);
		if (temp == NULL)
		{
			return NULL;
		}
		if (temp->EmployeeId==id)
		{
			//相同则返回
			return temp;
		}

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	return NULL;
}

//删除职工
bool  EmployeeService_DeleteById(EmployeeService* service, long long id)
{
	//检查是否为空
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return false;
	}
	int index = 0;
	EmployeeStorage_SetToHead(service->EmployeeStorage);
	do
	{
		const struct Employee* temp = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);
		if (temp->EmployeeId == id)
		{
			//相同则返回
			break;
		}

		index++;

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	//拿到索引后调用删除
	return EmployeeStorage_Delete(service->EmployeeStorage, index);

}

//修改职工 根据职工号进行索引
bool  EmployeeService_Edit(EmployeeService* service, Employee* item)
{
	//先删除
	if (EmployeeService_DeleteById(service, item->EmployeeId)==false)
	{
		return false;
	}
	//后添加
	if (EmployeeService_Add(service, item) == false)
	{
		return false;
	}

	return true;
}
//排序 封装后会多一层循环 但是我不关心
//1 职工号 2 姓名 3 工资
bool EmployeeService_Sort(EmployeeService* service,int type)
{
	//检查是否为空
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return false;
	}
	//冒泡排序
	for (int i = 0; i < count; i++)
	{
		//上一个节点
		//设置到指定索引
		EmployeeStorage_SetToHead(service->EmployeeStorage);
		const struct Employee* node1 = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);

		for (int j = 0; j < count - i - 1; j++)
		{
			EmployeeStorage_MoveToNext(service->EmployeeStorage);
			const struct Employee* node2 = EmployeeStorage_GetCurrentNodeData(service->EmployeeStorage);

			switch (type)
			{
			case 1:
				if (node1->EmployeeId > node2->EmployeeId)
				{
					EmployeeStorage_ExchangeNode(service->EmployeeStorage, j, j + 1);
					EmployeeStorage_MoveToNext(service->EmployeeStorage);
				}
				else
				{
					node1 = node2;
				}
				break;
			case 2:
				if (strcmp(node1->Name, node2->Name) > 0)
				{
					EmployeeStorage_ExchangeNode(service->EmployeeStorage, j, j + 1);
					EmployeeStorage_MoveToNext(service->EmployeeStorage);
				}
				else
				{
					node1 = node2;
				}
				break;
			case 3:
				if (node1->wages > node2->wages)
				{
					EmployeeStorage_ExchangeNode(service->EmployeeStorage, j, j + 1);
					EmployeeStorage_MoveToNext(service->EmployeeStorage);
				}
				else
				{
					node1 = node2;
				}
				break;
			default:
				return false;
			}

		}
	}

	return false;
}
