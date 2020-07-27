#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


const lli INF = 1e18;
vector<lli> d;

lli getMax(lli num)
{
    lli l = 0, r = d.size()-1;
    lli res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( d[mid]  <  num  )
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return res;
}

lli binariaLeft(lli num, lli idxMax)
{
    lli l = 0, r = idxMax;
    lli res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( d[mid] <= num)
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return res;
}


int main()
{
    fastIO();
    lli n; cin>>n;
    d.resize(n+1);
    d[0] = 0;
    for(int i = 1; i<=n; i++)
    {
        cin>>d[i];
    }
    
    lli q; cin>>q;
    while(q--)
    {
        lli X, Y; cin>>X>>Y;
        lli idxMax = getMax(Y);
        lli idLeft = binariaLeft( Y-X , idxMax);
        lli possible1 = d[idLeft];
        assert(idLeft != -1);
        assert(idxMax != -1);
        //cout << idxMax << " " << idLeft << endl;
        if(idLeft+1 <= idxMax)
        {
            lli possible2 = d[idLeft + 1];
            lli res = min( abs(Y-X-possible1), abs(Y-X-possible2));
            if(res == abs(Y-X-possible1))
            {
                cout<< idLeft << endl;
                assert( possible1 <= possible2);
            }
            else
            {
                assert( Y - possible2 > 0);
                cout<< idLeft + 1 << endl;
                assert( possible2 > possible1  );
            }
        }
        else
        {
            cout<< idLeft << endl;
            assert( idLeft + 1 > n || d[idLeft + 1] >= Y  );
        }                
    }

    return 0;
}