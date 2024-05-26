    #include<bits/stdc++.h>

    #define lli long long int
    #define ld long double
    #define all(a) a.begin(), a.end()
    #define SZ(a) (int) a.size()
    #define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    #define forn(i,n) for(int i = 0; i < n; i++)

    using namespace std;


    const ld eps = 1e-12;

    bool eq(ld a, ld b){return abs(a-b) <= eps;}
    bool le(ld a, ld b){return b-a > eps;}
    bool leq(ld a, ld b){return b-a >= -eps;}

    const ld pi = acos(-1);

    struct  point{
        ld x, y;
        point(): x(0), y(0) {}
        point(ld x, ld y): x(x), y(y) {}
        ld cross(const point& p)const{return x*p.y - y*p.x;}

        bool operator<(const point& p)const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
        point operator-(const point& p)const{return point(x - p.x, y - p.y);}

        ld ang() const{
            ld a = atan2l(y, x);
            a += le(a, 0) ? 2*pi : 0;
            return a;
        }

    };

    lli area(vector<point> P){
        int n = P.size();
        lli ans = 0;
        forn(i, n) ans += P[i].cross(P[(i + 1) % n]);
        return abs(ans);
    }

    vector<point> convexHull(vector<point> P){
        sort(all(P));
        vector<point> L, U;
        // for(int i = 0; i < P.size(); i++){
        // 	while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
        // 		L.pop_back();
        // 	}
        // 	L.push_back(P[i]);
        // }
        for(int i = P.size() - 1; i >= 0; i--){
            while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
                U.pop_back();
            }
            U.push_back(P[i]);
        }
        // U.pop_back();
        // L.pop_back();
        // L.insert(L.end(), U.begin(), U.end());
        return U;
    }





    int main() {
        fastIO();
        lli n;
        cin >> n;
        vector<point> P(n);
        forn(i, n){
            cin >> P[i].x >> P[i].y;
        }
        auto CH = convexHull(P);

        reverse(all(CH));

        lli m = SZ(CH);

        // for(auto p:CH) cout << p.x << ' ' << p.y << endl;


        ld ans = -pi;
        for(int i = 1; i < m; i++){
            auto point_1 = CH[i-1];
            auto point_2 = CH[i];

            ld ang = (point_2 - point_1).ang() * 180 / pi;
            if(0 <= ang && ang <= 90) {

            } else {
                ang = 360 - ang;
            }
            // cout << ang << endl;
            ans = max(ans, ang);    
        }

        cout << fixed << setprecision(15) << ans << endl;

        // for(auto p:CH) cout << p.x << ' ' << p.y << endl;
        return 0;
    }