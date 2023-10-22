//
//  Noble.cpp
//
//  Created by Yingtong Deng on 3/12/22.
//

#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft{
    //Constructor to initialize fields in Noble object
    Noble::Noble(const string& name): nobleName(name), livingStatus(true),
    totalStrength(0), army() {}

    //this method returns the name of the noble
    const string& Noble::getNobleName() const{
        return nobleName;
    }
        
    //this method is to hire the warrior in the noble's army, and will return
    //true if the warrior is hired while noble is alive, and false otherwise
    bool Noble::hire(Warrior& warrior){
        //make sure noble is alive and warrior is unhired
        if (livingStatus && !warrior.isHired()){
            army.push_back(&warrior);
            warrior.hired(*this);
            totalStrength += warrior.getStrength();
            return true;
        }
        else if (!livingStatus){ //noble is not alive
            cout << nobleName << " has been dead, can't hire "
            << warrior.getWarriorName() << endl;
        }
        else if (warrior.isHired()){ //warrior is hired by others
            cout << "Attempt to hire " << warrior.getWarriorName()
            << " by " << nobleName << " failed!" << endl;
        }
        //return false for the two cases that can't be hired
        return false;
    }

    //this method is to fire the warrior, it will return true if it succeeds,
    //and false otherwise
    bool Noble::fire(Warrior& warrior){
        if (livingStatus && warrior.isHired()){
            if (removeWarrior(warrior)){
                warrior.fired();
                cout << "You don't work for me anymore "
                << warrior.getWarriorName()
                << "! -- " << nobleName << "." << endl;
                return true;
            }
            else{
                //if it doesn't return true then the warrior's not in the army
                cout << warrior.getWarriorName() << " is not hired by "
                << nobleName << " , so can't be fired" << endl;
            }
        }
        else if (!livingStatus){
            cout << nobleName << " has been dead, can't fire "
            << warrior.getWarriorName() << endl;
        }
        else if (!warrior.isHired()){
            cout << warrior.getWarriorName() << " is not hired by anyone"
            << endl;
        }
        //return false for all three cases that can't be fired
        return false;
    }


    //this method is to remove the warrior from the army and return true or
    //false based on whether the warrior is in the army or not
    bool Noble::removeWarrior(const Warrior& warrior){
        size_t position = army.size();
        //this for loop finds and records the position of the warrior
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == &warrior){
                position = i;
                break;
            }
        }
        if (position != army.size()){
            //this for loop shift up the next pointer one position before
            //the last warriors will appear twice
            for (size_t curr = position; curr < army.size() - 1; ++curr){
                army[curr] = army[curr + 1]; //shift up the pointer
            }
            army.pop_back(); //pop back the repeated pointer
            totalStrength -= warrior.getStrength();
            return true;
        }
        return false;
    }

    //this method would initiate a battle between nobles and pass them into
    //the changeTheStrength method to update the noble's and the warrior's
    //living status or relative strengths
    void Noble::battle(Noble& opponent) {
        cout << nobleName << " battles " << opponent.nobleName << endl;
        double ratio1 = totalStrength / opponent.totalStrength;
        double ratio2 = opponent.totalStrength / totalStrength;
        if (opponent.totalStrength > totalStrength){
            if (!livingStatus){
                cout << "He's dead, " << opponent.nobleName << endl;
            }
            else{
                opponent.changeTheStrength(ratio1);
                changeTheStrength(ratio2);
                cout << opponent.nobleName << " defeats " << nobleName
                    << endl;
            }
        }
        else if (opponent.totalStrength < totalStrength){
            if (!opponent.livingStatus){
                cout << "He's dead, " << nobleName << endl;
            }
            else{
                opponent.changeTheStrength(ratio1);
                changeTheStrength(ratio2);
                cout << nobleName << " defeats " << opponent.nobleName
                    << endl;
            }
        }
        else{
            if (!livingStatus && !opponent.livingStatus){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else{
                cout << "Mutual Annihillation: " << nobleName << " and "
                    << opponent.nobleName << " die at each other's hands"
                    << endl;
                opponent.changeTheStrength(ratio1);
                changeTheStrength(ratio2);
            }
        }
    }

    //this method would change the status of the noble if the total strength is
    //0 and would also change the strength of each warrior in the noble
    void Noble::changeTheStrength(double ratio) {
        for (size_t i = 0; i < army.size() ; ++i){
        //if the ratio >= 1, they lose or draw, the noble and the army are dead
            if (ratio >= 1){
                //each warrior subtracts his own strength and set to 0
                army[i] -> changeStrength(-(army[i] -> getStrength()));
            }
            else{
        //if the ratio < 1, they win but the army and noble lose some strength
                army[i] -> changeStrength(-ratio * (army[i] -> getStrength()));
                totalStrength -= army.size() * ratio;
            }
        }
        //update that the noble is dead if he loses
        if (ratio >= 1){
            totalStrength = 0;
            livingStatus = false;
        }
    }

    //this will output the army of the noble that states the number of warriors
    //and the name and strength of the warriors through delegation
    ostream& operator << (ostream& os, const Noble& noble){
        os << noble.nobleName << " has an army of " << noble.army.size();
        for (const Warrior* warriorptr : noble.army){ //print out every warrior
            os << endl << *warriorptr;
        }
        os << endl;
        return os;
    }
}
