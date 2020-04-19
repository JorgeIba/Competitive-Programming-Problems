#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
    int limit = sqrt(n);
	for(long long int i = 3; i*i <= n; i += 2)
    {
		if(isPrime[i])
        {
			if(i <= limit)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}



int main()
{
    primesSieve(10000000);
    lli maxi = -1, aF = -10000, bF = -10000;

    for(int a = -999; a<1000; a++)
    {
        for(int b = 0; b<=1000; b++)
        {
            lli counting = 0;
            for(int n = 0; n<=79; n++)
            {
                lli f = n*n + a*n + b;
                if(f<0) break;
                if(isPrime[f])
                    counting++;
                else
                    break;
            }
            if(maxi <= counting)
            {
                maxi = counting;
                aF = a;
                bF = b;
            }
        }
    }
    cout<<aF<<" "<<bF<<" "<<maxi<<endl;
    return 0;
}