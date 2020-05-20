#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< string > mat;
const lli INF = numeric_limits<int>::max();
lli n, m; 
vector< pair<lli,lli> > dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};



int main()
{
    //fastIO();
    memset(visited, -1, sizeof(visited));
    cin>>n>>m;
    lli i, j; cin>>i>>j; 
    mat.resize(n);
    forn(i,0,n) cin>>mat[i];

    
    return 0;
}