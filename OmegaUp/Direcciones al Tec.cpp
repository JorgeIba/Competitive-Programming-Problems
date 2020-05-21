#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli n, m;
vector< vector<lli> > mapa;
vector< vector<bool> > check;
lli contador = 0;

lli fix(lli t)
{
    if(t == 2) return 3;
    if(t == 3) return 2;
    return t;
}


bool funcion(lli i, lli j)
{
    //cout<<"("<<i<<", "<<j<<")\n";
    
    if((i == n-1) and (j == m-1)) {return true;}

    if(i < 0 || i == n || j < 0 || j==m) {return false;}

    //if(check[i][j] == true) {return false;}
    
    check[i][j] = true;

    lli t = mapa[i][j];
    t = fix(t);
    lli move = (t + contador%4)%4;
    
    //cout<<t<<" "<<contador<<" "<<move<<endl;
    switch (t)
    {
        case 0:
            break;
        case 1:
            contador +=1;
            break;
        case 2: 
            contador +=2;
            break;
        case 3:
            contador +=3;
            break;
    }

    switch( move  )
    {
        case 0:
            return funcion(i, j+1);
        case 1:
            return funcion(i+1, j);
        case 2:
            return funcion(i, j-1);
        case 3:
            return funcion(i-1, j);
    }
}

int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    mapa.assign(n, vector<lli> (m));
    check.assign(n, vector<bool> (m, false));
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin>>mapa[i][j];
        }
    }

    if( funcion(0,0) )
    {
        cout<<"llegaste\n";
    }
    else
    {
        cout<<"te perdiste\n";
    }
    
    return 0;   
}