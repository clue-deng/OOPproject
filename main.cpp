//authpr: Yingtong(Clue) Deng
//hw03
//The purpose of this file is to read into warriors.txt to identify the warriors in the file with their names and weapons, and then put the warriors in a fight to change their according strength.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//class Warrior stores weapons and the warrior's name. it will tells weapons to change its strength and some part may change according to the fight
class Warrior{
    class Weapon;
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
    
public:
    //initialization of the Warrior object
    Warrior(const string& name, const string& weaponname, int weaponpower): warriorName(name), theWeapon(weaponname, weaponpower) {}
    
    //this method is to get and return the name of the warrior and it shouldn't return a copy
    const string& getName() const {
        return warriorName;
    }
    
    //this method is to get and return the strength of the weapon from the Weapon class, it is int so it should return the value
    int getStrength() const{
        return theWeapon.obtainStrength();
    }
    
    //this is to change the strength of the weapon from the fight with the other warrior, pass the task to Weapon class
    void changeStrength(int opponentStrength){
        int originalStrength = theWeapon.obtainStrength();
        if (originalStrength >= opponentStrength){
            theWeapon.change_the_strength(opponentStrength);
        }
        else{ //if the strength is less than the opponent's, then it would go to zero, meaning subtracting itself
            theWeapon.change_the_strength(originalStrength);
        }
    }
    
    //this method is to cause the battle between the two warriors inside, and it is passed in the opponent's Warrior object
    void battle(Warrior& opponent){
        int w1_strength = getStrength();
        int w2_strength =opponent.getStrength();
            
        if (w1_strength == w2_strength){
            if (w1_strength == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else{
                changeStrength(w2_strength);
                opponent.changeStrength(w1_strength);
                cout << "Mutual Annihillation: " << getName() << " and " << opponent.getName() << " die at each other's hands" << endl;
            }
        }
        else if (w1_strength > w2_strength){
            if (w2_strength == 0){
                cout << "He's dead, " << getName() << endl;
            }
            else{
                changeStrength(w2_strength);
                opponent.changeStrength(w1_strength);
                cout << getName()<< " defeats " << opponent.getName() << endl;
            }
        }
        else if (w1_strength < w2_strength){
            if (w1_strength == 0){
                cout << "He's dead, " << opponent.getName() << endl;
            }
            else{
                changeStrength(w2_strength);
                opponent.changeStrength(w1_strength);
                cout << opponent.getName()<< " defeats " << getName() << endl;
            }
        }
    }
    
private:
    //class Weapon is a nesting private class in Warrior that will store the strength and the name of the weapon
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& weapon);
    public:
        //initialization of the Weapon object
        Weapon(const string& aname,  int strengthnum): weaponName(aname), strength(strengthnum) {}
        
        //this is to pass the strength from the weapon to Warrior's getStrength() and return the int strength
        int obtainStrength() const{
            return strength;
        }
        
        //this method is to change the strength of the original strength after battling against the other warrior
        void change_the_strength(int other_strength){
            strength -= other_strength;
        }
        
    private:
        int strength;
        string weaponName;
    };
    
    string warriorName;
    Weapon theWeapon;

};

void fill_vector(vector<Warrior>& warriorv, const string& warrior_name, const string& weapon_name, int givenStrength);

size_t find_warrior(const string& warrior_name, const vector<Warrior>& warriorv);

void causeBattle(size_t place1, size_t place2, vector<Warrior>& warriorv);

void print_out_status(const vector<Warrior>& warriorv);


int main() {
    ifstream warriorfile("warriors.txt");
    if (!warriorfile){
        cerr << "failed to open warriors.txt" << endl;
        exit(1);
    }
    
    string commands;
    string warrior_name;
    string weapon_name;
    int givenStrength;
    string statusLine;
    vector<Warrior> warriorv;
    string warrior1; //name of the first warrior
    string warrior2; //name of the second warrior
    size_t nameRepetition; //check repetition of the name
    size_t place1; //record place 1 for warrior1
    size_t place2; //record place 2 for warrior2
    
    while (warriorfile >> commands){
        if (commands == "Warrior"){
            warriorfile >> warrior_name >> weapon_name >> givenStrength;
            nameRepetition = find_warrior(warrior_name, warriorv);
            if (nameRepetition == warriorv.size()){
                fill_vector(warriorv, warrior_name, weapon_name, givenStrength);
            }
            else{
                cout << warrior_name << " has been added before" << endl;
            }
        }
        else if (commands == "Battle"){
            warriorfile >> warrior1 >> warrior2;
                place1 = find_warrior(warrior1, warriorv);
                place2 = find_warrior(warrior2, warriorv);
                causeBattle(place1, place2, warriorv);
        }
        else if (commands == "Status"){
            print_out_status(warriorv);
            getline(warriorfile, statusLine);
        }
    }
    warriorfile.close();
}


//this function is to fill in the warrior vector with warrior information (name and weapon) and to check if the warrior is not in the vector before
void fill_vector(vector<Warrior>& warriorv, const string& warrior_name, const string& weapon_name, int givenStrength){
        warriorv.emplace_back(warrior_name, weapon_name, givenStrength); //create the warrior object with all the fields together
}


//this function is to find and return the place (size_t) of where the warrior is in the vector, it functions as to check the existence of the warrior, the repetition of the name, and the place of the warrior
size_t find_warrior(const string& warrior_name, const vector<Warrior>& warriorv){
    size_t place = warriorv.size();
    for (size_t ind = 0; ind < warriorv.size(); ++ind){
        if (warrior_name == warriorv[ind].getName()){
            place = ind;
        }
    }
    return place;
}

//this function is to cause battle between two existing warrior that might result a change in the strength of each warrior, it will call the method on the first warrior. It also prints out error messege for non existing warriors
void causeBattle(size_t place1, size_t place2, vector<Warrior>& warriorv){
    if (place1 != warriorv.size() && place2 != warriorv.size()){
        cout << warriorv[place1].getName() << " battles " << warriorv[place2].getName() << endl;
        warriorv[place1].battle(warriorv[place2]);
    }
    else if (place1 == warriorv.size() && place2 == warriorv.size()){
        cout << "Both warriors don't exist." << endl;
    }
    else if (place1 == warriorv.size()){
        cout << warriorv[place1] << " doesn't exist." << endl;
    }
    else if (place2 == warriorv.size()){
        cout << warriorv[place2] << " doesn't exist." << endl;
    }
}

//this function is to print out the status of all of warriors with respective weapons in the warrior vector
void print_out_status(const vector<Warrior>& warriorv){
    cout << "There are: " << warriorv.size() << " warriors" << endl;
    for (const Warrior& warrior: warriorv){
        cout << warrior;
    }
}


//this is the output operator in class Weapon to get the name and strength of weapon
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon){
    os << weapon.weaponName << ", " << weapon.strength;
    return os;
}

//this will output the things from weapon also the name of the warrior
ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "Warrior: " << warrior.warriorName << ", weapon: " << warrior.theWeapon << endl;
    return os;
}
