#include "DataModel.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

Employee* GetNewEmployee()
{
	Employee* temp = (Employee*)malloc(sizeof(Employee));
	if (temp == NULL)
	{
		return NULL;
	}

	temp->Name = (char*)malloc(sizeof(char) * 50);
	if (temp->Name == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->Name) = '\0';

	temp->BrithDay = (char*)malloc(sizeof(char) * 50);
	if (temp->BrithDay == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->BrithDay) = '\0';

	temp->Job = (char*)malloc(sizeof(char) * 50);
	if (temp->Job == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->Job) = '\0';

	temp->Address = (char*)malloc(sizeof(char) * 50);
	if (temp->Address == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->Address) = '\0';

	temp->Telephone = (char*)malloc(sizeof(char) * 50);
	if (temp->Telephone == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->Telephone) = '\0';

	temp->Education = (char*)malloc(sizeof(char) * 50);
	if (temp->Education == NULL)
	{
		DisposeEmployee(temp);
		return NULL;
	}
	*(temp->Education) = '\0';

	temp->wages = 0;
	temp->EmployeeId = 0;
	temp->Gender = Gender_None;
	return temp;
}

bool DisposeEmployee(Employee* item)
{
	free(item->Name);
	free(item->BrithDay);
	free(item->Job);
	free(item->Address);
	free(item->Telephone);
	free(item->Education);
	free(item);

	return true;
}
Employee* CopyEmployee(const struct Employee* item)
{
	Employee* temp= GetNewEmployee();
	if (temp == NULL)
	{
		return NULL;
	}
	strcpy(temp->Name, item->Name);
	strcpy(temp->BrithDay, item->BrithDay);
	strcpy(temp->Job, item->Job);
	strcpy(temp->Address, item->Address);
	strcpy(temp->Telephone, item->Telephone);
	strcpy(temp->Education, item->Education);

	temp->wages = item->wages;
	temp->EmployeeId = item->EmployeeId;
	temp->Gender = item->Gender;

	return temp;
}
