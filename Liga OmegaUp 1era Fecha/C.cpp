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


#define point pair<lli,lli>
#define x first
#define y second

lli sign(lli num)
{
    if(num < 0) return -1;
    else if(num > 0) return 1;
    else return 0;
}


lli get_cross(point a, point b)
{
    return a.x * b.y - a.y*b.x;
}


point resta(point a, point b)
{
    return {a.x - b.x, a.y - b.y};
}


string solve()
{
    point me;
    vector<point> esquinas(3);

    cin>>me.x>>me.y;

    for(auto &esquina: esquinas) cin>>esquina.x>>esquina.y;


    sort(all(esquinas));

    const lli INF = 1e18;
    lli sign_before = -INF;

    for(int i = 0; i<3; i++)
    {
        point seg1 = resta(esquinas[(i+1)%3], esquinas[i]);
        point seg2 = resta(me, esquinas[i]);

        lli cross = get_cross(seg1, seg2);
        lli curr_sign = sign(cross);

        
        if(sign_before == -INF)
        {
            sign_before = curr_sign;
        }
        else 
        {
            if(sign_before != curr_sign)
            {
                return "OUT";
            }
        }
        
        sign_before = curr_sign;
    }

    return "IN";
}


int main () {
	fastIO();
	lli t; cin>>t;

    for(int i = 1; i<=t; i++)
    {
        string ans = solve();
        cout << "Case #" << i << ": " << ans << endl;
    }

	


	return 0;
}

