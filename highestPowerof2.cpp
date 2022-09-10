//求小于等于x的最大2次幂

//return the number is less than or equal to x and power of 2
unsigned long long highestPowerof2(unsigned long long x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    x |= x >> 64;
    return x ^ (x >> 1);
}