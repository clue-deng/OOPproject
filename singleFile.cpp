//  Final complete single file
//  author: Yingtong(Clue) Deng
//  The purpose of this program is to model the battle game between different
//  types of nobles, and one kind of noble comes with an army of different types
//  of protectors. We use inheritance to achieve this

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Protector; //foward declaration

//the class Noble is an abstract class and is inherited by Lord and
//PersonWithStrengthToFight, it contains fields name, living status, and the
//total Strength
class Noble{
public:
    //constructor for noble class
    Noble(const string& name, double num = 0);
    
    //this battle method is to cause battle between two nobles
    void battle(Noble& opponent);
    
    //this is part of the output operator and will output depends on the type
    //of the noble, so it is an pure virtual method
    virtual void display(ostream& os) const = 0;
    
    //this method is to check is the noble is alive or not
    bool isAlive() const;
    
    //this method returns the name of the noble
    const string& getName() const;
    
    //this returns the total strength of the noble
    double getStrength() const;
    
protected:
    //this method is to set the total strength and will be called from
    //the derived class to set it (during battle or hire or fire)
    void setTotalStrength(double num);
    
    //this method is to make sure that both kinds of nobles have the defend
    //method and defend in their own way, it is pure abstract
    virtual void defend(double cut) = 0;
    
    //this method is to set the noble's living status to dead when they lose in
    //the battle
    void isDead();
    
private:
    string nobleName;
    bool livingStatus;
    double totalStrength;
    
};

class Lord : public Noble{
public:
    //constructor for Lord class
    Lord(const string& name);
    
    //this method is to hire the protector in the noble's army, and will return
    //true if the protector is hired while noble is alive, and false otherwise
    bool hires(Protector& pro);
    
    //this method is to fire the protector, it will return true if it succeeds,
    //and false otherwise
    bool fires(Protector& pro);
    
    //this method is to assist the output operator for lord class
    void display(ostream& os) const override;
    
    //this method is to remove the protector from the army and return true or false
    //based on whether the protector is in the army or not
    bool removeProtector(const Protector& pro);
    
    //this method would change the status of the noble if the total strength is
    //0 and would also change the strength of each warrior in the noble
    void defend(double cut) override;
private:
    vector<Protector*> army;
};

//the class PersonWithStrengthToFight is the second type of the noble who is
// able to fight on his own behalf with his strength
class PersonWithStrengthToFight : public Noble{
public:
    //constructor for PersonWithStrengthToFight class
    PersonWithStrengthToFight(const string& name, double num);
    
    //this method is to assist the output operator for PersonWithStrengthToFight
    void display(ostream& os) const override;
    
    //this defend method is for PersonWithStrengthToFight to fight in his own way,
    //it is overriden from noble and will make battle cry and change his strength
    //and living status accordingly
    void defend(double cut) override;
};

//make the Protector an abstract base class, it contains fields of name,
//strength, and a pointer to its lord
class Protector{
    //output operator for Protector class
    friend ostream& operator << (ostream& os, const Protector& rhs);
    
public:
    //constructor for protector class
    Protector(const string& name, double num);

    //this returns whether or not the protector is hired
    bool isHired() const;
    
    //this sets the protector hired by the lord, gets the pointer of the lord
    void hired(Lord& lord);
    
    //this sets the protector unhired, the pointer becomes nullptr
    void fired();
    
    //this returns the name of the protector
    const string& getName() const;
    
    //this returns the strength of the protector
    double getStrength() const;
    
    //this returns the pointer of the lord of the protector
    Lord* getBoss() const;
    
    //this pure virtual method is for each different protector to make their own
    //battle cry
    virtual void battle() const = 0;
    
    //this method is to change the strength of the protector
    void changeStrength(double deduction);
    
    //this method is for the protector to leave their boss and notify them
    bool runaway();
    
private:
    string ProName;
    double strength;
    Lord* boss;
};

//class Wizard publicly inherits from the protector and fights in his way
class Wizard : public Protector{
public:
    //constructor for Wizard inherits from protector
    Wizard(const string& name, double num);
    
    //battle cry for wizard
    void battle() const;
};
 
//class Warrior publicly inherits from the protector and is the abstract base
//class for Swordsman and Archer
class Warrior : public Protector{
public:
    //constructor for Warrior inherits from protector
    Warrior(const string& name, double num);
    
    //the battle method is overriden from the one in protector
    //but we want to make it pure virtual so warrior is abstract
    virtual void battle() const = 0;
};


//class Swordsman publicly inherits from Warrior
class Swordsman : public Warrior{
public:
    //constructor for Swordsman inherits from Warrior
    Swordsman(const string& name, double num);
    
    //overriden the battle from Warrior(Protector)
    void battle() const override;
};


//class Archer publicly inherits from Warrior
class Archer : public Warrior{
public:
    //constructor for Archer inherits from Warrior
    Archer(const string& name, double num);
    
    //overriden the battle from Warrior(Protector)
    void battle() const override;
};


/*  Your classes go here */

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}


//============= Implementation Code for Noble base class =============

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
            defend(-1); //initiate the battle cry/output by passing an undefined
            //value, i only use -1 instead of ratio1 (undefiend value) because
            //it runs in my program as undefined but not sure about others
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
            army[i] -> battle(); //initiate the battle cry
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
    else if (!isAlive()){ //noble is not alive
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
        if (removeProtector(pro)){ //if you actually hire the protector
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
    cout << "Ugh!" << endl; //make the battle cry too when cut is undefined (-1)
    if (cut >= 1){
        setTotalStrength(-(getStrength()));
        isDead();
    }
    else if (cut > 0 && cut < 1){
        setTotalStrength(-cut * getStrength());
    }
}

//============= Implementation Code for Protector class =======

//constructor for protector class
Protector::Protector(const string& name, double num) : ProName(name), strength(num)
, boss(nullptr) {}

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
    
//this returns the pointer to the lord of the protector
Lord* Protector::getBoss() const{
    return boss;
}

//this method is to make the battle cry and change the strength of the protector
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

