#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double eps = 0.1;

double fun1(double x)
{
    return cos(x) * tanh(x);
}

void print(int N, double a,double b,double x1, double x2, double fx1, double fx2)
{
    std::cout << std::fixed;
    std::cout.precision(3);
    if (b > 10) {
        std::cout  << "|   " << N << "   | "  << a << " | "<< b << "| " << fabs(b - a) << " | " << x1 << "  | " << x2 << "  | " << fx1 << "  | " << fx2 << "  |\n";
    } else {
        std::cout << "|   " << N << "   | " << a << " | "<< b << " | " << fabs(b - a) << " | " << x1 << "  | " << x2 << "  | " << fx1 << "  | " << fx2 << "  |\n";
    }
}

void passive_search(double a, double b) {
    double extremum;
    double length = b - a;
    int N = 2 * length / eps - 1;
    std::vector <double> x;
    std::cout << "Points " << N << "\n";
    std::cout << "Elements:\n";
    std::cout << "+-----------------------+\n";
    for (int i = 1; i <= N; i++)
    {
        x.push_back(a + i * length / (N + 1));
        std::cout.setf(std::ios::fixed);
        std::cout.precision(4);
        std::cout << "|\t" << x[i-1] << "\t|\t" << fun1(x[i-1]) << "\t|" <<std::endl;
        std::cout << "+-----------------------+\n";
    }
    extremum = x[0];
    for (int i = 0; i < N; i++) {
        if (fun1(x[i]) <= fun1(extremum)) extremum = x[i];
    }
    std::cout << "\nExtremum = " << extremum << " +- " << length/(N+1) << std::endl;
    x.clear();
}

int FibonacciNumber(int n) {
    return (n == 1 || n == 2) ? 1 : FibonacciNumber(n - 1) + FibonacciNumber(n - 2);
}

void PrintResult(int N, double result_x, double interval) {
    std::cout << "Result:\nx = " << std::fixed << std::setprecision(6) << result_x
              << "\t\tIndefinite interval: " << std::fixed << std::setprecision(6) << interval << "\t\tF(x) = "
              << std::fixed << std::setprecision(6) << fun1(result_x)
              << "\nNumber of points: " << N;
}

void FibonacciSearch(double begin, double end, double epsilon) {
    std::cout << "\n\n\n\t\t\t\tFibonacci Search:\n\n";
    std::cout << "+---------------------------------------------------------------------+\n"
              << "|   k   |   ak  |   bk  |   lk  |   x1   |   x2   |  f(x1)  |  f(x2)  |\n";
    std::cout << "+---------------------------------------------------------------------+\n";

    double begin_new = 0, end_new = 0, x1, x2, function_in_x1, function_in_x2;
    int N = 3;
    bool done = false;
    while (!done) {
        begin_new = begin;
        end_new = end;
        x1 = begin_new + (double) FibonacciNumber(N - 2) / FibonacciNumber(N) * (end_new - begin_new);
        x2 = end_new - (double) FibonacciNumber(N - 2) / FibonacciNumber(N) * (end_new - begin_new);
        function_in_x1 = fun1(x1);
        function_in_x2 = fun1(x2);
        for (int i = 0; i < N - 2; i++) {
            if (function_in_x1 > function_in_x2) {
                begin_new = x1;
                x1 = x2;
                function_in_x1 = function_in_x2;
                x2 = end_new - (double) FibonacciNumber(N - i - 2) / FibonacciNumber(N - i) * (end_new - begin_new);
                function_in_x2 = fun1(x2);
            } else if (function_in_x1 < function_in_x2) {
                end_new = x2;
                x2 = x1;
                function_in_x2 = function_in_x1;
                x1 = begin_new + (double) FibonacciNumber(N - i - 2) / FibonacciNumber(N - i) * (end_new - begin_new);
                function_in_x1 = fun1(x1);
            }
            if (fabs(end_new - begin_new) <= epsilon) {
                done = true;
                break;
            }
        }
        print(N - 2, begin_new, end_new,x1, x2, function_in_x1, function_in_x2);
        N++;
    }
    std::cout << "-----------------------------------------------------------------------\n";
    PrintResult(N - 3, (begin_new + end_new) / 2, fabs(end_new - begin_new) / 2);
}
