#include<iostream>
using namespace std;

void check_stats (string char_name, int level, int hp, int spd, int def, int bal, int stat_point) {
    cout << "Character " << char_name <<"'s stats (Level " << level << ")" << endl;
    cout << "HP: " << hp << endl;
    cout << "Speed: " << spd << endl;
    cout << "Defense: " << def << endl;
    cout << "Your current balance is: " << bal << endl;
    if (stat_point >= 1) {
        cout << "Stat points available: " << stat_point << endl;   
    }

}

main () {
    bool player_turn, enemy_turn, success;
    string char_name;
    int transac, balance_alloted, get_sp, use_sp, to_add, to_add_tot = 0;
    int hp, spd, def, base_attack, level, bal, stat_point, exp, exp_required, chp;
    int enemy_hp, enemy_spd, enemy_ba;

    int action, attack, enhancement, heal;
    float damage;

    // cout << "Character name: \n";
    // cin >> char_name;

    char_name = "oms";

    int player[9] = {100, 36, 0, 1, 1, 1000, 0, 0, 15};
    hp = player[0];
    spd = player[1];
    def = player[2];
    base_attack = player[3];
    level= player[4];
    bal = player[5];
    stat_point = player[6];
    exp = player[7];
    exp_required = player[8];

    int enemy[7] = {75, 35, 5, 3, 3, 300, 10};
    enemy_hp = enemy[0];
    enemy_spd = enemy[1];
    enemy_ba = enemy[3];
    exp = player[6];


    system("cls");
    check_stats(char_name, level, hp, spd, def, bal, stat_point);
    cout << "\nUse balance to increase stats? (1 for yes and 0 for no)\n";
    cin >> get_sp;

    if (get_sp == 1) {
        system("cls");
        cout << "How much do you want to use? (10 moula : 1 stat point)\n";
        cin >> balance_alloted;
        if (balance_alloted > bal) {
            cout << "You are not that rich! PEASANT!\n";
        }
        else {
            bal -= balance_alloted;
            bal += balance_alloted % 10;
            stat_point = balance_alloted / 10;
        }
        system("cls");
        cout << "You have currently have " << stat_point << " stat points.\n";
        cout << "Do you want to use your stat points? (1 for yes and 0 for no)\n";
        cin >> use_sp;

        if (use_sp == 1) {
            do {
            cout << "Input amount to add\n";
            cout << "HP: ";
            cin >> to_add;
            to_add_tot += to_add;
            if (to_add_tot > stat_point) {
                cout << "You only have " << stat_point << " stat points!\n"; // not yet done
            }
            hp += to_add;
            } while (true);
        }
    }
    
    // player first turn
    if (spd > enemy_spd) {
        player_turn = true;
        enemy_turn = false;
    }

    // enemy first turn
    else {
        player_turn = false;
        enemy_turn = true;
    }

    chp = hp; // player hp to use for battling
    while (true) {
        if (get_sp == 0) {
            cin.clear();
            cin.ignore();
        }

        // Damaging
        if (player_turn) {
            system("cls");
            cout << "Choose an action!\n";
            cout << "1. Attack\n";
            cout << "2. Heal\n";
            cout << "3. Use an Item\n";
            cout << "4. Forfeit\n";
            cin >> action;

            if (action == 1) {
                system("cls");
                cout << "Choose an attack!\n";
                cout << "1. Money enhanced attack\n";
                cout << "2. Normal attack\n";
                cin >> attack;
                system("cls;");
                if (attack == 1) {
                    cout << "You currently have: " << bal << " in your balance.\n";
                    cout << "How much do you want to use to enhance you attack?\n";
                    cin >> enhancement;
                    if (enhancement > bal) {
                        cout << "You don't have enough balance for that!\n";
                    }
                    else {
                        damage = base_attack * 0.10 * enhancement;
                        success = true;
                    }
                }
                else if (attack == 2) {
                    damage = base_attack;
                    success = true;
                }
                else {
                    cin.clear();
                }
                if (success) {
                    cout << "You dealt " << damage << endl;
                    enemy_hp -= damage;
                    cout << "Enemy's HP: " << enemy_hp << endl;
                    if (enemy_hp <= 0) {
                        cout << "YOU WON THE FIGHT!\n";
                        break;
                    }
                }
            }

            else if (action == 2) {
                if (chp > hp * 0.8) { // chp = curent hp ; hp = hp 
                    cout << "You're HP is still above 80%, are you sure?\n";
                    cout << "1 for yes 0 for no\n";
                    cin >> heal;
                    if (heal == 1) {
                        cout << "Heal options (current level " << level << ")\n";
                        cout << "Cost\tHP Recovery\tRequired Level\n";
                        cout << "100\t    15\t\t      1\n";
                        cout << "200\t    40\t\t      5\n";
                        cout << "400\t    100\t\t      10\n";
                        cout << "700\t    250\t\t      15\n";
                        cout << "1000\t    500\t\t      20\n";
                    }
                }
            }
        if (success) {
            enemy_turn = true;
            player_turn = false;
            }
        cout << "Press enter to continue!\n";
        cin.ignore();
        }

        else {
            damage = (rand() % enemy_ba + 1) * 12.5;
            cout << "Enemy dealt " << damage << endl;
            player_turn = true;
            enemy_turn = false;
            chp -= damage;
            cout << "Your HP: " << damage << endl;
            cout << "Press enter to continue!\n";
            if (chp <= 0) {
                cout << "YOU LOST THE FIGHT!\n";
                break;
            }
        }

    }
}
