#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< char > moves;
vector< char > poss = {'H', 'S', 'P'};
const lli maxN = 1e5+10;
lli dp[maxN][3][21];
lli n, k;
bool isWinner(char a, char b)
{
    if(a == b) return false;
    if(a == 'H' && b == 'S') return true;
    else if(a == 'S' && b == 'P') return true;
    else if(a == 'P' && b == 'H') return true;
    return false;
}

lli fun(lli idx, char curr, lli k)
{
    if(idx == n) return 0;
    lli idxCurr = -1;
    if(curr == 'H') idxCurr = 0;
    if(curr == 'S') idxCurr = 1;
    if(curr == 'P') idxCurr = 2;
    lli &res = dp[idx][idxCurr][k];
    if(res != -1) return res;
    res = 0;

    res = isWinner(curr, moves[idx]); // 1 o 0
    //cerr << res << endl;
    lli maximo = -1;
    for(auto c: poss)
    {
        lli aux = 0;
        if(c == curr) aux = fun(idx+1, curr, k);
        else
        {
            if(k>0)
            {
                aux = fun(idx+1, c, k-1);
            }
        }
        maximo = max(maximo, aux);
    }

    return res+=maximo;
}


int main() //H -> S, S -> P, P -> H
{
    fastIO();
    ifstream cin("hps.in");
    ofstream cout("hps.out");
    cin>>n>>k;
    memset(dp, -1, sizeof(dp));
    moves.resize(n);
    for(auto &x: moves) cin>>x;
    
    cout << max({fun(0, 'H', k), fun(0, 'S', k), fun(0, 'P', k)}) << endl;
    
    return 0;
}