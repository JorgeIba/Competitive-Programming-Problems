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


template <typename T,typename S> 
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = 0, neutro_lazy = 0;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;
    
    //S tipo de dato que recibe
	SegmentTreeItLazy(int n, T val = 0,  const vector<S> &v = vector<S>()){
		st.resize(2*n);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i]);
		build();
	}

	T merge(T a, T b){
		return a + b;
		//return a * b;
		//return __gcd(a, b);
		//return min(a, b);
	}
	void apply(int i, T val, int k){
		st[i] += val * k; 
		if (i < size) delUp[i] += val, upd[i] = 1;
	}
	void calc(int i){
		if (!upd[i]) st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void build(){
		for(int i = size - 1; i; i--) calc(i);
	}
	void build(int p) {
		while (p > 1) p >>= 1, calc(p);
	}
	void push(int p) {
		for (int s = height, k = 1 << (height - 1); s; s--, k >>= 1){
			int i = p >> s;
			if (upd[i]){
				apply(i << 1, delUp[i], k);
				apply(i << 1 | 1, delUp[i], k);
				upd[i] = 0, delUp[i] = neutro_lazy;
			}
		}
	}
	void update(int l, int r, T val){
		push(l += size), push(r += size);
		int ll = l, rr = r, k = 1;
		for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
			if (l & 1) apply(l++, val, k);
			if (~r & 1) apply(r--, val, k);
		}
		build(ll), build(rr);
	}
	T query(int l, int r){
		push(l += size), push(r += size);
		T res = neutro;
		for (; l <= r; l >>= 1, r >>= 1){
			if (l & 1) res = merge(res, st[l++]);
			if (~r & 1) res = merge(res, st[r--]);
		}
		return res;
	}
	T& operator[](int i) { return st[i + size]; }
	T set(S x){
		return x;
	}
};




vector<lli> nums;
lli n;

vector<lli> next_greater_element() {
    vector<lli> output;
    output.reserve(nums.size());

    stack<pair<lli,lli>> S; 
  
    for (int i=0; i<n; i++) 
    { 
        while (!S.empty() && S.top().second <= nums[i]) 
            S.pop(); 
  
        if (S.empty()) 
            output.push_back(-1);
        else 
            output.push_back(S.top().first);
        S.push({i, nums[i]}); 
    } 
    
    return output;
}


vector<lli> before_greater_element() {
    vector<lli> output;
    output.reserve(nums.size());

    stack<pair<lli,lli>> S; 
  
    for (int i=n-1; i>=0; i--) 
    { 
        while (!S.empty() && S.top().second <= nums[i]) 
            S.pop(); 
  
        if (S.empty()) 
            output.push_back(-1);
        else 
            output.push_back(S.top().first);
        S.push({i, nums[i]}); 
    } 
    
    return output;
}



int main () {
	//fastIO();
    cin>>n;

    nums.resize(n);
    for(auto &x: nums) cin>>x;

    auto next_greater = next_greater_element();
    auto before_greater = before_greater_element();
    reverse(all(before_greater));


    vector<pair<lli,lli>> ranges(n);
    for(int i = 0; i<n; i++)
    {
        ranges[i] = { next_greater[i], before_greater[i]  };
    }


    vector<lli> ans(n);
    SegmentTreeItLazy<lli,lli> *ST = new SegmentTreeItLazy<lli,lli>(n, 0, ans);


    for(int i = 0; i<n; i++)
    {
        lli L = ranges[i].first, R = ranges[i].second;
        if(L == -1)
        {
            if(i != 0) 
            {
                ST->update(0, i-1, 1);
            }
                
        }
        else
        {
            if(i != 0)
            {
                ST->update( (i+L)/2 + 1 , i-1, 1);
            }   
                
        }

        if(R == -1)
        {
            if(i != n-1)
            {
                ST->update(i+1, n-1, 1);
            }
                
        }
        else
        {
            if(i != n-1)
            {
                ST->update(i+1, (R+i-1)/2,1);
            }
                
        }
    }

    for(int i = 0; i<n; i++)
    {
        cout << ST->query(i,i) << " ";
    }


	return 0;
}

