#include <concepts>
#include <iostream>
#include <string>
#include <vector>
// C++20 FastIo

template <typename T> concept is_int = requires(T x) { x & 1; };
namespace IO {  // c++20
template <is_int T> inline bool read(T &ret) { char c; int sgn; if (c = getchar(), c == EOF) return false; while (c != '-' && (c < '0' || c > '9')) c = getchar(); c ^ '-' ? sgn = 1, ret = c - '0' : sgn = -1, c = 0; while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0'); return ret *= sgn, true; }
bool read(float &s) { return ~scanf("%f", &s); }
bool read(double &s) { return ~scanf("%lf", &s); }
bool read(char &c) { return ~(c = getchar()); }
bool read(char *s) { return ~scanf("%s", s); }
bool read(std::string &s) { return static_cast<bool>(std::cin >> s); }
template <is_int T> bool read(T *s, const size_t &n) { for (size_t i = 0; i < n; ++i) if (!read(s[i])) return false; return true; }
template <is_int T> bool read(std::vector<T> &s, const size_t &n) { for (size_t i = 0; i < n; ++i) if (!read(s[i])) return false; return true; }
template <is_int T> bool read(std::vector<T> &s) { for (T &e : s) if (!read(e)) return false; return true; }
template <typename A, typename... Args> bool read(A &a, Args &...arg) { return read(a), read(arg...); }
template <is_int T> inline void print(T x) { static T sta[41]; int top = 0; if (x < 0) putchar('-'), x = -x; do sta[top++] = x % 10, x /= 10; while (x); while (top) putchar(sta[--top] + 48); }
void print(const float &s) { printf("%f", s); }
void print(const double &s) { printf("%lf", s); }
void print(const char &c) { putchar(c); }
void print(const char *s) { printf("%s", s); }
void print(const std::string &s) { for (const char &c : s) putchar(c); }
template <is_int T> void print(const T *s, const size_t &n) { print(s[0]); for (size_t i = 1; i < n; ++i) putchar(' '), print(s[i]); }
template <is_int T> void print(const std::vector<T> &s, const size_t &n) { print(s[0]); for (size_t i = 1; i < n; ++i) putchar(' '), print(s[i]); }
template <is_int T> void print(const std::vector<T> &s) { print(s, s.size()); }
void print_() { return; }
template <typename T, typename... Args> void print_(const T &a, const Args &...args) { print(a), putchar(' '), print_(args...); }
template <typename T, typename... Args> void println(const T &a, const Args &...args) { print_(a, args...), putchar('\n'); }
long long read() { long long a; return read(a), a; }
}  // namespace IO