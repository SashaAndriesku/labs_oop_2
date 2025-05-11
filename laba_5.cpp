#include <iostream>
#include <string>
using namespace std;

class IInteractable {
public:
    virtual void interact() const = 0;
    virtual ~IInteractable() = default;
};

class LivingBeing {
protected:
    string name;
    int age;

public:
    LivingBeing() : name("Unknown"), age(0) {}
    LivingBeing(const string& n, int a) : name(n), age(a) {}
    LivingBeing(const LivingBeing& other) = default;
    LivingBeing(LivingBeing&& other) noexcept = default;
    LivingBeing& operator=(const LivingBeing& other) = default;
    LivingBeing& operator=(LivingBeing&& other) noexcept = default;
    virtual ~LivingBeing() {
        cout << "LivingBeing " << name << " has been deleted\n";
    }

    virtual void showInfo() const {
        cout << "Name: " << name << ", Age: " << age << " years\n";
    }

    virtual void speak() const {
        cout << name << " makes a sound.\n";
    }

    virtual void move() const {
        cout << name << " is moving.\n";
    }
};

class Animal : public LivingBeing, public IInteractable {
protected:
    string breed;
    static int animalCount;

public:
    Animal() : LivingBeing(), breed("Unknown") { animalCount++; }
    Animal(const string& n, const string& b, int a) : LivingBeing(n, a), breed(b) { animalCount++; }
    Animal(const Animal& other) = default;
    Animal(Animal&& other) noexcept = default;
    Animal& operator=(const Animal& other) = default;
    Animal& operator=(Animal&& other) noexcept = default;
    virtual ~Animal() {
        cout << "Animal " << name << " has been deleted\n";
        animalCount--;
    }

    void showInfo() const override {
        cout << "Animal: " << name << ", Breed: " << breed << ", Age: " << age << " years\n";
    }

    void speak() const override {
        cout << name << " makes an animal sound.\n";
    }

    void move() const override {
        cout << name << " the animal moves.\n";
    }

    void interact() const override {
        cout << name << " interacts with you.\n";
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
};

int Animal::animalCount = 0;

int main() {
    LivingBeing lb("Being", 5);
    lb.showInfo();
    lb.move();

    Animal a1("Leo", "Cat", 3);
    Animal a2("Max", "Dog", 5);

    a1.showInfo();
    a1.move();
    a1.interact();

    Animal a3 = a1 + a2;
    cout << a3 << endl;

    ++a1;
    cout << a1 << endl;

    return 0;
}
