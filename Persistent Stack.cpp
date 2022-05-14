#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


struct Node{
    Node *below;
    int value;

    Node() {}
    Node(int value): value(value) {}

    Node* push(int value) {
        Node* top = new Node(value);
        top->below = this;
        return top;
    }

    Node* pop() {
        return below;
    }

    int top() {
        return value;
    }
}; 



int main () {
	fastIO();
    int n; cin>>n;

    vector<Node*> stacks(1);
    stacks[0] = new Node();

    for(int i = 0; i < n; i++){
        int t, m; cin>>t>>m;
        
        Node *top = stacks[t];
        if(m == 0) {
            int value = top->top();
            top = top->pop();
            cout << value << endl;
        } else {
            top = top->push(m);
        }

        stacks.push_back(top);
    }


	return 0;
}

