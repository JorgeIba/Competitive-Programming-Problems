#include <bits/stdc++.h>

using namespace std;


vector<int> NextGreatAndNextSmaller(vector<int> numbers)
{
    int vectorSize = numbers.size();
    vector<int> indexGreater(vectorSize), indexLower(vectorSize), ans;
    stack<int> stackGreater, stackLower;
    for(int i=vectorSize-1; i>=0; i--)
    {
        while(!stackGreater.empty() and (numbers[ stackGreater.top() ] <= numbers[i]) )
        {
            stackGreater.pop();
        }

        if(stackGreater.empty())
        {
            indexGreater[i] = -1;
        }
        else
        {
            indexGreater[i] = stackGreater.top();
        }
        stackGreater.push(i);
    }

    for(int i=vectorSize-1; i>=0 ; i--)
    {
        while(!stackLower.empty() and (numbers[ stackLower.top() ] >= numbers[i]) )
        {
            stackLower.pop();
        }

        if(stackLower.empty())
        {
            indexLower[i] = -1;
        }
        else
        {
            indexLower[i] = stackLower.top();
        }
        stackLower.push(i);
    }

    for(int i=0; i<vectorSize; i++)
    {
        if(  (indexGreater[i] != -1)  and  (indexLower[indexGreater[i]] != -1) )
        {
            int number = numbers[ indexLower[indexGreater[i]] ];
            ans.push_back(  number );
        }
        else
        {
            ans.push_back( -1 );
        }
    }
    return ans;
}



int main()
{
    int n; cin>>n;
    vector<int> numeros(n);
    for(auto &num: numeros)
    {
        cin>>num;
    }
    vector<int> ans = NextGreatAndNextSmaller(numeros);
    for(auto x: ans)
    {
        cout<<x<<" ";
    }

    return 0;
}