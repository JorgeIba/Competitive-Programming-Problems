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

void solve()
{
    lli n, a, b; cin>>n>>a>>b;

    
    
    bool swaped = false;
    if(a < b)
    {
        swap(a, b);
        swaped = true;
    }
    

    set<lli> available;
    for(int i = 1; i<=n; i++) available.insert(i);


    auto get_L = [&]() {
        lli num = *available.begin();
        available.erase(num);
        return num;
    };

    auto get_H = [&](){
        lli num = *available.rbegin();
        available.erase(num);
        return num;
    };


    if(abs(a-b) >= 2 || n <= a+b+1)
    {
        cout << -1 << endl;
        return ;
    }


    vector<lli> ans(n);

    
    ans[0] = get_L();
    lli flag = 1;
    for(int i = 1; i < a + b + 1; i++)
    {
        if(flag)
        {
            ans[i] = get_H();
            flag = 0;
        }
        else 
        {
            ans[i] = get_L();
            flag = 1;
        }
    }
    for(int i = a+b+1; i<n; i++) ans[i] = flag ? get_L() : get_H();



    for(auto x: ans) cout << (swaped ? n-x+1 : x) << " ";
    cout << endl;

}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();
	


	return 0;
}

