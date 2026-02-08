/**
 * @file acm_io.cpp
 * @brief Fast I/O template for ACM/ICPC and Online Judge problems
 * 
 * Optimized for competitive programming with fast input/output.
 * Use this template for problems with large I/O datasets.
 * 
 * Compile: g++ -std=c++17 -O2 acm_io.cpp -o solution
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

/* ============================================================================
 * FAST I/O SETUP
 * ============================================================================ */

/**
 * @brief Optimize C++ I/O streams for competitive programming
 * 
 * Call this at the beginning of main() for faster cin/cout
 */
inline void fast_io() {
    ios_base::sync_with_stdio(false);  // Disable C/C++ stream synchronization
    cin.tie(NULL);                      // Untie cin from cout
    cout.tie(NULL);                     // Untie cout (optional)
}

/* ============================================================================
 * FAST INPUT FUNCTIONS
 * ============================================================================ */

/**
 * @brief Fast integer input using getchar_unlocked (Linux/Unix)
 * Much faster than cin for reading integers
 */
#ifdef __linux__
inline int fast_read_int() {
    int n = 0;
    int ch = getchar_unlocked();
    int sign = 1;
    
    // Skip whitespace
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar_unlocked();
    }
    
    // Read digits
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + ch - '0';  // n = n * 10 + digit
        ch = getchar_unlocked();
    }
    
    return n * sign;
}
#else
// Fallback for non-Linux systems
inline int fast_read_int() {
    int n;
    scanf("%d", &n);
    return n;
}
#endif

/**
 * @brief Fast long long input
 */
inline long long fast_read_ll() {
    long long n = 0;
    int ch = getchar();
    int sign = 1;
    
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar();
    }
    
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + ch - '0';
        ch = getchar();
    }
    
    return n * sign;
}

/* ============================================================================
 * FAST OUTPUT FUNCTIONS
 * ============================================================================ */

/**
 * @brief Fast integer output
 */
inline void fast_write_int(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    
    char buffer[12];
    int i = 0;
    
    do {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    } while (n > 0);
    
    while (i > 0) {
        putchar(buffer[--i]);
    }
}

/**
 * @brief Fast output with newline
 */
inline void fast_write_ln(int n) {
    fast_write_int(n);
    putchar('\n');
}

/* ============================================================================
 * COMMON MACROS
 * ============================================================================ */

#define ll long long
#define ull unsigned long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())

// Loop macros
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define RFOR(i, a, b) for(int i = (a); i > (b); i--)
#define REP(i, n) FOR(i, 0, n)
#define RREP(i, n) RFOR(i, n-1, -1)

// Debugging
#ifdef LOCAL
    #define debug(x) cerr << #x << " = " << (x) << endl
    #define debug2(x, y) cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#else
    #define debug(x)
    #define debug2(x, y)
#endif

// Constants
const int INF = 1e9 + 7;
const ll LINF = 1e18 + 7;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

// Directions for grid traversal (4-directional)
const int dx4[] = {-1, 0, 1, 0};
const int dy4[] = {0, 1, 0, -1};

// Directions for grid traversal (8-directional)
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

/* ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================ */

/**
 * @brief GCD (Greatest Common Divisor)
 */
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

/**
 * @brief LCM (Least Common Multiple)
 */
ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

/**
 * @brief Modular exponentiation: (base^exp) % mod
 */
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

/**
 * @brief Check if number is prime (simple trial division)
 */
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

/* ============================================================================
 * SOLUTION TEMPLATE
 * ============================================================================ */

/**
 * @brief Solve a single test case
 * 
 * Implement your solution logic here.
 * Return true if successful, false if error.
 */
bool solve() {
    // Read input
    int n;
    cin >> n;
    
    if (n == 0) return false;  // Example: end condition
    
    vi arr(n);
    REP(i, n) {
        cin >> arr[i];
    }
    
    // ==========================================
    // YOUR ALGORITHM HERE
    // ==========================================
    
    // Example: Find maximum element
    int max_val = *max_element(all(arr));
    
    // ==========================================
    // OUTPUT RESULT
    // ==========================================
    
    cout << max_val << "\n";
    
    return true;
}

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================ */

int main() {
    fast_io();  // Enable fast I/O
    
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    // Single test case
    solve();
    
    /* Multiple test cases (uncomment if needed):
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    */
    
    /* Unknown number of test cases (uncomment if needed):
    while (solve()) {
        // Continue until solve() returns false
    }
    */
    
    return 0;
}

/* ============================================================================
 * TIPS FOR ONLINE JUDGE PROBLEMS:
 * 
 * 1. Read the problem carefully - note input/output format
 * 2. Identify constraints - affects algorithm choice
 * 3. Consider edge cases:
 *    - Empty input (n = 0)
 *    - Single element (n = 1)
 *    - Maximum input size
 *    - Negative numbers, zeros
 * 4. Check for overflow:
 *    - Use 'long long' for large numbers
 *    - Be careful with multiplication
 * 5. Time complexity:
 *    - n ≤ 10^6: O(n) or O(n log n)
 *    - n ≤ 10^3: O(n^2) acceptable
 *    - n ≤ 100: O(n^3) acceptable
 * 6. Remember to flush output if needed:
 *    - cout << flush;
 *    - fflush(stdout);
 * 
 * COMMON PITFALLS:
 * - Forgetting to read all input
 * - Integer overflow
 * - Array index out of bounds
 * - Not handling edge cases
 * - Wrong output format (extra spaces, newlines)
 * 
 * DEBUGGING:
 * - Compile with -DLOCAL to enable debug output
 * - Use debug() macro to print variables
 * - Test with small inputs first
 * - Compare with brute force solution
 * 
 * ============================================================================ */
