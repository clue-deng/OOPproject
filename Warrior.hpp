//
//  Warrior.hpp
//
//  Created by Yingtong Deng on 3/12/22.
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft{

    class Noble; //foward declaration
    
//The class Warrior is to create the warrior that works for the noble to fight,
//it composes the name and the strength and warrior could be fired or hired by
//the noble or run away
    class Warrior{
        //overload output operator
        friend std::ostream& operator << (std::ostream& os, const Warrior& warrior);
    public:
        //constructor for Warrior class
        Warrior(const std::string& name, int strengthNum);
        //this method changes the strength of the warrior
        void changeStrength(double num);
        //this method will get the warrior hired
        void hired(Noble& noble);
        //this method will get the warrior fired
        void fired();
        //this return the strength of the warrior
        double getStrength() const;
        //this return the name of the warrior
        const std::string& getWarriorName() const;
        //this return whether the warrior is hired or not
        bool isHired()  const;
        //this method is for warrior to leave the noble and notify him
        bool runaway();
        
    private:
        std::string warriorName;
        double strength;
        Noble* boss;
    };
}

#endif
