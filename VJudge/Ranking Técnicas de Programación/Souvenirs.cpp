#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    fastIO()
    lli n; cin>>n;
    vector<lli> a(n), b(n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    
    lli mitad = n/2;
    lli mitad2 = n - mitad;
    vector< pair<lli,lli> > maskFirst(1<<mitad);
    for(int i = 0; i<(1<<mitad); i++)
    {
        lli aux = 0;
        for(int j = 0; j<mitad; j++)
        {
            if(i & (1<<j))
                aux+= a[j];
            else
                aux-= b[j];
        }
        maskFirst[i].first = aux;
        maskFirst[i].second = i;
    }

    vector< pair<lli,lli> > maskSecond(1<<mitad2);
    for(int i = 0; i<(1<<mitad2); i++)
    {
        lli aux = 0;
        for(int j = 0; j<mitad2; j++)
        {
            if(i & (1<<j))
                aux+= a[n-j-1];
            else
                aux-= b[n-j-1];
        }
        maskSecond[i].first = aux;
        maskSecond[i].second = i;
    }
    
    sort(all(maskSecond));

   
    lli answerF = 0, answerS=0, best = -1;
    for(int i = 0; i<maskFirst.size(); i++)
    {
        lli mask = maskFirst[i].first;
        lli l=0, r=maskSecond.size()-1;
        while(l<=r)
        {
            lli mid = l + (r-l)/2;
            lli diff = abs(maskSecond[mid].first + mask);
            lli looking = -mask;
            if(best == -1 || diff < best) 
            {
                best = diff;
                answerF = maskFirst[i].second;
                answerS = maskSecond[mid].second;
            }
            if( maskSecond[mid].first == looking )
            {
                break;
            }
            else if(maskSecond[mid].first < looking)
            {
                l = mid+1;
            }
            else
            {
                r = mid - 1;
            }
        }
    }

    cout<<best<<endl;
    vector<lli> primero;
    vector<lli> segundo;

    for(int j = 0; j<mitad; j++)
    {
        if(answerF & (1<<j))
            primero.push_back(j);
        else
            segundo.push_back(j);
    }

    for(int j = 0; j<mitad2; j++)
    {
        if(answerS& (1<<j))
            primero.push_back(n-j-1);
        else
            segundo.push_back(n-j-1);
    }
    cout<<primero.size()<<" ";
    for(auto x: primero) cout<<x+1<<" ";
    cout<<endl;
    cout<<segundo.size()<<" ";
    for(auto x: segundo) cout<<x+1<<" ";
    cout<<endl;
    return 0;
}