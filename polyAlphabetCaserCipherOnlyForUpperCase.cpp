#include<bits/stdc++.h>
using namespace std;

string encryption(string plainText,string key)
{
    int sz = key.size();
    int cnt=0;
    string cipherText;
    for(int i=0;i<plainText.size();i++){
        int shift = key[cnt++]-'A';
        cnt  = cnt%sz;
        cipherText += ((plainText[i]-'A')+shift)%26 + 'A';
    }
    return cipherText;
}

string decryption(string cipherText,string key)
{
    string plainText;
    int sz = key.size();
    int cnt=0;
    for(int i=0;i<cipherText.size();i++){
        int shift = key[cnt++]-'A';
        cnt  = cnt%sz;
        plainText += (cipherText[i]-'A'-shift+26)%26+'A';
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
        cout<<"Enter text: ";
        cin>>plain;
        cout<<"Enter Key: ";
        cin>>key;
        transform(plain.begin(),plain.end(),plain.begin(),::toupper);
        transform(key.begin(),key.end(),key.begin(),::toupper);
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
