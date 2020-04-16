#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> numeros;

bool checkmayor()
{
    lli j = 0;
    for(int i=0; i<numeros.size(); i++)
    {
        //cout<<"ASD";
        if( numeros[i] >= j)
        {
            //cout<<numeros[i]<<" "<<j<<endl;
            j++;
        }
        else
        {
            return false;
        }
        
    }
    return true;
}

bool checkmenor()
{
    lli j = numeros.size()-1;
    for(lli i = 0; i<numeros.size(); i++)
    {
        if(numeros[i] >= j)
        {
            j--;
        }   
        else
        {
            return false;
        }
        
    }
    return true;
}

bool checkmedio()
{
    lli l = 0, r = numeros.size()-1;
    lli aux = 0;
    while( (r-l) > 1  )
    {
        if(( numeros[r] >= aux  )and(numeros[l] >= aux))
        {
            l++;
            r--;
            aux++;
        }
        else
        {
            return false;
        }
    }
    if( numeros.size()%2 == 0)
    {
        if(( numeros[r] >= (aux+1)  )and(numeros[l] >= aux))
        {
            return true;
        }
        if(( numeros[r] >= (aux)  )and(numeros[l] >= aux+1))
        {
            return true;
        }
    }
    else
    {
        if(numeros[r]>=aux)
        {
            return true;
        }
    }
    
    
    return false;

}


void solve()
{
    lli n; cin>>n;
    numeros.clear();
    numeros.resize(n);
    for (auto &x: numeros)
    {
        cin>>x;
    }

    if(checkmayor() or checkmenor() or checkmedio())
    {
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
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