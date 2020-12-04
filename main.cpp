#include "worlds.hpp"



int main()
{
    std::srand(std::time(0));

    /*std::unordered_map<int, Planet> planets;

    Planet my_planet(100);

    planets.insert(std::pair(my_planet.get_name(), my_planet));

    std::vector<int> a;
    a.reserve(5);
    a[0] = 1;
    a[5] = 2;
    a.shrink_to_fit();*/

    Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();
    Player *player = new Player(starting_planet, world);
    int input = 0;
    while(input != -1){
        std::cout << "1 - where am I\n2 - travel\n3 - exit\n";
        std::cin >> input;
        switch (input) {
        case 1:
            player->where_am_i();
            break;
        case 2:
            std::cout << "Which portal\n";
            int x;
            std::cin >> x;
            player->use_portal(x);
            break;
        case 3:
            input = -1;
            break;

        default:
            break;
        }
    }

    //std::cout << planets.size();
    //Player player(&my_planet);

    //player.where_am_i();

    /*planets.insert(std::make_pair(my_planet.name, my_planet));

    //std::cout << my_planet.name << '\n' << my_planet.colour << '\n' << my_planet.nportals;
    //std::cout << planets[0].name << '\n' << planets[0].colour << '\n' << planets[0].nportals;
    std::cout << planets[my_planet.name].name << '\n' << planets[my_planet.name].colour << '\n' << planets[my_planet.name].nportals;*/

    return 0;
}
