#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef struct{
    string formula;//���ʽ
}grammerElement;
grammerElement form[100]; //ԭʼ�ķ��Ĳ���ʽ��

string ter_symbol;//�ս����
string non_ter;//���ս����
string inter_symbol;//�������
string first_set[100];//���ս����FIRST��
string follow_set[100];//���ս����FOLLOW��
int M[200][200];//������

int sum=0; //��¼����ʽ����

//��д��ĸ�Ƿ��ս��
int isUpper(char ch){
    if(ch>='A'&&ch<='Z')
        return true;
    return false;
}

//�����ս�����ж��Ƿ����ս��
int isTer(char a){
    for(int i=0;i<ter_symbol.size();i++)
        if(ter_symbol[i]==a)
            return true;
    return false;
}
//���ݷ��ս�����ж��Ƿ��Ƿ��ս��
int isNon(char a){
    for(int i=0;i<non_ter.size();i++){
        if(non_ter[i]==a)
            return true;
    }
    return false;
}

//��ȡ���ս�����±�
int getNonSite(char ch){
    int j=0;
    for(;j<non_ter.size();j++){
        if(non_ter[j]==ch){
            break;
        }
    }
    return j;
}
//��ȡ�ս�����±�
int getTerSite(char ch){
    int j=0;
    for(;j<ter_symbol.size();j++){
        if(ter_symbol[j]==ch){
            break;
        }
    }
    return j;
}

//ͳ���ս���ͷ��ս��
void init_NT(){
    //��дΪ���ս��������Ϊ�ս��,0���ս��
    int i,j;
    for(i=0;i<sum;i++){
        for(j=0;j<form[i].formula.size();j++){
            char ch=form[i].formula[j];
            if(ch=='-'||ch=='>'||ch==' ')
                continue;
            //�ս��
            if(!isUpper(ch)){
                //�����Ƿ����
                int flag=0;
                for(int k=0;k<ter_symbol.size();k++){
                    if(ter_symbol[k]==ch){
                        flag=1;
                        break;
                    }
                }
                if(!flag)
                    ter_symbol+=ch;
            }
            //���ս��
            else{
                //�����Ƿ����
                int flag=0;
                for(int k=0;k<non_ter.size();k++){
                    if(non_ter[k]==ch){
                        flag=1;
                        break;
                    }
                }
                if(!flag)
                    non_ter+=ch;
            }
        }
    }
}

//����first�����Ƿ��п�
//�пշ���true��û�пշ���false
int is_first_set_0(int col){
    for(int i=0;i<first_set[col].size();i++){
        if(first_set[col][i]=='0'){
            return true;
        }
    }
    return false;
}

//��A��first����ս��
//����˷���1��δ��ӷ���0
int addfirst_Ter(char ch,int col){
    int t_flag=0;
    int flag=0;
    for(int j=0;j<first_set[col].size();j++){
        if(first_set[col][j]==ch){
            t_flag=1;
            break;
        }
    }
    if(!t_flag){
        first_set[col]+=ch;
        flag=1;
    }
    return flag;
}

//��A��first��ӷ��ս����first
//����˷���1��δ��ӷ���0
int addfirst_Non(int i_ch,int col){
    int non_A_size=first_set[col].size();
    int flag=0;
    //��ch��first���ӵ�A��first��,��ȥ��
    for(int j=0;j<first_set[i_ch].size();j++){
        int t_flag=0;
        for(int k=0;k<non_A_size;k++){
            if(first_set[i_ch][j]==first_set[col][k]){
                t_flag=1;
                break;
            }
        }
        if(!t_flag){
            first_set[col]+=first_set[i_ch][j];
            flag=1;
        }
    }
    return flag;
}

//��ȡһ�����ս����first����
//�����˷���1��δ���ķ���0 
int getFirst(char A,int col){
//    int flag=1;
//    while(flag){
        int flag=0;
        //���������ķ�
        for(int i=0;i<sum;i++){
            // ���Ҹ��ַ���ͷ���ķ�
            if(A==form[i].formula[0]){
                //�ҳ���һ��first�������ջ����Ƿ��ս��
                int t=3;
                //�Ƿ��ս��
                while(t<form[i].formula.size()&&isNon(form[i].formula[t])){
                    //��ȡλ��
                    int i_t=0;
                    i_t=getNonSite(form[i].formula[t]);
                    //����
                    if(is_first_set_0(i_t)){
                        t++;
                    }
                    else{
                        break;
                    }
                }

                int t_flag=0;
                //ȫ�Ƿ��ս�������Һ��ռ�����ͷ�ˣ����0
                if(t==form[i].formula.size()){
                    t--;
                    //��A����ս��0
                    t_flag=addfirst_Ter('0',col);
                }
                //�ҵ����ս��
                else if(isTer(form[i].formula[t])){
                    //��A����ս��
                    t_flag=addfirst_Ter(form[i].formula[t],col);
                    t--;
                }
                for(int j=3;j<=t;j++){
                    char ch=form[i].formula[j];
                    //��ȡch���±�
                    int i_ch;
                    i_ch=getNonSite(ch);
                    t_flag=addfirst_Non(i_ch,col);
                }
                if(t_flag)
                    flag=1;
            }
        }
    }
}

//��ȡ���з��ս����first����
void First(){
    for(int i=0;i<non_ter.size();i++){
        getFirst(non_ter[i],i);
    }
}

int main()
{
    //�������ʽ
    int i=0;
    string s;
    cin>>s;
    while(s[0]!='#'){
        char ch=s[0];
        string s2;
        s2+=ch;
        s2+="->";
        for(int j=3;j<s.size();j++){
            string s3=s2;
            while(j<s.size()&&s[j]!='|'){
                s3+=s[j];
                j++;
            }
            form[i].formula=s3;
            i++;
        }
        cin>>s;
    }
    sum=i; //sum���������ѭ����i<sum
    cout<<"sum:"<<sum<<endl;
    cout<<"�����ķ�:"<<endl;
    for(int i=0;i<sum;i++){
        cout<<form[i].formula<<endl;
    }

    //ͳ���ս���ͷ��ս��
    init_NT();
    cout<<"�ս��:"<<ter_symbol<<endl;
    cout<<"���ս��:"<<non_ter<<endl;

    //��ȡfirst����
    First();
    cout<<"first����:"<<endl;
    for(int i=0;i<non_ter.size();i++){
        cout<<non_ter[i]<<":"<<first_set[i]<<endl;
    }

    return 0;
}

