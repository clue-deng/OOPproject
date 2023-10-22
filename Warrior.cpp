//
//  Warrior.cpp
//
//  Created by Yingtong on 3/12/22.
//

#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft{

    //initialization list for Warrior class
    Warrior::Warrior(const string& name, int strengthNum) : warriorName(name),
    strength(strengthNum), boss(nullptr) {}

    //this method is to change the strength of the warrior
    void Warrior::changeStrength(double num){
        strength += num;
    }

    //this method is to confirm that the warrior is hired by a noble and point
    //to a noble pointer
    void Warrior::hired(Noble& noble){
        boss = &noble;
    }

    //this method is to confirm that the warrior has been fired by his noble
    //and point to a nullptr
    void Warrior::fired() {
        boss = nullptr;
    }

    //this returns the strength of the warrior
    double Warrior::getStrength() const {
        return strength;
    }

    //this method returns the name of the warrior's name
    const string& Warrior::getWarriorName() const{
        return warriorName;
    }

    //this method returns the hiring/firing status of the warrior
    //by checking whehter its pointer is pointing to some thing or a nullptr
    bool Warrior::isHired()  const{
        return (boss != nullptr);
    }

    //this method is to leave the noble and notify him, it will
    //return true or false based on if he could run away successfully
    bool Warrior::runaway() {
        if (boss){ //not a null
            cout << warriorName << " flees in terror, abandoning his lord, " <<
            boss -> getNobleName() << endl;
            boss -> removeWarrior(*this);
            boss = nullptr;
            return true;
        }
        cout << warriorName << " is not hired by anyone, so can't run away"
        << endl;
        return false;
    }

    //this is the output operator for warrior class that outputs the warrior's
    //name and the strength
    ostream& operator << (ostream& os, const Warrior& warrior){
        os << "\t\t" << warrior.warriorName << ": " << warrior.strength;
        return os;
    }
}


