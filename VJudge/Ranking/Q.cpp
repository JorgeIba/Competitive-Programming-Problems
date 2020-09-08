#include<bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n,k; cin>>n>>k;
    vector<lli> numeros(n);

    for(auto &x: numeros)
    {
        cin>>x;
    }
    sort(numeros.begin(), numeros.end());

    lli l = 0, r = 0; 
    lli size = 0, auxSuma = 0, res = -1, numerores = -1;
    bool flag = true;
    while(r < n)
    {
        if(flag)
        {
            size = r-l +1;
            auxSuma += ( numeros[r] - numeros[r-1] )*(size-1);
        }
        
//        cout<<l<<" ------- "<<r<<" "<<auxSuma<<" "<<size<<endl;

        if(auxSuma <= k)
        {
            if( size  >= res )
            {
                if((size==res)and(numeros[r] <= numerores))
                {
                    res = size;
                    numerores = numeros[r];
                }
                if (size > res)
                {
                    res = size;
                    numerores = numeros[r];
                }
            }
            r++;
            flag = true;
            
        }
        else
        {
            lli diff = numeros[r] - numeros[l];
            //cout<<numeros[r]<<" asdasd "<<numeros[l]<<endl;
            auxSuma -= diff;
            size--;
            l++;
            flag = false;
        }
    }

    cout<<res<<" "<<numerores<<endl;


    return 0;
}