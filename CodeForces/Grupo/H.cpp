#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
 
string s; 
//lli dp[500010];
vector< vector<lli> > dp(2, vector<lli>(500010, -1));
 
lli funcion(lli index, lli suma) //Abre -> 0, cierra -> 1
{
    if(index > s.length() || suma < 0) return 0;
    if(index == s.length() && suma == 0) return 1;

    if(dp[0][index] == 1) return 1;
    if(dp[1][index] == 1) return 1;

    bool flagAbrir =true, flagCerrar = true;

    if(dp[0][index] == 0) flagAbrir = false;
    if(dp[1][index] == 0) flagCerrar = false;

    char actual = s[index];

    if(actual == '(')
    {
        return funcion(index+1, suma + 1);
    }
    if(actual == ')')
    {
        return funcion(index+1, suma - 1);
    }
    lli abrir = 0;
    if(flagAbrir)
    {
        abrir = funcion(index+1, suma + 1);
    }
    lli cerrar = 0;
    if(flagCerrar)
    {
        cerrar = funcion(index + 1, suma - 1);
    }
    
    if(abrir == 1)
    {
        return dp[0][index] = 1;
    }
    if(cerrar == 1)
    {
        return dp[1][index] = 1;
    }
    return 0;
}
 

void rec(lli index, lli suma, string &res)
{
    if(index > s.length() || suma < 0) return;


    if(s[index] == '?')
    {
        if(dp[0][index] == 1)
        {
            res[index] = '(';
            rec(index+1, suma+1, res);
            return;
        }
        res[index] = ')';
        rec(index+1, suma - 1, res);
        return;
    }
    if(s[index] == ')')
    {
        res[index] = ')';
        rec(index+1, suma -1, res);
    }
    else
    {
        res[index] = '(';
        rec(index+1, suma + 1, res);
    }
    
    
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>s;
    if(funcion(0,0))
    {
        string res(s.length(), '(');
        rec(0,0,res);
        cout<<res<<endl;
    }
    else
    {
        cout<<"Impossible\n";
    }
    
    
 
    return 0;
}