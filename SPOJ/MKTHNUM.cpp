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
    int l, r, sum;
    Node *left, *right;

    Node(int l, int r): l(l), r(r) {
        if(l != r) {
            int mid = l + (r-l)/2;
            left = new Node(l, mid);
            right = new Node(mid+1, r);
        }
    }
    
    // Create leaf
    Node(int l, int r, int val): l(l), r(r), sum(val) {}

    // Create intermediate leaf
    Node(int l, int r, Node* left, Node* right): l(l), r(r), left(left), right(right) {
        sum = left->sum + right->sum;
    }
};


Node* build_ST(int l, int r) {
    if(l == r) { return new Node(l, r, 0); }
    else {
        int mid = l + (r-l)/2;
        Node* left = build_ST(l, mid);
        Node* right = build_ST(mid+1, r);
        return new Node(l, r,  left, right);
    }
}


lli query_sum(int l, int r, Node* curr) {
    if( curr->l > r || curr->r < l) return 0;
    else if( l <= curr->l && curr->r <= r ) return curr->sum;
    return query_sum(l, r, curr->left) + query_sum(l, r, curr->right);
}


Node* update_val(int pos, int l, int r, Node* curr, int val) {   
    if( l == r ) return new Node(l, r, val);
    int mid = l + (r-l)/2;
    if(pos <= mid){
        return new Node(l, r, update_val(pos, l, mid, curr->left, val), curr->right);        
    }
    return new Node(l, r, curr->left, update_val(pos, mid+1, r, curr->right, val));
}


int kthSmallest(Node* curr, Node* v2, int k) {
    int l = curr->l, r = curr->r;
    // auto [l, r] = tuple<int,int>{ curr->l, curr->r };
    if(l == r){
        // cout << k << endl;
        assert(k == 1);
        return l;
    }

    int left_sum = curr->left->sum - v2->left->sum;


    if(k > left_sum) {
        return kthSmallest(curr->right, v2->right, k - left_sum);
    } else { 
        return kthSmallest(curr->left, v2->left, k);
    }

}



int main () {
	// fastIO();
    int n, m; cin>>n>>m;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    map<int, int> nums_to_map;
    map<int, int> map_to_nums;
    int id = 1;

    auto sorted_nums = nums; sort(all(sorted_nums));
    for(auto x: sorted_nums) {
        if(!nums_to_map.count(x)) {
            nums_to_map[x] = id;
            map_to_nums[id++] = x;
        }
    }

    vector<int> nums_mapped(n);
    for(int i = 0; i < n; i++) {
        nums_mapped[i] = nums_to_map[nums[i]];
    }


    vector<Node*> roots = { build_ST(1, n) };

    for(int i = 0; i < n; i++) {
        roots.push_back( update_val( nums_mapped[i], 1, n, roots.back(), 1) );
    }




    while(m--){
        int l, r, k; cin>>l>>r>>k;


        // int sum = l-1? query_sum(roots[l-1]->l, roots[l-1]->r, roots[l-1]) : 0;

        // auto idx = kthSmallest(roots[r], roots[l-1], k);
        // cout << idx << endl;

        cout << map_to_nums[ kthSmallest(roots[r], roots[l-1], k) ] << endl;
    }

	return 0;
}

