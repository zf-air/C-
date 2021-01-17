#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct{
    string formula;//���ʽ
}grammerElement;
grammerElement form[100]; //ԭʼ�ķ��Ĳ���ʽ��

string ter_symbol;//�ս����
string non_ter;//���ս����
int sum=0; //��¼����ʽ����
int firstvt[200][200];//firstvt��
int lastvt[200][200];//lastvt��
string firstset[200];//firstvt����
string lastset[200];//lastvt����
char M[200][200];//������ȱ�

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

void setFirstVt(){
    //��ʼ��firstvt��
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_symbol.size();j++)
            firstvt[i][j]=false;
    }
    //��������ʽ
    for(int i=0;i<sum;i++){
        //��0������
        char ch0=form[i].formula[0];
        //��ȡ��0�����ŵ��±�
        int i_ch0=getNonSite(ch0);
        //����������
        char ch3=form[i].formula[3];        
        //������ս��
        if(isTer(ch3)){
            //��ȡ���������ŵ��±�
            int i_ch3=getTerSite(ch3);
            //����firstvt��
            firstvt[i_ch0][i_ch3]=true;
        }
        else{
            if(form[i].formula.size()>4){
                //���ĸ�����
                char ch4=form[i].formula[4];
                //�жϵ��ĸ������ǲ����ս��
                if(isTer(ch4)){
                    //��ȡ���ĸ����ŵ��±�
                    int i_ch4=getTerSite(ch4);
                    //����firstvt��
                    firstvt[i_ch0][i_ch4]=true;
                }
            }
        }
    }

    //����ջ
    stack<string> ss;
    //������Ϊ��ķ��Ŷ�(P,a)��ջ
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_symbol.size();j++){
            if(firstvt[i][j]){
                string st="";
                st+=non_ter[i];
                st+=ter_symbol[j];
                ss.push(st);
            }
        }
    }

    //����ջ
    while(!ss.empty()){
        //��ȡջ��Ԫ��s
        string s=ss.top();
        ss.pop();
        //����������,���ս��Q
        char ch3=s[0];
        //�������в���ʽ
        for(int i=0;i<sum;i++){
            if(form[i].formula[3]==ch3){
                //��ȡ��0������
                char ch0=form[i].formula[0];
                //��ȡ��0�����ŵ��±�
                int i_ch0=getNonSite(ch0);
                //��ȡ�ս��a�±�
                int i_ch_a=getTerSite(s[1]);
                if(!firstvt[i_ch0][i_ch_a]){
                    firstvt[i_ch0][i_ch_a]=true;
                    string st="";
                    st+=ch0;
                    st+=s[1];
                    ss.push(st);
                }
            }
        }
    }
}

void setLastVt(){
    //��ʼ��lastvt��
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_symbol.size();j++)
            lastvt[i][j]=false;
    }
    //��������ʽ
    for(int i=0;i<sum;i++){
        int length=form[i].formula.size();
        //��0������
        char ch0=form[i].formula[0];
        //��ȡ��0�����ŵ��±�
        int i_ch0=getNonSite(ch0);
        //���һ������
        char chn1=form[i].formula[length-1];
        //������ս��
        if(isTer(chn1)){
            //��ȡ���������ŵ��±�
            int i_chn1=getTerSite(chn1);
            //����lastvt��
            lastvt[i_ch0][i_chn1]=true;
        }
        else{
            if(form[i].formula.size()>4){
                //�����ڶ�������
                char chn2=form[i].formula[length-2];
                //�жϵ����ڶ��������ǲ����ս��
                if(isTer(chn2)){
                    //��ȡ�����ڶ������ŵ��±�
                    int i_chn2=getTerSite(chn2);
                    //����lastvt��
                    lastvt[i_ch0][i_chn2]=true;
                }
            }
        }
    }

    //����ջ
    stack<string> ss;
    //������Ϊ��ķ��Ŷ�(P,a)��ջ
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_symbol.size();j++){
            if(lastvt[i][j]){
                string st="";
                st+=non_ter[i];
                st+=ter_symbol[j];
                ss.push(st);
            }
        }
    }

    //����ջ
    while(!ss.empty()){
        //��ȡջ��Ԫ��s
        string s=ss.top();
        ss.pop();
        //���һ������,���ս��Q
        char chn1=s[0];
        //�������в���ʽ
        for(int i=0;i<sum;i++){
            int length=form[i].formula.size();
            if(form[i].formula[length-1]==chn1){
                //��ȡ��0������
                char ch0=form[i].formula[0];
                //��ȡ��0�����ŵ��±�
                int i_ch0=getNonSite(ch0);
                //��ȡ�ս��a�±�
                int i_ch_a=getTerSite(s[1]);
                if(!lastvt[i_ch0][i_ch_a]){
                    lastvt[i_ch0][i_ch_a]=true;
                    string st="";
                    st+=ch0;
                    st+=s[1];
                    ss.push(st);
                }
            }
        }
    }
}

