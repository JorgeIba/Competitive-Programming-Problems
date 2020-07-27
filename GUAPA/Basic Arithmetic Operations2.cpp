#include <bits/stdc++.h> 
#define lli long long int
using namespace std; 
  
// This function returns repeating sequence of 
// a fraction.  If repeating sequence doesn't 
// exits, then returns empty string 
lli idx = 0;

vector<lli> pos;

string fractionToDecimal(int numr, int denr) 
{ 
    string res; // Initialize result 
  
    map <int, int> mp; 
    mp.clear(); 
  
    // Find first remainder 
    int rem = numr%denr; 
  
    // Keep finding remainder until either remainder 
    // becomes 0 or repeats 
    while ( (rem!=0) && (mp.find(rem) == mp.end()) ) 
    { 
        // Store this remainder 
        mp[rem] = res.length(); 
        // Multiply remainder with 10 
        rem = rem*10; 
  
        // Append rem / denr to result 
        int res_part = rem / denr; 
        res += to_string(res_part); 
  
        // Update remainder 
        rem = rem % denr; 
        idx++;
    } 
  
    
    cout << res << endl;
    cout<< mp[rem] << endl;
    return res;
} 
  
// Driver code 
int main() 
{ 
    int numr = 1, denr = 840; 
    string res = fractionToDecimal(numr, denr); 
    
    cout << "Recurring sequence is " << res << endl; 

    cout<<idx<<endl;
    return 0; 
} 