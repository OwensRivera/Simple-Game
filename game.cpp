#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Hacker {
    string name;
    int health;
    int attackPower;
    int defense;
    int baseDefense;
    bool specialReady;
};

// Display hacker status
void showStatus(const Hacker& h) {
    cout << "Hacker: " << h.name << endl;
    cout << "Health: " << h.health << endl;
    cout << "Attack: " << h.attackPower << endl;
    cout << "Defense: " << h.defense << endl;
    cout << "Special Ready: " << (h.specialReady ? "Yes" : "No") << endl;
    cout << "-------------------------------------" << endl;
}

bool isAlive(const Hacker& h) {
    return h.health > 0;
}

void resetDefense(Hacker& h) {
    h.defense = h.baseDefense;
}

int rollVariance(int spread) {
    return (rand() % (spread * 2 + 1)) - spread;
}

void attack(Hacker& attacker, Hacker& defender) {
    const int variance = rollVariance(3);
    int damage = attacker.attackPower + variance - defender.defense;

    if (damage < 0) {
        damage = 0;
    }

    defender.health -= damage;
    if (defender.health < 0) {
        defender.health = 0;
    }

    cout << attacker.name << " launches an exploit attack on " << defender.name << "!" << endl;
    cout << "Damage dealt: " << damage << endl;
    cout << defender.name << "'s health is now " << defender.health << "\n" << endl;
}

int readPlayerChoice() {
    while (true) {
        cout << "Choose your action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defend (reduce incoming damage)" << endl;
        cout << "Enter choice: ";

        int choice = 0;
        if (cin >> choice && (choice == 1 || choice == 2)) {
            return choice;
        }

        cout << "Please enter 1 or 2." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Hacker player = {"Owen", 100, 20, 5, 5, true};
    Hacker enemy = {"ShadowGhost", 100, 15, 4, 4, true};

    cout << "== Welcome to Cyberpunk Hacker Battle! ==" << endl;

    while (isAlive(player) && isAlive(enemy)) {
        cout << "\n--- Your Turn ---" << endl;
        showStatus(player);
        showStatus(enemy);

        const int choice = readPlayerChoice();
        if (choice == 1) {
            attack(player, enemy);
        } else {
            cout << player.name << " is defending this turn!" << endl;
            player.defense += 3;
        }

        if (!isAlive(enemy)) {
            cout << enemy.name << " has been defeated! YOU WIN!" << endl;
            break;
        }

        cout << "--- Enemy Turn ---" << endl;
        const int enemyChoice = rand() % 2;

        if (enemyChoice == 0) {
            attack(enemy, player);
        } else {
            cout << enemy.name << " is defending!" << endl;
            enemy.defense += 3;
        }

        if (!isAlive(player)) {
            cout << player.name << " has been defeated! GAME OVER." << endl;
            break;
        }

        resetDefense(player);
        resetDefense(enemy);
    }

    return 0;
}
