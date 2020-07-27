#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

class BagPacking
{
    public:
        int minPay(vector<int> bagsizes)
        {
            int n = bagsizes.size();
            int arreglo[101][101]; // arreglo[1][j] total, arreglo[0][i] disponibles

            for(int i = 0; i<n; i++)
            {
                arreglo[0][ bagsizes[i] ] ++;
                arreglo[1][ bagsizes[i] ] ++;
            }

            for(int i = 1; i<=100; i++)
            {
                if(arreglo[1][i] == 0) continue;
                for(int j = i+1; j<=100; j++)
                {
                    if(arreglo[0][j] > 0)
                    {
                        lli minimo = min(arreglo[0][j], arreglo[1][i]);
                        arreglo[0][j] -= minimo;
                        arreglo[1][i] -= minimo;
                    }
                }
            }

            int ans = 0;
            for(int i = 1; i<=100; i++)
            {
                ans += arreglo[1][i];
            }
            return ans;
        }

};




int main()
{
    //fastIO();
    lli n; cin>>n;
    vector< int > nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    BagPacking a;
    cout << a.minPay(nums);
    return 0;
}