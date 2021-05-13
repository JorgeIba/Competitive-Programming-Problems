#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef long double ld;
typedef vector<int> vi;

template<class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = 0;
    while (!isdigit(c)) {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x = flag ? -x : x;
}

const int MAXN = 1e6;

int A[MAXN], B[MAXN];

int main(){
  //fastIO();
  while(true){
    int n, m; read(m), read(n);
    //cin >> m >> n;
    if(m == 0 && n == 0) break;
    set<int> a;
	int inter = 0;
	int x;
    forn(i, m){
      read(A[i]);
      //cin >> x;
      a.insert(x);
      /* aub.insert(x); */
    }
    forn(i, n){
      //cin >> x;
      read(B[i]);
      /* b.insert(x); */
      /* aub.insert(x); */
      /* if(a.count(B[i])) */
      /*   inter++; */
    }
	sort(A, A + m);
	sort(B, B + n);
	int i, j;
	i = j = 0;
	while(i < m && j < n){
		if(A[i] == B[j]){
			inter++;
			i++; j++;
		}
		else if(A[i] < B[j]) i++;
		else j++;
	}
    printf("%d %d %d %d\n", m - inter, inter, n - inter, m + n - inter);
  }
  return 0;
}
