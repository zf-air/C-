#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//���ڵ��Գ���,��Ҫ�Ļ�д�ϣ�����Ҫ�Ļ�����ע�ͣ��Ͳ�������м���
#define debug

//�������debug�Ļ�������������
//#define debug

#define Size 100  //�����ַ���ԭʼ��С

// ջ�ṹ�Ķ���
typedef struct _stack
{
    int size;   // ջ�洢�ռ�ĳߴ�
    int* base;   // ջ��ַ
    int* sp;    // ջ��
} stack;

//�����ṹ��
struct var{
    char* var_name;//������
    int start;//��ʼλ��
    int end;//����λ��
    int bc;//����
}vars[2];

void init(stack* s, int n)
{
    s->base = (int*)malloc(sizeof(int)*n);
    s->size = n;
    s->sp = s->base;
}

void push(stack* s, int val)
{
    if(s->sp - s->base == s->size)
    {
        puts("none");
        exit(1);
    }
    *s->sp++ = val;
}

int pop(stack* s)
{
    if(s->sp == s->base)
    {
        puts("none");
        exit(2);
    }
    return *--s->sp;
}
int top(stack*s)
{
    if(s->sp == s->base)
    {
        puts("none");
        exit(2);
    }

    return *(s->sp-1);
}

int empty(stack* s)
{
    return s->sp == s->base;
}

int size(stack* s)
{
    return s->sp-s->base;
}

void clean(stack* s)
{
    if(s->base)
        free(s->base);
}

//�ж������ŵ����ȹ�ϵ
char Precede(char t1, char t2){
    int i=0,j=0;

    //�����֮������ȼ�������һ�ű��
    char pre[7][7]={
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}
    };
    switch(t1){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '=': i=6; break;
    }
    switch(t2){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '=': j=6; break;
    }
    return pre[i][j];
}

//�ж�c�Ƿ�Ϊ�����
bool isOperator(char c)
{
    switch(c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}

//�ж�c�Ƿ�Ϊ����
bool isNumber(char c){
    if(c>='0'&&c<='9')
        return true;
    return false;
}

//�ж��Ƿ��ǵ����֣��ѵ����ֵ�������
bool isVariable(char c){
    //����c�������ж� ���������Ǳ�����
    if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c==':'||c=='|')
        return true;
    return false;
}

//���������ջ������ջ�Ͳ�����ջ��ջ������t1
void calculate_twonums(stack* s_operator,stack* s_number,char t1){
    //��������ջ����������ѹ��s_number��
    pop(s_operator);

    //��ȡ����������,ע��ȡ��˳�򣬺���ȳ�
    int a2=top(s_number);
    pop(s_number);
    int a1=top(s_number);
    pop(s_number);

#ifdef debug
    printf("a1:%d a2:%d\n",a1,a2);
#endif

    //a1 t1 a2,��������
    int t=0;
    if(t1=='+')
        t=a1+a2;
    else if(t1=='-')
        t=a1-a2;
    else if(t1=='*')
        t=a1*a2;
    else if(t1=='/')
        t=a1/a2;

#ifdef debug
    printf("t:%d\n",t);
#endif

    //�����ջ
    push(s_number,t);

}

int calculate(char* s){
    stack s_operator;
    stack s_number;
    //�����ջ������ʼ��
    init(&s_operator,Size);
    //����ջ
    init(&s_number,100);
    int length=strlen(s);  //ԭʼ�ַ�������

#ifdef debug
    printf("length:%d\n",length);
#endif

    int i=0;    //�ַ������±꣬���Կ���ָ��
    int res=-1; //�������

    //�����ַ���,��ȡÿ���ַ�(char)
    while(i<length){

        //���������
        if(isNumber(s[i])){
            int num=s[i]-'0';   //s[i]��char���ͣ���Ҫ-'0',�õ�int�͵�����
            i++;
            //���ֿ����ж�λ������123
            while(i<length&&isNumber(s[i])){
                num=num*10+(s[i]-'0');
                i++;
            }
            push(&s_number,num);
        }

        //����������
        else if(isOperator(s[i])){
            //����ջΪ�գ�ֱ����ջ
            if(empty(&s_operator)){
                push(&s_operator,s[i]);
                i++;
                continue;
            }
            //����ջ��Ϊ��
            else{
                char t1,t2;
                t1=top(&s_operator); //��һ��������
                t2=s[i];  //���ڵĲ�����

#ifdef debug
                printf("t1:%d\n",t1);
                printf("t2:%d\n",t2);
#endif

                switch(Precede(t1, t2))
                {
                case '<':   //��ǰ�Ѿ�ѹջһ���������t1���Ⱥ�һ���������t2����ʱ���ͽ�t2ѹջ
#ifdef debug
                    printf("���ȼ���>\n");
#endif
                    push(&s_operator,t2);
                    i++;
                    break;
                case '=':
#ifdef debug
                    printf("���ȼ���=\n");
#endif
                    pop(&s_operator);   //������
                    i++;
                    break;
                case '>':
                {
#ifdef debug
                    printf("���ȼ���>\n");
#endif
                    //���ü���a1 t1 a2�ĺ���
                    calculate_twonums(&s_operator,&s_number,t1);
                    break;
                }
                default:
                    printf("���������\n");
                    return -1;
                }
            }
        }
    }
    //����ջ����,�������к���Ĳ���,�Ӻ���ǰ������
    while(!empty(&s_operator)&&!empty(&s_number)){
        char t1;
        t1=top(&s_operator);
        calculate_twonums(&s_operator,&s_number,t1);
    }
    //�����һ������������ջ�������ս��
    if(size(&s_number)==1){
        res=top(&s_number);
        pop(&s_number);
    }
    return res;

}

