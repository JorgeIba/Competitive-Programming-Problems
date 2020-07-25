#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > Mat(5);
vector< lli > posibles;

void prec()
{
    Mat[0].resize(3, 0);
    Mat[1].resize(4, 0);
    Mat[2].resize(5, 0);
    Mat[3].resize(4, 0);
    Mat[4].resize(3, 0);
}

void read(lli howMuch, lli row)
{
    for(int i = 0; i<howMuch; i++)
    {
        string aux; cin>>aux;
        if(aux == ".") Mat[row][i] = 0;
        else if(aux == "O") Mat[row][i] = 1;
    }
}

void generarPosibles()
{
    // en diagonales izq a derecha
    

}


int main()
{
    //fastIO();
    prec();
    read(3,0);
    read(4,1);
    read(5,2);
    read(4,3);
    read(3,4);
    vector< lli > ordenado(19);
    lli idx = 0;
    for(int i = 0; i<3; i++) ordenado[idx++] = Mat[0][i];
    for(int i = 0; i<4; i++) ordenado[idx++] = Mat[1][i];
    for(int i = 0; i<5; i++) ordenado[idx++] = Mat[2][i];
    for(int i = 0; i<4; i++) ordenado[idx++] = Mat[3][i];
    for(int i = 0; i<3; i++) ordenado[idx++] = Mat[4][i];

    lli maskPrincipal = 0;
    for(int i = 0; i<ordenado.size(); i++)
    {
        if(ordenado[i])
        {
            maskPrincipal |= (1<<i);
        }
    }
    /*
    for(int i = 0; i<19; i++)
    {
        if(maskPrincipal&(1<<i)) cout << 1;
        else cout << 0;
    }
    */

    generarPosibles();
    vector< lli > dp((1<<19));
    dp[maskPrincipal] = 1;
    for(int mask = 0; mask < (1<<19); mask++)
    {
        for(auto maskMov: movimientos)
        {
            if(maskMov && (1<<i))
            {
                dp[mask] += dp[mask ^ (1<<i)];
            }
        }
    }
    if(dp[0])

    return 0;
}