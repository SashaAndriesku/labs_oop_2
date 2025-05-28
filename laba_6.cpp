#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <locale>
#include <windows.h>
#include <stdexcept>
using namespace std;

class LivingBeing {
protected:
    string name;
    int age;

public:
    LivingBeing() : name("Unknown"), age(0) {}
    LivingBeing(string n, int a) : name(n), age(a) {}
    virtual ~LivingBeing() {}

    virtual void showInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual void greet() const {
        cout << name << " greets you!\n";
    }

    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    int getAge() const { return age; }
};

class Speaker {
public:
    virtual void speak() const = 0;
    virtual ~Speaker() = default;
};

class Animal : public LivingBeing, public Speaker {
protected:
    string breed;
    static int animalCount;

public:
    Animal() : LivingBeing(), breed("Unknown") { animalCount++; }
    Animal(string n, string b, int a) : LivingBeing(n, a), breed(b) { animalCount++; }

    virtual ~Animal() { animalCount--; }

    virtual void showInfo() const override {
        cout << "Animal: " << name << ", Breed: " << breed << ", Age: " << age << " years\n";
    }

    void speak() const override {
        cout << name << " makes a sound!\n";
    }

    friend ostream& operator<<(ostream& os, const Animal& a) {
        os << a.age << "," << a.name << "," << a.breed;
        return os;
    }

    friend istream& operator>>(istream& is, Animal& a) {
        cout << "Name: ";
        is >> a.name;
        cout << "Breed: ";
        is >> a.breed;
        cout << "Age: ";
        is >> a.age;
        return is;
    }

    string getBreed() const { return breed; }

    static int getAnimalCount() { return animalCount; }
};

int Animal::animalCount = 0;

void logAction(const string& action) {
    ofstream log("history.txt", ios::app);
    time_t now = time(0);
    log << ctime(&now) << ": " << action << "\n";
    log.close();
}

void saveAnimalsToFile(const vector<Animal>& animals) {
    ofstream out("animal.txt");
    if (!out) throw runtime_error("Cannot open animal.txt for writing!");
    for (const auto& a : animals) out << a << "\n";
    out.close();
}

void loadAnimalsFromFile(vector<Animal>& animals) {
    ifstream in("animal.txt");
    if (!in) return;
    animals.clear();
    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string ageStr, name, breed;
        if (getline(iss, ageStr, ',') && getline(iss, name, ',') && getline(iss, breed)) {
            animals.emplace_back(name, breed, stoi(ageStr));
        }
    }
    in.close();
}

void adminMenu(vector<Animal>& animals) {
    int choice;
    do {
        cout << "\n[Адмін-меню]\n"
            << "1. Додати тварину\n"
            << "2. Переглянути всіх тварин\n"
            << "3. Зберегти дані\n"
            << "4. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            Animal a;
            cin >> a;
            animals.push_back(a);
            logAction("Адмін додав тварину: " + a.getName());
            break;
        }
        case 2:
            for (const auto& a : animals) a.showInfo();
            break;
        case 3:
            saveAnimalsToFile(animals);
            cout << "Дані збережено у файл animal.txt\n";
            logAction("Адмін зберіг тварин у файл");
            break;
        }
    } while (choice != 4);
}

void userMenu(const vector<Animal>& animals) {
    int choice;
    do {
        cout << "\n[Меню користувача]\n"
            << "1. Переглянути тварин\n"
            << "2. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;
        if (choice == 1) {
            for (const auto& a : animals) a.showInfo();
            logAction("Користувач переглянув список тварин");
        }
    } while (choice != 2);
}

void login(vector<Animal>& animals) {
    cout << "\nУвійти як:\n1. Адміністратор\n2. Користувач\nВаш вибір: ";
    int role;
    cin >> role;
    if (role == 1) {
        string password;
        cout << "Введіть пароль: ";
        cin >> password;
        if (password == "admin123") {
            logAction("Адміністратор увійшов у систему");
            adminMenu(animals);
        }
        else {
            cout << "Невірний пароль!\n";
            logAction("Невдала спроба входу адміністратором");
        }
    }
    else if (role == 2) {
        logAction("Користувач увійшов у систему");
        userMenu(animals);
    }
    else {
        cout << "Невірний вибір!\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    vector<Animal> animals;
    try {
        loadAnimalsFromFile(animals);
        login(animals);
        saveAnimalsToFile(animals);
    }
    catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
        logAction("Виникла помилка: " + string(e.what()));
    }
    return 0;
}