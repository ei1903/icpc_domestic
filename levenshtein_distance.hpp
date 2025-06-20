template <class Container>
auto levenshtein_distance(const Container& as, const Container& bs) {
    const size_t N = as.size();
    const size_t M = bs.size();
    vector<vector<size_t>> dp(N + 1, vector<size_t>(M + 1));

    for (size_t i = 1; i <= N; ++i) dp[i][0] = i;
    for (size_t j = 1; j <= M; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= M; ++j) {
            if (as[i - 1] == bs[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
            }
        }
    }

    return (dp);
}