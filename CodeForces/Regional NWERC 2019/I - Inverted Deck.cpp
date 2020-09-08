#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

bool cmp(pair<lli,lli> a, pair<lli,lli> b)
{
    if(a.first == b.first)
    {
        return a.second < b.second;
    }
    return a.first < b.first;
}


int main () {
	fastIO();
    lli n; cin>>n;
    vector< pair<lli,lli> > nums(n+1);
    for(int i = 1; i<=n; i++){
        cin>>nums[i].first;
        nums[i].second = i;
    }
    vector< pair<lli,lli> > copia = nums;

    sort(all(copia), cmp);


    if(copia == nums)
    {
        cout << 1 << " "  << 1 << endl;
        return 0;
    }

    lli l = -1, r = -1;


    for(l = 1; l<=n; l++)
    {
        if(copia[l] != nums[l]) break;
    }
    if(l == n)
    {
        cout << 1 << " " << 1 << endl; return 0;
    }


    for(r = n; r>=1; r--)
    {
        if(copia[r] != nums[r]) break;
    }
    if(r == 1)
    {
        cout << 1 << " " << 1 << endl; return 0;
    }

    //cout << l << " " << r << endl;

    if(l >= r){
        cout << 1 << " " << 1 << endl;
        return 0;
    }
    for(int i = l; i<=r-1; i++)
    {
        if(nums[i].first < nums[i+1].first)
        {
            cout << "impossible\n";
            return 0;
        }
    }
    cout << l << " " << r << endl;
    
	
	return 0;
}