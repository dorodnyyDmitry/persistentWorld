#ifndef WORLDS_HPP
#define WORLDS_HPP

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <iterator>

#define COLOUR_MAX 16777215
#define PLANET_MAX 100

class Planet{
public:
    Planet(int max_planets): name(gen_name(max_planets)), colour(gen_colour()), nportals(gen_nportals()), is_warpable(!(1-nportals)){
        this->portals.reserve(nportals);
        assert(nportals >= 1);
        assert(name >= 0 && name <= PLANET_MAX);
        assert(colour >= 0 && colour <= COLOUR_MAX);
    }

    inline int get_name() const {
        return this->name;
    }

    inline int get_colour() const {
        return this->colour;
    }

    inline int get_nportals() const {
        return this->nportals;
    }

    inline std::vector<Planet*>* get_portals(){
        return &(this->portals);
    }

    inline bool get_status() const {
        return this->is_warpable;
    }

    void det_status();

    int get_exit();
private:
    int name = 0;
    int colour = 0;
    int nportals = 1;
    bool is_warpable;
    int gen_name(int);
    int gen_colour();
    int gen_nportals();
    std::vector<Planet*> portals;
};

class Universe{
public:
    Universe(int init_max_planets): max_planets(init_max_planets){

    }

    inline int get_max_planets(){
        return this->max_planets;
    }

    inline std::unordered_map<int, Planet*>* get_planets(){
        return &(this->planets);
    }

    inline std::unordered_map<int, Planet*>* get_warpable(){
        return &(this->warpable);
    }
    Planet *new_planet();
private:
    std::unordered_map<int, Planet*> planets;
    std::unordered_map<int, Planet*> warpable;
    int max_planets;
};

/*class Portal{
public:
    Portal()
    Planet* node1;
    Planet* node2;
    Planet* current_pos;
    void use_portal(int);
};*/


class Player{
public:

    Player(Planet* position, Universe* universe): current_pos(position), universe(universe){

    }

    inline Planet* get_pos() const{
        return this->current_pos;
    }

    inline Universe* get_uni() const{
        return this->universe;
    }

    void use_portal(int);
    void where_am_i();
private:
    Planet* current_pos;
    Universe* universe;
};

#endif//WORLDS_HPP
