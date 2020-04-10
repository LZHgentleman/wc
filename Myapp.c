# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<string.h>
# include<windows.h>


//ȫ�ֱ���
char ope[5] = {0};//����ģ���д��һ��������ɵ������
char result[200] = {0};//����ģ���д������������������
char answer[200] = {0};//����ģ���д�������ַ�����������������


//��������
int judge_simplest(int a, int b);
char *creat_num(int max);
char *creat_operator();
char *creat_formula(int max_num, int op_num);
char *compute(long a, int op, long b);
char *cal(char *num1, char c, char *num2);
char *creat_answer(char *formula);


//�ж����������Ƿ���Լ�ֵĺ���
int judge_simplest(int a, int b)
{
    int temp,num1,num2;
    num1 = b;
    num2 = a;
    while(num2 != 0){//����շת�����������Լ��
        temp = num1 % num2;
        num1 = num2;
        num2 = temp;
    }
    if(num1 == 1) return 1;//a��b�����Լ��Ϊ1,֤��a��b�Ѿ�������Լ��
    return 0;
}


//����������������ַ������ĺ���
char *creat_num(int max)
{
    int j = 0;
    char *figure;//������������������
    char *temp;//������ʱ��������������ֵ�����
    figure = (char*)malloc(100 * sizeof(char));//�����ڴ�
    memset(figure, 0, 100 * sizeof(char));//��ʼ��
    temp = (char*)malloc(100 * sizeof(char));
    memset(temp, 0, 100 * sizeof(char));
    int number = 0;//��Ȼ�����ߴ���������������
    int denominator = 0;//��ĸ
    int numerator = 0;//����
    j = 0;//rand() % 10;//���������Ȼ������������ߴ�����������������Ȼ���ĸ������
    switch(j){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7: number = rand() % max + 1;//��Ȼ��
                itoa(number, temp, 10);//��������ת�����ַ���
                strcat(figure, temp);//�������ַ������ӵ�figure������
                break;
        case 8:
                do{                          //�����
                    denominator = rand() % max + 1;//��ĸ
                    numerator = rand() % max + 1;//����
                }while(numerator >= denominator || judge_simplest(numerator, denominator) == 0);
                //���Ʒ���С�ڷ�ĸ����ͨ������judge_simplest�������жϷ������ĸ�ܷ����Լ��
                //������������������ѭ���������������ɷ������ĸ
                itoa(numerator, temp, 10);
                strcat(figure, temp);
                strcat (figure,"/");
                itoa(denominator, temp, 10);
                strcat(figure, temp);
                break;
        case 9: number = rand() % max + 1;//������
                do{
                    denominator = rand() % max + 1;//��ĸ
                    numerator = rand() % max + 1;//����

                }while(numerator >= denominator || judge_simplest(numerator, denominator) == 0);
                itoa(number, temp, 10);   //���������������������������ӣ���/���ͷ�ĸƴ������
                strcat(figure, temp);
                strcat(figure, "'");
                itoa(numerator, temp, 10);
                strcat(figure, temp);
                strcat(figure,"/");
                itoa(denominator, temp, 10);
                strcat(figure, temp);
                break;
    }
    free(temp);//�ͷŶ�̬�ڴ�ռ�
    return figure;//����figure������׵�ַ
}


//�������������ĺ���
char *creat_operator()
{
    int j = 0;
    j = rand() % 4;
    switch(j){
        case 0: strcpy(ope, "+");break;
        case 1: strcpy(ope, "-");break;
        case 2: strcpy(ope, "*");break;
        case 3: strcpy(ope, "/");break;
    }
    return ope;
}


