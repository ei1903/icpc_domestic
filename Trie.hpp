template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> nxt;    // 子の頂点番号を格納、存在しなければ -1
        vector<int> accept; // 末端がこの頂点になる文字列の word_id を保存
        int c;              // base からの間隔
        int common;         // いくつの文字列がこの頂点を共有しているか
        Node(int c_) : c(c_), common(0) {
            nxt.assign(char_size, -1);
        }
    };

    vector<Node> nodes;
    int root;

    Trie() : root(0) {
        nodes.emplace_back(root);
    }

    // 文字列の挿入
    void insert(const string &ward, int ward_id) {
        int node_id = 0;
        for (const auto e: ward) {
            const int c = int(e - base);
            int &nxt_id = nodes[node_id].nxt[c];
            if (nxt_id == -1) {
                nxt_id = (int) nodes.size();
                nodes.emplace_back(c);
            }
            nodes[node_id].common++;
            node_id = nxt_id;
        }
        nodes[node_id].common++;
        nodes[node_id].accept.emplace_back(ward_id);
    }

    void insert(const string &ward) {
        insert(ward, nodes[0].common);
    }

    // 指定した文字列の総数
    int countString(const string &word) {
        int node_id = 0;
        for (const auto e: word) {
            const int c = int(e - base);
            const int nxt_id = nodes[node_id].nxt[c];
            if (nxt_id == -1) {
                return 0;
            }
            node_id = nxt_id;
        }
        return nodes[node_id].accept.size();
    }

    // 指定した接頭辞 (prefix) を持つ文字列の総数
    int countPrefix(const string &prefix) {
        int node_id = 0;
        for (const auto e: prefix) {
            const int c = int(e - base);
            const int nxt_id = nodes[node_id].nxt[c];
            if (nxt_id == -1) {
                return 0;
            }
            node_id = nxt_id;
        }
        return nodes[node_id].common;
    }

    // 文字列 word[word_id...|word|] の接頭辞 (prefix) に一致する文字列を検索し、一致した文字列ごとに関数 fn が呼び出される
    template <class Fn>
    void query(const string &word, const Fn &fn, int word_id, int node_id) {
        for (const auto i: nodes[node_id].accept) fn(i);
        if (word_id >= word.size()) {
            return;
        } else {
            const int c = int(word[word_id] - base);
            if (nodes[node_id].nxt[c] == -1) return;
            query(word, fn, word_id + 1, nodes[node_id].nxt[c]);
        }
    }

    // 挿入した文字列の総数
    int count() const {
        return nodes[0].common;
    }

    // 頂点の総数
    int size() const {
        return (int) nodes.size();
    }
};