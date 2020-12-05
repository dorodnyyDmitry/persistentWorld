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

#define COLOUR_MAX 16777215

class Planet{
private:
    friend class boost::serialization::access;
    int name = 0;
    int colour = 0;
    int nportals = 1;
    bool is_warpable;
    int gen_name(int);
    int gen_colour();
    int gen_nportals();
    std::vector<Planet*> portals;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & name;
        ar & colour;
        ar & nportals;
        ar & is_warpable;
        ar & this->portals;
    }

public:
    friend class boost::serialization::access;
    Planet(){}
    Planet(int max_planets): name(gen_name(max_planets)), colour(gen_colour()), nportals(gen_nportals()), is_warpable(!(1-nportals)){
        //portals = std::vector<Planet*> ;
        //this->portals(nportals, 0);
        this->portals.resize(nportals);
        assert(nportals >= 1);
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

};

class Universe{
public:
    Universe(){}
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
    friend class boost::serialization::access;
    std::unordered_map<int, Planet*> planets;
    std::unordered_map<int, Planet*> warpable;
    int max_planets;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar & max_planets;
        ar & this->planets;
        ar & this->warpable;
    }
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
    Player(){}
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
    friend class boost::serialization::access;
    Planet* current_pos;
    Universe* universe;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        ar & this->current_pos;
        ar & this->universe;
    }
};

#endif//WORLDS_HPP