//��������ʽ�ĺ�����max_num��ʾ�����������ֵ��op_num��operator_number����ʾʽ����������ܸ���
//�ݹ�������������������������㵥Ԫ����������ʽ�ӣ�
char *creat_formula(int max_num, int op_num)
{
    char **formula;//ż��λ������㵥Ԫ������������ʽ�ӣ�������λ��������
    char *final_formula;
    final_formula = (char*)malloc(op_num * 20 * sizeof(char));
    memset(final_formula, 0, sizeof(char) * op_num * 20);
    int i = 0;
    int j = 0;
    formula = (char**)malloc((2*op_num + 1) * sizeof(char*));
    for(i=0; i< 2*op_num+1; i++){
        formula[i] = (char*)malloc(op_num * 20 * sizeof(char));
    }
    for(i=0; i< 2*op_num+1; i++){
        for(j=0; j< op_num * 20; j++){
            formula[i][j] = 0;
        }
    }
    int *n;
    n = (int*)malloc((op_num+5) * sizeof(int));
    memset(n, 0, sizeof(int) * (op_num+5));
    int sum = 0;
    int op_num2 = 0;//��ʽ����������ĸ���
    if(op_num > 1){
        op_num2 = rand() % op_num + 1;//���������ʽ����������ĸ���
        for(i = 0; i <= op_num2; i++){//������ɸ������㵥Ԫ��������ĸ��������Ϊ������ȥ��ʽ����������ĸ���
            if(i == 0){
                n[i] = rand() % (op_num - op_num2 + 1);
                sum += n[i];
            }
            else if(i > 0 && i < op_num2){
                n[i] = rand() % (op_num - op_num2 + 1 - sum);
                sum += n[i];
            }
            else if(i == op_num2)
                n[i] = op_num - op_num2 - sum;
        }
    }
    else op_num2 = op_num;
    for(i = 0; i < op_num2 + 1; i++){//����������㵥Ԫ
        if(n[i] > 0)
            strcat(formula[2*i], creat_formula(max_num, n[i]));//�ݹ���������ʽ
        else{
            strcat(formula[2*i], creat_num(max_num));//����creat_num�����������������
        }
    }
    for(i = 0; i < op_num2; i++){
        strcat(formula[2*i + 1], creat_operator());
    }
    strcat(final_formula, "(");
    for(i = 0; i <= op_num2 * 2; i++){
        strcat(final_formula, formula[i]);
        if(i < op_num2 * 2) strcat(final_formula, " ");
    }
    strcat(final_formula, ")");
    for(i = 0; i < 2 * op_num + 1; i++){
        free(formula[i]);
    }
    free (formula);
    return final_formula;
}


//�����������������㺯��
char *compute(long a, int op, long b){
    int t = 1;//Լ��ʱ����ʱ����
    int num = 0;
    int num1 = 0;
    int num2 = 0;
    int den = 0;
    char temp[200] = {0};
    if(op == 1)
        itoa(a + b, result, 10);
    else if(op == 2){
        if(a >= b)
            itoa(a - b, result, 10);
        else return "ERROR";
    }
    else if(op == 3)
        itoa(a * b, result, 10);
    else if(op == 4){
        if(b == 0) return "ERROR";
        if(a == 0) return "0";
        num1 = b;
        num2 = a;
        while(num2 != 0){//����շת�����������Լ��
            t = num1 % num2;
            num1 = num2;
            num2 = t;
        }
        num = a / num1;//Լ�ֺ�ķ���
        den = b / num1;//Լ�ֺ�ķ�ĸ
        if(num >= den){
            itoa(num / den, result, 10);
            if(num % den != 0){
                itoa(num / den, result, 10);
                strcat(result, "'");
                itoa(num % den, temp, 10);
                strcat(result, temp);
                strcat(result, "/");
                itoa(den, temp, 10);
                strcat(result, temp);
            }
        }
        else if(num < den){//
            itoa(num, result, 10);
            strcat(result, "/");
            itoa(den, temp, 10);
            strcat(result, temp);

        }
    }
    return result;
}


