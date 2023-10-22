//
//  Protector.hpp
//  separate compilation
//
//  Created by Yingtong Deng on 4/14/22.
//

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <string>

namespace WarriorCraft{
    class Lord; //foward declaration

    //make the Protector an abstract base class, it contains fields of name,
    //strength, and a pointer to its lord
    class Protector{
        //output operator for Protector class
        friend std::ostream& operator << (std::ostream& os, const Protector& rhs);
        
    public:
        //constructor for protector class
        Protector(const std::string& name, double num);

        //this returns whether or not the protector is hired
        bool isHired() const;
        
        //this sets the protector hired and gets the pointer of the lord
        void hired(Lord& lord);
        
        //this sets the protector unhired, the pointer becomes nullptr
        void fired();
        
        //this returns the name of the protector
        const std::string& getName() const;
        
        //this returns the strength of the protector
        double getStrength() const;
        
        //this returns the pointer of the lord of the protector
        Lord* getBoss() const;
        
        //this pure virtual method is for each different protector to make their
        //own battle cry
        virtual void battle() const = 0;
        
        //this method is to change the strength of the protector
        void changeStrength(double deduction);
        
        //this method is for the protector to leave their boss and notify them
        bool runaway();
        
    private:
        std::string ProName;
        double strength;
        Lord* boss;
    };

    //class Wizard publicly inherits from the protector and fights in his way
    class Wizard : public Protector{
    public:
        //constructor for Wizard inherits from protector
        Wizard(const std::string& name, double num);
        
        //battle cry for wizard
        void battle() const;
    };
     
    //class Warrior publicly inherits from the protector and is the abstract
    //basew class for Swordsman and Archer
    class Warrior : public Protector{
    public:
        //constructor for Warrior inherits from protector
        Warrior(const std::string& name, double num);
        
        //the battle method is overriden from the one in protector
        //but we want to make it pure virtual so warrior is abstract
        virtual void battle() const = 0;
    };


    //class Swordsman publicly inherits from Warrior
    class Swordsman : public Warrior{
    public:
        //constructor for Swordsman inherits from Warrior
        Swordsman(const std::string& name, double num);
        
        //overriden the battle from Warrior(Protector)
        void battle() const override;
    };


    //class Archer publicly inherits from Warrior
    class Archer : public Warrior{
    public:
        //constructor for Archer inherits from Warrior
        Archer(const std::string& name, double num);
        
        //overriden the battle from Warrior(Protector)
        void battle() const override;
    };
}

#endif
