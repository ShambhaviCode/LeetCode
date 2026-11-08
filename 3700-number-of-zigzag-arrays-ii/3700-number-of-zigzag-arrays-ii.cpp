class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!A[i][k]) continue;

                long long aik = A[i][k];

                for (int j = 0; j < n; j++) {
                    if (!B[k][j]) continue;

                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }

        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix res(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

    vector<long long> multiplyMatVec(
        const Matrix& A,
        const vector<long long>& v
    ) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;

            for (int j = 0; j < n; j++) {
                if (!A[i][j]) continue;

                cur = (cur + A[i][j] * v[j]) % MOD;
            }

            res[i] = cur;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        int S = 2 * m;

        Matrix T(S, vector<long long>(S, 0));

        // indices:
        // 0..m-1       -> up
        // m..2m-1      -> down

        for (int v = 1; v <= m; v++) {

            // up'[v] = sum_{u < v} down[u]
            for (int u = 1; u < v; u++) {
                T[v - 1][m + (u - 1)] = 1;
            }

            // down'[v] = sum_{u > v} up[u]
            for (int u = v + 1; u <= m; u++) {
                T[m + (v - 1)][u - 1] = 1;
            }
        }

        vector<long long> base(S, 0);

        // length = 2
        for (int v = 1; v <= m; v++) {
            base[v - 1] = v - 1;     // up
            base[m + v - 1] = m - v; // down
        }

        Matrix P = power(T, n - 2);
        vector<long long> state = multiplyMatVec(P, base);

        long long ans = 0;
        for (long long x : state) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};