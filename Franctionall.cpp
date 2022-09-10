#include<bits/stdc++.h>
using namespace std;
//分数类 不好用

//#define Mixed_Number
//#define Always_Reduce
//#define Check_Overflow

#ifdef Check_Overflow
#define Check_Add_Overflow(a, b) assert(((a) + (b) - (b)) == (a))
#define Check_Mul_Overflow(a, b) assert(((a) * (b) / (b)) == (a))
#else
#define Check_Add_Overflow(a, b) 114514
#define Check_Mul_Overflow(a, b) 114514
#endif

template <std::integral T>
inline T gcd(T a, T b) {
    while (b) a %= b, std::swap(a, b);
    return std::abs(a);
}

template <typename T>
concept is_float_v = std::is_floating_point<T>::value;
template <typename T>
concept arithmetic = std::is_arithmetic<T>::value;

class Fraction {
private:
    bool m_minus;
    long long m_numerator;
    long long m_denominator;

public:
    Fraction() : m_minus(false), m_numerator(0), m_denominator(1) {}
    Fraction(long long numerator, long long denominator)
        : m_numerator(std::abs(numerator)), m_denominator(std::abs(denominator)), m_minus((numerator < 0) ^ (denominator < 0)) {
        assert(m_denominator != 0);
        reduce();
    }
    explicit Fraction(std::string x) {
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
                m_minus = (c == '-');
                if (c == '-') continue;
            }
            if (c == '.') {
                flag = true;
                continue;
            }
            number << c;
            if (flag) ++digits;
        }
        m_numerator = std::stoll(number.str());
        m_denominator = 1;
        long long base = 10;
        for (; digits; digits >>= 1, base *= base)
            if (digits & 1) m_denominator *= base;
        reduce();
    }
    Fraction(const Fraction& frac) : m_numerator(frac.m_numerator), m_denominator(frac.m_denominator), m_minus(frac.m_minus) {}
    template <is_float_v T>
    Fraction(T x) : Fraction(std::to_string(x)) {}
    template <std::integral T>
    Fraction(T x) : m_minus(x < 0), m_numerator(std::abs(x)), m_denominator(1) {}
    ~Fraction() {}

    void set(long long numerator, long long denominator) {
        m_minus = (numerator < 0) ^ (denominator < 0);
        m_numerator = std::abs(numerator), m_denominator = std::abs(denominator);
        reduce();
    }
    void set_numerator(long long numerator) {
        m_minus = m_minus ^ (numerator < 0);
        m_numerator = std::abs(numerator);
        reduce();
    }
    void set_Denominator(long long denominator) {
        assert(denominator != 0);
        m_minus = m_minus ^ (denominator < 0);
        m_denominator = std::abs(denominator);
        reduce();
    }
    void set_sign(bool flag) { m_minus = m_minus ^ (flag == 0); }

    Fraction operator-() const { return Fraction((m_minus ? 1 : -1) * m_numerator, m_denominator); }
    Fraction operator~() const { return Fraction((m_minus ? -1 : 1) * m_denominator, m_numerator); }
    Fraction operator+(const Fraction& frac) const {
        long long mu = m_denominator * frac.m_denominator;
        long long t1 = (m_minus ? -1 : 1) * m_numerator * frac.m_denominator, t2 = (frac.m_minus ? -1 : 1) * frac.m_numerator * m_denominator;
        Check_Add_Overflow(t1, t2);
        Check_Mul_Overflow(m_numerator, frac.m_denominator);
        Check_Mul_Overflow(m_denominator, frac.m_numerator);
        Check_Mul_Overflow(m_denominator, frac.m_denominator);
        long long t = t1 + t2;
#ifdef Always_Reduce
        long long g = gcd(t, mu);
        return Fraction(t / g, mu / g);
#endif
        return Fraction(t, mu);
    }
    Fraction operator-(const Fraction& frac) { return (*this) + (-frac); }
    Fraction operator*(const Fraction& frac) {
        long long z = m_numerator * frac.m_numerator, m = m_denominator * frac.m_denominator;
        Check_Mul_Overflow(m_numerator, frac.m_numerator);
        Check_Mul_Overflow(m_denominator, frac.m_denominator);
#ifdef Always_Reduce
        long long g = gcd(z, m);
        return Fraction((m_minus ^ frac.m_minus ? -1ll : 1ll) * z / g, m / g);
#endif
        return Fraction((m_minus ^ frac.m_minus ? -1ll : 1ll) * z, m);
    }
    Fraction operator/(const Fraction& frac) { return (*this) * (~frac); }
    Fraction& operator*=(const Fraction& frac) { return (*this) = (*this) * frac; }
    Fraction& operator/=(const Fraction& frac) { return (*this) = (*this) / frac; }
    Fraction& operator+=(const Fraction& frac) { return (*this) = (*this) + frac; }
    Fraction& operator-=(const Fraction& frac) { return (*this) = (*this) - frac; }

    template <arithmetic T>
    friend Fraction& operator+(T x, const Fraction& frac) { return frac + x; }
    template <arithmetic T>
    friend Fraction& operator-(T x, const Fraction& frac) { return -(frac - x); }
    template <arithmetic T>
    friend Fraction& operator*(T x, const Fraction& frac) { return frac * x; }
    template <arithmetic T>
    friend Fraction& operator/(T x, const Fraction& frac) { return ~(frac / x); }

    friend long long compare(const Fraction& a, const Fraction& b) {
        long long t1 = a.SignPart() * a.m_numerator * b.m_denominator;
        long long t2 = b.SignPart() * b.m_numerator * a.m_denominator;
        Check_Add_Overflow(t1, t2);
        Check_Mul_Overflow(a.m_numerator, b.m_denominator);
        Check_Mul_Overflow(b.m_numerator, a.m_denominator);
        return t1 - t2;
    }
    friend bool operator==(const Fraction& left, const Fraction& right) { return compare(left, right) == 0; }
    friend bool operator!=(const Fraction& left, const Fraction& right) { return compare(left, right) != 0; }
    friend bool operator>(const Fraction& left, const Fraction& right) { return compare(left, right) > 0; }
    friend bool operator<(const Fraction& left, const Fraction& right) { return compare(left, right) < 0; }
    friend bool operator>=(const Fraction& left, const Fraction& right) { return compare(left, right) >= 0; }
    friend bool operator<=(const Fraction& left, const Fraction& right) { return compare(left, right) <= 0; }

    [[nodiscard]] long long NumeratorPart() const { return m_numerator; }
    [[nodiscard]] long long DenominatorPart() const { return m_denominator; }
    [[nodiscard]] int SignPart() const { return m_minus ? -1 : 1; }
    [[nodiscard]] long long IntegerPart() const { return m_numerator / m_denominator; }
    [[nodiscard]] std::pair<long long, long long> FractionPart() const { return {m_numerator % m_denominator, m_denominator}; }

    [[nodiscard]] float toFloat() const { return static_cast<float>(toLDouble()); }
    [[nodiscard]] double toDouble() const { return static_cast<double>(toLDouble()); }
    [[nodiscard]] long double toLDouble() const { return static_cast<long double>(SignPart()) * m_numerator / m_denominator; }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
#ifdef Mixed_Number
        const long long &a = frac.m_numerator, &b = frac.m_denominator;
        if (frac.m_minus) os << '-';
        if (a % b) {
            if (a > b) os << a / b << ' ';
            os << a % b << '/' << b;
        } else
            os << a / b;
        return os;
#endif
        if (frac.m_minus) os << '-';
        os << frac.m_numerator << "/" << frac.m_denominator;
        return os;
    }
    inline void reduce() {
#ifdef Always_Reduce
        auto tmp = gcd(m_numerator, m_denominator);
        m_numerator /= tmp, m_denominator /= tmp;
#endif
    }
};
Fraction pow(Fraction f, long long b) {
    Fraction ret(1ll);
    for (; b; b >>= 1, f = f * f)
        if (b & 1) ret = f * ret;
    return ret;
}