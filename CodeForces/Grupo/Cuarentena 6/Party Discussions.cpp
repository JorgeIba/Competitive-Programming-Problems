#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> sums;


vector<int> Phi;
void phiSieve(int n){
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

lli binaryS(lli k)
{
    lli l = 0, r = 1813809, res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( sums[mid] >= k  )
        {
            res = mid;
            r = mid-1;
        }
        else
        {
            l = mid +1;
        }
    }
    return res;
}

int main()
{
    lli k; cin>>k;
    phiSieve(1813810);
    sums.resize(1813910);
    sums[0] = 0;
    for(int i = 1; i < 1813810; i++)
    {
        sums[i] = sums[i-1] + Phi[i] - 1;
    }
    lli index = binaryS(k);
    lli sumParcial = sums[index-1];
    for(lli i = 2; i < index; i++)
    {
        if( __gcd(index, i) == 1  )
        {      
            sumParcial += 1;
        }
        if(sumParcial == k)
        {
            cout<<i<<" "<<index<<endl;
            return 0;
        }
        //cout<<sumParcial<<endl;
    }
    return 0;
}