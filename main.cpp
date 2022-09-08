#include <iostream>
#include <chrono>

#define micro std::chrono::microseconds
#define MAX 20000
#define ll long long int

using namespace std;

ll fib_2n(ll x)
{
    if (x == 0 || x == 1)
        return x;
    return fib_2n(x - 1) + fib_2n(x - 2);
}

ll fib_n(ll x)
{
    ll F[MAX];
    F[0] = 0;
    F[1] = 1;
    for (ll i = 2; i <= x; i++)
        F[i] = F[i - 1] + F[i - 2];
    return F[x];
}

// R[0] R[1]
// R[2] R[3]
void m_expo(int p, ll R[4])
{
    if (p == 0){
        R[0] = 1, R[1] = 0, R[2] = 0, R[3] = 1;
        return;
    }
    if (p == 1){
        R[0] = 1, R[1] = 1, R[2] = 1, R[3] = 0;
        return;
    }
    m_expo(p >> 1, R);
    ll t0 = R[0], t1 = R[1], t2 = R[2], t3 = R[3];
    R[0] = t0 * t0 + t1 * t2;
    R[1] = t0 * t1 + t1 * t3;
    R[2] = t0 * t2 + t2 * t3;
    R[3] = t1 * t2 + t3 * t3;
    if (p & 1)
    {
        t1 = R[0], t2 = R[2];
        R[0] += R[1];
        R[1] = t1;
        R[2] += R[3];
        R[3] = t2;
    }
}

ll fib_log_n(ll x)
{
    ll M[4];
    m_expo(x - 1, M);
    return M[2] + M[3];
}

void test(const char* s, int n, ll (*fibo)(ll))
{
    cout << s << endl;
    auto start = std::chrono::high_resolution_clock::now();
    ll F1 = fibo(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<micro>(end - start).count();
    cout << "F(" << n << ") = " << F1 << endl;
    cout << elapsed << " milliseconds" << endl;
    cout << endl;
}

int main()
{
    int n;
    cout << "Ingrese n: ";
    cin >> n;

    test("O(log n):", n, &fib_log_n);
    test("O(n):", n, &fib_n);
    if (n < 50)
        test("O(2^n):", n, &fib_2n);
    else
        cout << "Tiempo muy largo para O(2^n)" << endl << endl;

    return 0;
}