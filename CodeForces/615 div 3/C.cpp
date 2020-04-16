#include <bits/stdc++.h>
#define lli long long int

using namespace std;


pair<lli,lli> fact(lli n, lli x)
{
    pair<lli, lli> res;
    for(int i=(x+1); i*i<=n; i++)
    {
        if((n % i == 0)and(i*i != n))
           {
               res = make_pair(i, n/i);
               return res;
           }
    }
    return make_pair(-1,-1);
}


void solve()
{
   lli n; cin>>n;
   vector<lli> res;
   if(n%2==0)
   {
       res.push_back(2);
       n/=2;
       for(int i=3; i*i<=n; i++)
       {
           if((n % i == 0)and(i*i != n))
           {
               res.push_back(i);
               res.push_back(n/i);
               cout<<"YES\n";
               for(auto x: res)
               {
                   cout<<x<<" ";
               }
               cout<<endl;
               return;
           }
       }
       cout<<"NO\n";
       return;
       
   }
   else
   {
       pair<lli,lli> aux = fact(n, 2);
       if(aux.first == (-1))
       {
           cout<<"NO\n";
           return;
       }
       vector<lli> asd;
       asd.push_back(aux.first);
       asd.push_back(aux.second);
       lli a = aux.first;
       lli b = aux.second;
       aux = fact(a, b);
       if(aux.first == (-1))
       {
           //cout<<a<<" "<<b<<endl;
           aux = fact(b, a);
           if(aux.first == (-1))
           {
               cout<<"NO\n";
               return;
           }
           else
           {
               cout<<"YES\n";
               cout<<a<<" "<<aux.first<<" "<<aux.second<<endl;
               return;
           }
       }
       else
       {
            cout<<"YES\n";
            cout<<b<<" "<<aux.first<<" "<<aux.second<<endl;
            return;
       }       
   }
   
   
    
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}