template <int CHAR_SIZE, int BASE, int MAX_LOG>
struct Trie {
    struct Node {
        vector<Node *> nxt, prev;
        vector<int> accept;
        int c, d, num;
        Node(int c_, int num_, int d_) : c(c_), num(num_), d(d_) {
            nxt.assign(CHAR_SIZE, nullptr);
            prev.assign(MAX_LOG + 1, nullptr);
        }
    };

    vector<Node *> str_ptr;
    Node *root;
    int sz;

    Trie() : root(new Node(0, 0, 0)), sz(1) {}

    void insert(const string &word, Node *pre) {
        Node *ptr = pre;
        for (const auto e : word) {
            const int c = int(e - BASE);
            auto &nxt = ptr->nxt[c];
            if (nxt == nullptr) {
                Node *n = new Node(c, sz++, ptr->d + 1);
                n->prev[0] = ptr;
                for (int i = 1; i < MAX_LOG; ++i) {
                    if (n->prev[i - 1] == nullptr) break;
                    n->prev[i] = n->prev[i - 1]->prev[i - 1];
                }
                nxt = n;
            }
            ptr = nxt;
        }
        ptr->accept.emplace_back(str_ptr.size());
        str_ptr.emplace_back(ptr);
    }

    void insert(const string &word) {
        insert(word, root);
    }

    Node *lcp(Node *u, Node *v) {
        if (u->d < v->d) swap(u, v);
        for (int i = MAX_LOG - 1; i >= 0; --i) {
            if (u->d - v->d >> i & 1) {
                u = u->prev[i];
            }
        }
        if (u == v) return u;
        for (int i = MAX_LOG - 1; i >= 0; --i) {
            if (u->prev[i] != v->prev[i]) {
                u = u->prev[i];
                v = v->prev[i];
            }
        }
        return u->prev[0];
    }

    Node *getPtr(const int str_id) {
        if (0 <= str_id && str_id < str_ptr.size()) return str_ptr[str_id];
        return nullptr;
    }

    Node *find(const string &word, Node *pre) {
        Node *ptr = pre;
        for (const auto e : word) {
            const int c = int(e - BASE);
            Node *nxt = ptr->nxt[c];
            if (nxt == nullptr) return nullptr;
            ptr = nxt;
        }
        return ptr;
    }

    Node *find(const string &word) {
        return find(word, root);
    }

    bool contain(const string &word, Node *pre) {
        Node *ptr = find(word, pre);
        return ptr != nullptr && !ptr->accept.empty();
    }

    bool contain(const string &word) {
        return contain(word, root);
    }

    Node *climb(Node *ptr, int k) {
        for (int i = MAX_LOG - 1; i >= 0 && ptr != nullptr; --i) {
            if (k >> i & 1) {
                ptr = ptr->prev[i];
            }
        }
        return ptr;
    }

    void calcMinmax() {
        calcMin(root);
        calcMax(root);
    }

    Node *calcMin(Node *cur) {
        if (cur == nullptr) return nullptr;
        if (!cur->accept.empty()) cur->minimum = cur;
        for (auto to : cur->nxt) {
            if (cur->minimum == nullptr) {
                cur->minimum = calcMin(to);
            } else {
                calcMin(to);
            }
        }
        return cur->minimum;
    }

    Node *calcMax(Node *cur) {
        if (cur == nullptr) return nullptr;
        for (auto itr = cur->nxt.rbegin(); itr != cur->nxt.rend(); ++itr) {
            if (cur->maximum == nullptr) {
                cur->maximum = calcMax(*itr);
            } else {
                calcMax(*itr);
            }
        }
        if (cur->maximum == nullptr && !cur->accept.empty()) cur->maximum = cur;
        return cur->maximum;
    }

    Node *min(Node *ptr) {
        return ptr->minimum;
    }

    Node *min() {
        return min(root);
    }

    Node *max(Node *ptr) {
        return ptr->maximum;
    }

    Node *max() {
        return max(root);
    }

    string str(Node *ptr) {
        string ret;
        while (ptr != root) {
            ret.push_back(ptr->c + BASE);
            ptr = ptr->prev[0];
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    int count() {
        return str_ptr.size();
    }

    int size() const {
        return sz;
    }
};