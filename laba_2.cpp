#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
using namespace std;


class Animal {
private:
    string name;
    string breed;
    int age;

public:
    
    Animal() : name("Unknown"), breed("Unknown"), age(0) {}

    
    Animal(string n, string b, int a) : name(n), breed(b), age(a) {}

    
    Animal(string n) : Animal(n, "Unknown", 0) {}

    
    ~Animal() {
        cout << "Animal " << name << " has been deleted\n";
    }

    
    void showInfo() const {
        cout << "Animal: " << name << ", Breed: " << breed << ", Age: " << age << " years\n";
    }
};


class Adopter {
private:
    string fullName;
    int age;
    string phoneNumber;

public:
    
    Adopter() : fullName("Unknown"), age(0), phoneNumber("Unknown") {}

    
    Adopter(string fn, int a, string pn) : fullName(fn), age(a), phoneNumber(pn) {}

    
    Adopter(string fn) : Adopter(fn, 18, "Unknown") {}

    
    ~Adopter() {
        cout << "Adopter " << fullName << " has been deleted\n";
    }

    
    void showInfo() const {
        cout << "Adopter: " << fullName << ", Age: " << age << ", Phone: " << phoneNumber << endl;
    }
};


class Shelter {
private:
    string name;
    string address;
    int capacity;

public:
    
    Shelter() : name("Unknown"), address("Unknown"), capacity(0) {}

    
    Shelter(string n, string a, int c) : name(n), address(a), capacity(c) {}

    
    Shelter(string n) : Shelter(n, "Unknown", 10) {}

    
    ~Shelter() {
        cout << "Shelter " << name << " has been deleted\n";
    }

    
    void showInfo() const {
        cout << "Shelter: " << name << ", Address: " << address << ", Capacity: " << capacity << endl;
    }
};


int main() {
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Animal dog("Barsik", "Labrador", 3);
    Adopter adopter("Oleksandr", 25, "+380123456789");
    Shelter shelter("Good Friend", "Kyiv, Lisova St. 5", 50);

    dog.showInfo();
    adopter.showInfo();
    shelter.showInfo();

    return 0;
}
