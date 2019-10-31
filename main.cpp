#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
std::mt19937 generator{ std::random_device{}() };

double bestFIT = 0;
double AVGfit = 0;

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
    std::uniform_real_distribution<> ran{0, 1};
    double delta = num(generator);
    if(ran(generator) <= 0.5) {
        Cordinates[i].set_cord(Cordinates[i].get_x() + delta, Cordinates[i].get_y());
    }
    else {
        Cordinates[i].set_cord(Cordinates[i].get_x() , Cordinates[i].get_y() + delta);
    }
}

void crossover(std::vector<Genethic>& Cordinates) {
    AVGfit = (Cordinates[0].func() + Cordinates[1].func() + Cordinates[2].func() + Cordinates[3].func()) / 4;
    std::vector<Genethic> RulletResult;
    std::vector<Genethic> ChildsAndParents;
    std::vector<double> RulletIntervals;
    std::uniform_real_distribution<> ran{0,1};
    double SumFIT = 0;
    double randomNumber = 0;

    for(int iterator = 0; iterator < Cordinates.size(); iterator++){
        SumFIT += Cordinates[iterator].func();
    }
    for(int iterator = 0; iterator < Cordinates.size(); iterator++){
        RulletIntervals.push_back(Cordinates[iterator].func() / SumFIT);
    }
    for(int iterator = 1; iterator < RulletIntervals.size(); iterator++){
        RulletIntervals[iterator] += RulletIntervals[iterator - 1];
    }

    for(int iter = 0; iter < 2; iter++){
        randomNumber = ran(generator);
        if(randomNumber <= RulletIntervals[0]){
            RulletResult.push_back(Cordinates[0]);
        }
        if(randomNumber > RulletIntervals[0] && randomNumber <= RulletIntervals[1]){
            RulletResult.push_back(Cordinates[1]);
        }
        if(randomNumber > RulletIntervals[1] && randomNumber <= RulletIntervals[2]){
            RulletResult.push_back(Cordinates[2]);
        }
        if(randomNumber > RulletIntervals[2] && randomNumber <= RulletIntervals[3]){
            RulletResult.push_back(Cordinates[3]);
        }
    }

    ChildsAndParents.push_back(RulletResult[0]);
    ChildsAndParents.push_back(RulletResult[1]);

    Genethic child1; child1.set_cord(RulletResult[0].get_x(), RulletResult[1].get_y());
    Genethic child2; child2.set_cord(RulletResult[1].get_x(), RulletResult[0].get_y());
    ChildsAndParents.push_back(child1); ChildsAndParents.push_back(child2);

    Genethic max1;
    max1.set_cord(-100, -100);

    for (int iterator = 0; iterator < ChildsAndParents.size(); iterator++) {
        if(ChildsAndParents[iterator].func() > max1.func()) {
            max1 = ChildsAndParents[iterator];
        }
    }

    bestFIT = max1.func();

    for (int i = 0; i < 4; i++){
        Cordinates[i] = ChildsAndParents[i];
    }

    for(int iter = 0; iter < Cordinates.size(); iter++) {
            if(ran(generator) <= 0.25){
                mutation(Cordinates, iter);
            }
    }
    RulletResult.clear();
    ChildsAndParents.clear();
    RulletIntervals.clear();
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