//
//  Noble.cpp
//  hw7 - separate compilation
//
//  Created by 邓映彤 on 4/14/22.
//

#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft{

    //============= Implementation Code for Noble class =============
    //constructor for Noble class
    Noble::Noble(const string& name, double num) : nobleName(name),
    livingStatus(true), totalStrength(num){}

    //this method would initiate a battle between nobles and pass them into
    //the defend method to update the noble's (and the protector's)
    //living status or relative strengths
    void Noble::battle(Noble& opponent){
        cout << nobleName << " battles " << opponent.nobleName << endl;
        
        double ratio1 = opponent.totalStrength / totalStrength;
        double ratio2 = totalStrength / opponent.totalStrength;
        
        if (totalStrength > opponent.totalStrength){
            if (!opponent.livingStatus){
                defend(-1); //make the battle cry/output by passing an undefined
                //value, i only use -1 instead of the undefiend ratio1 because
                //it runs in my program as undefined but not yours
                cout << "He's dead, " << nobleName << endl;
            }
            else{
                defend(ratio1);
                opponent.defend(ratio2);
                cout << getName() << " defeats " << opponent.getName() << endl;
            }
        }
        
        else if (totalStrength < opponent.totalStrength){
            if (!livingStatus){
                opponent.defend(-1); //make the battle cry by passing an
                //undefined value, same reason for passing in -1
                cout << "He's dead, " << opponent.nobleName << endl;
            }
            else{
                defend(ratio1);
                opponent.defend(ratio2);
                cout << opponent.getName() << " defeats " << getName() << endl;
            }
        }
        else {
            if (!livingStatus && !opponent.livingStatus){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else{
                opponent.defend(ratio2);
                defend(ratio1);
                cout << "Mutual Annihillation: " << nobleName << " and "
                    << opponent.nobleName << " die at each other's hands"
                    << endl;
            }
        }
    }

    //This returns the living status of the Noble
    bool Noble::isAlive() const {
        return livingStatus;
    }

    //this method returns the name of the noble
    const string& Noble::getName() const{
        return nobleName;
    }

    //this returns the total strength of the noble
    double Noble::getStrength() const{
        return totalStrength;
    }

    //this method is to set the total strength and will be called from
    //the derived class to set it (during battle or hire or fire), protected the
    //dervied class from other dervied class
    void Noble::setTotalStrength(double num){
        totalStrength += num;
    }

    //this method is to set the noble's living status to dead when they lose in
    // the battle
    void Noble::isDead(){
        livingStatus = false;
    }

    //output operator for Noble, will call the display method of the noble
    ostream& operator<<(ostream& os, const Noble& rhs){
        rhs.display(os);
        return os;
    }

    //============= Implementation Code for Lord class =============

    //constructor for Lord class
    Lord::Lord(const string& name) : Noble(name), army() {}

    //this method is to assist the output operator for lord class
    void Lord::display(ostream& os) const{
        os << getName() << " has an army of : " << army.size() << endl;
        for (const Protector* lhs: army){
            os << *lhs << endl;
        }
    }

    //this method would change the status of the noble if the total strength is
    //0 and would also change the strength of each warrior in the noble
    void Lord::defend(double cut) {
        for (size_t i = 0; i < army.size(); ++i){
            if (cut >= 1){ //if the cut is over 1, lord loses and dies
                army[i] -> changeStrength(-(army[i] -> getStrength()));
            }
            else if (cut > 0 && cut < 1){ //if the cut is within 0 and 1, lord wins
                setTotalStrength(-cut * (army[i] -> getStrength()));
                army[i] -> changeStrength(-cut * (army[i] -> getStrength()));
            }
            else{ //if cut is undefined, meaning the other noble is dead
                army[i] -> battle();
            }
        }
        if (cut >= 1){
            setTotalStrength(-getStrength());
            isDead();
        }
    }

    //this method is to hire the protector in the noble's army, and will return
    //true if the protector is hired while noble is alive, and false otherwise
    bool Lord::hires(Protector& pro){
        if (isAlive() && !pro.isHired()){
            army.push_back(&pro);
            pro.hired(*this);
            setTotalStrength(pro.getStrength());
            return true;
        }
        else if (!isAlive()){//noble is not alive
            cout << getName() << " has been dead, can't hire "
            << pro.getName() << endl;
        }
        else if (pro.isHired()){ //warrior is hired by others
            cout << "Attempt to hire " << pro.getName()
            << " by " << getName() << " failed!" << endl;
        }
        //return false for the two cases that can't be hired
        return false;
    }

    //this method is to fire the protector, it will return true if it succeeds,
    //and false otherwise
    bool Lord::fires(Protector& pro){
        if (isAlive() && pro.isHired()){
            if (removeProtector(pro)){
                pro.fired();
                cout << "You don't work for me anymore "<< pro.getName()
                << "! -- " << getName() << "." << endl;
                return true;
            }
            else{
                //if it doesn't return true meaning the warrior is not in the army
                cout << pro.getName() << " is not hired by "
                << getName() << " , so can't be fired" << endl;
            }
        }
        else if (!isAlive()){
            cout << getName()<< " has been dead, can't fire "
            << pro.getName() << endl;
        }
        else if (!pro.isHired()){
            cout << pro.getName() << " is not hired by anyone" << endl;
        }
        //return false for all three cases that can't be fired
        return false;
    }

    //this method is to remove the protector from the army and return true or false
    //based on whether the protector is in the army or not
    bool Lord::removeProtector(const Protector& pro){
        size_t position = army.size();
        //this for loop finds and records the position of the warrior
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == &pro){
                position = i;
                break;
            }
        }
        if (position != army.size()){
            //this for loop shift up the next pointer one position before
            //the last protector will appear twice
            for (size_t curr = position; curr < army.size() - 1; ++curr){
                army[curr] = army[curr + 1]; //shift up the pointer
            }
            army.pop_back(); //pop back the repeated pointer
            setTotalStrength(-pro.getStrength());//deduce strength
            return true;
        }
        return false; //return false protector is not hired by you
    }


    //============= Implementation Code for PersonWithStrengthToFight class =======

    //constructor for PersonWithStrengthToFight class
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name,
    double num) : Noble(name, num){}

    //this method is to assist the output operator for PersonWithStrengthToFight
    void PersonWithStrengthToFight::display(ostream& os) const {
        os << getName() << " is fighting with his own strength " << getStrength();
    }

    //this defend method is for PersonWithStrengthToFight to fight in his own way,
    //it is overriden from noble and will make battle cry and change his strength
    //and living status accordingly
    void PersonWithStrengthToFight::defend(double cut) {
        cout << "Ugh!" << endl;//make the battle cry too when cut is undefined
        if (cut >= 1){
            setTotalStrength(-(getStrength()));
            isDead();
        }
        else if (cut > 0 && cut < 1){
            setTotalStrength(-cut * getStrength());
        }
    }

}
