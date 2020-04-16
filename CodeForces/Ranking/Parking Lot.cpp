#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;

int main()
{
    lli n; cin>>n;
    lli l = 1, r = n;
    lli res = 0;
    while(r <= (2*n - 2))
    {
        lli auxIzq = l - 1;
        lli auxDer = 2*n-2 - r;
        lli auxSuma = 1;
        if(auxIzq > 0)
        {
            auxSuma*= 3;
            auxIzq--;
        }
        if(auxDer > 0)
        {
            auxSuma*=3;
            auxDer--;
        }
        ///////////////////////////////
        if(auxIzq > 0)
        {
            auxSuma*= pow(4, auxIzq);
        }
        if(auxDer > 0)
        {
            auxSuma*= pow(4, auxDer);
        }
        l++;
        r++;

        res += auxSuma;
    }

    cout<<(res*4)<<endl;



    return 0;
}