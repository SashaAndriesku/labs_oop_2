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
    static int animalCount;

public:
    Animal() : name("Unknown"), breed("Unknown"), age(0) { animalCount++; }
    Animal(string n, string b, int a) : name(n), breed(b), age(a) { animalCount++; }
    Animal(string n) : Animal(n, "Unknown", 0) {}

    Animal(const Animal& other) : name(other.name), breed(other.breed), age(other.age) {
        cout << "Copy constructor called for " << name << endl;
        animalCount++;
    }

    Animal(Animal&& other) noexcept : name(move(other.name)), breed(move(other.breed)), age(other.age) {
        cout << "Move constructor called for " << name << endl;
        other.age = 0;
    }

    ~Animal() {
        cout << "Animal " << name << " has been deleted\n";
        animalCount--;
    }

    void showInfo() const {
        cout << "Animal: " << name << ", Breed: " << breed << ", Age: " << age << " years\n";
    }

    void setName(const string& n) { this->name = n; }
    static int getAnimalCount() { return animalCount; }

    Animal& operator++() {
        ++age;
        return *this;
    }

    Animal operator+(const Animal& other) const {
        return Animal(name + "-Mix", breed + "-Mix", (age + other.age) / 2);
    }

    friend ostream& operator<<(ostream& os, const Animal& a) {
        os << "Animal: " << a.name << ", Breed: " << a.breed << ", Age: " << a.age;
        return os;
    }

    friend istream& operator>>(istream& is, Animal& a) {
        cout << "Enter name: "; is >> a.name;
        cout << "Enter breed: "; is >> a.breed;
        cout << "Enter age: "; is >> a.age;
        return is;
    }
};

int Animal::animalCount = 0;

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
    Animal cat("Murka", "Siamese", 5);
    Animal mixed = dog + cat;

    Adopter adopter("Oleksandr", 25, "+380123456789");
    Shelter shelter("Good Friend", "Kyiv, Lisova St. 5", 50);

    dog.showInfo();
    cat.showInfo();
    mixed.showInfo();
    adopter.showInfo();
    shelter.showInfo();

    cout << "Total animals: " << Animal::getAnimalCount() << endl;

    cout << "Incrementing dog's age..." << endl;
    ++dog;
    dog.showInfo();

    cout << "Enter new animal details:\n";
    Animal newAnimal;
    cin >> newAnimal;
    cout << newAnimal << endl;

    return 0;
}
