struct Grid2Graph {
public:
    int h, w;
    vector<vector<int> > comp, grid;

    struct Node {
        int num;
        vector<pair<int, int> > cells;
        vector<int> to;
    };

    vector<Node> g;

    Grid2Graph() = default;

    Grid2Graph(const vector<vector<int> > &grid) : grid(grid), h(grid.size()), w(grid[0].size()), comp(h, vector(w, -1)) {
        int n = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (comp[i][j] == -1) {
                    dfs(i, j, n++);
                }
            }
        }
        g.resize(n);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                g[comp[r][c]].cells.emplace_back(r, c);
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (inside(nr, nc) && comp[r][c] != comp[nr][nc]) {
                        g[comp[r][c]].to.emplace_back(comp[nr][nc]);
                        g[comp[nr][nc]].to.emplace_back(comp[r][c]);
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            g[i].num = i;
            sort(g[i].to.begin(), g[i].to.end());
            g[i].to.erase(unique(g[i].to.begin(), g[i].to.end()), g[i].to.end());
        }
    }

private:
    const int dr[4] = {0, 1, 0, -1};
    const int dc[4] = {-1, 0, 1, 0};

    bool inside(int r, int c) {
        return 0 <= r && r < h && 0 <= c && c < w;
    }

    void dfs(int r, int c, int num) {
        comp[r][c] = num;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (inside(nr, nc) && grid[r][c] == grid[nr][nc] && comp[nr][nc] == -1) {
                dfs(nr, nc, num);
            }
        }
    }
};