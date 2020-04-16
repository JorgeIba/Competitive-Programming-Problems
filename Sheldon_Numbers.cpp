#include <bits/stdc++.h>
#define lli long long unsigned int
#define ulli long long unsigned int

using namespace std;

set<ulli> num;
vector<ulli> nums;

void precal(){
        int N = 1;
        int M = 1;
        int pos = 0;
        while(M <= 64){
                N = 0;
                while(M + N <= 64){
                        ulli nume = 0;
                        ulli num2 = 0;
                        int pos2 = M;
                        while(pos <= 64){
                                ulli valor = ((1ull << (N+1))-1);
                                nume |= (valor<<pos);
                                num2 |= (valor<<pos2);
                                num.insert(nume);
                                num.insert(num2);
                                pos += N+1;
                                pos += M;
                                pos2 += (N+M+1);
                        }
                        N++;
                        pos = 0;
                }
                M++;
        }

    for(auto x: num)
    {
        nums.push_back(x);
    }

}


lli binaria(lli index)
{
    lli l = 0, r = nums.size(), res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(  nums[mid] == index  )
        {
            return mid;
        }
        else if(nums[mid] < index)
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid-1;
        }
    }
    return res;
}

int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    precal();
    lli l, r;
    //cout<<num.size();
    while(cin>>l>>r)
    {
        lli le = binaria(l-1);
        lli re = binaria(r);
        cout<<(re-le)<<endl;
    }
    

    return 0;
}