//�����������������ַ������ĺ���
char *cal(char *num1, char c, char *num2){
    int i = 0;
    int j = 0;
    int k = 0;
    int tag1 = 1;//��ֵΪ1��ʾ��Ȼ����2��ʾ������3Ϊ��ʾ������
    int tag2 = 1;
    int a = 0;
    int b = 0;
    int n = 0;//�ֱ�Ϊ1 2 3 4����opΪ'+'����nֵΪ1����opΪ'-'����nֵΪ2���Դ�����
    char final[200] = {0};
    char temp1[4][200] = {0};//��ŷ����ĸ�������
    char temp2[4][200] = {0};
    char tmp[200] = {0};
    int number[3][4] = {0};//�����Ȼ����������ʹ������ĸ�λ����������
                           //���������ԣ������number[i][0]
                           //����������ԣ�number[i][0]��ŷ��ӣ�number[i][1]��ŷ�ĸ��
                           //�Դ��������ԣ�number[i][0]���������number[i][1]��ŷ��ӣ�number[i][2]��ŷ�ĸ
    for(i = 0; num1[i]; i ++){
        if(num1[i] == 39){
            tag1 = 3;
            break;
        }
        else if(num1[i] == '/')
            tag1 = 2;
    }
    for(i = 0; num2[i]; i ++){
        if(num2[i] == 39){
            tag2 = 3;
            break;
        }
        else if(num2[i] == '/')
            tag2 = 2;
    }
    switch(c){
        case '+': n = 1;break;
        case '-': n = 2;break;
        case '*': n = 3;break;
        case '/': n = 4;break;
    }

    for(i=0; num1[i]; i ++){
        if(num1[i] >= '0' && num1[i] <= '9'){
            temp1[j][k ++] = num1[i];
        }
        else if(num1[i] == '/' || num1[i] == 39){
            j ++;
            k = 0;
        }
    }
    j = 0;
    k = 0;
    for(i=0; num2[i]; i ++){
        if(num2[i] >= '0' && num2[i] <= '9'){
            temp2[j][k ++] = num2[i];
        }
        else if(num2[i] == '/' || num2[i] == 39){
            j ++;
            k = 0;
        }
    }
    for(i=0; temp1[i][0] != 0; i++){
        number[0][i] = atoi(temp1[i]);
    }
    for(i=0; temp2[i][0] != 0; i++){
        number[1][i] = atoi(temp2[i]);
    }
    if(tag1 == 3){
        number[0][0] = number[0][0] * number[0][2] + number[0][1];
        number[0][1] = number[0][2];
        number[0][2] = 0;
        tag1 = 2;
    }
    if(tag2 == 3){
        number[1][0] = number[1][0] * number[1][2] + number[1][1];
        number[1][1] = number[1][2];
        number[1][2] = 0;
        tag2 = 2;
    }
    if(tag1 == 1 && tag2 == 1){
        return compute(number[0][0], n, number[1][0]);
    }
    else if(tag1 == 1 && tag2 == 2){
        if(n == 1){
            return compute(atoi(compute(atoi(compute(number[0][0], 3, number[1][1])), 1, number[1][0])), 4, number[1][1]);
        }
        else if(n == 2){
            if(atoi(compute(number[0][0], 3, number[1][1])) > number[1][0])
                return compute(atoi(compute(atoi(compute(number[0][0], 3, number[1][1])), 2, number[1][0])), 4, number[1][1]);
            else
                return "ERROR";
        }
        else if(n == 3){
            return compute(atoi(compute(number[0][0], 3, number[1][0])), 4, number[1][1]);
        }
        else if(n == 4){
            return compute(atoi(compute(number[0][0], 3, number[1][1])), 4, number[1][0]);
        }
    }
    else if(tag1 == 2 && tag2 == 1){
        if(n == 1){
            return compute(atoi(compute(number[0][0], 1, atoi(compute(number[0][1], 3, number[1][0])))), 4, number[0][1]);
        }
        else if(n == 2){
            if(number[0][0] > atoi(compute(number[0][1], 3, number[1][0])))
                return compute(atoi(compute(number[0][0], 2, atoi(compute(number[0][1], 3, number[1][0])))), 4, number[0][1]);
            else
                return "ERROR";
        }
        else if(n == 3){
            return compute(atoi(compute(number[0][0], 3, number[1][0])), 4, number[0][1]);
        }
        else if(n == 4){
            return compute(number[0][0], 4, atoi(compute(number[0][1], 3, number[1][0])));
        }
    }
    else if(tag1 == 2 && tag2 == 2){
        if(n == 1){
            return compute(atoi(compute(atoi(compute(number[0][0], 3, number[1][1])), 1,
                                        atoi(compute(number[0][1], 3, number[1][0])))), 4, atoi(compute(number[0][1], 3, number[1][1])));
        }
        else if(n == 2){
            if(atoi(compute(number[0][0], 3, number[1][1])) > atoi(compute(number[0][1], 3, number[1][0])))
                return compute(atoi(compute(atoi(compute(number[0][0], 3, number[1][1])), 2,
                                        atoi(compute(number[0][1], 3, number[1][0])))), 4, atoi(compute(number[0][1], 3, number[1][1])));
            else
                return "ERROR";
        }
        else if(n == 3){
            return compute(atoi(compute(number[0][0], 3, number[1][0])) , 4, atoi(compute(number[0][1], 3, number[1][1])));
        }
        else if(n == 4){
            return compute(atoi(compute(number[0][0], 3, number[1][1])) , 4, atoi(compute(number[0][1], 3, number[1][0])));
        }
    }
}


