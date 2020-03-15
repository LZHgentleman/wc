#include<stdio.h>
#include<tchar.h>
#include<stdlib.h>

int charnum(char file[]) {
	
	int charnum = 0;
	FILE *fp = NULL;
	char c;
	fp = fopen(file, "r");
	if(NULL == fp){
		printf("******���ļ�����Ч\n");
		return -1;	
	}
	printf("******�ļ��򿪳ɹ���");
	c = getc(fp);
	while (c != EOF){
        c = getc(fp);
        charnum++;
    }
    fclose(fp);
    return charnum; 
}


int wordnum(char file[]){
	int wordnum = 0;
	FILE *fp = NULL;
	char c;
	fp = fopen(file, "r");
	if(NULL == fp){
		printf("******���ļ�����Ч\n");
		return -1;	
	}
	printf("******�ļ��򿪳ɹ���");
	c = fgetc(fp);
	while (c != EOF)
    {
        if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c >= '0'&&c <= '9')
        {
            while (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c >= '0'&&c <= '9' || c == '_')
            {
                c = fgetc(fp);
            }
            wordnum++;
            c = fgetc(fp);
        }
        c = fgetc(fp);
    }
    fclose(fp);
	return wordnum;	
}


int linenum(char file[]){	
	int linenum = 0;
	FILE *fp = NULL;
	char c, lc;
	fp = fopen(file, "r");
	if(NULL == fp){
		printf("******���ļ�����Ч\n");
		return -1;	
	}
	printf("******�ļ��򿪳ɹ���");
	c = getc(fp);	
	while(c != EOF){
		if(c == '\n') linenum ++; //ͳ��������
        lc = c; //������һ�ַ���	
		c=getc(fp);		
	}
	fclose(fp);
	if(lc != '\n') linenum ++;//����ĩ��
	return linenum;
}

int codenum(char file[])//������ͳ�ƺ���
{
    FILE *fp = NULL;
    char c;
    int codenum = 0;
    int count = 0;
    int flag = 0;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("******���ļ�����Ч\n");
        return -1;
    }
    printf("******�ļ��򿪳ɹ���"); 
    c = fgetc(fp);
    while (c != EOF)
    {
        if (c == '/')
        {
            c = fgetc(fp);
            if (c == '/')
            {
                flag=1;
            }
        }
        if (c != ' ')
        {
            count++;
        }
        if (count>=2 && c == '\n'&&flag==0)
        {
            codenum++;
        }
        if (c == '\n')
        {
            count = 0;
            flag = 0;
        }
        c = fgetc(fp);
    }
    fclose(fp);
    return codenum;
}

int spacenum(char file[])//����ͳ�ƺ���
{
    FILE *fp = NULL;
    char c;
    int spacenum = 0;
    int codenum = 0;
    int annonum = 0;
    int count = 0;
    fp = fopen(file, "r");
    if (fp == NULL) return -1;
    c = fgetc(fp);
    while (c != EOF)
    {
        if (c != ' ')
        {
            count++;
        }
        if (count<2&&c == '\n')
        {
            spacenum++;
        }
        if (c == '\n')
        {
            count = 0;
        }
        c = fgetc(fp);
    }
    fclose(fp);
    return spacenum;
}

int annonum(char file[])//ע����ͳ�ƺ���
{
    FILE *fp = NULL;
    char c;
    int annonum = 0;
    int count = 0;
    fp = fopen(file, "r");
    if (fp == NULL) return -1;
    c = fgetc(fp);
    while (c != EOF)
    {
        if (c == '/')
        {
            c = fgetc(fp);
            if (c == '/')
            {
                annonum++;
            }
        }
        c = fgetc(fp);
    }
    fclose(fp);
    return annonum;
}


int main(){
	char file[40];
	int ch=0;
	int num,num1,num2,num3;
	printf("***********************************************************\n");
	printf("******            ��ӭʹ��WordCountС����            ******\n");
LL1:
	printf("******            �������ļ���·��������             ******\n");
	scanf("%s", file);
LL2:
	printf("***********************************************************\n");	
	printf("******     ����������������ʵ�ֶ�Ӧ����              ******\n");
	printf("******     1.  ��ӡ�ļ����ַ���                      ******\n");
	printf("******     2.  ��ӡ�ļ��Ĵ���                        ******\n");
	printf("******     3.  ��ӡ�ļ�������                        ******\n");
	printf("******     4.  ��ӡ�ļ��Ĵ�����������������ע������  ******\n");	
	printf("******     5.  �ر��ļ����˳�����                    ******\n");	
	printf("******     6.  ���µ��ļ�                          ******\n");
	printf("******     ��ѡ���������:");
	scanf("%d", &ch);
	switch(ch){
		case 1: 
			num = charnum(file); 
			if(num != -1) 
				printf("�ַ���Ϊ:%d\n",num);	
			break;
		case 2: 
			num = wordnum(file);
			if(num != -1)
				printf("����Ϊ:%d\n",num);		 
			break;
		case 3: 
			num = linenum(file);
			if(num != -1)
				printf("����Ϊ:%d\n",num);	 
			break;
		case 4:
			num1 = codenum(file);
			num2 = spacenum(file);
			num3 = annonum(file);
			if(num1 != -1 && num2 != -1 && num3 != -1)
				printf("��������Ϊ��%d, ������Ϊ��%d, ע������Ϊ��%d\n",num1, num2,num3);
			break;
		case 5:
			exit(0);
	    case 6:
	    	goto LL1; 
		default: 
			printf("******���������������\n");
	}
	goto LL2;
			
}





	





