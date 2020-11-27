#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

typedef struct{
    string formula;//���ʽ
}grammerElement;
grammerElement form[100]; //ԭʼ�ķ��Ĳ���ʽ��

string ter_symbol;//�ս����
string ter_table;//Ԥ����õ��ս��
string non_ter;//���ս����
string inter_symbol;//�������
string first_set[100];//���ս����FIRST��
string follow_set[100];//���ս����FOLLOW��
string M[200][200];//������
stack<char> ss;//����ջ
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
    return flag;
}

//��ȡ���з��ս����first����
void First(){
    int flag=1;
    while(flag){
        flag=0;
        int t_flag=0;
        for(int i=0;i<non_ter.size();i++){
            t_flag=getFirst(non_ter[i],i);
            if(t_flag)
                flag=1;
        }
    }
}

//��A��follow����ս��
//����˷���1��δ��ӷ���0
int addFollow_Ter(char ch,int col){
    int t_flag=0;
    int flag=0;
    for(int j=0;j<follow_set[col].size();j++){
        if(follow_set[col][j]==ch){
            t_flag=1;
            break;
        }
    }
    if(!t_flag){
        follow_set[col]+=ch;
        flag=1;
    }
    return flag;
}

//��A��follow��ӷ��ս����first����0
//����˷���1��δ��ӷ���0
int addfollow_NonFirst(int i_ch,int col){
    int non_A_size=follow_set[col].size();
    int flag=0;
    //��ch��first������0�ӵ�A��follow��,��ȥ��
    for(int j=0;j<first_set[i_ch].size();j++){
        if(first_set[i_ch][j]!='0'){
            int t_flag=0;
            for(int k=0;k<non_A_size;k++){
                if(first_set[i_ch][j]==follow_set[col][k]){
                    t_flag=1;
                    break;
                }
            }
            if(!t_flag){
                follow_set[col]+=first_set[i_ch][j];
                flag=1;
            }
        }
    }
    return flag;
}

//��A��follow��ӵ����ս����follow
//����˷���1��δ��ӷ���0
int addfollow_NonFollow(int i_ch,int col){
    int non_ch_size=follow_set[i_ch].size();
    int flag=0;
    //��A��follow��ӵ�ch��follow,��ȥ��
    for(int j=0;j<follow_set[col].size();j++){
        int t_flag=0;
        for(int k=0;k<non_ch_size;k++){
            if(follow_set[i_ch][k]==follow_set[col][j]){
                t_flag=1;
                break;
            }
        }
        if(!t_flag){
            follow_set[i_ch]+=follow_set[col][j];
            flag=1;
        }
    }
    return flag;
}

