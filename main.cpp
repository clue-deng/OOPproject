//  author: Yingtong(Clue) Deng
//  The purpose of this program is to simulate a battle game in medieval times.
//  we will read into the file and create Noble and Warrior object. The noble
//  hires or fires warriors to in order to cause battle with another noble.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior;
class Noble;
size_t find_noble(const string& name, const vector<Noble*>& noblev);
size_t find_warrior(const string& name, const vector<Warrior*>& warriorv);
bool create_noble(const string& name, vector<Noble*>& noblev);
bool create_warrior(const string& name, int strength, vector<Warrior*>& warriorv);
void hire_command(const string& nobleName, const string& warriorName,
    vector<Noble*>& noblev, vector<Warrior*>& warriorv);
void fire_command(const string& nobleName, const string& warriorName,
    vector<Noble*>& noblev, vector<Warrior*>& warriorv);
void cause_battle(const string& initiator, const string& opponent,
    vector<Noble*>& noblev);
void print_status(const vector<Noble*>& noblev, const vector<Warrior*>& warriorv);
void clear_command(vector<Noble*>& noblev, vector<Warrior*>& warriorv);

//The class Warrior is to create the warrior that works for the noble to fight,
//it composes its name and the strength and could be fired or hired by the noble
class Warrior{
    friend ostream& operator<<(ostream& os,const Warrior& warrior);
public:
    //Warrior Construtor to initialize
    Warrior(const string& name, int strengthNum): warriorName(name),
    strength(strengthNum), hiring(false) {}
    
    //this method is to change the strength of the warrior after the battle
    void changeStrength(double num){
        strength += num;
    }
    
    //this method is to confirm that the warrior is hired by a noble
    void hired(){
        hiring = true;
    }
    
    //this method is to confirm that the warrior has been fired by his noble
    void fired() {
        hiring = false;
    }
    
    //this returns the strength of the warrior
    double getStrength() const {
        return strength;
    }
    
    //this method returns the name of the warrior's name
    const string& getWarriorName() const{
        return warriorName;
    }
    
    //this method returns the hiring/firing status of the warrior
    bool isHired()  const{
        return hiring;
    }
    
private:
    string warriorName;
    double strength;
    bool hiring; //if the warrior is hired or not
};

//the class Noble has a name and an army(vector) composed of warrior class
//it can hire, fire the warriors and also battle with another noble
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble);
    