//����ʽ�ӽ���ĺ���������ֵΪ�ַ���
//�������ţ���ݹ���������������ڲ����ţ�Ȼ���������������
char *creat_answer(char *formula){
    int i = 0;
    int j = 0;
    int k = 0;
    int k1 = 0;
    int k2 = 0;
    int n = 0;
    int m = 0;
    int s = 0;
    int flag = 0;
    int tag[100] = {0};
    char ope[20] = {0};
    char b[200] = {0};
    char unit[10][200] = {0};
    char temp[10][200] = {0};//���һ�������ĳ˳�ʽ�ӵĽ��������
    for(i = 0; formula[i]; i++){
        if(flag == 0){
            if(formula[i] == '('){
                flag ++;
                tag[i + 1] = 10;
            }
            else if(formula[i] >= '0' && formula[i] <= '9' || formula[i] == 39){
                tag[i] = 1;
            }
            else if(formula[i] == '/'){
                if(tag[i - 1] == 1)
                    tag[i] = 1;
                else
                    tag[i] = 2;
            }
            else if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*')
                tag[i] = 2;

        }
        else if(flag != 0){
            if(formula[i] == '('){
                flag ++;
                tag[i] = 10;
            }
            else if(formula[i] == ')'){
                flag --;
                if(flag != 0)
                    tag[i] = 10;
                else
                    tag[i] = 0;
            }
            else
                tag[i] = 10;
        }
    }
    for(i = 0; formula[i]; i++){
        if(tag[i] == 1){
            unit[j][k ++] = formula[i];
            if(tag[i + 1] == 0){//��i��һ����Ԫ�Ľ���
                j ++;//�����µ�һά����
                k = 0;//k�ص�0ֵ
            }
        }
        else if(tag[i] == 2){
            ope[n ++] = formula[i];
        }
        else if(tag[i] == 10){
            unit[j][k ++] = formula[i];
            if(tag[i + 1] == 0){//��i��һ����Ԫ�Ľ���
       //         f[t ++] = j + 1;//���unit�ĵڼ���Ԫ��Ϊʽ��
                j ++;//�����µ�һά����
                k = 0;//k�ص�0ֵ
            }
        }
    }
    for(i = 0; unit[0][i] != 0; i ++){
        if(unit[0][i] == '+' || unit[0][i] == '-' || unit[0][i] == '*' || unit[0][i] == '/' && unit[0][i - 1] == ' '){
            strcpy(temp[0], creat_answer(unit[0]));
            if(0 == strcmp(temp[0], "ERROR")) return "ERROR";
            break;
        }
        else
            strcpy(temp[0], unit[0]);
    }
    j = 0;
    m = 0;
    for(i = 0; ope[i] != 0; i++){
        k1 = 0;
        k2 = 0;
        for(j = 0; unit[i][j] != 0; j ++){
            if(unit[i][j] == '+' || unit[i][j] == '-' || unit[i][j] == '*' || unit[i][j] == '/' && unit[i][j - 1] == ' '){
                k1 = 1;
                break;
            }
        }
        for(j = 0; unit[i + 1][j] != 0; j ++){
            if(unit[i + 1][j] == '+' || unit[i + 1][j] == '-' || unit[i + 1][j] == '*' || unit[i + 1][j] == '/' && unit[i + 1][j - 1] == ' '){
                k2 = 1;
                break;
            }
        }
        strcpy(b, creat_answer(unit[i + 1]));
        if(0 == strcmp(b, "ERROR")) return "ERROR";
        if(ope[i] == '*' || ope[i] == '/'){
            if(k2 == 1)
                strcpy(temp[m], cal(temp[m], ope[i], b));
            else if(k2 == 0)
                strcpy(temp[m], cal(temp[m], ope[i], unit[i + 1]));
        }
        else if(ope[i] == '+' || ope[i] == '-'){
            m ++;
            if(k2 == 1)
                strcpy(temp[m], b);
            else if(k2 == 0)
                strcpy(temp[m], unit[i + 1]);
        }
    }
    k1 = 0;
    s = 0;
    strcpy(answer, temp[0]);
    for(i = 1; temp[i][0] != 0; i ++){
        while(ope[s] == '*' || ope[s] == '/') s ++;
        if(0 != strcmp(answer, "ERROR") && 0 != strcmp(temp[i], "ERROR"))
            strcpy(answer, cal(answer, ope[s ++], temp[i]));
        else
            return "ERROR";
    }
    return answer;
}


