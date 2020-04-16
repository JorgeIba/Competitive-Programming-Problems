#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<string> cadenas;
lli sizee;

bool check(string a, string b)
{
    lli contador=0;
    for(int i=0; i<a.size(); i++)
    {
        if( a[i] != b[i]  )
        {
            contador++;
        }
        if(contador>2)
        {
            return false;
        }
    }
    return true;
}



lli funcion(lli i, vector<string> toCompare)
{
    if(i==sizee)
    {
        return 0;
    }
    string actual = cadenas[i];
    bool flag = true;
    for(int x=0; x<toCompare.size(); x++)
    {
        string compare = toCompare[x];
        if(!check(actual, compare))
        {
            flag = false;
            break;
        }
    }
    lli no=0, si = 0;
    if(flag)
    {
        no = funcion(i+1, toCompare);
        toCompare.push_back(actual);
        si = funcion(i+1, toCompare)+1;    
        return max(si,no);
    }
    else
    {
        return funcion(i+1, toCompare);
    }
        
}




int main()
{
    lli n; cin>>n;
    cadenas.resize(n);
    for(lli i=0; i<n; i++)
    {
        cin>>cadenas[i];
    }
    sizee = cadenas[0].length();

    vector<string> toCompare;
    lli no = funcion(1, toCompare);
    toCompare.push_back(cadenas[0]);
    lli si = funcion(1, toCompare)+1;
    
    //cout<<si<<" "<<no<<endl;

    lli res = max(si,no);

    cout<<res<<endl;




    return 0;
}