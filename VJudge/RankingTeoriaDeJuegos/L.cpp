#include <bits/stdc++.h>
#define lli long long int 

using namespace std;

void solve()
{
    string s; cin>>s;
    char start, last;
    bool contando = false;
    vector< lli > nim;
    lli t = s.length();
    lli comodinA = 0, comodinB = 0, cont = 0;
    for(int i = 0; i < t ; i++)
    {
        if(s[i]!='.')
        {
            if(!contando)
            {
                start = s[i];
                contando = true;
            } 
            else
            {
                last = s[i];
                if((start == 'A') and (last == 'A'))
                {
                    comodinA += cont;
                }
                else if ((start == 'B') and (last == 'B'))
                {
                    comodinB += cont;
                }
                else
                {
                    nim.push_back( cont );
                }
                contando = false;
                cont=0;
            } 
        }
        else
        {
            if(contando)
            {
                cont++;
            } 
        }
    }
    if((cont != 0)and(contando))
    {
        if(start == 'A')
        {
            comodinA += cont;
        }
        else if (start == 'B')
        {
            comodinB += cont;
        }
    }
    
    int res = 0;
    for(int i = 0; i< nim.size(); i++)
    {
        res = res ^  nim[i];
    }
    if(comodinA > comodinB)
    {
        cout<<"A\n";
    }
    else if (comodinB > comodinA)
    {
        cout<<"B\n";
    }
    else
    {
        if(res == 0)
        {
            cout<<"B\n";
        }
        else
        {
            cout<<"A\n";
        }
    }

}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--) 
    {
        solve();
    }
    return 0;
}