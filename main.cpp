#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
static std::mt19937 generator{ std::random_device{}() };

class Genethic {
private:
    double x;
    double y;
    double left_lim = -2.2;
    double right_lim = 2.2;
public:
    Genethic();
    double func(double, double);
    void mutation(std::unique_ptr<double[]>);
    void crossover();
    bool run();

};
Genethic::Genethic() {
    std::uniform_real_distribution<> dist{left_lim, right_lim};
    x = dist(generator);
    y = dist(generator);

}

void Genethic::mutation(std::unique_ptr<double[]> Cordinates) {

}

double Genethic::func(double x, double y){
    return exp(-pow(x,2))*exp(-pow(y, 2)) / (1+pow(x,2) + pow(y, 2));
}

int main()
{
    Genethic gen_algorithm;
    std::unique_ptr<double[]> cordinates(new double[4]);
    gen_algorithm.mutation(std::move(cordinates));

    return 0;
}