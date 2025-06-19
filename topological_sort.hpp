template<class Graph = vector<vector<int> > >
vector<int> topological_sort(const Graph &g){
    const int n = g.size();
    vector<int> deg(n);
    for(int i = 0; i < n; ++i){
        for(auto &to: g[i]) ++deg[to];
    }
    vector<int> st;
    for(int i = 0; i < n; ++i){
        if(deg[i] == 0) st.emplace_back(i);
    }
    vector<int> ord;
    while(!st.empty()){
        auto p = st.back();
        st.pop_back();
        ord.emplace_back(p);
        for(auto &to: g[p]){
            if(--deg[to] == 0) st.emplace_back(to);
        }
    }
    return (ord);
};