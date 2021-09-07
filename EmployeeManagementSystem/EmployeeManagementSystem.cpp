// EmployeeManagementSystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "EmployeeService.h"
#include "Tools.h"

void InputEmployeeInfor();
void About();
bool GenerateTable(const struct Employee** items, int count);
void OutputAllEmployeeInfor();
void FindEmployee();
void FindEmployeeById();
void FindEmployeeByName();
void EditEmployee();
void DeleteEmployee();
void SortEmployee();


EmployeeService* _employeeService = EmployeeService_GetNewService();

static char chars = '=';
static int screenLength = 100;

int main()
{
   
    while (true)
    {
        system("cls");
        printf("\n");
        RepeatOutput(chars, screenLength, true);
        CenterOutput("职工信息管理系统", screenLength, 1, true);
        printf("\n");
        CenterOutput("Powered By LittleFish", screenLength, 1, true);
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        const char* options[] = {
            "职工信息录入", "输出职工信息", "查询职工信息", "删除职工信息", "修改职工信息", "排序", "退出"
        };
        double parameters[]{
            1, 1, 1, 1,1, 1, 1
        };
        OutputOption(options,7, screenLength, 3, parameters, true);
        int a = 0;
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            InputEmployeeInfor();
            break;
        case 2:
            OutputAllEmployeeInfor();
            break;
        case 3:
            FindEmployee();
            break;
        case 4:
            DeleteEmployee();
            break; 
        case 5:
            EditEmployee();
            break;
        case 6:
            SortEmployee();
            break;
        case 7:
            About();
            return 0;
        default:
            printf("请输入1-8的数字\n");
            break;
        }
    }
    return 0;
}

void About()
{
    system("cls");
    for (int i = 0; i < 8; i++)
    {
        printf("\n");
    }
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("Powered By LittleFish", screenLength, 1, true);
    printf("\n");
    CenterOutput("2021/9/7 22:27", screenLength, 1, true);
    Sleep(5000);
}

void InputEmployeeInfor()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("职工信息录入", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    Employee* item = GetNewEmployee();
    printf("请输入职工号：");
    scanf("%lld", &item->EmployeeId);
    printf("\n请输入姓名：");
    scanf("%s", item->Name);
    printf("\n请输入性别 1 男 2 女 3 其他：");
    scanf("%d", &item->Gender);
    printf("\n请输入出生年月：");
    scanf("%s", item->BrithDay);
    printf("\n请输入学历：");
    scanf("%s", item->Education);
    printf("\n请输入职务：");
    scanf("%s", item->Job);
    printf("\n请输入工资：");
    scanf("%d", &item->wages);
    printf("\n请输入住址：");
    scanf("%s", item->Address);
    printf("\n请输入电话：");
    scanf("%s", item->Telephone);

    if (EmployeeService_Add(_employeeService, item))
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("录入职工信息成功！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    else
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("录入职工信息失败！", screenLength, 1, true);
        printf("\n");
        CenterOutput("如果重试后仍然出现此错误，请联系开发人员", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        return;
    }


}

const char*** InitTableChars(int count)
{
    const char*** chart = (const char***)malloc(sizeof(char**) * (count + 1));
    if (chart == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < count + 1; i++)
    {
        *(chart + i) = (const char**)malloc(sizeof(char*) * 10);
        if (*(chart + i) == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(*(chart + j));
            }
        }
    }
    return chart;
}

void DisposeTableChars(const char*** chart, int count)
{
    for (int j = 0; j < count; j++)
    {
        free(*(chart + j));
    }
    free(chart);
}

double** InitTableParameters(int count)
{

    double** parameters = (double**)malloc(sizeof(double*) * (count + 1));
    if (parameters == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < count + 1; i++)
    {
        *(parameters + i) = (double*)malloc(sizeof(double) * 10);
        if (*(parameters + i) == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(*(parameters + j));
            }
        }
    }
    return parameters;
}

void DisposeTableParameters(double** parameters,int count)
{
    for (int j = 0; j < count; j++)
    {
        free(*(parameters + j));
    }
    free(parameters);
}

