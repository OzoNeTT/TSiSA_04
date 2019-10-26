#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
static std::mt19937 generator{ std::random_device{}() };
double bestFIT = 0;
double AVGfit = 0;

double function(double x, double y) {
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
    void print() {
        std::cout << "X= " << x << "  Y= " << y << "  FIT= " << func() << "\n";
    }
};
Genethic::Genethic() {
    std::uniform_real_distribution<> dist{left_lim, right_lim};
    x = dist(generator);
    y = dist(generator);

}

void mutation(std::vector<Genethic>& Cordinates, size_t i) {
    std::uniform_real_distribution<> num{-1, 1};

    double delta = num(generator);
    Cordinates[i].set_cord(Cordinates[i].get_x() + delta, Cordinates[i].get_y() + delta);
}

void crossover(std::vector<Genethic>& Cordinates) {
    Genethic max1;
    Genethic max2;
    max1.set_cord(-100,-100);
    max2.set_cord(-100,-100);
    std::uniform_real_distribution<> ran{0, 1};
    AVGfit = (Cordinates[0].func() + Cordinates[1].func() + Cordinates[2].func() + Cordinates[3].func()) / 4;
    for (size_t iter = 0; iter  < 4; iter++ ) {
        if (Cordinates[iter].func() > max1.func() && Cordinates[iter].func() > max2.func()) {
            max2 = max1;
            max1 = Cordinates[iter];
        } else if (Cordinates[iter].func() > max2.func()) {
            max2 = Cordinates[iter];
        }
    }
    bestFIT = max1.func();
    Cordinates[0].set_cord(max1.get_x(), max1.get_y());
    if(ran(generator) <= 0.25){
        mutation(Cordinates, 0);

    }
    Cordinates[1].set_cord(max1.get_x(), max2.get_y());
    if(ran(generator) <= 0.25){
        mutation(Cordinates, 1);

    }
    Cordinates[2].set_cord(max2.get_x(), max1.get_y());
    if(ran(generator) <= 0.25){
        mutation(Cordinates, 2);

    }
    Cordinates[3].set_cord(max2.get_x(), max2.get_y());
    if(ran(generator) <= 0.25){
        mutation(Cordinates, 3);

    }



}

int main()
{
    Genethic a, b, c, d;
    size_t populations = 0;
    std::vector<Genethic> Coords;
    Coords.push_back(a);
    Coords.push_back(b);
    Coords.push_back(c);
    Coords.push_back(d);
    std::cout << "Enter Populations: "; std::cin >> populations;
    for(size_t iterator = 0; iterator <= populations; iterator++) {
        std::cout << "Population " << iterator << std::endl;
        for (size_t jterator = 0; jterator < 4; jterator++) {
            Coords[jterator].print();

        }
        crossover(Coords);
        std::cout << "Best FIT: " << bestFIT << "    AVG FIT: " << AVGfit << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;

}