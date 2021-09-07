#include "EmployeeService.h"

//��ʼ��
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
//��ȡ�����нڵ����
int EmployeeService_Count(EmployeeService* service)
{
	return EmployeeStorage_Count(service->EmployeeStorage);
}

//���Ա��
bool  EmployeeService_Add(EmployeeService* service, Employee* item)
{
	return EmployeeStorage_Insert(service->EmployeeStorage, item);
}

//��ȡ����ְ����Ϣ �����������ȡ
const struct Employee** EmployeeService_GetAll(EmployeeService* service)
{
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return NULL;
	}
	//Ϊ��������ָ����������ڴ�
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

	//�����ָ�븴λ
	result -= count;
	return result;
}

//��ȡָ��������ְ��
const struct Employee* EmployeeService_FindByName(EmployeeService* service,const char* name)
{
	//����Ƿ�Ϊ��
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
			//��ͬ�򷵻�
			return temp;
		}

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	return NULL;
}

//��ȡָ��ְ���ŵ�ְ��
const struct Employee* EmployeeService_FindById(EmployeeService* service, long long id)
{
	//����Ƿ�Ϊ��
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
			//��ͬ�򷵻�
			return temp;
		}

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	return NULL;
}

//ɾ��ְ��
bool  EmployeeService_DeleteById(EmployeeService* service, long long id)
{
	//����Ƿ�Ϊ��
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
			//��ͬ�򷵻�
			break;
		}

		index++;

	} while (EmployeeStorage_MoveToNext(service->EmployeeStorage));

	//�õ����������ɾ��
	return EmployeeStorage_Delete(service->EmployeeStorage, index);

}

//�޸�ְ�� ����ְ���Ž�������
bool  EmployeeService_Edit(EmployeeService* service, Employee* item)
{
	//��ɾ��
	if (EmployeeService_DeleteById(service, item->EmployeeId)==false)
	{
		return false;
	}
	//�����
	if (EmployeeService_Add(service, item) == false)
	{
		return false;
	}

	return true;
}
//���� ��װ����һ��ѭ�� �����Ҳ�����
//1 ְ���� 2 ���� 3 ����
bool EmployeeService_Sort(EmployeeService* service,int type)
{
	//����Ƿ�Ϊ��
	int count = EmployeeStorage_Count(service->EmployeeStorage);
	if (count == 0)
	{
		return false;
	}
	//ð������
	for (int i = 0; i < count; i++)
	{
		//��һ���ڵ�
		//���õ�ָ������
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
