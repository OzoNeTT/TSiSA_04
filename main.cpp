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
    AVGfit = (Cordinates[0].func() + Cordinates[1].func() + Cordinates[2].func() + Cordinates[3].func()) / 4;
    std::vector<Genethic> RulletResult;
    std::vector<Genethic> ChildsAndParents;
    std::vector<double> Propes;
    std::uniform_real_distribution<> ran{0, 1};
    double sumFIT = 0;
    double randomNumber = 0;
    for(size_t iterator = 0; iterator < Cordinates.size(); iterator++) {
        sumFIT +=  Cordinates[iterator].func();
    }
    for(size_t iterator = 0; iterator < Cordinates.size(); iterator++) {
        Propes.push_back(Cordinates[iterator].func() / sumFIT);
    }
    for(size_t alpha = 1; alpha < Propes.size(); alpha++) {
        Propes[alpha] += Propes[alpha - 1];
    }


    for(int iter = 0; iter < 2; iter++) {
        randomNumber = ran(generator);
        if (randomNumber <= Propes[0]){
            RulletResult.push_back(Cordinates[0]);
        }
        else if ( randomNumber > Propes[0] && randomNumber <= Propes[1]){
            RulletResult.push_back(Cordinates[1]);
        }
        else if (randomNumber > Propes[1] && randomNumber <= Propes[2]){
            RulletResult.push_back(Cordinates[2]);
        }
        else if (randomNumber > Propes[2] && randomNumber <= Propes[3]){
            RulletResult.push_back(Cordinates[3]);
        }
    }
    for (auto it: RulletResult){
        ChildsAndParents.push_back(it);
    }
    Genethic alpha1;
    Genethic alpha2;
    alpha1.set_cord(RulletResult[0].get_x(), RulletResult[1].get_y());
    alpha2.set_cord(RulletResult[1].get_x(), RulletResult[0].get_y());
    ChildsAndParents.push_back(alpha1);
    ChildsAndParents.push_back(alpha2);

    Genethic max1;
    Genethic max2;
    max1.set_cord(-100,-100);
    max2.set_cord(-100,-100);

    //AVGfit = (Cordinates[0].func() + Cordinates[1].func() + Cordinates[2].func() + Cordinates[3].func()) / 4;
    for (size_t iter = 0; iter  < ChildsAndParents.size(); iter++ ) {
        if(ChildsAndParents[iter].func() > max1.func()&& ChildsAndParents[iter].func() > max2.func()){
            max2 = max1;
            max1 = ChildsAndParents[iter];
        }
        else if(ChildsAndParents[iter].func() > max2.func()){
            max2 = ChildsAndParents[iter];
        }
    }
    bestFIT = max1.func();
    for(size_t iter = 0; iter < Cordinates.size(); iter++){
        Cordinates[iter] = ChildsAndParents[iter];
    }

    if(ran(generator) <= 0.25){
        mutation(Cordinates, 0);
    }

    if(ran(generator) <= 0.25){
        mutation(Cordinates, 1);
    }

    if(ran(generator) <= 0.25){
        mutation(Cordinates, 2);
    }

    if(ran(generator) <= 0.25){
        mutation(Cordinates, 3);
    }
    ChildsAndParents.clear();
    RulletResult.clear();
    Propes.clear();
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