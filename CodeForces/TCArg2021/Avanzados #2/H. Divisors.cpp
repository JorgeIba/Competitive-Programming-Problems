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


map<lli,lli> factors;


lli is_square(lli n)
{
    lli l = 1, r = sqrt(n) + 2;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(mid * mid == n) return mid;
        else if( mid * mid < n) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

lli is_tri(lli n)
{
    lli l = 1, r = pow(n, 1.0/3.0) + 2;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(mid * mid * mid == n) return mid;
        else if( mid * mid * mid < n) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}


lli is_quartic(lli n)
{
    lli l = 1, r = sqrt(sqrt(n) + 2)+2;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(mid * mid * mid * mid == n) return mid;
        else if( mid * mid * mid * mid < n) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

const lli MOD = 998244353;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b>>=1;
        a = a*a % MOD;
    }
    return res;
}


int main () {
	//fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    VLL sobras;

    for(auto x: nums)
    {
        lli p = is_quartic(x);
        if(p != -1)
        {
            factors[p] += 4;
        }
        else
        {
            p = is_tri(x);
            if(p != -1)
            {
                factors[p] += 3;
            }
            else
            {
                p = is_square(x);
                if(p != -1)
                {
                    factors[p] += 2;
                }
                else
                {
                    sobras.push_back(x);
                }
            }
        }
    }


    
    vector<lli> sobras2;
    for(auto x: sobras)
    {
        bool flag = false;

        pair<lli,lli> facts;

        for(auto f: factors)
        {
            lli p = f.first;
            if( x % p == 0 )
            {
                facts = {p, x/p};
                flag = true;
                break;
            }
        }

        if(!flag)
        {
            sobras2.push_back(x);
        }
        else
        {
            factors[facts.first]++; factors[facts.second]++;
        }
    }


    map<lli,lli> fr;
    set<lli> sobras_set;
    for(auto x: sobras2)
    {
        fr[x]++;
        sobras_set.insert(x);
    }

    sobras.clear();
    for(auto x: sobras_set) sobras.push_back(x);


    int m = SZ(sobras), irrepetibles = 0;

    vector<lli> unknown;

    for(int i = 0; i<m; i++)
    {
        bool flag = false;
        for(int j = 0; j<m; j++)
        {
            if(i == j) continue;

            lli p_i = __gcd(sobras[i], sobras[j]);
            if(p_i == 1) continue;

            flag = true;
            factors[p_i] += fr[sobras[i]];
            factors[sobras[i] / p_i] += fr[sobras[i]];
            break;
        }

        if(!flag)
        {
            if(!fr[sobras[i]])
                irrepetibles += 2;
            else
            {
                unknown.push_back(fr[sobras[i]]);
                unknown.push_back(fr[sobras[i]]);
            }
        }

    }
        
    
    lli ans = 1;
    for(auto x: factors)
    {
        ans = ans * ((x.second+1)%MOD) % MOD;
    }
    
    ans = ans * binPow(2, irrepetibles) % MOD;

    for(auto x: unknown)
    {
        ans = (ans * (x+1))%MOD;
    }


    cout << ans << endl;

    //for(auto x: factors) cout << x.first << "^" << x.second << "   ";
    //cout << "No se repiten: " << irrepetibles << endl;


	return 0;
}

