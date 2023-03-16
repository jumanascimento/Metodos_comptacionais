#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

double bisectionMethod(double a, double b, function<double(double)> f, int max_iter) {
    double c = 0.0;
    int iter = 0;
    
    while (iter < max_iter) {
        c = (a + b) / 2.0;
        
        if (f(c) == 0.0 || (b - a) / 2.0 < 1e-8) {
            return c;
        }
        
        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
        
        iter++;
    }
    
    return c;
}

double newtonMethod(double x0, function<double(double)> f, function<double(double)> df, int max_iter) {
    double x1 = 0.0;
    int iter = 0;
    
    while (iter < max_iter) {
        x1 = x0 - f(x0) / df(x0);
        
        if (abs(x1 - x0) < 1e-8 || abs(f(x1)) < 1e-8) {
            return x1;
        }
        
        x0 = x1;
        iter++;
    }
    
    return x1;
}

double secantMethod(double x0, double x1, function<double(double)> f, int max_iter) {
    double x2 = 0.0;
    int iter = 0;
    
    while (iter < max_iter) {
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        
        if (abs(x2 - x1) < 1e-8 || abs(f(x2)) < 1e-8) {
            return x2;
        }
        
        x0 = x1;
        x1 = x2;
        iter++;
    }
    
    return x2;
}

double fixedPointMethod(double x0, function<double(double)> g, int max_iter) {
    double x1 = 0.0;
    int iter = 0;
    
    while (iter < max_iter) {
        x1 = g(x0);
        
        if (abs(x1 - x0) < 1e-8 || abs(g(x1) - g(x0)) < 1e-8) {
            return x1;
        }
        
        x0 = x1;
        iter++;
    }
    
    return x1;
}

int main() {
    string function_string;
    cout << "Enter a function f(x): ";
    getline(cin, function_string);
    function<double(double)> f = [&](double x) { return eval(function_string.c_str()); };
    
    int max_iter;
    cout << "Enter the maximum number of iterations: ";
    cin >> max_iter;
    
    double a, b;
    cout << "Enter the interval [a,b] for the bisection method: ";
    cin >> a >> b;
    double bisection_result = bisectionMethod(a, b, f, max_iter);
    cout << "Bisection method: root = "
