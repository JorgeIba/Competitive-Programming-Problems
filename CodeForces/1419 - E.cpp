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

vector<pair<lli,lli>> factorize(lli n)
{
    vector<pair<lli,lli>> facts;
    for(lli i = 2; i*i <=n; i++)
    {
        if(n % i == 0)
        {
            lli cont = 0;
            while(n % i == 0)
            {
                cont++;
                n/=i;
            }
            facts.push_back({i,cont});
        }
    }
    if(n>1) facts.push_back({n, 1});
    return facts;
}

vector<lli> prime;
vector<lli> power;
set<lli> divisor;
lli sz;

void getDivisors(lli idx, lli num)
{
    if(num!=1)
        divisor.insert(num);
    if(idx == sz) return;
    lli p = 1;
    for(int i = 0; i<=power[idx]; i++)
    {
        getDivisors(idx+1, num*p);
        p *= prime[idx];
    }
    return;
}


void solve()
{
    lli n; cin>>n;
    auto facts = factorize(n);
    sz = SZ(facts);
    prime.resize(sz);
    power.resize(sz);    
    for(int i = 0; i<sz; i++)
    {
        prime[i] = facts[i].first;
        power[i] = facts[i].second;
    }
    getDivisors(0, 1);

    vector<lli> ans;
    if(sz == 1)
    {
        for(auto d: divisor)
        {
            cout << d << " ";
        }
        cout << endl << 0 << endl;
    }
    else if(sz == 2 && power[0] == 1 && power[1] == 1)
    {
        cout << prime[0] << " " << prime[1] << " " << n << endl << 1 << endl;
    }
    else
    {
        divisor.erase(n);
        for(int i = 0; i<sz; i++)
        {
            lli first = prime[i], last = prime[i]*prime[(i+1)%sz];
            divisor.erase(first);
            divisor.erase(last);
            ans.push_back(first);
            vector<lli> anexar;
            for(auto d: divisor)
            {
                if(d % prime[i] == 0) anexar.push_back(d);
            }
            for(auto d: anexar)
            {
                divisor.erase(d);
                ans.push_back(d);
            } 
            ans.push_back(last);
        }
        ans.pop_back();
        ans.push_back(n);
        for(auto x: ans) cout << x << " "; 
        cout << endl << 0 << endl;
    }
    
}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--)
    {
        prime.clear(); 
        power.clear();
        divisor.clear();
        solve();
    } 

    
	return 0;
}