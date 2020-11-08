#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

int m, d;
int n;
VI digits;
vector<lli> pows10;
lli const MOD = 1e9+7;

void precPows()
{
    pows10.resize(2010);
    pows10[0] = 1 % m;
    for(int i = 1; i<2010; i++)
    {
        pows10[i] = (pows10[i-1]*10)%m;
    }
}

lli dp[2010][2][2010];

lli fun(lli idx, bool canAll, lli numero)
{
    if(idx == n)
    {
        return numero == 0;
    }

    int digit = digits[idx];
    int limit = canAll? 9: digit;

    lli &ans = dp[idx][canAll][numero];
    if(ans != -1) return ans;

    ans = 0;
    for(int di = 0; di<=limit; di++)
    {            
        if((idx%2 == 1 && di == d) || (idx%2 == 0 && di !=d))
        {
            ans = (ans + fun(idx+1, canAll | (di<limit), (numero + di*pows10[n-idx-1])%m )) % MOD;
        }
    }
    return ans;
}


lli f(const VI &num)
{
    if(num[0] == -1) return 0;
    digits = num;
    n = SZ(num);
    memset(dp, -1, sizeof(dp));
    return fun(0, false, 0);
}



int main () {
	fastIO();
    cin>>m>>d;
    string l, r; cin>>l>>r;
    vector<int> L, R;
    for(auto x: l) L.push_back(x-'0');
    for(auto x: r) R.push_back(x-'0');

    int aux = L.back() - 1; L.back() = aux;
    for(int i = SZ(L)-1; i>=0; i--)
    {
        if(L[i] < 0)
        {
            L[i] = 9;
            if(i-1 < 0) L = {-1};
            L[i-1]--;
        }
    }

    precPows(); 
    //cerr << f(R) << " " << f(L) << endl;
    cout << (f(R) - f(L) + MOD)%MOD << endl;
	return 0;
}