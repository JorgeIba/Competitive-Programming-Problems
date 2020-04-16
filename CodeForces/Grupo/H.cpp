#include <bits/stdc++.h>
#define lli long long int

using namespace std;

string s; 
lli dp[500010];

lli funcion(lli index, lli suma) //Abre -> 0, cierra -> 1
{
    if((index > s.length())or(suma < 0))
    {
        return 0;
    }
    if((index==s.length())and(suma==0))
    {
        return 1;
    }
    if( dp[index] != -1)
    {
        return dp[index];
    }
    char aux = s[index];
    if(aux=='(')
    {
        return funcion(index+1, suma+1);
    }
    else if (aux == ')')
    {
        return funcion(index + 1, suma -1);
    }
    else
    {
        lli ab = funcion(index+1, suma+1);
        lli cer = funcion(index + 1, suma -1);
        if(ab == 1)
        {
            s[index] = '(';
        }
        else if(cer == 1)
        {
            s[index] = ')';
        }
        return dp[index] = max(ab,cer);
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>s;
    if(funcion(0,0))
    {
        cout<<s<<endl;
    }
    else
    {
        cout<<"Impossible\n";
    }
    
    

    return 0;
}