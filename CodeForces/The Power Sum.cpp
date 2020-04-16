#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli target, powers;

lli funcion(lli actual, lli suma)
{
    if (actual > pow(target, (double)1/powers))
    {
        return 0;
    }    
    if (suma>target)
    {
    	return 0;
	}
    if (suma + pow(actual,powers) == target)
    {
        return 1;
    }
    
    lli si = funcion(actual+1, suma + pow(actual,powers));
    lli no = funcion(actual+1, suma);
    
    return si + no;
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>target>>powers;
    cout<<funcion(1,0)<<endl;
    return 0;
}
