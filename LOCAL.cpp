// Expand the stack
#pragma comment(linker, "/STACK:1024000000,1024000000")

#include <bits/stdc++.h>
using namespace std;
// color
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

string to_string(const char c) { return char(39) + string(1, c) + char(39); }
string to_string(string s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
//#define debug(...) cerr << BOLDBLACK << "[" << #__VA_ARGS__ << "]:" << BOLDGREEN, debug_out(__VA_ARGS__), cerr << RESET;
//#define debug_info(...) cerr << BOLDBLACK << "File: " << RED << __FILE__ << RESET << ",  " << BOLDBLACK << "Function: " << BOLDCYAN << __FUNCTION__ << RESET << ",  " << BOLDBLACK << "Line: " << BOLDMAGENTA << __LINE__ << RESET << ",  ", debug(__VA_ARGS__)
#define debug(...) cerr << BOLDRED << __FUNCTION__ << ": " << __LINE__ << "  [" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__), cerr << RESET;

// random number
#define seed chrono::system_clock::now().time_since_epoch().count()
mt19937 gen(seed);

// get random integer from L to R ;
template <integral T>
T int_rand(T L, T R) { return std::uniform_int_distribution<T>(L, R)(gen); }

template <typename T>
concept arithmetic = std::is_arithmetic<T>::value;
// get random real from L to R ;
template <arithmetic T>
double real_rand(T L, T R) { return std::uniform_real_distribution<double>(L, R)(gen); }

template <integral T>
void int_rand(vector<T> &a, T L, T R) {
    for (T &e : a) e = int_rand(L, R);
}

template <arithmetic T>
void real_rand(vector<T> &a, T L, T R) {
    for (T &e : a) e = real_rand(L, R);
}

#ifdef Check_Overflow
#define Check_Add_Overflow(a, b) assert((a + b - b) == a)
#define Check_Mul_Overflow(a, b) assert((a * b / b) == a)
#endif