//�ж���������ʽ�Ƿ��ظ��ĺ���
int judge_repetitive(char *formula1, char *formula2)
{

}




//������
int main(int argc, char *argv[]){
L1: srand((unsigned)time(NULL));//���������������
    char *temp;
    char temp2[100] = {0};
    char **answer;
    char *p;
    char sc1[100] = {0};
    char sc2[100] = {0};
    char cha1[10] = {0};
    char cha2[10] = {0};
    char num1[20] = {0};
    char num2[20] = {0};
    char judge[10] = {0};
    char times[100] = {0};
    char order[20] = {0};
    char sum1[10] = {0};
    char sum2[10] = {0};
    char **cor;
    char **wro;
    char exe[200] = {0};
    char ans[100] = {0};
    char a1[100] = {0};
    char unit[7][50] = {0};
    char unit2[7][50] = {0};
    char flag[100] = {0};
    char flag2[100] = {0};
    int i = 0;
    int j = 0;
    int t = 0;
    int k = 0;
    int sum = 0;
    int n = 0;
    int m = 0;
    int r = 0;
    int ch = 0;
    int correct = 0;
    int wrong = 0;
    int row = 0;
    FILE *fpe, *fpa, *fpg;

    printf("\n%s\nPlease enter '-n <number>' or '-r maximum>'\n", argv[0]);
    printf("or '-n <number> -r <maximum>' or '-r <maximum> -n <number>'(1 <= n <=10000, 1 <= r <= 1000)\n");
    printf("or '-e <exercisefile>.txt -a <answerfile>.txt': ");
    gets(sc1);
    for(i = 0; sc1[i]; i++){
        if(sc1[i] != ' ')
            flag[i] = 1;
    }
    j = 0;
    k = 0;
    for(i = 0; sc1[i]; i++){
        if(flag[i] == 1)
            unit[j][k ++] = sc1[i];
        else if(flag[i] == 0 && flag[i + 1] != 0){
            j ++;
            k = 0;
        }
    }

    if(0 == strcmp(unit[0], "-n")){
        if(atof(unit[1]) - atoi(unit[1]) < 0.000001 && atoi(unit[1]) > 0 && atoi(unit[1]) < 10001){
            n = atoi(unit[1]);
            if(unit[2][0] == 0){
                printf("\nPlease enter '-r <maximum>'(1 <= r <= 1000): ");
                gets(sc2);
                for(i = 0; sc2[i]; i++){
                    if(sc2[i] != ' ')
                        flag2[i] = 1;
                }
                j = 0;
                k = 0;
                for(i = 0; sc2[i]; i++){
                    if(flag2[i] == 1)
                        unit2[j][k ++] = sc2[i];
                    else if(flag2[i] == 0 && flag2[i + 1] != 0){
                        j ++;
                        k = 0;
                    }
                }
                if(0 == strcmp(unit2[0], "-r")){
                    if(atof(unit2[1]) - atoi(unit2[1]) < 0.000001 && atoi(unit2[1]) > 0 && atoi(unit2[1]) < 1001)
                        r = atoi(unit2[1]);
                    else{
                        printf("\nThe parameter you entered is illegal.\n");
                        goto L1;
                    }
                }
                else{
                    printf("\nThe function you entered is illegal.\n");
                    goto L1;
                }
            }
            else if(unit[2][0] != 0){
                if(0 == strcmp(unit[2], "-r")){
                    if(atof(unit[3]) - atoi(unit[3]) < 0.000001 && atoi(unit[3]) > 0 && atoi(unit[3]) < 1001)
                        r = atoi(unit[3]);
                    else{
                        printf("\nThe second parameter you entered is illegal.\n");
                        goto L1;
                    }
                }
                else{
                    printf("\nThe second function you entered is illegal.\n");
                    goto L1;
                }
            }
        }
        else{
            printf("\nThe first parameter you entered is illegal.\n");
            goto L1;
        }
    }
    else if(0 == strcmp(unit[0], "-r")){
        if(atof(unit[1]) - atoi(unit[1]) < 0.000001 && atoi(unit[1]) > 0 && atoi(unit[1]) < 1001){
            r = atoi(unit[1]);
            if(unit[2][0] == 0){
                printf("\nDo you want to specify the total number of questions? 1 for yes,0 for no: ");
                gets(judge);
                if(2 == atoi(judge)) n = 10000;
                else if(1 == atoi(judge)){
                    printf("\nPlease enter '-n <number>'(1 <= n <=10000): ");
                    gets(sc2);
                    for(i = 0; sc2[i]; i++){
                    if(sc2[i] != ' ')
                        flag2[i] = 1;
                    }
                    j = 0;
                    k = 0;
                    for(i = 0; sc2[i]; i++){
                        if(flag2[i] == 1)
                            unit2[j][k ++] = sc2[i];
                        else if(flag2[i] == 0 && flag2[i + 1] != 0){
                            j ++;
                            k = 0;
                        }
                    }

                    if(0 == strcmp(unit2[0], "-n")){
                        if(atof(unit2[1]) - atoi(unit2[1]) < 0.000001 && atoi(unit2[1]) > 0 && atoi(unit2[1]) < 10001)
                            n = atoi(unit2[1]);
                        else{
                            printf("\nThe second parameter you entered is illegal.\n");
                            goto L1;
                        }
                    }
                    else{
                        printf("\nThe second function you entered is illegal.\n");
                        goto L1;
                    }
                }
                else{
                    printf("\nThe number you entered is illegal.");
                    goto L1;
                }
            }
            else if(unit[2] != 0){
                if(0 == strcmp(unit[2], "-n")){
                    if(atof(unit[3]) - atoi(unit[3]) < 0.000001 && atoi(unit[3]) >= 0 && atoi(unit[3]) < 10001)
                        n = atoi(unit[3]);
                    else{
                        printf("\nThe second parameter you entered is illegal.\n");
                        goto L1;
                    }
                }
                else{
                    printf("\nThe second function you entered is illegal.\n");
                    goto L1;
                }
            }
        }
        else{
                printf("\nThe first parameter you entered is illegal.\n");
                goto L1;
        }

    }
    else if(0 == strcmp(unit[0], "-e") && 0 == strcmp(unit[2], "-a"));

    else{
        printf("\nThe function you entered is illegal.\n");
        goto L1;
    }
    if(n > 0){

        answer = (char**)malloc(n * sizeof(char*));
        for(i=0; i < n; i++){
            answer[i] = (char*)malloc(50 * sizeof(char));
        }
        for(i=0; i < n; i++){
            for(j=0; j < 50; j++){
                answer[i][j] = 0;
            }
        }
        if((fpe = fopen("Exercises.txt","w")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }
        if((fpa = fopen("Answers.txt","w")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }
        m = n;
        i = 0;
        sum = 0;
        while(i < m){
            j = rand() % 3 + 1;
            temp = (char*)malloc(j * 30 * sizeof(char));
            memset(temp, 0, sizeof(char) * j * 30);
            strcpy(temp, creat_formula(r, j));
            for(p = temp; *p; p++);
            *(--p)='\0';
            for(k = 0; temp[k] != '\0'; k++){ //i��1��ʼ����ʾ�ӵڶ���Ԫ�ؿ�ʼǰ��
                temp[k]=temp[k+1];
            }
            temp[k]=temp[k+1];
            strcpy(temp2, creat_answer(temp));
            strcat(temp, " = ");
            if(0 != strcmp(temp2, "ERROR")){
                itoa(sum + 1, times, 10);
                strcat(times, ". ");
                fputs(times, fpe);
                fputs(temp, fpe);
                fputc('\n', fpe);
                fputs(times, fpa);
                fputs(temp2, fpa);
                fputc('\n', fpa);
                printf("%8d. %s", sum + 1, temp);
                printf("%s", temp2);
                strcpy(answer[sum], temp2);
                sum ++;
                printf("\n\n");
            }
            else m ++;
            i++;
            free(temp);
        }
        fclose(fpe);
        fclose(fpa);
        for(i = 0; i < n; i++){
            free(answer[i]);
        }
        free (answer);
    }


    else if(n == 0){
        correct = 0;
        wrong = 0;
        m = 0;
        if((fpe = fopen("Exercises.txt","r")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }
        while(fgets(exe, sizeof(exe), fpe) != NULL){
            m ++;
        }
        fclose(fpe);
        cor = (char**)malloc((m+5) * sizeof(char*));
        for(i=0; i < m+5; i++){
            cor[i] = (char*)malloc(20 * sizeof(char));
        }
        for(i=0; i < m+5; i++){
            for(j=0; j < 20; j++){
                cor[i][j] = 0;
            }
        }

        wro = (char**)malloc((m+5) * sizeof(char*));
        for(i=0; i < m+5; i++){
            wro[i] = (char*)malloc(20 * sizeof(char));
        }
        for(i=0; i < m+5; i++){
            for(j=0; j < 20; j++){
                wro[i][j] = 0;
            }
        }

        if((fpe = fopen(unit[1],"r")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }
        if((fpa = fopen(unit[3],"r")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }
        if((fpg = fopen("Grade.txt","w")) == NULL)
        {
            printf("\nopen file Fail,close!");
            getchar();
            exit(1);
        }

        k = 0;
        t = 0;
        while(fgets(exe, sizeof(exe), fpe) != NULL && fgets(ans, sizeof(ans), fpa) != NULL){
            i = 0;
            ch = 0;
            j = 0;
            while(exe[i] != '.'){
                if(exe[i] >= '0' && exe[i] <= '9')
                    order[j ++] = exe[i];
                ch ++;
                i ++;
            }

            strncpy(exe, exe + ch + 1, sizeof(exe));
            i = 0;
            ch = 0;
            while(ans[i ++] != '.'){
                ch ++;
            }
            strncpy(ans, ans + ch + 1, sizeof(ans));
            i = 0;
            ch = 0;
            while(ans[i ++] == ' '){
                ch ++;
            }
            strncpy(ans, ans + ch, sizeof(ans));
            strcpy(a1, creat_answer(exe));
            i = 0;
            while(a1[i] >= '0' && a1[i] <= '9' || a1[i] == '/' || a1[i] == 39) i ++;
            a1[i] = '\0';
            i = 0;
            while(ans[i] >= '0' && ans[i] <= '9' || ans[i] == '/' || ans[i] == 39) i ++;
            ans[i] = '\0';
            if(0 == strcmp(a1, ans)){
                correct ++;
                strcpy(cor[k ++], order);
            }
            else{
                wrong ++;
                strcpy(wro[t ++], order);
            }
        }
        itoa(correct, sum1, 10);
        itoa(wrong, sum2, 10);
        fputs("Correct: ", fpg);
        fputs(sum1, fpg);
        fputs(" (", fpg);
        row = 0;
        for(i = 0; cor[i][0] != 0; i ++){
            fputs(cor[i], fpg);
            if(cor[i + 1][0] != 0) fputs(",", fpg);
            row ++;
            if(row % 8 == 0) fputc('\n', fpg);
        }
        fputs(")", fpg);
        fputc('\n', fpg);
        fputs("Wrong: ", fpg);
        fputs(sum2, fpg);
        fputs(" (", fpg);
        row = 0;
        for(i = 0; wro[i][0] != 0; i ++){
            fputs(wro[i], fpg);
            if(wro[i + 1][0] != 0) fputs(",", fpg);
            row ++;
            if(row % 8 == 0) fputc('\n', fpg);
        }
        fputs(")", fpg);
        fputc('\n', fpg);
        fclose(fpe);
        fclose(fpa);
        fclose(fpg);
        for(i = 0; i < m+5; i++){
            free(cor[i]);
        }
        free (cor);
        for(i = 0; i < m+5; i++){
            free(wro[i]);
        }
        free (wro);
    }
    goto L1;
    return 0;
}









