#include <bits/stdc++.h>
#define lli long long int

using namespace std;


bitset<10> desc(lli n)
{
    bitset<10> ans;
    while(n)
    {
        lli res = n%10;
        n/=10;
        ans |= (1<<(res));
    }
    return ans;
}

int strip(lli a, lli digit)
{
    lli ans = 0, aux = 1;
    while(a)
    {
        lli res = a%10;
        a/=10;
        if(res == digit)
        {
            continue;
        } 
        ans += aux*res;
        aux*=10;
    }
    return ans;
}

bool check(lli a, lli b)
{
    bitset<10> digitsA = desc(a);
    bitset<10> digitsB = desc(b);
    bitset<10> intersect = digitsA & digitsB;
    if(digitsA.count() == 1 or digitsB.count() == 1 or intersect.count() != 1 or (intersect[0]==1))
    {
        return false;
    }
    lli digitIntersect;
    for(int i=0; i<10; i++)
    {
        if(intersect.to_ulong() & (1<<i))
        {
            digitIntersect = i;
            break;
        }
    }
    int wtA = strip(a, digitIntersect);
    int wtB = strip(b, digitIntersect);
    if(  wtB*a == wtA*b   )
    {
        cout<<a<<" "<<b<<" "<<wtA<<" "<<wtB<<endl;
        return true;
    }
    return false;

}



int main()
{
    lli contador = 0;
    vector< pair<int, int> > fractions;
    for(int i = 10; i<100; i++)
    {
        for(int j = i+1; j<100; j++)
        {
            if(check(i,j))
            {
                fractions.emplace_back(i,j);
            }
        }
    }
    lli num = 1, den = 1;
    for(auto x: fractions)
    {
        num *= x.first;
        den *= x.second;
    }

    lli gcd = __gcd(num, den);
    cout<<(int) den/gcd<<endl;
    

    return 0;
}