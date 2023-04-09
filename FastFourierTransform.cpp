#include "FastFourierTransform.h"
#include <bits/stdc++.h>
#include <complex>

const double PI = acos(-1.0);

void FastFourierTransform::FFT(std::vector<std::complex<double>>& a, int inv){
    int n = a.size();
    if (n == 1) return;

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    FFT(a0, inv);
    FFT(a1, inv);

    double ang = 2 * PI / n * inv;
    std::complex<double> w(1), wn(cos(ang), sin(ang));

    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }
}

std::vector<int> FastFourierTransform::multiply(std::vector<int> &a, std::vector<int> &b) {
    int n = 1;
    while (n < a.size() + b.size())
        n *= 2;

    std::vector<std::complex<double>> fa(n), fb(n);
    for (int i = 0; i < a.size(); i++)
        fa[i] = a[i];

    for (int i = 0; i < b.size(); i++)
        fb[i] = b[i];

    FFT(fa, 1);
    FFT(fb, 1);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    FFT(fa, -1);

    std::vector<int> res(n);
    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real() / n);
    return res;
}