bool GenerateTable(const struct Employee** items, int count)
{
    //行列式
    const char*** chart = InitTableChars(count);
    if (chart == NULL)
    {
        return false;
    }

    double** parameters = InitTableParameters(count);
    if (parameters == NULL)
    {
        DisposeTableChars(chart, count);
        return false;
    }



    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            *(*(parameters + i) + j) = 1;
        }
    }

    *(*(chart + 0) + 0) = "序号";
    *(*(chart + 0) + 1) = "职工号";
    *(*(chart + 0) + 2) = "姓名";
    *(*(chart + 0) + 3) = "性别";
    *(*(chart + 0) + 4) = "出生年月";
    *(*(chart + 0) + 5) = "学历";
    *(*(chart + 0) + 6) = "职务";
    *(*(chart + 0) + 7) = "工资";
    *(*(chart + 0) + 8) = "住址";
    *(*(chart + 0) + 9) = "电话";

    for (int i = 0; i < count; i++)
    {
        *(*(chart + i + 1) + 0) = itoa((long long)i + 1);
        *(*(chart + i + 1) + 1) = itoa((*(items + i))->EmployeeId);
        *(*(chart + i + 1) + 2) = (*(items + i))->Name;
        switch ((*(items + i))->Gender)
        {
        case 1:
            *(*(chart + i + 1) + 3) = "男";
            break;
        case 2:
            *(*(chart + i + 1) + 3) = "女";
            break;
        default:
            *(*(chart + i + 1) + 3) = "其他";
            break;
        }

        *(*(chart + i + 1) + 4) = (*(items + i))->BrithDay;
        *(*(chart + i + 1) + 5) = (*(items + i))->Education;
        *(*(chart + i + 1) + 6) = (*(items + i))->Job;
        *(*(chart + i + 1) + 7) = itoa((*(items + i))->wages);
        *(*(chart + i + 1) + 8) = (*(items + i))->Address;
        *(*(chart + i + 1) + 9) = (*(items + i))->Telephone;
    }

    OutputTable(chart, count + 1, 10, parameters, true);

    //注意释放内存
    DisposeTableParameters(parameters, count);
    DisposeTableChars(chart, count);


    return true;
}

