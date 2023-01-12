#include<bits/stdc++.h>
using namespace std;

string encryption(string plainText,string key)
{
    int sz = key.size();
    int cnt=0;
    //encryption
    string cipherText;
    transform(key.begin(),key.end(),key.begin(),::tolower);
    for(int i=0;i<plainText.size();i++){
        int shift = key[cnt++]-'a';
        cnt  = cnt%sz;
        if(plainText[i]>='a'&&plainText[i]<='z'){
            int ci = plainText[i]-'a';
            ci = (ci+shift)%26;
            cipherText += char(ci+'a');
        }
        else{
            int ci = plainText[i]-'A';
            ci = (ci+shift)%26;
            cipherText += char(ci+'A');
        }
    }
    return cipherText;
}

string decryption(string cipherText,string key)
{
    string plainText;
    int sz = key.size();
    int cnt=0;
    //decryption
    transform(key.begin(),key.end(),key.begin(),::tolower);
    for(int i=0;i<cipherText.size();i++){
        int shift = key[cnt++]-'a';
        cnt  = cnt%sz;
        if(cipherText[i]>='a'&&cipherText[i]<='z'){
            int ci = cipherText[i]-'a';
            ci = (ci-shift+26)%26;
            plainText += char(ci+'a');
        }
        else{
            int ci = cipherText[i]-'A';
            ci = (ci-shift+26)%26;
            plainText += char(ci+'A');
        }
    }
    return plainText;
}

int main()
{
    while(1){
        cout<<"Enter 1 for encryption\nEnter 2 for decryption\nEnter 3 for break\nEnter choice: ";
        int ch;
        cin>>ch;
        string plain,key,output;
        cin>>plain>>key;
        if(ch==1){
            output = encryption(plain,key);
            cout<<"Encrypted Text: "<<output<<endl;
        }
        else if(ch==2){
            output = decryption(plain,key);
            cout<<"Decrypted Text : "<<output<<endl;
        }
        else{
            break;
        }
    }
    return 0;
}
