#include<bits/stdc++.h>
using namespace std;

float keyMatrix[3][3],cipherMatrix[3],messageMatrix[3],inverseKeyMatrix[3][3],plainMatrix[3];

void matrix_gen(string& key,int keysize)
{
    int i=0,j=0;
    for(int k=0;k<key.size();k++){
        keyMatrix[i][j++]=key[k]-'A';
        cout<<keyMatrix[i][j-1]<<" ";
        if(j==keysize){
            j=0;
            i++;
            cout<<endl;
        }
    }

}

string encyptionTotal(string& plainText,string& key,int keysize){
    for(int i=0;i<(plainText.size()%keysize);i++){
        plainText+='X';
    }
    matrix_gen(key,keysize);
    string cipherText;
    for(int i=0;i<plainText.size();i+=keysize){
        for(int j=0;j<keysize;j++){
            messageMatrix[j]=plainText[i+j]-'A';
        }
        for(int j=0;j<keysize;j++){
            cipherMatrix[j]=0;
            for(int k=0;k<keysize;k++){
                cipherMatrix[j]+=keyMatrix[j][k]*messageMatrix[k];
            }
        }
        for(int j=0;j<keysize;j++){
            cipherText+=char(fmod(cipherMatrix[j],26)+'A');
        }
    }
    return cipherText;
}

bool find_inverse_2(){


    return true;
}

bool find_inverse_3(){
    float det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) - keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])+ keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    if (det == 0) {
        cout << "Matrix is singular and has no inverse." << endl;
        return false;
    }
    inverseKeyMatrix[0][0] = (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) / det;
    inverseKeyMatrix[0][1] = -(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]) / det;
    inverseKeyMatrix[0][2] = (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) / det;
    inverseKeyMatrix[1][0] = -(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) / det;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]) / det;
    inverseKeyMatrix[1][2] = -(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]) / det;
    inverseKeyMatrix[2][0] = (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]) / det;
    inverseKeyMatrix[2][1] = -(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]) / det;
    inverseKeyMatrix[2][2] = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) / det;
    return true;
}


string decryption(string& cipherText,string& key,int keysize){
    string plainText;
    matrix_gen(key,keysize);
    bool inversePossible = false;
    if(keysize==2){
        inversePossible=find_inverse_2();
    }
    else{
        inversePossible=find_inverse_3();
    }
    if(!inversePossible)return "Inverse Not Possible";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<inverseKeyMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<cipherText.size();i+=keysize){
        for(int j=0;j<keysize;j++){
            messageMatrix[j]=cipherText[i+j]-'A';
            //cout<<messageMatrix[j]<<" ";
        }
        for(int j=0;j<keysize;j++){
            plainMatrix[j]=0;
            for(int k=0;k<keysize;k++){
            	cout<<fmod(inverseKeyMatrix[j][k],26)<<" "<<messageMatrix[k]<<endl;
                plainMatrix[j]+=inverseKeyMatrix[j][k]*messageMatrix[k];
            }
        }
        for(int j=0;j<keysize;j++){
        	cout<<plainMatrix[j]<<endl;
            plainText+=(char)(fmod(plainMatrix[j],26)+'A');
        }
    }

    return plainText;
}




void solve(int keysize){
    string text,key,cipherText,output;
    while(1){
        int choice=0;
        cout<<endl<<"Enter 1 to Encryption: \nEnter 2 to Decryption\nEnter your choice: ";
        cin>>choice;
        if(choice==1){
            cout<<"Enter PlainText: ";
            cin>>text;
            cout<<"Enter key (length="<<keysize<<"): ";
            cin>>key;
            cipherText = encyptionTotal(text,key,keysize);
            cout<<cipherText<<endl;
        }else if(choice==2){
            cout<<"Enter CipherText: ";
            cin>>text;
            cout<<"Enter key (length="<<keysize<<"): ";
            cin>>key;
            output = decryption(text,key,keysize);
            cout<<output<<endl;
        }else{
            return;
        }
    }
}

int main()
{
    while(1){
        int choice=0;
        cout<<"Enter 1 to key length 4\nEnter 2 to key length 9\nEnter your choice: ";
        cin>>choice;
        if(choice==1){
            solve(2);
        }else if(choice==2){
            solve(3);
        }else{
            break;
        }
    }
    return 0;
}
