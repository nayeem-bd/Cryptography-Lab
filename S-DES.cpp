#include <bits/stdc++.h>
using namespace std;
string Key = "1010000010";

vector<int> P10 = {3,5,2,7,4,10,1,9,8,6}, P8 = {6,3,7,4,8,5,10,9} , IP = {2,6,3,1,4,8,5,7}, EP = {4,1,2,3,2,3,4,1}, P4 = {2,4,3,1};
vector<vector<int>> S0 = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}}, S1 = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

vector<string> genKey()
{
    vector<string> ret;
    string pKey, K;
    for(int i=0; i<10; i++){
        pKey += Key[P10[i]-1];
    }
    string lpKey, rpKey;
    for(int i=0; i<5; i++){
        lpKey += pKey[i];
        rpKey += pKey[i+5];
    }
    lpKey += *lpKey.begin();
    lpKey.erase(lpKey.begin());
    rpKey += *rpKey.begin();
    rpKey.erase(rpKey.begin());

    pKey = lpKey+rpKey;

    for(int i=0; i<8; i++){
        K += pKey[P8[i]-1];
    }
    ret.push_back(K);

    lpKey += *lpKey.begin();
    lpKey.erase(lpKey.begin());
    rpKey += *rpKey.begin();
    rpKey.erase(rpKey.begin());
    lpKey += *lpKey.begin();
    lpKey.erase(lpKey.begin());
    rpKey += *rpKey.begin();
    rpKey.erase(rpKey.begin());

    pKey = lpKey+rpKey;

    K="";
    for(int i=0; i<8; i++){
        K += pKey[P8[i]-1];
    }
    ret.push_back(K);

    return ret;
}

string encrypt_des(string & plaintext, vector<string>& key)
{
    string lpt,rpt,ppt=plaintext,erpt;
    for(int i=0; i<8; i++){
        ppt[i] = plaintext[IP[i]-1];
    }
    for(int i=0; i<4; i++){
        lpt += ppt[i];
        rpt += ppt[i+4];
    }

    for(int i=0; i<8; i++){
        erpt += rpt[EP[i]-1];
    }

    for(int i=0; i<8; i++){
        if(erpt[i]==key[0][i]) erpt[i]='0';
        else erpt[i]='1';
    }

    auto fnc = [&](int i, int j)
    {
        int ind;
        if(erpt[i]=='0')
        {
            if(erpt[j]=='1') return 1;
            else return 0;
        }
        else if(erpt[j]=='1') return 3;
        else return 2;
    };

    string fkrpt;

    int ia = fnc(0,3);
    int ib = fnc(1,2);

    int num = S0[ia][ib];
    if(num==0) fkrpt="00";
    else if(num==1) fkrpt="01";
    else if(num==2) fkrpt="10";
    else fkrpt="11";

    ia = fnc(4,7);
    ib = fnc(5,6);

    num = S1[ia][ib];
    if(num==0) fkrpt+="00";
    else if(num==1) fkrpt+="01";
    else if(num==2) fkrpt+="10";
    else fkrpt+="11";

    string pfkrpt;

    for(int i=0; i<4; i++){
        pfkrpt += fkrpt[P4[i]-1];
    }

    for(int i=0; i<4; i++){
        if(pfkrpt[i]==lpt[i]) lpt[i]='0';
        else lpt[i]='1';
    }

    swap(lpt,rpt);
    erpt="";
    for(int i=0; i<8; i++){
        erpt += rpt[EP[i]-1];
    }

    for(int i=0; i<8; i++){
        if(erpt[i]==key[1][i]) erpt[i]='0';
        else erpt[i]='1';
    }

    fkrpt="";

    ia = fnc(0,3);
    ib = fnc(1,2);

    num = S0[ia][ib];
    if(num==0) fkrpt="00";
    else if(num==1) fkrpt="01";
    else if(num==2) fkrpt="10";
    else fkrpt="11";

    ia = fnc(4,7);
    ib = fnc(5,6);

    num = S1[ia][ib];
    if(num==0) fkrpt+="00";
    else if(num==1) fkrpt+="01";
    else if(num==2) fkrpt+="10";
    else fkrpt+="11";

    pfkrpt ="";

    for(int i=0; i<4; i++){
        pfkrpt += fkrpt[P4[i]-1];
    }

    for(int i=0; i<4; i++){
        if(pfkrpt[i]==lpt[i]) lpt[i]='0';
        else lpt[i]='1';
    }

    vector<int> inv_IP(8);
    for(int i=0; i<8; i++){
        inv_IP[IP[i]-1]=i+1;
    }

    string cpt = lpt+rpt,ct;
    for(int i=0; i<8; i++){
        ct+=cpt[inv_IP[i]-1];
    }
    return ct;
}

int main()
{
    auto KK = genKey();
    cout<<"Keys:"<<endl;
    for(auto x: KK) cout<<x<<endl;
    string pt = "10010101";

    auto en = encrypt_des(pt,KK);
    cout<<"Encrypted:"<<endl;
    cout<<en<<endl;
    swap(KK[0],KK[1]);
    cout<<"Decrypted:"<<endl;
    cout<<encrypt_des(en,KK)<<endl;

    return 0;
}
