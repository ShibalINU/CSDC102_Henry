#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
    string name;
    int season;
    string engine;
    int weight;
    int hybridSystem;
    int totalDisplacement;
    string maxTurboChargerSpeed;

public:
    // Constructor
    Car(string n, int s, string e, int w, int h, int d, string m)
    {
        name = n;
        season = s;
        engine = e;
        weight = w;
        hybridSystem = h;
        totalDisplacement = d;
        maxTurboChargerSpeed = m;
    }

    // Getters
    string getName() { return name; }
    int getWeight() { return weight; }

    void setWeight(int w)
    {
        if (w > 0)
        {
            weight = w;
        }
        else
        {
            cout << "[ERROR] Invalid weight (" << w
                 << ") for car: " << name << " [using old weight]" << endl;
        }
    }

    void upgradeEngine()
    {
        cout << name << " engine updragaded" << endl;
    }

    bool isHighPerformance()
    {
        return (weight <= 800 && hybridSystem == 1);
    }

    // Display method
    void displayInfo()
    {
        cout << "=========================" << endl;
        cout << "Car Name: " << name << endl;
        cout << "Season: " << season << endl;
        cout << "Engine: " << engine << endl;
        cout << "Weight: " << weight << endl;
        cout << "Hybrid System: " << hybridSystem << endl;
        cout << "Displacement: " << totalDisplacement << endl;
        cout << "Max Turbo Speed: " << maxTurboChargerSpeed << endl;
        cout << "High Performance: " << (isHighPerformance() ? "Yes" : "No") << endl;
    }
};
struct Driver
{
    string name;
    string team;
    int age;
    int wins;
    int WdcTitle;
    string bestLapTime;
    string bestLapTimeTrack;
};

struct Constructor
{
    string teamName;
    string teamPrincipal;
    int championships;
    int wins;
    int podiums;
    int totalPoints;
    int yearsActive;
};

void printDriver(const Driver &c);
void printConstructor(const Constructor &c);
void printCar(const Car &c);

int main()
{

    Driver drivers[3];

    drivers[0] = {"Lewis Hamilton", "Ferrari", 41, 105, 7, "1:18.887", "Monza"};
    drivers[1] = {"Charles Leclerc", "Ferrari", 27, 8, 0, "1:19.000", "Monza"};
    drivers[2] = {"Max Verstappen", "Red Bull", 27, 60, 3, "1:17.500", "Spa"};

    Constructor constructors[3];

    constructors[0] = {"Ferrari", "Fred Vasseur", 16, 240, 800, 9000, 70};
    constructors[1] = {"Red Bull Racing", "Christian Horner", 6, 120, 300, 7000, 20};
    constructors[2] = {"Mercedes", "Toto Wolff", 8, 130, 350, 7500, 15};

    Car c1("Ferrari SF-26", 2026, "V6 Turbo Hybrid", 798, 1, 1600, "125000 RPM");
    Car c2("Red Bull RB26", 2026, "V6 Turbo Hybrid", 798, 1, 1600, "125000 RPM");
    Car c3("Mercedes W16", 2026, "V6 Turbo Hybrid", 798, 1, 1600, "125000 RPM");

    cout << "--------------------------------ALL CARS--------------------------------" << endl;
    c1.displayInfo();
    c2.displayInfo();
    c3.displayInfo();

    cout << endl;

    cout << "=========================Upgrades=========================" << endl;
    c1.upgradeEngine();
    c2.upgradeEngine();
    c3.upgradeEngine();

    cout << endl;

    cout << "=========================Weight changs=========================" << endl;
    c1.setWeight(790);
    c2.setWeight(-100);
    c3.setWeight(800);

    cout << endl;

    cout << c1.getName() << " weighs " << c1.getWeight() << " kg." << endl;
    cout << c2.getName() << " weighs " << c2.getWeight() << " kg." << endl;
    cout << c3.getName() << " weighs " << c3.getWeight() << " kg." << endl;

    cout << "--------------------------------ALL DRIVERS--------------------------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Driver: " << i + 1 << endl;
        printDriver(drivers[i]);
        cout << endl;
    }

    cout << "--------------------------------ALL CONSTRUCTORS--------------------------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Constructors: " << i + 1 << endl;
        printConstructor(constructors[i]);
        cout << endl;
    }

    return 0;
}

void printDriver(const Driver &c)
{
    cout << "=========================" << endl;
    cout << "Name: " << c.name << endl;
    cout << "Team: " << c.team << endl;
    cout << "Age: " << c.age << endl;
    cout << "Wins: " << c.wins << endl;
    cout << "WDC Titles: " << c.WdcTitle << endl;
    cout << "Best Lap Time: " << c.bestLapTime << endl;
    cout << "Track: " << c.bestLapTimeTrack << endl;
}
void printConstructor(const Constructor &c)
{
    cout << "=========================" << endl;
    cout << "Team Name: " << c.teamName << endl;
    cout << "Team Principal: " << c.teamPrincipal << endl;
    cout << "Championships: " << c.championships << endl;
    cout << "Wins: " << c.wins << endl;
    cout << "Podiums: " << c.podiums << endl;
    cout << "Total Points: " << c.totalPoints << endl;
    cout << "Years Active: " << c.yearsActive << endl;
}
