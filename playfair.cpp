#include<bits/stdc++.h>
using namespace std;

char matrix[5][5];

void gen_Table(string key)
{
    key+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i,j,k;
    i=0,j=0;
    int flag[26]={0};
    for(k=0;k<key.size();k++){
        char ch = toupper(key[k]);
        if(ch=='J')ch--;
        if(flag[ch-'A']==0){
            matrix[i][j]=ch;
            flag[ch-'A']=1;
            j++;
            if(j==5){
                i++;
                j=0;
            }
        }
    }
}

void get_index(char ch,int &c,int &d)
{
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(matrix[i][j]==ch){
                c = i;
                d = j;
                return;
            }
        }
    }
}

string encryption(string plainText)
{
    string cipherText;
    for(int i=0;i<plainText.size();i++){
        if(plainText[i]=='J')plainText[i]='I';
    }
    for(int i=0;i<plainText.size();){
        char a,b;
        int ax,ay,bx,by;
        a = plainText[i];
        if(i+1<plainText.size()){
            b = plainText[i+1];
            i+=2;
        }
        else{
            i++;
            b = 'X';
        }
        if(a==b){
            if(a=='X'){
                    cipherText+="XX ";
                    continue;
            }
            else{
                b='X';
                i--;
            }
        }
        get_index(a,ax,ay);
        get_index(b,bx,by);
        if(ax==bx){
            cipherText+=matrix[ax][(ay+1)%5];
            cipherText+=matrix[bx][(by+1)%5];
            cipherText+=' ';
        }
        else if(ay==by){
            cipherText+=matrix[(ax+1)%5][ay];
            cipherText+=matrix[(bx+1)%5][by];
            cipherText+=' ';
        }
        else{
            cipherText+=matrix[ax][by];
            cipherText+=matrix[bx][ay];
            cipherText+=' ';
        }
   }
   return cipherText;
}

string decryption(string cipher)
{
    string plain;
    for(int i=0;i<cipher.size();i++)
    {
        char a,b;
        int ax,ay,bx,by;
        a = cipher[i++];
        b = cipher[i++];
        if(a==b){
            if(a=='X'){
                    plain+="XX ";
                    continue;
            }
        }
        get_index(a,ax,ay);
        get_index(b,bx,by);
        if(ax==bx){
            plain+=matrix[ax][(ay-1+5)%5];
            plain+=matrix[bx][(by-1+5)%5];
            plain+=' ';
        }
        else if(ay==by){
            plain+=matrix[(ax-1+5)%5][ay];
            plain+=matrix[(bx-1+5)%5][by];
            plain+=' ';
        }
        else{
            plain+=matrix[ax][by];
            plain+=matrix[bx][ay];
            plain+=' ';
        }
    }
    return plain;
}

int main()
{
    string plainText,key,cipherText;
    cout<<"Enter Plain Text: ";
    cin>>plainText;
    //getline(cin,plainText);
    cout<<"Enter Key: ";
    cin>>key;
    gen_Table(key);
    cout<<"Key Matrix : "<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
    transform(plainText.begin(),plainText.end(),plainText.begin(),::toupper);
    string cipher = encryption(plainText);
    cout<<"Encrypted : "<<cipher<<endl;
    string plain = decryption(cipher);
    cout<<"Decrypted : "<<plain<<endl;
    return 0;
}
