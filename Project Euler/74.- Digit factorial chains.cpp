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


lli fact[10];


lli f(lli n)
{
    lli ans = 0;
    while(n)
    {
        ans += fact[n % 10];
        n /= 10;
    }
    return ans;
}


int main () {
	//fastIO();

    time_t beginn = clock();


    fact[0] = 1;
    for(int i = 1; i<10; i++) fact[i] = i * fact[i-1];

    
    const lli N = 1e6;

    lli ans = 0;
    for(lli poss = 1; poss <= N; poss++){
        unordered_set<lli> counting;
    
        // cout << poss << endl;
        lli curr = poss;
        do {
            counting.insert(curr);
            curr = f(curr);
        }while(!counting.count(curr) && SZ(counting) <= 60);

        ans += (SZ(counting) == 60);
    }
    
    cout << ans << endl;
    cout << "Time: " << (double) (clock() - beginn) / CLOCKS_PER_SEC << endl;


	return 0;
}

