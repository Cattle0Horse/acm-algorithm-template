//扩展欧几里得：
//求ax+by=gcd(a,b)的(x,y)可行解
int exgcd(int a, int b, int& x, int& y) {
    if (!b) return x = 1, y = 0, a;
    int res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}
int inv(int a, int b) {
    int x, y;
    exgcd(a, b, x, y);
    return (b + x % b) % b;
}