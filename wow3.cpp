#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

const int ICEMAN = 0, LION = 1, WOLF = 2, NINJA = 3, DRAGON = 4;
const string COLORS[2] = {"red", "blue"};
const string WEAPONS[] = {"sword", "bomb", "arrow"};
int init_hp[5];
class weapons;
class sword;
class arrow;
class warriors
{
    public:
    warriors(int, int, int);
    ~warriors();
    virtual bool will_escape(){return false;};//是否 lion会跑
    virtual void get_weapons();//用于wolf获得武器
    virtual void yelled();//dragonyell
    bool is_killed();//是否被杀死
    friend class city;
    protected:
    int hp;
    int _color;
    int _type;
    int _id;
    int attack;
    int arrows;
    int swords;
    vector<weapons*>;
    bool _bomb;//有没有炸弹
};
warriors::warriors(int color, int id, int type)
{
    _color = color;
    _id = id;
    hp = init_hp[type];
    switch(type)
    {
        case NINJA:
            break;
    }
}
class lion:public warriors
{
    
};
class  city
{
    int id;
    int color;
    int hp;
    public:
    warriors * warrior[2];
    bool is_taken();//是否被占领
    void create_warrior(int);
    void go_another_city(city*, int);
    void esacpe();
    void yell();
    void attack();
    void tell_hp();
    bool is_headsquarter();
};

class weapons
{
    public:
    int force;
    void use();
    bool used;
    int type;
    weapons(int n):force(n),used(0){};
};

int main(int argv, char** argc)
{
    return 0;
}