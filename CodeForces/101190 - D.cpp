#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)
#define fore(i, a, b) for(int i = (a); i < (b); i++)

using namespace std;


typedef double num_t;
typedef vector<num_t> Vec;
typedef vector<Vec> Mat;


const num_t EPS = 1e-3;
vector<int> X,Y;
vector<vector<num_t> > A;
vector<num_t> b,c;
num_t z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	fore(i,0,m)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	fore(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		fore(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	fore(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<num_t,vector<num_t> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<num_t> > _A, vector<num_t> _b, vector<num_t> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	fore(i,0,m)X[i]=i;
	fore(i,0,n)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		num_t mn=-EPS;
		fore(i,0,n)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		fore(i,0,m)if(A[x][i]<-EPS){y=i;break;}
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		num_t mx=EPS;
		int x=-1,y=-1;
		fore(i,0,m)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		num_t mn=1e200;
		fore(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<num_t> r(m);
	fore(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}


int main () {
	fastIO();


    #ifdef ONLINE_JUDGE
    freopen("delight.in", "r", stdin);
    freopen("delight.out", "w", stdout);
    #endif

    int n, k, m_s, m_e; cin>>n>>k>>m_s>>m_e;

    vector<int> sleep(n), eat(n);
    for(auto &x: sleep) cin>>x;
    for(auto &x: eat) cin>>x;

    int sz_rest = n + 2*(n-k+1);

    Mat A(sz_rest, Vec(n));
    Vec R(sz_rest);

    for(int i = 0; i < n; i++){
        A[i][i] = 1;
        R[i] = 1;
    }

    int entry = n;
    for(int i = 0; i + k - 1< n; i++, entry++){
        for(int j = i; j < i+k; j++) {
            A[entry][j] = 1;
        }
        R[entry] = k - m_s;
    }

    for(int i = 0; i + k - 1< n; i++, entry++){
        for(int j = i; j < i+k; j++) {
            A[entry][j] = -1;
        }
        R[entry] = -m_e;
    }


    Vec M(n);
    for(int i = 0; i < n; i++)
        M[i] = eat[i] - sleep[i];

    
    auto ans = simplex(A, R, M);


    lli C = 0;
    for(auto x: sleep) 
        C += x;

    cout << (lli)round(ans.first) + C << endl;

    for(auto &x: ans.second) {
        x = (int)round(x);
        if(x) cout << "E";
        else cout << "S";
    }
    cout << endl;
    




	return 0;
}

