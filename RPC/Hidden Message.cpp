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

const lli MOD = 1e9+7;

/*

int dp[110][110][110][310];

lli fun(int i0, int i1, int i2, int j)
{
    //cout << i[0] << " " << i[1] << " " << i[2] << endl;
    if(i0 > n[0] || i1 > n[1] || i2 > n[2]) return 0;
    if(j == m)
    {
        if(i0 == n[0] && i1 == n[1] && i2 == n[2]) return 1;
        else return 0;
    }

    int &res = dp[i0][i1][i2][j];
    if(res != -1) return res;

    int ans = 0;
    for(int x = 0; x<3; x++)
    {
        int choose = 0;
        if(x==0) choose = i0;
        if(x==1) choose = i1;
        if(x==2) choose = i2;

        if(s[x][ choose ] == t[j])
        {
            if(x==0) ans = (ans+fun(i0+1, i1, i2, j+1))%MOD;
            if(x==1) ans = (ans+fun(i0, i1+1, i2, j+1))%MOD;
            if(x==2) ans = (ans+fun(i0, i1, i2+1, j+1))%MOD;
        }
    }

    return res = ans;
}
*/


int dp[105][105][105];

int main () {
	fastIO();
    string s0, s1, s2, t; cin>>s0>>s1>>s2>>t;
    int a, b, c;
    a = s0.length();
    b = s1.length();
    c = s2.length();

    dp[0][0][0] = 1;


    for(int i = 0; i<=a; i++)
    {
        for(int j = 0; j<=b; j++)
        {
            for(int k = 0; k<=c; k++)
            {
                int total = i + j + k;
                if(s0[i] == t[total])
                {
                    dp[i+1][j][k] = (dp[i+1][j][k] +  dp[i][j][k])%MOD;
                }
                if(s1[j] == t[total])
                {
                    dp[i][j+1][k] = (dp[i][j+1][k] +  dp[i][j][k])%MOD;
                }
                if(s2[k] == t[total])
                {
                    dp[i][j][k+1] = (dp[i][j][k+1] +  dp[i][j][k])%MOD;
                }
            }
        }
    }

    cout << dp[a][b][c] << endl;
	return 0;
}