//��ȡһ�����ս����follow����
int getFollow(char A,int col){
    int flag=0;
    //���������ķ�
    for(int i=0;i<sum;i++){
        // ���Ҹ��ַ���ͷ���ķ�
        if(A==form[i].formula[0]){
            int t_flag=0;
            int len=form[i].formula.size();

            // 1.���first��
            int t=len-1;
            //�ҵ���һ���ս�����߲����յķ��ս��
            while(t>=3&&isNon(form[i].formula[t])){
                int i_t;
                i_t=getNonSite(form[i].formula[t]);
                //����
                if(is_first_set_0(i_t)){
                    t--;
                }else{
                    break;
                }
            }

            //���ǰ��ȫ�Ǻ��յķ��ս��
            if(t<3){
                continue;
            }
            char ch=form[i].formula[t];
            //������ս��
            if(isTer(ch)){
                if(ch!='0'){
                    if(t-1>=3){
                        //ǰһ���Ƿ��ս��
                        if(isNon(form[i].formula[t-1])){
                            //�����ӵ����ս����
                            int i_t;
                            i_t=getNonSite(form[i].formula[t-1]);
                            t_flag=addFollow_Ter(ch,i_t);
                            //����t,ǰ��ȫ�Ǻ��յķ��ս�����������һ��
                            t++;
                        }
                    }
                }
            }
            //����Ƿ��ս��������,�����ս��ǰ��ȫ�Ǻ��յķ��ս�����������һ��
            //���һ��ֱ�Ӳ�ִ��
            for(int k=len-1;k>=t+1;k--){
                //��һ��
                int i_ch;
                i_ch=getNonSite(form[i].formula[k]);
                //ǰһ��
                int i_t;
                i_t=getNonSite(form[i].formula[k-1]);

                t_flag=addfollow_NonFirst(i_ch,i_t);
            }

            //2.���follow��
            //�Ӻ���ǰ�ҳ���һ��first�����ջ������ս��
            t=len-1;
            //��A��follow���ӵ�ĩβ���ս����follow��
            if(isNon(form[i].formula[t])){
                int i_t;
                i_t=getNonSite(form[i].formula[t]);
                t_flag=addfollow_NonFollow(i_t,col);
            }
            //�Ƿ��ս��
            while(t>=3&&isNon(form[i].formula[t])){
                //��ȡλ��
                int i_t=0;
                i_t=getNonSite(form[i].formula[t]);
                //����
                if(is_first_set_0(i_t)){
                    t--;
                }
                else{
                    break;
                }
            }

            //���ȫ�Ƿ��ս�����Һ��пռ�����ͷ��
            if(t<3){
                continue;
            }
            //����������ս��,ǰ�涼�Ǻ��յķ��ս�����������һ��
            else if(isTer(form[i].formula[t])){
                continue;
            }
            //�����˵�һ�������յķ��ս��
            else if(isNon(form[i].formula[t])){

                //��A��follow���ӵ�����follow��
                int i_ch;
                i_ch=getNonSite(form[i].formula[t]);
                t_flag=addfollow_NonFollow(i_ch,col);
            }

            if(t_flag)
                flag=1;
        }
    }
    return flag;
}

//��ȡfollow����
void Follow(){
    int flag=1;
    //����ʼ�������#
    follow_set[0]+='#';
    while(flag){
        flag=0;
        int t_flag=0;
        for(int i=0;i<non_ter.size();i++){
            t_flag=getFollow(non_ter[i],i);
            if(t_flag)
                flag=1;
        }
    }
}

//��ȡԤ��������õ��ս���±�
int getTer_table(char ch){
    for(int i=0;i<ter_table.size();i++){
        if(ter_table[i]==ch)
            return i;
    }
    return -1;
}

//����Ԥ�������
void setTable(){
    //�������в���ʽ
    for(int i=0;i<sum;i++){
        string s=form[i].formula;
        //����ߵķ���
        char A=s[0];
        //��ȡ���ս��A���±�
        int i_A;
        i_A=getNonSite(A);
        //�Ҳ�����ߵĵ�һ������
        char ch=s[3];
        //���ս��
        if(isTer(ch)){
            if(ch!='0'){
                //��ȡ�ս��ch���±�
                int i_ch;
                i_ch=getTer_table(ch);
                //�Ѳ���ʽ���뵽������M[A,ch]
                M[i_A][i_ch]=s;
            }
            else{
                //����A��follow����
                for(int j=0;j<follow_set[i_A].size();j++){
                    char b=follow_set[i_A][j];
                    //��ȡb���±�
                    int i_b;
                    i_b=getTer_table(b);
                    //����ʽ��ӵ�M[A,b]��
                    M[i_A][i_b]=s;
                }
            }
        }
        //���ս��
        else{
            //��ȡ���ս���±�
            int i_ch;
            i_ch=getNonSite(ch);
            //����ch��first����
            int t_flag=0; //�ж�ch��first�����Ƿ��п�
            for(int j=0;j<first_set[i_ch].size();j++){
                char a=first_set[i][j];
                //��Ϊ�գ��Ѳ���ʽ��ӽ�������M[A,a]
                if(a!='0'){
                    //��ȡ�ս��a���±�
                    int i_a;
                    i_a=getTer_table(a);
                    M[i_A][i_a]=s;
                }
                //Ϊ��
                else{
                    t_flag=1;
                    continue;
                }
            }
            //����follow(A)��Ԫ��b,�Ѳ���ʽ���뵽M[A,b]
            if(t_flag){
                //����A��follow����
                for(int j=0;j<follow_set[i_A].size();j++){
                    char b=follow_set[i_A][j];
                    //��ȡb���±�
                    int i_b;
                    i_b=getTer_table(b);
                    //����ʽ��ӵ�M[A,b]��
                    M[i_A][i_b]=s;
                }
            }
        }
    }
}

