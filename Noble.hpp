//
//  Noble.hpp
//
//  Created by Yingtong Deng on 3/12/22.
//

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft{
    
    class Warrior; //foward declaration

    //the class Noble has a name and an army(vector) composed of warrior class
    //it can hire, fire the warriors and also battle with another noble
    class Noble{
        //overload output operator
        friend std::ostream& operator << (std::ostream& os, const Noble& noble);
        //this method would change the strength of the warrior and noble after
        //the war
        void changeTheStrength(double ratio);
    public:
        //constructor for Noble class
        Noble(const std::string& name);
        //this returns the name of the noble
        const std::string& getNobleName() const;
        //this will hire the warrior into the army and return a bool
        bool hire(Warrior& warrior);
        //this will fire the warrior from the army and return a bool
        bool fire(Warrior& warrior);
        //this helper func will remove the warrior from the army and return a bool
        bool removeWarrior(const Warrior& warrior);
        //this method is to cause a fight between two nobles
        void battle(Noble& opponent);
        

    private:
        std::string nobleName;
        std::vector<Warrior*> army;
        bool livingStatus; //if the noble is alive or not
        double totalStrength; //combined strength of all warriors
    };
}

#endif
