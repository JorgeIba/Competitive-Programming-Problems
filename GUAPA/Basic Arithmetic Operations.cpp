#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void reduce(lli &a, lli &b)
{
    lli gcd = __gcd(a,b);
    a /= gcd;
    b /= gcd; //reducidos
    lli fl = a/b;
    if(fl > 0)
    {
        a -= fl*b;
    }
}


const lli MOD = 999999937;

lli binPow(lli a, lli b)
{
    lli res = 1;
    a = a%MOD;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b>>=1;
        a = (a*a)%MOD;
    }
    return res%MOD;
}

map <lli, lli> mp; 
lli r = 0, l = 0;
bool flag;


string fractionToDecimal(int numr, int denr) 
{ 
    string res; // Initialize result 
    r = 0, l = 0;
    mp.clear(); 
  
    // Find first remainder 
    int rem = numr%denr; 
  
    while ( (rem!=0) && (mp.find(rem) == mp.end()) ) 
    { 
        mp[rem] = res.length(); 
  
        rem = rem*10; 
  
        int res_part = rem / denr; 
        res += to_string(res_part); 
  

        rem = rem % denr; 
        r++;
    } 
    l = mp[rem];
    if(rem == 0)
    {
        flag = 0;
    }
    else
    {
        flag = 1;
    }
    return res;
} 

lli getValue(lli li, lli ri, string &res)
{
    lli actual = 1;
    for(int i = li; i<ri; i++)
    {
        if(res[i] == '0') res[i] = '7';
        actual = (actual * (res[i] - '0'))%MOD;
    }
    return actual%MOD;
}

void solve()
{
    lli a, b, n; cin>>a>>b>>n;
    reduce(a, b);
    string res = fractionToDecimal(a, b);


    if(!flag) // No tiene ciclo
    {
        lli actual = 1;
        if(n > r)
        {
            actual = binPow(7, n-r);
        }
        actual = (actual*getValue(0, r, res))%MOD;
        cout << actual << endl;
    }
    else
    {
        if( l == 0 ) // Periodico Puro
        {
            lli actual = 1;
            lli sz = res.length();
            lli total = getValue(0,r,res);
            if( n > sz )
            {
                lli cuantos = n/sz;
                actual = binPow(total, cuantos);
            }
            actual = (actual * getValue(0, n%sz, res))%MOD;
            cout << actual << endl;
        }
        else //Periodico Mixto
        {
            lli actual = 1;
            if(n <= l)
            {
                actual = getValue(0, n, res);
                cout << actual << endl;
                return;
            }
            actual = getValue(0, l, res);
            string perrona = res.substr(l);
            
            n -= l;
            r-=l;
            l = 0;


            lli sz = perrona.length();
            lli total = getValue(0,r,perrona);
            if( n > sz )
            {
                lli cuantos = n/sz;
                actual = (binPow(total, cuantos)*actual)%MOD;
            }
            actual = (actual * getValue(0, n%sz, perrona))%MOD;
            cout << actual << endl;
        }
    }
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}