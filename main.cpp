#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
static std::mt19937 generator{ std::random_device{}() };
double func(double x, double y) {
    return exp(-pow(x,2))*exp(-pow(y, 2)) / (1+pow(x,2) + pow(y, 2));
}
class Genethic {
private:
    double x;
    double y;
    double left_lim = -2;
    double right_lim = 2;
public:
    Genethic();
    void set_cord(double _x, double _y ) { x = _x; y = _y;}
    double get_x() { return x;}
    double get_y() { return y;}
    double func() {
        return exp(-pow(x,2))*exp(-pow(y, 2)) / (1+pow(x,2) + pow(y, 2));
    }
};
Genethic::Genethic() {
    std::uniform_real_distribution<> dist{left_lim, right_lim};
    x = dist(generator);
    y = dist(generator);

}

void mutation(std::vector<Genethic>& Cordinates) {
    std::uniform_real_distribution<> num{-0.1, 0.1};

    double delta = num(generator);
    for(size_t i = 0; i < 2; i++) {
        Cordinates[i].set_cord(Cordinates[i].get_x() + delta, Cordinates[i].get_y() + delta);
    }
}

void crossover(std::vector<Genethic>& Cordinates) {
    std::vector<Genethic> Cord;
    Cord.resize(Cordinates.size());

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 1; j < 4; j++) {
            if (Cordinates[j].func() > Cordinates[j - 1].func()) {
                std::swap(Cordinates[j], Cordinates[j - 1]);
            }
        }
    }

    Cord[0].set_cord(Cordinates[1].get_x(), Cordinates[0].get_y());
    Cord[1].set_cord(Cordinates[2].get_x(), Cordinates[0].get_y());
    Cord[2].set_cord(Cordinates[0].get_x(), Cordinates[1].get_y());
    Cord[3].set_cord(Cordinates[0].get_x(), Cordinates[2].get_y());
    mutation(Cord);

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 1; j < 4; j++) {
            if (Cord[j].func() > Cord[j - 1].func()) {
                std::swap(Cord[j], Cord[j - 1]);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        Cordinates[i] = Cord[i];
    }
}

int main()
{
    Genethic a, b, c, d;
    std::vector<Genethic> Coords;
    Coords.push_back(a);
    Coords.push_back(b);
    Coords.push_back(c);
    Coords.push_back(d);
    int N = 0;
    while (N != 30) {
        double SumOfX = 0;
        double SumOfY = 0;
        crossover(Coords);
        N++;
        std::cout << std::endl << "Номер популяции :" << N << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << "x = " << Coords[i].get_x() << " y = " << Coords[i].get_y() << " f = " << Coords[i].func() << std::endl;
            SumOfX += Coords[i].get_x();
            SumOfY += Coords[i].get_y();
        }
        std::cout << std::endl << "Среднее x = " << SumOfX / 4 << " Среднее y = " << SumOfY / 4 << " f(среднее x, среднее y) = " << func(SumOfX / 4, SumOfY / 4) << std::endl;
    }
    std::cout << std::endl << "максимум равен F = " << Coords[0].func();
    std::cout << std::endl;
    return 0;

}