#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
#include <map>
#include <unordered_map>
static std::mt19937 generator{ std::random_device{}() };

double func(double x, double y){
    return exp(-pow(x,2))*exp(-pow(y, 2)) / (1+pow(x,2) + pow(y, 2));
}

int main()
{
    std::uniform_real_distribution<> dis{-2.2, 2.2};
    double x1 = dis(generator), x2 = dis(generator), x3 = dis(generator), x4 = dis(generator);
    std::pair<double, double> alpha1(x1, x2);
    std::pair<double, double> alpha2(x3, x4);
    std::swap(alpha1.second, alpha2.second);
    std::cout << "";
    return 0;
}