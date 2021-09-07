#ifndef  __DATAMODEL_H__

#define   __DATAMODEL_H__
#include <stdlib.h>
#include <string.h>

enum Gender
{
	Gender_None,
	Gender_Man,
	Gender_Woman,
	Gender_Other
};

struct Employee {
	long long EmployeeId;
	char* Name;
	Gender Gender;
	char* BrithDay;
	char* Job;
	char* Education;
	int wages;
	char* Address;
	char* Telephone;
};

Employee* GetNewEmployee();
bool DisposeEmployee(Employee* item);
Employee* CopyEmployee(const struct Employee* item);


#endif
