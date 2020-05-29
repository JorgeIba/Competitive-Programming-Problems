#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<double> s, problems;
vector< vector<char> > resultados;
double dp[105][105][105];
bool check[105][105][105];
lli t, p; 
vector<lli> need;
vector<lli> puntaje;

double funcion(lli i, lli j, lli llevo)
{
    double stren = s[i];
    lli needed = need[i];
    if(j==p)
    {
        if(llevo >= needed) return 1;
        return 0;
    }
    if(check[i][j][llevo]) return dp[i][j][llevo];

    double smn = stren * problems[j];
    if(resultados[i][j] == 'X')
    {
        check[i][j][llevo] = true;
        return dp[i][j][llevo] = funcion(i, j+1, llevo);
    }
    else if(resultados[i][j] == '-')
    {
        check[i][j][llevo] = true;
        return  dp[i][j][llevo] = funcion(i, j+1, llevo);
    }
    else
    {
        check[i][j][llevo] = true;
        double no = funcion(i, j+1, llevo) * (1-smn);
        double si = funcion(i, j+1, llevo + 1) * smn;
        return dp[i][j][llevo] = si + no;
    }
}



int main()
{
    fastIO();
    cin>>t>>p;
    s.resize(t-1); problems.resize(p);
    puntaje.resize(t);
    need.resize(t-1);
    resultados.assign(t, vector<char>(p));
    for(auto &x: s)
    {
        cin>>x;
    }
    for(auto &x: problems)
    {
        cin>>x;
    }

    for(auto &team: resultados)
    {
        for(auto &ver: team)
        {
            cin>>ver;
        }
    }
    lli suma = 0;
    for(int i = 0; i<p; i++)
    {
        suma += (resultados[t-1][i]=='X');
    }

    for(int i = 0; i<t-1; i++)
    {
        lli aux = 0;
        for(int j = 0; j<p; j++)
        {
            aux += (resultados[i][j]=='X');
        }
        need[i] = suma - aux + 1;
    }

    double res = 1;
    for(int i = 0; i<t-1; i++)
    {
        //cout<<funcion(i,0,0)<<endl;
        res*=(1-funcion(i,0,0));
    }
    cout<<res<<endl;
    



    return 0;
}