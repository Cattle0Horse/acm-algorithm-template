#include<bits/stdc++.h>
#include<Cattle_Horse/LOCAL.h>
//随机数生成

// random number
#define seed std::chrono::system_clock::now().time_since_epoch().count()
std::mt19937 gen(seed);

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