void setYouxianTable(){
    //��ʼ�����ȹ�ϵ��
    for(int i=0;i<ter_symbol.size();i++){
        for(int j=0;j<ter_symbol.size();j++){
            M[i][j]=' ';
        }
    }
    //��������ʽ
    for(int i=0;i<sum;i++){
        int length=form[i].formula.size();
        for(int j=3;j<length-1;j++){
            char ch1=form[i].formula[j];
            char ch2=form[i].formula[j+1];
            //aa,�������ڵ��ս��
            if(isTer(ch1)&&isTer(ch2)){
                int i_ch1=getTerSite(ch1);
                int i_ch2=getTerSite(ch2);
                M[i_ch1][i_ch2]='=';
            }
            //aAa
            if(j+2<length&&isTer(ch1)&&isNon(ch2)&&isTer(form[i].formula[j+2])){
                char ch3=form[i].formula[j+2];
                int i_ch1=getTerSite(ch1);
                int i_ch3=getTerSite(ch3);
                M[i_ch1][i_ch3]='=';
            }
            //aA
            if(isTer(ch1)&&isNon(ch2)){
                int i_ch1=getTerSite(ch1);
                int i_ch2=getNonSite(ch2);
                for(int k=0;k<ter_symbol.size();k++){
                    if(firstvt[i_ch2][k]){
                        M[i_ch1][k]='<';
                    }
                }
            }
            //Aa
            if(isNon(ch1)&&isTer(ch2)){
                int i_ch1=getNonSite(ch1);
                int i_ch2=getTerSite(ch2);
                for(int k=0;k<ter_symbol.size();k++){
                    if(lastvt[i_ch1][k]){
                        M[k][i_ch2]='>';
                    }
                }
            }
        }
    }
}
void addString(string &s,char ch){
    string s2="";
    s2+=ch;
    s2+=s;
    s=s2;
}
void Yuce(string s){
    char ss[200];
    int k=0;//ss���±�
    ss[k]='#';
    int i=0;//s���±�
    int j=0;
    do{
        if(isTer(ss[k])){
            j=k;
        }
        else
            j=k-1;
        //��ȡa���±�
        int i_si=getTerSite(s[i]);
        //��ȡջ�����±�
        int i_ss=getTerSite(ss[j]);
        //ջ����������
        while(M[i_ss][i_si]=='>'){
            int i_j=0;
            int i_j_1=0;
            //Ѱ���ض����ͷ
            do{
                i_j=getTerSite(ss[j]);
                if(isTer(ss[j-1]))
                    j=j-1;
                else
                    j=j-2;
                i_j_1=getTerSite(ss[j]);
            }while(M[i_j_1][i_j]=='=');
            //��ʼ��Լ,j+1->k
            int n=j+1;
            for(int l=0;l<sum;l++){
                int m;
                int flag=0;
                for(m=3;m<form[l].formula.size();m++){
                    if(isNon(form[l].formula[m])){
                        continue;
                    }
                    else{
                        if(form[l].formula[m]==ss[n]){
                            flag=1;
							n++;
                        }
                        else{
                        	flag=0;
                            break;
                        }
                    }
                }
                //ƥ��ɹ�
                if(flag&&n>k&&m>=form[l].formula.size()){
                    k=j+1;
                    ss[k]=form[l].formula[0];
                    cout<<form[l].formula<<endl;
                    break;
                }
            }
        }
        if(M[i_ss][i_si]=='<'||M[i_ss][i_si]=='='){
            k++;
            ss[k]=s[i];
            i++;
        }
    }while(s[i]!='#');
}
void fenge(){
    cout<<"-------------------------"<<endl;
}
int main()
{
    //�������ʽ
    int i=0;
    string s;
    cout<<"�������ķ�:"<<endl;
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
    fenge();

    //ͳ���ս���ͷ��ս��
    init_NT();
    cout<<"�ս��:"<<ter_symbol<<endl;
    cout<<"���ս��:"<<non_ter<<endl;
    fenge();

    //����firstvt��
    cout<<"firstvt����:"<<endl;
    setFirstVt();
    cout<<"   ";
    for(int i=0;i<ter_symbol.size();i++)
        cout<<" "<<ter_symbol[i]<<" ";
    cout<<endl;
    for(int i=0;i<non_ter.size();i++){
        cout<<" "<<non_ter[i]<<" ";
        for(int j=0;j<ter_symbol.size();j++){
            cout<<" "<<firstvt[i][j]<<" ";
        }
        cout<<endl;
    }
    fenge();

    //����lastvt��
    cout<<"lastvt����:"<<endl;
    setLastVt();
    cout<<"   ";
    for(int i=0;i<ter_symbol.size();i++)
        cout<<" "<<ter_symbol[i]<<" ";
    cout<<endl;
    for(int i=0;i<non_ter.size();i++){
        cout<<" "<<non_ter[i]<<" ";
        for(int j=0;j<ter_symbol.size();j++){
            cout<<" "<<lastvt[i][j]<<" ";
        }
        cout<<endl;
    }
    fenge();

    //����firstvt��lastvt����
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_symbol.size();j++){
            if(firstvt[i][j]){
                firstset[i]+=ter_symbol[j];
            }
            if(lastvt[i][j]){
                lastset[i]+=ter_symbol[j];
            }
        }
    }
    cout<<"firstvt����:"<<endl;
    for(int i=0;i<non_ter.size();i++)
        cout<<non_ter[i]<<":"<<firstset[i]<<endl;
    fenge();
    cout<<"lastvt����:"<<endl;
    for(int i=0;i<non_ter.size();i++)
        cout<<non_ter[i]<<":"<<lastset[i]<<endl;
    fenge();

    //�������ȹ�ϵ��
    cout<<"���ȹ�ϵ��:"<<endl;
    setYouxianTable();
    cout<<"   ";
    for(int i=0;i<ter_symbol.size();i++)
        cout<<" "<<ter_symbol[i]<<" ";
    cout<<endl;
    for(int i=0;i<ter_symbol.size();i++){
        cout<<" "<<ter_symbol[i]<<" ";
        for(int j=0;j<ter_symbol.size();j++){
            cout<<" "<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    fenge();

    //Ԥ�����
    cout<<"�������ַ���:";
    cin>>s;
    Yuce(s);
    fenge();

}

