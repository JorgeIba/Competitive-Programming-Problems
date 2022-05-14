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


const lli maxN = 100;
//15
lli nCr[maxN+5][maxN+5];
void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<=maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else
            {
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % 4;
            }
            //cout << nCr[i][j] << " ";
        }
        //cout << endl;
    }
}

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"




pair<lli,lli> sum_odd(lli n){
    if(n <= 1) return {n+1, n+1};

    lli last_level = 1LL << (lli)(log2(n));
    auto [total_sum, sum_idx] = sum_odd(n-last_level);

    return {2*total_sum, total_sum*(n+2)};
}

ld log4(lli n) {
    return log2(n) / log2(4);
}


lli powerMod(lli a, lli b){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}


const lli INF = 1e9;
lli first_idx(lli n){
    if(n == 2) return 2;
    if(n == 4) return 3;
    if(__builtin_popcount(n+1) == 1 ) return INF;

    lli last_level = 1LL << (lli)(log2(n));
    lli equiv = n - last_level;
    auto last_idx = first_idx(equiv);

    // cout << n << " " << equiv << endl;

    if(last_idx == INF){
        lli total_next_level = last_level;
        /*
        cout << total_next_level/2 << endl;
        */

        return total_next_level/2 + 1;
    } else {
        // cout << n << " ->2 " << last_idx << endl;
        return last_idx;
    }
}


int main () {
	//fastIO();
    
    prec();

    lli N, X; cin>>N>>X;
    
    

    /*
    for(int i = 0; i<=N; i++)
    {
        // lli sum1 = 0, sum2 = 0;
        for(int j = 0; j<=i; j++)
        {
            lli v = nCr[i][j] % 4;
            if(v == 2) cout << GREEN << v << RESET << " ";
            else cout << RED << v << RESET << " ";
        }
        cout << " <- " << i << endl;
        //cout << sum1 << " -- " << sum2 << " ";
    }
    cout << endl;
    */
    



    /*
    for(int i = 1; i<=N; i++)
    {
        lli last_idx = INF;
        for(int j = 0; j<=i; j++)
        {
            lli v = nCr[i][j] % 4;
            if(v == 2) {
                last_idx = j+1;
                break;
            }
        }
        cout << last_idx << " ";
    }
    cout << endl;
    

    for(int i = 1; i <= N; i++) {
        cout << first_even(i) << " ";
        // first_even(i);
    }
    */


	return 0;
}