void OutputAllEmployeeInfor()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("职工信息录入", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    const struct Employee** items= EmployeeService_GetAll(_employeeService);
    int count = EmployeeService_Count(_employeeService);
    if (GenerateTable(items, count) == false)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("申请内存失败，请尝试重新启动！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    //注意释放内存
    free(items);

    if (count == 0)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("还没有职工信息，请先录入职工信息！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    else
    {
        RepeatOutput(chars, screenLength, true);

        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
    }
}

void FindEmployee()
{
    while (true)
    {
        system("cls");
        printf("\n");
        RepeatOutput(chars, screenLength, true);
        CenterOutput("职工信息管理系统", screenLength, 1, true);
        printf("\n");
        CenterOutput("查询职工信息", screenLength, 1, true);
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        const char* options[] = {
            "按姓名查询", "按职工号查询","返回上级菜单"
        };
        double parameters[]{
            1, 1
        };
        OutputOption(options, 3, screenLength, 3, parameters, true);
        int a = 0;
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            FindEmployeeByName();
            break;
        case 2:
            FindEmployeeById();
            break;
        case 3:
            return;

        default:
            printf("请输入1-3的数字\n");
            break;
        }
    }
    return;
}

void FindEmployeeByName()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("按姓名查询", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    printf("请输入职工姓名：");
    char name[50];
    scanf("%s", name);
    const Employee* item= EmployeeService_FindByName(_employeeService, name);

    if (item == NULL)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("找不到该职工信息！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    else
    {
        if (GenerateTable(&item, 1) == false)
        {
            RepeatOutput(chars, screenLength, true);
            printf("\n");
            CenterOutput("申请内存失败，请尝试重新启动！", screenLength, 1, true);
            printf("\n");
            CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
            printf("\n");

            RepeatOutput(chars, screenLength, true);
            getchar();
            getchar();
            return;
        }
        else
        {
            RepeatOutput(chars, screenLength, true);

            printf("\n");
            CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
            printf("\n");

            RepeatOutput(chars, screenLength, true);
            getchar();
            getchar();
        }
    }
}

void FindEmployeeById()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("按职工号查询", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    printf("请输入职工号：");
    int id = 0;
    scanf("%d", &id);
    const Employee* item = EmployeeService_FindById(_employeeService, id);

    if (item == NULL)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("找不到该职工信息！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    else
    {
        if (GenerateTable(&item, 1) == false)
        {
            RepeatOutput(chars, screenLength, true);
            printf("\n");
            CenterOutput("申请内存失败，请尝试重新启动！", screenLength, 1, true);
            printf("\n");
            CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
            printf("\n");

            RepeatOutput(chars, screenLength, true);
            getchar();
            getchar();
            return;
        }
        else
        {
            RepeatOutput(chars, screenLength, true);

            printf("\n");
            CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
            printf("\n");

            RepeatOutput(chars, screenLength, true);
            getchar();
            getchar();
        }
    }
}

void DeleteEmployee()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("删除职工信息", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    printf("请输入职工号：");
    int id = 0;
    scanf("%d", &id);
    bool isSuccess = EmployeeService_DeleteById(_employeeService, id);

    if (isSuccess == false)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("找不到该职工信息！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
    else
    {

        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("成功删除该职工！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }
}

void EditEmployee()
{
    system("cls");
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    CenterOutput("职工信息管理系统", screenLength, 1, true);
    printf("\n");
    CenterOutput("删除职工信息", screenLength, 1, true);
    RepeatOutput(chars, screenLength, true);
    printf("\n");

    printf("请输入职工号：");
    int id = 0;
    scanf("%d", &id);
    const Employee* item = EmployeeService_FindById(_employeeService, id);

    if (item == NULL)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("找不到该职工信息！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }

    if (GenerateTable(&item, 1) == false)
    {
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        CenterOutput("申请内存失败，请尝试重新启动！", screenLength, 1, true);
        printf("\n");
        CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();
        return;
    }

    //询问修改哪一项
    RepeatOutput(chars, screenLength, true);
    printf("\n");
    CenterOutput("请选中要修改的项目", screenLength, 1, true);
    printf("\n");
    RepeatOutput(chars, screenLength, true);
    const char* options[] = {
     "姓名", "性别", "出生年月", "学历", "职务", "工资", "住址","电话"
    };
    double parameters[]{
        1, 1, 1, 1,1, 1, 1, 1
    };
    OutputOption(options, 8, screenLength, 3, parameters, true);
    int a = 0;
    scanf("%d", &a);

    Employee* temp = CopyEmployee(item);
    printf("\n请输入%s：", *(options + a-1));
    switch (a)
    {
    case 1:
        scanf("%s", temp->Name);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 2:
        scanf("%d", &temp->Gender);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 3:
        scanf("%s", temp->BrithDay);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 4:
        scanf("%s", temp->Education);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 5:
        scanf("%s", temp->Job);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 6:
        scanf("%d", &temp->wages);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 7:
        scanf("%s", temp->Address);
        EmployeeService_Edit(_employeeService, temp);
        break;
    case 8:
        scanf("%s", temp->Telephone);
        EmployeeService_Edit(_employeeService, temp);
        break;
    default:
        return;
    }

    RepeatOutput(chars, screenLength, true);

    printf("\n");
    CenterOutput("修改职工信息成功", screenLength, 1, true);
    printf("\n");
    CenterOutput("按下回车返回上级菜单", screenLength, 1, true);
    printf("\n");

    RepeatOutput(chars, screenLength, true);
    getchar();
    getchar();


}

void SortEmployee()
{
    while (true)
    {
        system("cls");
        printf("\n");
        RepeatOutput(chars, screenLength, true);
        CenterOutput("职工信息管理系统", screenLength, 1, true);
        printf("\n");
        CenterOutput("排序", screenLength, 1, true);
        RepeatOutput(chars, screenLength, true);
        printf("\n");
        const char* options[] = {
            "按职工号排序", "按姓名排序","按工资排序","退出"
        };
        double parameters[]{
            1, 1,1,1
        };
        OutputOption(options, 4, screenLength, 3, parameters, true);
        int a = 0;
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            EmployeeService_Sort(_employeeService, 1);
            break;
        case 2:
            EmployeeService_Sort(_employeeService, 2);
            break;
        case 3:
            EmployeeService_Sort(_employeeService, 3);
            break;
        case 4:
            return;

        default:
            printf("请输入1-4的数字\n");
            break;
        }
        RepeatOutput(chars, screenLength, true);

        printf("\n");
        CenterOutput("重新排序成功！", screenLength, 1, true);
        printf("\n");

        RepeatOutput(chars, screenLength, true);
        getchar();
        getchar();

    }

    return;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