//ָ���ַ����滻Դ�ַ���
void replace(char* ss,char* pos,int length,char num_str[]){
    char* st=(char*)malloc(sizeof (char)*Size);
    int s=pos-ss;
    int i=s,j=0;
    for(j=0;j<s;j++){
        st[j]=ss[j];
    }
    for(j=s;j<s+strlen(num_str);j++){
        st[j]=num_str[j-s];
    }
    for(j=s+strlen(num_str);j<s+strlen(num_str)+strlen(ss)-s-length;j++){
        st[j]=ss[j-strlen(num_str)+length];
    }
    st[j]='\0';
    strcpy(ss,st);
}

int main(){
    char* s=(char *)malloc(sizeof(char)*Size);
    scanf("%s",s);
#ifdef debug
    printf("Դ�ַ���:%s\n",s);
#endif
    //�ж��Ƿ��ǵ��������
    int i;
    int flag=0;
    int length=strlen(s);
    for(i=0;i<length;i++){
        if(isVariable(s[i])){   //�ж���������
            flag=1;
            break;
        }
    }

    int res=-1;
    if(flag==0){    //��һ���������
#ifdef debug
        printf("���1,2\n");
#endif
        res=calculate(s);
        printf("res:%d\n",res);
    }
    else{   //���������
#ifdef debug
        printf("���3\n");
#endif
        char* s_sub=(char *)malloc(sizeof(char)*Size);//�Ӵ�����x,y������
        i=0;
        while(i<length&&s[i]!='|')
            i++;
		//��ȡ���ʽ 
        strncpy(s_sub,s,i);
        s_sub[i]='\0';
        i++;//���� |

#ifdef debug
        printf("s_sub:%s\n",s_sub);
#endif

        //����ֻ�������������������Ҫ����
        int var_num=0;//��������

        //�������������ʼλ�ã�����λ�ã�����
        while(i<length){
            //��ȡ����
            char* st=(char *)malloc(sizeof(char)*Size); //��ʱ����,��¼ÿ������
            int st_i=0;//��¼st���±�
            while(i<length&&s[i]!=':'){
//                st+=s[i];
                st[st_i]=s[i];
                i++;
                st_i++;
            }
            st[st_i]='\0';
            i++; //����ð��

            //��ȡѭ������ ��ʼ������������ ǰ�պ�
            int start,end,bc;
            //��ʼ
            start=s[i]-'0';
            i++;
            //��ȡȫ������
            while(i<length&&s[i]!=','){
                start=start*10+(s[i]-'0');
                i++;
            }
            i++; //��������

            //����
            end=s[i]-'0';
            i++;
            while(i<length&&s[i]!=','){
                end=end*10+(s[i]-'0');
                i++;
            }
            i++;

            //����
            bc=s[i]-'0';
            i++;
            while(i<length&&s[i]!=';'){
                bc=bc*10+(s[i]-'0');
                i++;
            }
            if(i<length)
                i++;

#ifdef debug
            printf("st:%s\n",st);
            printf("start:%d\n",start);
            printf("end:%d\n",end);
            printf("bc:%d\n",bc);
#endif

            //����ṹ������
            vars[var_num].var_name=(char*)malloc(sizeof (char)*Size);
            strcpy(vars[var_num].var_name,st);
            vars[var_num].start=start;
            vars[var_num].end=end;
            vars[var_num].bc=bc;
            var_num++;
        }

#ifdef debug
        //��ӡ�ṹ������
        int a=0;
        for(a=0;a<2;a++){
            printf("var_name:%s start:%d end:%d bc:%d\n",vars[a].var_name,
                        vars[a].start,vars[a].end,vars[a].bc);
        }
        printf("\n");
#endif

        //ѭ����Ѱ�ұ��������滻Ϊ��Ӧ������
        int k,l;
        for(k=vars[0].start;k<vars[0].end;k+=vars[0].bc){
            for(l=vars[1].start;l<vars[1].end;l+=vars[1].bc){
                //�����ַ���
                char* ss=(char*)malloc(sizeof (char)*Size);
                strcpy(ss,s_sub);

                //����0��name������k���棬����1��name������l����
                char* pos;
                pos = strstr(ss,vars[0].var_name); //����ָ���Ĵ�,���ص�һ�γ��ֵ�λ��

                //ѭ���������еģ����滻
                while (pos != NULL)
                {
                    //�����滻���ַ����飬�������
                    char num_str[10];
                    //����ת�ַ���
                    sprintf(num_str,"%d",k);
                    //���µĴ��滻��ָ���Ĵ�
                    replace(ss,pos,strlen(vars[0].var_name),num_str);
                    //��������ָ���Ĵ���ֱ�����еĶ��ҵ�Ϊֹ
                    pos = strstr(ss,vars[0].var_name);
                }

                pos = strstr(ss,vars[1].var_name);//����ָ���Ĵ�
                while (pos != NULL)
                {
                    char num_str[10];
                    sprintf(num_str,"%d",l);
                    replace(ss,pos,strlen(vars[1].var_name),num_str);//���µĴ��滻��ָ���Ĵ�
                    pos = strstr(ss,vars[1].var_name);//��������ָ���Ĵ���ֱ�����еĶ��ҵ�Ϊֹ
                }
#ifdef debug
                //����滻����ַ���
                printf("ss:%s\n",ss);
#endif
                res=calculate(ss); //���м���
                printf("result:%d\n",res);
#ifdef debug
                printf("\n");
#endif
            }
        }
    }
    return 0;
}

