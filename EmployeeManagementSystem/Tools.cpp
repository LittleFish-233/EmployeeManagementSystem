#include "Tools.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

/// <summary>
/// �ظ�����ַ���
/// </summary>
/// <param name="char_">Ҫ������ַ���</param>
/// <param name="frequency">�ظ�����</param>
/// <param name="isLineFeed">�Ƿ���</param>
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
/// ������ʾ
/// </summary>
/// <param name="chars">������ַ���</param>
/// <param name="length">��Ļ����</param>
/// <param name="parameter">ƫ��ֵ</param>
/// <param name="if_LineFeed">�Ƿ���</param>
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
/// ���ѡ��
/// </summary>
/// <param name="chars">ѡ��</param>
/// <param name="length">��Ļ����</param>
/// <param name="optionNum">ѡ����Ŀ</param>
/// <param name="Columns">����</param>
/// <param name="parameters">ƫ����</param>
/// <param name="if_LineFeed">�Ƿ���</param>
void OutputOption(const char* chars[],int optionNum ,int length, int Columns, double* parameters, bool if_LineFeed)
{
    //һ�еĿ��
    int dan_lie = length / Columns;
    //��ǰ������ڼ���
    int danqian_lie = 0;
    //����ѡ��
    for (int i = 0; i < optionNum; i++)
    {
        //��ǰѡ��ռ���˼���
        int lie_zhanyong = (int)(strlen( chars[i]) * parameters[i] / dan_lie) + 1;
        //�ж�ռ�������Ƿ�����������
        if (lie_zhanyong > Columns)
        {
            lie_zhanyong = Columns;
        }
        //���µ�ǰ�����������
        danqian_lie += lie_zhanyong;
        //�����ǰ�������������������� ���� ����
        if (danqian_lie > Columns)
        {
            printf("\n");
            danqian_lie = lie_zhanyong;
        }
        //���ѡ��
        printf("%d�� %s", i+1, chars[i]);
        //����ʣ��ĳ���
        double kong = (double)dan_lie * lie_zhanyong - strlen(chars[i]) * parameters[i];

        //������ÿո�
        RepeatOutput(' ', (int)kong, false);
    }
    //�ж��Ƿ���
    if (if_LineFeed)
    {
        printf("\n");
    }
}

/// <summary>
/// ������
/// </summary>
/// <param name="chart">����е�����</param>
/// <param name="hang">��Ļ���</param>
/// <param name="lie">����</param>
/// <param name="parameters">����е����ݵ�ƫ����</param>
/// <param name="if_LineFeed">�Ƿ���</param>
void OutputTable(const char** chart[], int hang, int lie, double* parameters[], bool if_LineFeed)
{
    //������� ȷ���п�
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
    //�������

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
//���� ת char* ʹ�����ǵ��ͷ�

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
        des[i] = (char)(temp + 48);//accii��0��Ӧ48
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

