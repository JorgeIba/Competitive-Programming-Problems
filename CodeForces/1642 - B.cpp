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


int solve()
{
    lli a, b, c; cin>>a>>b>>c;


    lli diff1 = b-a;
    lli next1 = a + 2*diff1;

    bool flag = false;

    if(next1 % c == 0){
        lli ans = next1 / c;
        if(ans > 0) flag = true;
    } 
    
    lli diff2 = c-b;
    lli next2 = b - diff2;
    if(next2 % a == 0){
        lli ans = next2 / a;
        if(ans > 0) flag = true;
    } 
    

    lli diff3 = c-a;
    if(diff3 % 2 == 0){
        diff3 = (c-a)/2;
        lli next3 = a + diff3;
        if(next3 % b == 0){
            lli ans = next3 / b;
            if(ans > 0) flag = true;
        } 
    }
    
    cout << (flag ? "YES" : "NO") << endl;
    return 0;
}



int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

