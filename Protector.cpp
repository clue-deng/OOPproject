//
//  Protector.cpp
//  separate compilation
//
//  Created by Yingtong Deng on 4/14/22.
//

#include "Protector.h"
#include "Noble.h"
using namespace std;

namespace WarriorCraft{
    //============= Implementation Code for Protector class =======

    //constructor for protector class
    Protector::Protector(const string& name, double num) : ProName(name),
    strength(num), boss(nullptr) {}

    //this returns whether or not the protector is hired
    bool Protector::isHired() const{
        return (boss != nullptr);
    }

    //this sets the protector hired by the lord, gets the pointer of the lord
    void Protector::hired(Lord& lord){
        boss = &lord;
    }

    //this sets the protector unhired, the pointer becomes nullptr
    void Protector::fired(){
        boss = nullptr;
    }

    //this returns the name of the protector
    const string& Protector::getName() const{
        return ProName;
    }

    //this returns the strength of the protector
    double Protector::getStrength() const{
        return strength;
    }
        
    //this returns the pointer of the lord of the protector
    Lord* Protector::getBoss() const{
        return boss;
    }

    //this method is to make the battle cry and change the strength of the
    //protector
    void Protector::changeStrength(double deduction){
        battle();
        if (boss -> isAlive()){
            strength -= deduction;
        }
    }

    //this method is for the protector to leave their boss and notify them
    bool Protector::runaway(){
        if (boss){ //not a null
            cout << ProName << " flees in terror, abandoning his lord, "
            << boss -> getName() << endl;
            boss -> removeProtector(*this);
            boss = nullptr;
            return true;
        }
        //if boss is a nullptr, meaning he is not hired
        cout << ProName << " is not hired by anyone, so can't run away" << endl;
        return false;
    }


    //output operator for Protector, since all child classes share the same one,
    //we can just use one unified output operator
    ostream& operator<<(ostream& os, const Protector& rhs){
        os << rhs.ProName << "has his own strength: " << rhs.strength << endl;
        return os;
    }


    //============= Implementation Code for Wizard class =======

    //constructor for Wizard inherits from protector
    Wizard::Wizard(const string& name, double num) : Protector(name, num) {}

    //battle cry for wizard, overriding the base class function
    void Wizard::battle() const {
        cout << "POOF!" << endl;
    }


    //============= Implementation Code for Warrior class =======

    //constructor for Warrior inherits from protector
    Warrior::Warrior(const string& name, double num) : Protector(name, num) {}

    //the battle method is overriden from the one in protector
    //but we want to make it pure virtual
    void Warrior::battle() const {
        cout << getName() << " says: Take that in the name of my lord, "
        << getBoss() -> getName() << endl;
    }

    //============= Implementation Code for Swordsman class =======

    //constructor for Swordsman inherits from Warrior
    Swordsman::Swordsman(const string& name, double num) : Warrior(name, num) {}

    //overriden the battle from Warrior(Protector)
    void Swordsman::battle() const {
        cout << "CLANG! ";
        Warrior::battle(); //use the one from warrior class
    }

    //============= Implementation Code for Archer class =======

    //constructor for Archer inherits from Warrior
    Archer::Archer(const string& name, double num) : Warrior(name, num) {}

    //overriden the battle from Warrior(Protector)
    void Archer::battle() const {
        cout << "TWANG! ";
        Warrior::battle(); //use the one from warrior class
    }


}
