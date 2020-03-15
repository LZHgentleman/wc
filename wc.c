#include<stdio.h>
#include<tchar.h>
#include<stdlib.h>

int charnum(char file[]) {
	
	int charnum = 0;
	FILE *fp = NULL;
	char c;
	fp = fopen(file, "r");
	if(NULL == fp){
		printf("******该文件名无效\n");
		return -1;	
	}
	printf("******文件打开成功，");
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
		printf("******该文件名无效\n");
		return -1;	
	}
	printf("******文件打开成功，");
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
		printf("******该文件名无效\n");
		return -1;	
	}
	printf("******文件打开成功，");
	c = getc(fp);	
	while(c != EOF){
		if(c == '\n') linenum ++; //统计行数。
        lc = c; //保存上一字符。	
		c=getc(fp);		
	}
	fclose(fp);
	if(lc != '\n') linenum ++;//处理末行
	return linenum;
}

int codenum(char file[])//代码行统计函数
{
    FILE *fp = NULL;
    char c;
    int codenum = 0;
    int count = 0;
    int flag = 0;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("******该文件名无效\n");
        return -1;
    }
    printf("******文件打开成功，"); 
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

int spacenum(char file[])//空行统计函数
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

int annonum(char file[])//注释行统计函数
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
	printf("******            欢迎使用WordCount小工具            ******\n");
LL1:
	printf("******            请输入文件的路径和名称             ******\n");
	scanf("%s", file);
LL2:
	printf("***********************************************************\n");	
	printf("******     请输入以下数字以实现对应功能              ******\n");
	printf("******     1.  打印文件的字符数                      ******\n");
	printf("******     2.  打印文件的词数                        ******\n");
	printf("******     3.  打印文件的行数                        ******\n");
	printf("******     4.  打印文件的代码行数，空行数和注释行数  ******\n");	
	printf("******     5.  关闭文件，退出程序                    ******\n");	
	printf("******     6.  打开新的文件                          ******\n");
	printf("******     您选择的数字是:");
	scanf("%d", &ch);
	switch(ch){
		case 1: 
			num = charnum(file); 
			if(num != -1) 
				printf("字符数为:%d\n",num);	
			break;
		case 2: 
			num = wordnum(file);
			if(num != -1)
				printf("词数为:%d\n",num);		 
			break;
		case 3: 
			num = linenum(file);
			if(num != -1)
				printf("行数为:%d\n",num);	 
			break;
		case 4:
			num1 = codenum(file);
			num2 = spacenum(file);
			num3 = annonum(file);
			if(num1 != -1 && num2 != -1 && num3 != -1)
				printf("代码行数为：%d, 空行数为：%d, 注释行数为：%d\n",num1, num2,num3);
			break;
		case 5:
			exit(0);
	    case 6:
	    	goto LL1; 
		default: 
			printf("******您输入的数字有误\n");
	}
	goto LL2;
			
}





	





