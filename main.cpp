#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>

#define COLOUR_MAX 16777215
#define PLANET_MAX 100

int gen_portals(){
    std::random_device r;
    std::default_random_engine re(r());
    int n = 1;
    while(true){
        if(std::round(std::generate_canonical<double, 10>(re)))
            break;
        n++;
    }
    return n;
}

int gen_colour(){
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_int_distribution<> dist(0, COLOUR_MAX);

    return dist(re);
}

int gen_name(){
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_int_distribution<> dist(0, PLANET_MAX);

    return dist(re);
}

class Planet{
public:
    std::string name;
    int colour;
    int *portals;
};

class Portal{

};

class Player{
public:
    Planet *current_pos;
    void use_portal(int);
};

int main()
{

    std::srand(std::time(0));
    const int N = 10;
    int A[N];
    for(int i = 0; i < N; i++){
        A[i] = gen_portals();
    }

    /*for(int i = 0; i < N; i++){
        std::cout << std::round(std::generate_canonical<double, 10>(re)) << '\n';
    }*/

    /*for(int i = 0; i < N; i++){
        std::cout << A[i] << '\n';
    }*/

    std::cout << std::hex << gen_colour();

    return 0;
}
