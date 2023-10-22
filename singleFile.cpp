//  author: Yingtong(Clue) Deng
//  The purpose of this program is to model the battle game between nobles with
//  their own armies in the medieval times. The noble hires or fires warriors
//  to in order to cause battle with another noble. The warrior could run away.

#include <iostream>
#include <string>
#include <vector>
using namespace std;
    
class Noble; //foward declaration

//The class Warrior is to create the warrior that works for the noble to fight,
//it composes the name and the strength and warrior could be fired or hired by
//the noble or run away
class Warrior{
    friend ostream& operator << (ostream& os, const Warrior& warrior);
public:
    Warrior(const string& name, int strengthNum);
    void changeStrength(double num);
    void hired(Noble& noble);
    void fired();
    double getStrength() const;
    const string& getWarriorName() const;
    bool isHired()  const;
    bool runaway();
    
private:
    string warriorName;
    double strength;
    Noble* boss;

};

//the class Noble has a name and an army(vector) composed of warrior class
//it can hire, fire the warriors and also battle with another noble
class Noble{
    friend ostream& operator << (ostream& os, const Noble& noble);
    void changeTheStrength(double ratio);
public:
    Noble(const string& name);
    const string& getNobleName() const;
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    bool removeWarrior(const Warrior& warrior);
    void battle(Noble& opponent);
    

private:
    string nobleName;
    vector<Warrior*> army;
    bool livingStatus; //if the noble is alive or not
    double totalStrength; //combined strength of all warriors
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

    

            
//============ implementation Code for Warrior class ============

//initialization list for Warrior class
Warrior::Warrior(const string& name, int strengthNum) : warriorName(name),
strength(strengthNum), boss(nullptr) {}

//this method is to change the strength of the warrior
void Warrior::changeStrength(double num){
    strength += num;
}

//this method is to confirm that the warrior is hired by a noble
void Warrior::hired(Noble& noble){
    boss = &noble;
}

//this method is to confirm that the warrior has been fired by his noble
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
bool Warrior::isHired()  const{
    return (boss != nullptr);
}

//this method is to leave the noble and notify him, it will
//return true or false based on if he could run away successfully
bool Warrior::runaway() {
    if (boss){
        cout << warriorName << " flees in terror, abandoning his lord, " <<
        boss -> getNobleName() << endl;
        boss -> removeWarrior(*this);
        boss = nullptr;
        return true;
    }
    //if boss is a nullptr, meaning he is not hired
    cout << warriorName << " is not hired by anyone, so can't run away" << endl;
    return false;
}

//this is the output operator for warrior class that outputs the warrior's name
//and the strength
ostream& operator << (ostream& os, const Warrior& warrior){
    os << "\t\t" << warrior.warriorName << ": " << warrior.strength;
    return os;
}



//============= Implementation Code for Noble class =============

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
            cout << "You don't work for me anymore "<< warrior.getWarriorName()
            << "! -- " << nobleName << "." << endl;
            return true;
        }
        else{
            //if it doesn't return true meaning the warrior is not in the army
            cout << warrior.getWarriorName() << " is not hired by "
            << nobleName << " , so can't be fired" << endl;
        }
    }
    else if (!livingStatus){
        cout << nobleName << " has been dead, can't fire "
        << warrior.getWarriorName() << endl;
    }
    else if (!warrior.isHired()){
        cout << warrior.getWarriorName() << " is not hired by " << nobleName
        << endl;
    }
    //return false for all three cases that can't be fired
    return false;
}

//this method is to remove the warrior from the army and return true or false
//based on whether the warrior is in the army or not
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