public:
    //Constructor to initialize fields in Noble object
    Noble(const string& name): nobleName(name), livingStatus(true),
    totalStrength(0), army() {}
    
    //this method returns the name of the noble
    const string& getNobleName() const{
        return nobleName;
    }
    
    //this method is to hire the warrior in the noble's army, and will return
    //true if the warrior is hired while noble is alive, and false otherwise
    bool hire(Warrior& warrior){
        //make sure noble is alive and warrior is unhired
        if (livingStatus && !warrior.isHired()){
            army.push_back(&warrior);
            warrior.hired();
            totalStrength += warrior.getStrength();
            return true;
        }
        else if (!livingStatus){ //noble is not alive
            cout << nobleName << " has been dead, can't hire " << warrior.getWarriorName() << endl;
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
    bool fire(Warrior& warrior){
        if (livingStatus && warrior.isHired()){
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
                army.pop_back();
                warrior.fired();
                totalStrength -= warrior.getStrength();
                cout << "You don't work for me anymore " << warrior.getWarriorName() << "! -- " << nobleName << "."
                << endl;
                return true;
            }
            //if it doesn't return true meaning the warrior is not in the army
            cout << warrior.getWarriorName() << " is not hired by "
            << nobleName << " , so can't be fired" << endl;
        }
        else if (!livingStatus){
            cout << nobleName << " has been dead, can't fire " << warrior.getWarriorName() << endl;
        }
        else if (!warrior.isHired()){
            cout << warrior.getWarriorName() << " is not hired by " << nobleName
            << endl;
        }
        //return false for all three cases that can't be fired
        return false;
    }
    
    //this method would initiate a battle between nobles and pass them into
    //the changeTheStrength method to update the noble's and the warrior's
    //living status or relative strengths
    void battle(Noble& opponent) {
        cout << nobleName << " battles " << opponent.nobleName << endl;
        double ratio1 = totalStrength / opponent.totalStrength;
        double ratio2 = opponent.totalStrength / totalStrength;
        if (opponent.totalStrength > totalStrength){
            if (livingStatus == false){
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
            if (opponent.livingStatus == false){
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
            if (livingStatus == false && opponent.livingStatus == false){
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
    void changeTheStrength(double ratio) {
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
         
private:
    string nobleName;
    vector<Warrior*> army;
    bool livingStatus; //if the noble is alive or not
    double totalStrength; //combined strength of all warriors
};


int main() {
    ifstream nobleWarrior("nobleWarriors.txt");
    if (!nobleWarrior){
        cerr << "failed to open the file nobleWarriors.txt" << endl;
        exit(1);
    }
    
    string commandline;
    string noble_name;
    string opponent;
    string warrior_name;
    int strength;
    vector<Noble*> noblev;
    vector<Warrior*> warriorv;
    bool can_run;

    while (nobleWarrior >> commandline){
        if (commandline == "Noble"){
            nobleWarrior >> noble_name;
            can_run = create_noble(noble_name, noblev);
            if (!can_run){
                cout << noble_name << " has already existed" << endl;
             }
        }
        if (commandline == "Warrior"){
            nobleWarrior >> warrior_name >> strength;
            can_run = create_warrior(warrior_name, strength, warriorv);
            if (!can_run){
                cout << warrior_name << " has already existed" << endl;
            }
        }
        if (commandline == "Hire"){
            nobleWarrior >> noble_name >> warrior_name;
            hire_command(noble_name, warrior_name, noblev, warriorv);
        }
        if (commandline == "Fire"){
            nobleWarrior >> noble_name >> warrior_name;
            fire_command(noble_name, warrior_name, noblev, warriorv);
        }
        if (commandline == "Battle"){
            nobleWarrior >> noble_name >> opponent;
            cause_battle(noble_name, opponent, noblev);
        }
        if (commandline == "Status"){
            print_status(noblev, warriorv);
        }
        //two for loops to clear the pointer vectors
        if (commandline == "Clear"){
            clear_command(noblev, warriorv);
            warriorv.clear();
            noblev.clear();
        }
    }
    nobleWarrior.close();
}
    
//this is the output operator for warrior class that outputs the warrior's name
//and the strength
ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "\t\t" << warrior.warriorName << ": " << warrior.strength;
    return os;
}
            
//this will output the army of the noble that states the number of warriors
//and the name and strength of the warriors through delegation
ostream& operator<<(ostream& os, const Noble& noble){
    os << noble.nobleName << " has an army of " << noble.army.size();
    for (const Warrior* warriorptr : noble.army){ //print out every warrior
        os << endl << *warriorptr;
    }
    return os;
}

//this function will call the find_noble to check existence and create the noble
//if it doesn't exist and return if it is created
bool create_noble(const string& name, vector<Noble*>& noblev){
    size_t place = find_noble(name, noblev);
    if (place == noblev.size()){
        noblev.push_back(new Noble(name));
        return true;
    }
    else{
        return false;
    }
}

//this function will call the find_warrior to check existence and create the
//warrior if it doesn't exist and return if it is created
bool create_warrior(const string& name, int strength, vector<Warrior*>& warriorv){
    size_t place = find_warrior(name, warriorv);
    if (place == warriorv.size()){
        warriorv.push_back(new Warrior(name, strength));
        return true;
    }
    else{
        return false;
    }
}


//this method is to find and return the index of the address of the the noble
size_t find_noble(const string& name, const vector<Noble*>& noblev){
    for (size_t i = 0; i < noblev.size(); ++i){
        if (name == noblev[i] -> getNobleName()){
            return i;
        }
    }
    return noblev.size();
}

//this method is to find and return the index of the address of the warrior
size_t find_warrior(const string& name, const vector<Warrior*>& warriorv){
    for (size_t i = 0; i < warriorv.size(); ++i){
        if (name == (warriorv[i] -> getWarriorName())){
            return i;
        }
    }
    return warriorv.size();
}

//this function handles the hire command and will handle errors when either
//noble or warrior or both do not exist
void hire_command(const string& nobleName, const string& warriorName,
    vector<Noble*>& noblev, vector<Warrior*>& warriorv){
    size_t place1 = find_noble(nobleName, noblev);
    size_t place2 = find_warrior(warriorName, warriorv);
    if (place1 != noblev.size() && place2 != warriorv.size()){
        noblev[place1] -> hire(*warriorv[place2]);
    }
    else if (place1 == noblev.size()){
        cout << nobleName << " does not exist" << endl;
    }
    else if (place2 == warriorv.size()){
        cout << "Attempting to hire using unknown warrior: " << warriorName
        << endl;
    }
    else if (place1 == noblev.size() && place2 == warriorv.size()){
        cout << nobleName << " and " << warriorName << "don't exist" << endl;
    }
}

//this function handles the fire command and will handle errors when either
//noble or warrior or both do not exist
void fire_command(const string& nobleName, const string& warriorName,
    vector<Noble*>& noblev, vector<Warrior*>& warriorv){
    size_t place1 = find_noble(nobleName, noblev);
    size_t place2 = find_warrior(warriorName, warriorv);
    if (place1 != noblev.size() && place2 != warriorv.size()){
        noblev[place1] -> fire(*warriorv[place2]);
    }
    else if (place1 == noblev.size()){
        cout << nobleName << " does not exist" << endl;
    }
    else if (place2 == warriorv.size()){
        cout << "Attempting to fire using unknown warrior: " << warriorName
        << endl;
    }
    else if (place1 == noblev.size() && place2 == warriorv.size()){
        cout << nobleName << " and " << warriorName << "don't exist" << endl;
    }
}

    
//this function causes battles between two nobles and handles error when either
//one or both do not exist
void cause_battle(const string& initiator, const string& opponent,
vector<Noble*>& noblev){
    size_t place1 = find_noble(initiator, noblev);
    size_t place2 = find_noble(opponent, noblev);
    if (place1 != noblev.size() && place2 != noblev.size()){
        noblev[place1] -> battle(*noblev[place2]);
    }
    else if (place1 == noblev.size()){
        cout << initiator << " does not exist" << endl;
    }
    else if (place2 == noblev.size()){
        cout << opponent << " does not exist" << endl;
    }
    else if (place1 == noblev.size() && place2 == noblev.size()){
        cout << initiator << " and " << opponent << "don't exist" << endl;
    }
}
    
//this function deals with the Status command and print out the status of each
//noble with their armies and unemployed warriors
void print_status(const vector<Noble*>& noblev, const vector<Warrior*>& warriorv){
    cout << "Status \n======\n";
    cout << "Nobles:" << endl;
    //print out the nobles
    if (noblev.size() == 0){
        cout << "NONE" << endl;
    }
    else{
        // this for loop print out the status of each noble
        for (const Noble* nobleptr : noblev){
            cout << *nobleptr << endl;
        }
    }
    //print out the unemployed warriors
    cout << "\nUnemployed Warriors:" << endl;
    int unemploy_count = 0; //count unemployed warriors
    for (const Warrior* warriorptr : warriorv){
        if (!warriorptr -> isHired()){ //detects if there is any unemployed
            cout << *warriorptr << endl; //warrior and print out
            unemploy_count += 1;       //their information
        }
    }
    //if there is no unemployed warrior
    if (unemploy_count == 0){
        cout << "NONE" << endl;
    }
}

//this function deals with the clear command and will delete each object of the
//pointer in noblev or warriorv is pointing to
void clear_command(vector<Noble*>& noblev, vector<Warrior*>& warriorv){
    for (size_t i = 0; i < warriorv.size(); ++i){ //delete the warrior object
        delete warriorv[i];
        warriorv[i] = nullptr;
    }
    
    for (size_t i = 0; i < noblev.size(); ++i){ //delete the noble object
        delete noblev[i];
        noblev[i] = nullptr;
    }
}