int Yuce(string s){
    int t=0;//����
    int i=0; //i��Ϊs���±�
    //ѹ��#�Ϳ�ʼ����
    ss.push('#');
    ss.push(non_ter[0]);

    int flag=1;
    while(flag){
        //��ȡջ��Ԫ��
        char ch=ss.top();
        //�ս��
        if(isTer(ch)){
            if(i<s.size()&&ch==s[i]){
                //�����ɹ�
                if(ch=='#'){
                    cout<<t;
                    cout<<'#';
                    cout<<'#';
                    flag=false;
                    return true;
                }
                //�ս��ƥ��
                else{
                    ss.pop();
                    i++;
                }
            }
            else
                return false;
        }
        //���ս��
        else if(isNon(ch)){
            //��ȡ���ս���±�
            int i_ch;
            i_ch=getNonSite(ch);
            //��ȡ�ս���±�
            int i_a;
            i_a=getTer_table(s[i]);
            //���ҷ��������Ƿ��в���ʽ
            if(M[i_ch][i_a]!=""){
                ss.pop();
                string ts=M[i_ch][i_a];
//                cout<<"ts:"<<ts<<endl;
                for(int j=ts.size()-1;j>=3;j--){
                    if(ts[j]=='0'){
                        continue;
                    }
                    else{
                        ss.push(ts[j]);
                    }
                }
            }
            else
                return false;
        }
        else{
        	flag=false;
		}
        stack<char> ss2;
        while(!ss.empty()){       	
            ss2.push(ss.top());
            ss.pop();           
        }
        cout<<endl;
        while(!ss2.empty()){
            ss.push(ss2.top());
			cout<<ss.top();
            ss2.pop();
        }
    }

    return true;
}
void fenge(){
    cout<<"-------------------------"<<endl;
}

int main()
{
    //�������ʽ
    int i=0;
    string s;
    cout<<"�������ķ�:";
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

    //��ȡfirst����
    First();
    cout<<"first����:"<<endl;
    for(int i=0;i<non_ter.size();i++){
        cout<<non_ter[i]<<":"<<first_set[i]<<endl;
    }
    fenge();

    //��ȡfollow����
    Follow();
    cout<<"follow����:"<<endl;
    for(int i=0;i<non_ter.size();i++){
        cout<<non_ter[i]<<":"<<follow_set[i]<<endl;
    }
    fenge();

    //����Ԥ��������õ��ս��
    for(int i=0;i<ter_symbol.size();i++){
        if(ter_symbol[i]!='0'){
            ter_table+=ter_symbol[i];
        }
    }
    ter_table+='#';
    cout<<"ter_table:"<<ter_table<<endl;
    //��ʼ��Ԥ�������
    for(int i=0;i<non_ter.size();i++){
        for(int j=0;j<ter_table.size();j++){
            M[i][j]="";
        }
    }
    //����Ԥ�������
    setTable();
    //���Ԥ�������
    cout<<"Ԥ�������:"<<endl;
    //7���ո�
    cout<<"       |";
    for(int i=0;i<ter_table.size();i++){
        //��ȡ�ս��a
        char a=ter_table[i];
        cout<<"   "<<a<<"   |";
    }
    cout<<endl;
    for(int i=0;i<non_ter.size();i++){
        //��ȡ���ս��
        char A=non_ter[i];
        cout<<"   "<<A<<"   |";
        for(int j=0;j<ter_table.size();j++){
            //��ȡ�ս��a
            char a=ter_table[j];
            cout<<M[i][j];
            for(int k=0;k<(7-M[i][j].size());k++){
                cout<<" ";
            }
            cout<<"|";
        }
        cout<<endl;
    }
    fenge();

    string s2;
    cout<<"�����봮:";
    cin>>s2;
    int flag=Yuce(s2);
    if(flag)
        cout<<"Ԥ��ɹ�!"<<endl;
    else
        cout<<"Ԥ��ʧ��!"<<endl;
    return 0;
}

