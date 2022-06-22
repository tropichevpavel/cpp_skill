
#include "calculate.h"

double plus(const double& a, const double& b) {
    return a + b;
}

double minus(const double& a, const double& b) {
    return a - b;
}

double multy(const double& a, const double& b) {
    return a * b;
}

double div(const double& a, const double& b) {
    return a / b;
}

long long fact(const int& a) {
    return a == 1 ? a : (a * fact(a - 1));
}

double expon(const double& a, const double& b) {
    return b == 1 ? a : (a * expon(a, b - 1));
}