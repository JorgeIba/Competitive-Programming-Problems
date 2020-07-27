#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n; 

lli cont(string a)
{
    lli cnt = 0;
    char last = a[n-1];
    for(int i = 0; i<n; i++)
    {
        if(a[i] != last) cnt++;
        last = a[i];
    }
    return cnt;
}

int main()
{
    fastIO();
    cin>>n;
    string a, b; cin>>a>>b;
    lli contA = cont(a), contB = cont(b);
    //cout<< contA << " " << contB << endl;
    assert(a != b);
    if(contA > contB)
    {
        cout<<"yes\n";
    }
    else if( contA < contB)
    {
        cout<<"no\n";
    }
    else
    {
        if(contA == 0 || contA == n)
        {
            cout<<"no\n";
        }
        else
        {
            cout<<"yes\n";
        }
    }


    return 0;
}