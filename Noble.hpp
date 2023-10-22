//
//  Noble.hpp 
//  separate compilation
//  header file for noble class and its children
//

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft{
    class Protector; //foward declaration

    //the class Noble is an abstract class and is inherited by Lord and
    //PersonWithStrengthToFight, it contains fields name, living status, and
    //the total Strength
    class Noble{
    public:
        //constructor for noble class
        Noble(const std::string& name, double num = 0);
        
        //this battle method is to cause battle between two nobles
        void battle(Noble& opponent);
        
        //this is part of the output operator and will output depends on the
        //type of the noble, so it is an pure virtual method
        virtual void display(std::ostream& os) const = 0;
        
        //this method is to check is the noble is alive or not
        bool isAlive() const;
        
        //this method returns the name of the noble
        const std::string& getName() const;
        
        //this returns the total strength of the noble
        double getStrength() const;
        
    protected:
        //this method is to set the total strength and will be called from
        //the derived class to set it (during battle or hire or fire)
        void setTotalStrength(double num);
        
        //this method is to make sure that both kinds of nobles have the defend
        //method and defend in their own way, it is pure abstract
        virtual void defend(double cut) = 0;
        
        //this method is to set the noble's living status to dead when they lose
        //in the battle
        void isDead();
        
    private:
        std::string nobleName;
        bool livingStatus;
        double totalStrength;
        
    };

    class Lord : public Noble{
    public:
        //constructor for Lord class
        Lord(const std::string& name);
        
        //this method is to hire the protector in the noble's army, and will
        //return true if the protector is hired while noble is alive, and false
        //otherwise
        bool hires(Protector& pro);
        
        //this method is to fire the protector, it will return true if it
        //succeeds, and false otherwise
        bool fires(Protector& pro);
        
        //this method is to assist the output operator for lord class
        void display(std::ostream& os) const override;
        
        //this method is to remove the protector from the army and return true
        //or false based on whether the protector is in the army or not
        bool removeProtector(const Protector& pro);
        
        //this method would change the status of the noble if the total strength
        //is 0 and would also change the strength of each warrior in the noble
        void defend(double cut) override;
    private:
        std::vector<Protector*> army;
    };

    //the class PersonWithStrengthToFight is the second type of the noble who is
    // able to fight on his own behalf with his strength
    class PersonWithStrengthToFight : public Noble{
    public:
        //constructor for PersonWithStrengthToFight class
        PersonWithStrengthToFight(const std::string& name, double num);
        
        //this method is to assist the output operator for PersonWithStrengthToFight
        void display(std::ostream& os) const override;
        
        //this defend method is for PersonWithStrengthToFight to fight in his
        //own way,it is overriden from noble and will make battle cry and change
        //his strength and living status accordingly
        void defend(double cut) override;
    };

}

#endif
