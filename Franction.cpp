#include <algorithm>
#include <cassert>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
//分数类 较好用

struct Fraction {
    bool f;
    long long a, b;
    static long long GCD(const long long& A, const long long& B) {  // assert(A>=0&&B>=0);
        long long a = A, b = B;
        while (b) a %= b, std::swap(a, b);
        return a;
    }
    static void simple(Fraction& x) {
        long long g = GCD(x.a, x.b);
        if (g != 1) x.a /= g, x.b /= g;
    }
    static long long fu(const bool& f) { return static_cast<long long>(f ? -1 : 1); }
    Fraction() : f(false), a(0), b(1) {}
    template <typename T, std::enable_if<std::is_integral<T>::value, int>::type = 0>
    Fraction(const T& a) : f(a < 0), a(std::abs(a)), b(1) {}
    template <typename T, std::enable_if<std::is_integral<T>::value, int>::type = 0>
    Fraction(const T& num, const T& den) : f((num < 0) ^ (den < 0)), a(std::abs(num)), b(std::abs(den)) { assert(b != 0), simple(*this); }
    explicit Fraction(const std::string& x) {
        try {
            std::stold(x);
        } catch (std::exception e) {
            std::stringstream msg;
            msg << "The argument \"std::string x\"(" << x << ") is invalid";
            throw std::runtime_error(msg.str());
        }
        std::stringstream number;
        int digits = 0;
        bool flag = false;
        int len = x.size();
        for (int i = 0; i < len; ++i) {
            const auto& c = x[i];
            if (i == 0) {
                f = (c == '-');
                if (c == '-') continue;
            }
            if (c == '.') {
                flag = true;
                continue;
            }
            number << c;
            if (flag) ++digits;
        }
        long long base = 10;
        for (a = std::stoll(number.str()), b = 1; digits; digits >>= 1, base *= base)
            if (digits & 1) b *= base;
        simple(*this);
    }
    template <typename T, std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    Fraction(const T& x) : Fraction(std::to_string(x)) {}
    const Fraction abs() const { return Fraction(a, b); }
    Fraction operator-() const { return Fraction((f ? 1 : -1) * a, b); }
    Fraction operator~() const { return Fraction((f ? -1 : 1) * b, a); }
    Fraction& operator+=(Fraction const& o) {
        a *= fu(f);
        if (b == o.b) return a += o.a * fu(o.f), *this;
        long long lcm = b / GCD(b, o.b) * o.b;
        (a *= lcm / b) += lcm / o.b * o.a, b = lcm;
        simple(*this);
        return *this;
    }
    Fraction& operator-=(Fraction const& o) { return *this += -o; }
    Fraction& operator*=(Fraction const& o) {
        f ^= o.f, a *= o.a, b *= o.b;
        simple(*this);
        return *this;
    }
    Fraction& operator/=(Fraction const& o) { return (*this) *= ~o; }
    Fraction operator+(Fraction const& o) const { return Fraction(*this) += o; }
    Fraction operator-(Fraction const& o) const { return Fraction(*this) -= o; }
    Fraction operator*(Fraction const& o) const { return Fraction(*this) *= o; }
    Fraction operator/(Fraction const& o) const { return Fraction(*this) /= o; }

    bool operator<(Fraction const& o) const {
        if (f != o.f) return f;
        if (f) return b * o.a < a * o.b;
        return a * o.b < b * o.a;
    }
    bool operator==(Fraction const& o) const { return f == o.f ? a * o.b == o.a * b : false; }
    bool operator<=(Fraction const& o) const { return (*this) < o || (*this) == o; }
    bool operator>(Fraction const& o) const { return !((*this) <= o); }
    bool operator>=(Fraction const& o) const { return !((*this) < o); }
    bool operator!=(Fraction const& o) const { return !((*this) == o); }

    double Double() const { return static_cast<double>(a) / b; }
    void print() const {
        if (f) putchar('-');
        long long x = a / b, y = a - x * b;
        if (x) printf("%lld", x);
        if (y) {
            if (x) putchar(' ');
            printf("%lld/%lld", y, b);
        }
    }
    void print(const char& ch) const { print(), putchar(ch); }
    template <typename T, std::enable_if<std::is_integral<T>::value, int>::type = 0>
    Fraction& be_pow(const T& p) {
        Fraction a(*this);
        (*this) = 1;
        for (T b = p; b; b >>= 1, a *= a)
            if (b & 1) (*this) *= a;
        return *this;
    }
    template <typename T, std::enable_if<std::is_integral<T>::value, int>::type = 0>
    const Fraction qpow(const T& p) { return Fraction(*this).be_pow(p); }
};