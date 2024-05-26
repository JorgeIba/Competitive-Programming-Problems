    while(q--){
        int t, x, k; cin>>t>>x>>k; x--;
        int pos; 
        auto parent = root(nodes[x], pos);

        int sz = cnt(parent);
        int to_print = (pos + k) % sz;
        // cout <<
        // cout << to_print << " ---> " << endl;
        output(parent);
        cout << endl;
    }


