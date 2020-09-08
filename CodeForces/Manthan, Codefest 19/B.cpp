#include <bits/stdc++.h>
#define lli long long
using namespace std;
const int N = 2e3 + 10;
int a[N], l[N], r[N];
int n;
int check(int siz){
    unordered_map<int, int> m;
    for(int i = 1; i <= n; i++) m[a[i]]++;
 
    
	for(auto x: m)
    {
    	cout<<x.first<<" "<<x.second<<endl;
	}

 
	for(int i = 1; i <= siz; i++){
        m[a[i]]--;
        if(m[a[i]] == 0) m.erase(a[i]);
    }
    cout<<"///////////\n";
    for(auto x: m)
    {
    	cout<<x.first<<" "<<x.second<<endl;
	}
 
    if(m.size() == n - siz) return 1;
 
    for(int i = siz + 1; i <= n; i++){
    	cout<<"m[a[i - siz]]:  "<<a[i - siz]<<endl;
    	cout<<"m[a[i]]  "<<a[i]<<endl;
        m[a[i - siz]]++;
        m[a[i]]--;
        if(m[a[i]] == 0) m.erase(a[i]);
        	cout<<"///////////\n";
		    for(auto x: m)
		    {
		    	cout<<x.first<<" "<<x.second<<endl;
			}
        if(m.size() == n - siz) return true;
    }
    return false;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    cout<<check(3);
    return 0;
}
