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


void solve(int arr[], int n) 
{ 
    // Since we traverse array from end, extected item 
    // is initially  n 
    int expectedItem = n; 
  
    // Taverse array from end 
    for (int i=n-1; i >= 0; i--) 
    { 
        // If current item is at its correct position, 
        // decrement the expectedItem (which also means 
        // decrement in minimum number of moves) 
        if (arr[i] == expectedItem) 
            expectedItem--; 
    } 
  
    return expectedItem; 
} 

int main () {
	//fastIO();
    int n; cin>>n;
    vector<lli>
	


    
	return 0;
}