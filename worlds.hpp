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
#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <nonius/nonius.h++>

#define COLOUR_MAX 16777215

class Planet{
private:
    friend class boost::serialization::access;
    int name = 0;
    int colour = 0;
    int nportals = 1;
    bool is_warpable;
    int gen_name(int max, std::mt19937*);
    int gen_colour(std::mt19937*);
    int gen_nportals(std::mt19937*);
    std::vector<Planet*> portals;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & name;
        ar & colour;
        ar & nportals;
        ar & is_warpable;
        ar & portals;
    }

public:
    friend class boost::serialization::access;
    Planet(){}
    Planet(int max_planets, std::mt19937 *mt): name(gen_name(max_planets, mt)), colour(gen_colour(mt)), nportals(gen_nportals(mt)), is_warpable(!(1-nportals)){
        portals.resize(nportals);
        assert(nportals >= 1);
        assert(colour >= 0 && colour <= COLOUR_MAX);
    }

    int get_name() const {
        return name;
    }

    int get_colour() const {
        return colour;
    }

    int get_nportals() const {
        return nportals;
    }

    std::vector<Planet*>* get_portals(){
        return &portals;
    }

    bool get_status() const {
        return is_warpable;
    }

    int get_exit();

};

class Universe{
public:
    Universe(){}
    Universe(int init_max_planets): max_planets(init_max_planets){
        std::random_device r;
        rnd = std::mt19937{r()};
    }

    inline int get_max_planets() const{
        return this->max_planets;
    }

    inline std::unordered_map<int, Planet*>* get_planets(){
        return &(this->planets);
    }

    inline std::unordered_map<int, Planet*>* get_warpable(){
        return &(this->warpable);
    }

    std::mt19937 *get_rnd(){
        return &(this->rnd);
    }

    Planet *new_planet();
private:
    std::mt19937 rnd;
    friend class boost::serialization::access;
    std::unordered_map<int, Planet*> planets;
    std::unordered_map<int, Planet*> warpable;
    int max_planets;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar & max_planets;
        ar & planets;
        ar & warpable;
    }
};

class Player{
public:
    Player(){}
    Player(Planet* position, Universe* universe): current_pos(position), universe(universe){

    }

    inline Planet* get_pos() const{
        return this->current_pos;
    }

    inline Universe* get_uni() const{
        return this->universe;
    }

    void use_portal(int nportal);
    void where_am_i();
private:
    friend class boost::serialization::access;
    Planet* current_pos;
    Universe* universe;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar & current_pos;
        ar & universe;
    }
};

void init_interactive();

void init_automatic(int jumps);

#endif//WORLDS_HPP
