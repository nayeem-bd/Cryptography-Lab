#include<bits/stdc++.h>
using namespace std;

int keyMatrix[3][3],cipherMatrix[3],messageMatrix[3],inverseKeyMatrix[3][3],plainMatrix[3];

int gcd(int a,int b,int *x,int *y)
{
    if(b==0){
        *x = 1;
        *y = 0;
        return a;
    }
    int x1,y1;
    int gc = gcd(b,a%b,&x1,&y1);
    *x = y1;
    *y = x1 - (a/b)*y1;
    return gc;
}

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
    if(key.size()!=keysize*keysize) return "Key size doesn't match";
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
    int det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    if(det==0){
        cout<<"Inverse is not possible: "<<endl;
        return false;
    }
    int x,y;
    int gc = gcd(det,26,&x,&y);
    if(gc!=1){
        cout<<"Determinant: "<<det<<endl;
        cout<<"Gcd is not 1"<<endl;
        return false;
    }
    //here x is modular multiplicative inverse which is declared globally
    inverseKeyMatrix[0][0] = (keyMatrix[1][1]*gc)%26;
    inverseKeyMatrix[0][1] = (26-keyMatrix[0][1]*gc)%26;
    inverseKeyMatrix[1][0] = (26-keyMatrix[1][0]*gc)%26;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0]*gc)%26;
    return true;
}

bool find_inverse_3(){
    int det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) - keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])+ keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    if (det == 0) {
        cout << "Matrix is singular and has no inverse." << endl;
        return false;
    }
    int x,y;
    int gc = gcd(det,26,&x,&y);
    if(gc!=1){
        cout<<"Determinant: "<<det<<endl;
        cout<<"Gcd is not 1"<<endl;
        return false;
    }
    //here x is modular multiplicative inverse which is declared globally
    inverseKeyMatrix[0][0] = ((keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1])*x)%26 ;
    inverseKeyMatrix[0][1] = (26-(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1])*x)%26;
    inverseKeyMatrix[0][2] = ((keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1])*x)%26;
    inverseKeyMatrix[1][0] = (26-(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])*x)%26;
    inverseKeyMatrix[1][1] = ((keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0])*x)%26;
    inverseKeyMatrix[1][2] = (26-(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0])*x)%26;
    inverseKeyMatrix[2][0] = ((keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0])*x)%26;
    inverseKeyMatrix[2][1] = (26-(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0])*x)%26;
    inverseKeyMatrix[2][2] = ((keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0])*x)%26;
    return true;
}


string decryption(string& cipherText,string& key,int keysize){
    if(key.size()!=keysize*keysize) return "Key size doesn't match";
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
    for(int i=0;i<keysize;i++){
        for(int j=0;j<keysize;j++){
            cout<<inverseKeyMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<cipherText.size();i+=keysize){
        for(int j=0;j<keysize;j++){
            messageMatrix[j]=cipherText[i+j]-'A';
        }
        for(int j=0;j<keysize;j++){
            plainMatrix[j]=0;
            for(int k=0;k<keysize;k++){
                plainMatrix[j]+=inverseKeyMatrix[j][k]*messageMatrix[k];
            }
        }
        for(int j=0;j<keysize;j++){
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
            cout<<"Enter key (length="<<keysize*keysize<<"): ";
            cin>>key;
            transform(text.begin(),text.end(),text.begin(),::toupper);
            transform(key.begin(),key.end(),key.begin(),::toupper);
            cipherText = encyptionTotal(text,key,keysize);
            cout<<cipherText<<endl;
        }else if(choice==2){
            cout<<"Enter CipherText: ";
            cin>>text;
            cout<<"Enter key (length="<<keysize*keysize<<"): ";
            cin>>key;
            transform(text.begin(),text.end(),text.begin(),::toupper);
            transform(key.begin(),key.end(),key.begin(),::toupper);
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
