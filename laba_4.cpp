#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
using namespace std;

class LivingBeing {
protected:
    string name;
    int age;

public:
    LivingBeing() : name("Unknown"), age(0) {}
    LivingBeing(string n, int a) : name(n), age(a) {}
    LivingBeing(const LivingBeing& other) : name(other.name), age(other.age) {}
    LivingBeing(LivingBeing&& other) noexcept : name(move(other.name)), age(other.age) {}
    virtual ~LivingBeing() {
        cout << "LivingBeing " << name << " has been deleted\n";
    }

    virtual void showInfo() const {
        cout << "Name: " << name << ", Age: " << age << " years\n";
    }

    void setName(const string& n) { name = n; }
    int getAge() const { return age; }
};

class Animal : public LivingBeing {
protected:
    string breed;
    static int animalCount;

public:
    Animal() : LivingBeing(), breed("Unknown") { animalCount++; }
    Animal(string n, string b, int a) : LivingBeing(n, a), breed(b) { animalCount++; }
    Animal(string n) : Animal(n, "Unknown", 0) {}

    Animal(const Animal& other) : LivingBeing(other), breed(other.breed) {
        cout << "Copy constructor called for Animal: " << name << endl;
        animalCount++;
    }

    Animal(Animal&& other) noexcept : LivingBeing(move(other)), breed(move(other.breed)) {
        cout << "Move constructor called for Animal: " << name << endl;
    }

    Animal& operator=(const Animal& other) {
        if (this != &other) {
            LivingBeing::operator=(other);
            breed = other.breed;
        }
        return *this;
    }

    Animal& operator=(Animal&& other) noexcept {
        if (this != &other) {
            LivingBeing::operator=(move(other));
            breed = move(other.breed);
        }
        return *this;
    }

    virtual ~Animal() {
        cout << "Animal " << name << " has been deleted\n";
        animalCount--;
    }

    virtual void showInfo() const override {
        cout << "Animal: " << name << ", Breed: " << breed << ", Age: " << age << " years\n";
    }

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

    static int getAnimalCount() { return animalCount; }
};

int Animal::animalCount = 0;

class Dog : public Animal {
private:
    string favoriteToy;

public:
    Dog() : Animal(), favoriteToy("Ball") {}
    Dog(string n, string b, int a, string toy) : Animal(n, b, a), favoriteToy(toy) {}

    void showInfo() const override {
        Animal::showInfo();
        cout << "Favorite Toy: " << favoriteToy << endl;
    }
};

class Cat : public Animal {
private:
    bool isIndoor;

public:
    Cat() : Animal(), isIndoor(true) {}
    Cat(string n, string b, int a, bool indoor) : Animal(n, b, a), isIndoor(indoor) {}

    void showInfo() const override {
        Animal::showInfo();
        cout << "Indoor Cat: " << (isIndoor ? "Yes" : "No") << endl;
    }
};

class Person : public LivingBeing {
protected:
    string phoneNumber;

public:
    Person() : LivingBeing(), phoneNumber("Unknown") {}
    Person(string n, int a, string p) : LivingBeing(n, a), phoneNumber(p) {}

    virtual void showInfo() const override {
        LivingBeing::showInfo();
        cout << "Phone: " << phoneNumber << endl;
    }
};

class Adopter : public Person {
public:
    Adopter() : Person() {}
    Adopter(string fn, int a, string pn) : Person(fn, a, pn) {}
    Adopter(string fn) : Person(fn, 18, "Unknown") {}

    ~Adopter() {
        cout << "Adopter " << name << " has been deleted\n";
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

    Dog dog("Barsik", "Labrador", 3, "Bone");
    Cat cat("Murka", "Siamese", 5, true);
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
