#include "Tools.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

/// <summary>
/// 重复输出字符串
/// </summary>
/// <param name="char_">要输出的字符串</param>
/// <param name="frequency">重复次数</param>
/// <param name="isLineFeed">是否换行</param>
 void RepeatOutput(const char char_, int frequency, bool isLineFeed)
{
    for (int i = 0; i < frequency; i++)
    {
        printf("%c", char_);
    }
    if (isLineFeed)
    {
        printf("\n");
    }
}

/// <summary>
/// 居中显示
/// </summary>
/// <param name="chars">输出的字符串</param>
/// <param name="length">屏幕长度</param>
/// <param name="parameter">偏移值</param>
/// <param name="if_LineFeed">是否换行</param>
 void CenterOutput(const char* chars, int length, double parameter, bool if_LineFeed)
{
    int length_front = (int)((length - strlen(chars) * parameter) / 2);

    RepeatOutput(' ', length_front, false);

    printf("%s",chars);

    RepeatOutput(' ', length_front, false);

    if (if_LineFeed == true)
    {
        printf("\n");
    }
}

/// <summary>
/// 输出选项
/// </summary>
/// <param name="chars">选项</param>
/// <param name="length">屏幕长度</param>
/// <param name="optionNum">选项数目</param>
/// <param name="Columns">列数</param>
/// <param name="parameters">偏移量</param>
/// <param name="if_LineFeed">是否换行</param>
void OutputOption(const char* chars[],int optionNum ,int length, int Columns, double* parameters, bool if_LineFeed)
{
    //一列的宽度
    int dan_lie = length / Columns;
    //当前输出到第几列
    int danqian_lie = 0;
    //遍历选项
    for (int i = 0; i < optionNum; i++)
    {
        //当前选项占用了几列
        int lie_zhanyong = (int)(strlen( chars[i]) * parameters[i] / dan_lie) + 1;
        //判断占用列数是否大于最大列数
        if (lie_zhanyong > Columns)
        {
            lie_zhanyong = Columns;
        }
        //更新当前输出到的列数
        danqian_lie += lie_zhanyong;
        //如果当前输出的列数大于最大列数 换行 重置
        if (danqian_lie > Columns)
        {
            printf("\n");
            danqian_lie = lie_zhanyong;
        }
        //输出选项
        printf("%d） %s", i+1, chars[i]);
        //计算剩余的长度
        double kong = (double)dan_lie * lie_zhanyong - strlen(chars[i]) * parameters[i];

        //输出后置空格
        RepeatOutput(' ', (int)kong, false);
    }
    //判断是否换行
    if (if_LineFeed)
    {
        printf("\n");
    }
}

/// <summary>
/// 输出表格
/// </summary>
/// <param name="chart">表格中的数据</param>
/// <param name="hang">屏幕宽度</param>
/// <param name="lie">列数</param>
/// <param name="parameters">表格中的数据的偏移量</param>
/// <param name="if_LineFeed">是否换行</param>
void OutputTable(const char** chart[], int hang, int lie, double* parameters[], bool if_LineFeed)
{
    //遍历表格 确定列宽
    int* lie_kuan = (int*)malloc(sizeof(int) * lie);
    for (int i = 0; i < lie; i++)
    {
        double kuan_zui = 0;
        for (int k = 0; k < hang; k++)
        {
            if (strlen(*(*(chart+k)+i)) /* *(*(parameters + k))[i] */> kuan_zui)
            {
                kuan_zui = strlen(*(*(chart + k) + i));//* (*(parameters + k))[i];
            }
        }
        *(lie_kuan+i) = (int)kuan_zui;
    }
    //遍历输出

    for (int k = 0; k < hang; k++)
    {
        for (int i = 0; i < lie; i++)
        {
            int a = *(lie_kuan + i);
            const char* b = (*(*(chart + k) + i));
            int c =  1; // (*(parameters + k))[i];


            double kong = a - strlen(b) * c;
            printf("%s", b);

            RepeatOutput(' ', (int)kong, false);
          
            printf(" | ");
        }
        if (k == 0)
        {
            printf("\n");
            for (int i = 0; i < lie; i++)
            {
                double kong = *(lie_kuan+i);
                for (int m = 0; m < kong; m++)
                {
                    printf("-");
                }
                printf(" | ");
            }
        }
        printf("\n");
    }
    if (if_LineFeed == true)
    {
        printf("\n");
    }

    free(lie_kuan);
}
//数字 转 char* 使用完后记得释放

char* itoa(long long src)
{
    long long temp = -1;
    long long tv = src > 0 ? src : -src;
    long long length = 0;
    while ((tv = tv / 10) > 0) {
        length++;
    }
    length++;
    tv = src > 0 ? src : -src;
    char* des = (char*)malloc(sizeof(char) * (int)(length + 1));
    if (des == NULL)
    {
        return NULL;
    }
    memset(des, 0, (int)length + 1);
    for (long long i = 0; i < length; i++) {
        long long v = 1;
        for (long long j = length - i; j > 1; j--) {
            v = v * 10;
        }
        temp = tv / (v);
        des[i] = (char)(temp + 48);//accii码0对应48
        if (temp == 0) {
            temp = 1;
        }
        tv = tv % (temp * v);
    }
    des[length] = '\0';
    if (src < 0) {
        char* nSrc = (char*)malloc((strlen(des) + 2) * sizeof(char));
        if (nSrc == NULL)
        {
            return NULL;
        }
        sprintf(nSrc, "-%s", des);
        free(des);
        des = nSrc;
    }
    return des;
}

