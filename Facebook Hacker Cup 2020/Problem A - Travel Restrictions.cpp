#include <bits/stdc++.h>

#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< string > Mat;
vector< vector< int > > ans;
int n; 

void dfsIzq(int index, int current)
{
    if(index == 0) return;
    if(Mat[1][index] == 'Y' && Mat[0][index-1] == 'Y')
    {
        ans[current][index-1] = 1;
        dfsIzq(index-1, current);
    }
}

void dfsDer(int index, int current)
{
    if(index == n-1) return;
    if(Mat[1][index] == 'Y' && Mat[0][index+1] == 'Y')
    {
        ans[current][index+1] = 1;
        dfsDer(index+1, current);
    }
}


void solve(int t)
{
    cin>>n;
    Mat.clear(); Mat.resize(2);
    for(int i = 0; i < 2; i++) cin>>Mat[i];

    ans.clear(); ans.resize(n, vector< int > (n));
    
    for(int i = 0; i<n; i++) ans[i][i] = 1;

    for(int i = 0; i<n; i++)
    {
        dfsIzq(i, i);
        dfsDer(i, i);
    }
    cout << "Case #"<<t<<":\n";
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(ans[i][j]) cout << "Y";
            else cout << "N";
        }
        cout << endl;
    }
}

int main()
{
    //fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        solve(i);
    }
    return 0;
}