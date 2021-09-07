#ifndef  __EMPLOYEESERVICE_H__

#define   __EMPLOYEESERVICE_H__

#include <stdlib.h>
#include "DataModel.h"
#include "EmployeeStorage.h"
#include <string.h>

struct EmployeeService
{
	EmployeeStorage* EmployeeStorage = NULL;
};
EmployeeService* EmployeeService_GetNewService();
bool  EmployeeService_Add(EmployeeService* service, Employee* item);
const struct Employee** EmployeeService_GetAll(EmployeeService* service);
const struct Employee* EmployeeService_FindByName(EmployeeService* service, const char* name);
const struct Employee* EmployeeService_FindById(EmployeeService* service, long long id);
bool  EmployeeService_DeleteById(EmployeeService* service, long long id);
bool  EmployeeService_Edit(EmployeeService* service, Employee* item);
bool EmployeeService_Sort(EmployeeService* service, int type);
int EmployeeService_Count(EmployeeService* service);


#endif

