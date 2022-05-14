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


int N = 10;

bool isValidGame(vector<pair<lli,lli>> &pieces)
{
    for(int i = 1; i < N; i++)
    {
        if( pieces[i].first != pieces[i-1].second ) return false; 
    }
    return true;

}

bool isPerfect(vector<pair<lli,lli>> &pieces)
{
    if(!isValidGame(pieces)) return false;

    if(pieces[0].first != pieces[N-1].second) return false;

    lli P = pieces[0].first;
    


    lli counting = 0;

    for(int i = 0; i < N; i++)
    {
        if( pieces[i].first == P) counting++;
        if( pieces[i].second == P) counting++;
    }

    if(counting != 8) return false;

    return true;
}

bool isPermutation(vector<pair<lli,lli>> &pieces)
{
    vector<lli> fr(7);
    for(auto x: pieces) {
        fr[x.first]++;
        fr[x.second]++;
    }

    lli p = -1;
    for(auto x: fr)
        if(x == 8) p = x;
    
    if(p == -1) return false;

    for(auto &x: fr)
    {
        if(x != 8 ) 
        {
            if(x != 2) return false;
        }
    }

    return true;
}




int main () {
	fastIO();

	string s;

    while(cin>>s)
    {
        vector< pair<lli,lli> > pieces(10);
        for(int i = 0; i < 10; i++)
        {
            pieces[i] = {s[2*i] - '0', s[2*i+1] - '0'};
        }
        bool isValid = isValidGame(pieces), isPerfectP = isPerfect(pieces), isPerm = isPermutation(pieces);

        cout << (isValid ? "YES" : "NO") << " " << (isPerm ? "YES" : "NO") << " " << (isPerfectP ? "YES" : "NO") << endl;
    } 


	return 0;
}

