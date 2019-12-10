#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

const double eps = 0.1;
std::ofstream out("data.txt");

double fun1(double x)
{
    return (cos(x) * tanh(x));
}

void print(double x1, double x2, double fx1, double fx2)
{
    
    std::cout << std::fixed;
    std::cout.precision(3);
    if ((x1 > 10) || (x2 > 10)) {
        out <<" | " << x1 << "  | " << x2 << " | " << fx1 << "  | " << fx2 << "  |\n";
    }
    else {
        out << " | " << x1 << "  | " << x2 << "  | " << fx1 << "  | " << fx2 << "  |\n";
    }
}

void passive_search(double a, double b) {
    
    double extremum;
    double length = b - a;
    int N = 2 * length / eps - 1;
    std::vector <double> x;
    std::cout << "Points " << N << "\n";
    std::cout << "Elements:\n";
    std::cout << "-------------------------\n";
    for (auto i = 1; i <= N; i++)
    {
        x.push_back(a + i * length / (N + 1));
        std::cout.setf(std::ios::fixed);
        std::cout.precision(3);
        std::cout << "| " << x[i - 1] << " | " << fun1(x[i - 1]) << " |" << std::endl;
        std::cout << "-------------------------\n";
    }
    extremum = x[0];
    for (int i = 0; i < N; i++) {
        if (fun1(x[i]) <= fun1(extremum)) extremum = x[i];
    }
    std::cout << "\nExtremum = " << extremum << " +- " << length / (N + 1) << std::endl;
    x.clear();
}

int fib_num(int n)
{
    int f, f1(1), f2(1), m(0);
    while (m < n - 1)
    {
        f = f1 + f2;
        f1 = f2;
        f2 = f;
        ++m;
    }
    return f1;
}

void fibonacci_method(double a, double b)
{
    out << "\n\n\n\t\t\t\tFibonacci Search:\n\n";
    out << "-----------------------------------------------------------------------\n" 
        << "|   k   |   ak  |   bk  |   lk  |   x1   |   x2   |  f(x1)  |  f(x2)  |\n";

    double x1, x2, _x, xf1, xf2;
    int k(0);
    int N(3);
    double fn1(1), fn2(1), fn, f = (b - a) / eps;
    while (fn1 < f)
    {
        fn = fn1 + fn2;
        fn1 = fn2;
        fn2 = fn;
        ++N;
    }
    x1 = a + (double)fib_num(N - 2) / fib_num(N) * (b - a) - (N & 1 ? -1 : 1) * eps / fib_num(N);
    x2 = a + (double)fib_num(N - 1) / fib_num(N) * (b - a) + (N & 1 ? -1 : 1) * eps / fib_num(N);
    xf1 = fun1(x1);
    xf2 = fun1(x2);
P:
    ++k;
    out.setf(std::ios::fixed);
    out << std::setprecision(3);
    out << "-----------------------------------------------------------------------\n";
    if (b > 10) {
        out << "|   " << k << "   | " << a << " | " << b << "| " << (b - a);
    }
    else {
        out << "|   " << k << "   | " << a << " | " << b << " | " << (b - a);
    }
    if (xf1 >= xf2) {
        a = x1;
        x1 = x2;
        xf1 = xf2;
        x2 = a + (double)fib_num(N - k - 1) / fib_num(N - k) * (b - a) + ((N - k) & 1 ? -1 : 1) * eps / fib_num(N - k);
        xf2 = fun1(x2);
    } else {
        b = x2;
        x2 = x1;
        xf2 = xf1;
        x1 = a + (double)fib_num(N - k - 2) / fib_num(N - k) * (b - a) - ((N - k) & 1 ? -1 : 1) * eps / fib_num(N - k);
        xf1 = fun1(x1);
    }
 
    print(x1, x2, fun1(x1), fun1(x2));

    if (fabs(b - a) <= eps)
    {
        out << "-----------------------------------------------------------------------\n";
        _x = (a + b) / 2;
        out << "Extremum: x = " << _x;
    }
    else
        goto P;
}
