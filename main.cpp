#define NONIUS_RUNNER
#include "worlds.hpp"

#include <nonius/nonius.h++>


int main()
{
    std::srand(std::time(0));

    Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();
    Player *player = new Player(starting_planet, world);
    int input = 0;
    while(input != -1){
        std::cout << std::endl;
        std::cout << "1 - where am I\n2 - travel\n3 - save\n4 - load\n5 - exit\n";
        std::cin >> input;
        switch (input) {
        case 1:{
            player->where_am_i();
            break;
        }
        case 2:{
            std::cout << "Which portal\n";
            int x;
            std::cin >> x;
            player->use_portal(x);
            player->where_am_i();
            break;
        }

        case 3:{
            std::ofstream ofs("save.dat", std::ios::binary);
            boost::archive::binary_oarchive oa(ofs);
            oa << player;
            ofs.close();
            break;
        }
        case 4:{
            std::ifstream ifs("save.dat", std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia >> player;
            ifs.close();
            nonius::go();
            break;
        }
        case 5:{
            input = -1;
            break;
        }
        default:
            break;

        }
    }

    return 0;
}
