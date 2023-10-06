#include<iostream>
#include<map>
#include<vector>
using namespace std;

void check_stats (string char_name, int level, int hp, int spd, int def, int base_attack ,int bal, int stat_point) {
    cout << "Character " << char_name <<"'s stats (Level " << level << ")" << endl;
    cout << "HP: " << hp << endl;
    cout << "Speed: " << spd << endl;
    cout << "Defense: " << def << endl;
    cout << "Base Attack: " << base_attack << endl;
    cout << "Your current balance is: " << bal << endl;
    if (stat_point >= 1) {
        cout << "Stat points available: " << stat_point << endl;   
    }
}

map<int, pair<vector<string>, vector<int>>>
items_dec () {
    map<int, pair<vector<string>, vector<int>>> items;

	system("cls");
	items[101] = {{"Common", "Rusty Sword", "Weapon", "Sword", "Increase base attack"}, {100, 1, 2}};
	items[102] = {{"Common", "Jagged Bow", "Weapon", "Bow", "Increase base attack"}, {100, 1, 3}};
	items[103] = {{"Common", "Rusty Dagger", "Weapon", "Dagger", "Increase base attack and speed"}, {100, 1, 1, 2}};
	items[104] = {{"Common", "Damaged Helm", "Armor", "Helm", "Increase defence"}, {100, 1, 1}};
	items[105] = {{"Common", "Damaged Chestplate", "Armor", "Chestplate", "Increase defence"}, {100, 1, 2}};
	items[106] = {{"Common", "Damaged Leggings", "Armor", "Leggings", "Increase defence"}, {100, 1, 2}};
	items[107] = {{"Common", "Damaged Boots", "Armor", "Boots", "Increase defence"}, {100, 1, 1}};
    
    return items;
}

int shop () {
    string rarity, name, category, sub_category, effect;
	int effect_nums, cost, lvl_req, item_id, _x = 1;
    map<int, pair<vector<string>, vector<int>>> items = items_dec();

	system("cls");
	map<int, pair<vector<string>, vector<int>>>::iterator iter;

    for (iter = items.begin(); iter != items.end(); iter++) {
        name = iter->second.first.at(1);
        cout << _x << ". " << name << endl;
        _x++;
    }
    cout << "0. Exit Shop\n";

    cout << "\nView Item: ";
	cin >> item_id;
    if (item_id == 0) {
        return item_id;
    }
    item_id += 100;

    

    system("cls");
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (item_id == iter->first) {
            rarity = iter->second.first.at(0);
            name = iter->second.first.at(1);
            category = iter->second.first.at(2);
            sub_category = iter->second.first.at(3);
            effect = iter->second.first.at(4);
            cost = iter->second.second.at(0);
            lvl_req = iter->second.second.at(1);
            effect_nums = iter->second.second.at(2);
            system("cls");
			cout << "Name: " << name << endl;
			cout << "Category: " <<  category << " - ";
			cout << sub_category << endl;
			cout << "Rarity: " <<  rarity << endl;
			cout << "Effect: " <<  effect << " + ";
			cout << effect_nums << endl;
			cout << "Level Requirement: " << lvl_req << endl;
			cout << "Cost: " << cost << endl << endl;
            cout << "Buy this item? (1 for yes)\n";
            cout << "Type 0 to go back.\n";
            return item_id;
		}
	}
    return 0;
}

int main () {
    bool player_turn, enemy_turn, success;
    string char_name, category, name, sub_category;
    int transac, balance_alloted, get_sp, use_sp, to_add, to_add_tot = 0, option;
    int hp, spd, def, base_attack, level, bal, stat_point, exp, exp_required, chp;
    int enemy_hp, enemy_spd, enemy_ba, enemy_def, enemy_level, enemy_reward, exp_gain, echp;

    int action, attack, enhancement, heal;
    int weapon, helm, chestplate, leggings, boots, _back, item_id, cost;
    float damage;

    // cout << "Character name: \n";
    // cin >> char_name;

    // Testing Character Name (Nothing is affected with it)
    char_name = "oms";

    // Player Stats (HP, Speed, Defense, Base Attack, Level, Balance, Stat points, Current exp, Exp needed to level up)
    // The rest uses ITEM_ID for its value, DON'T CHANGE!
    // Weapon (Index 9 or the 10th value/data in player)
    // Armor (Index 10 to 13 or the 11th value/data to 14th value/data in player)
    // Armor has Helm, Chestplate, Leggings, and Boots 
    int player[14] = {100, 36, 0, 1, 1, 1000, 0, 0, 15, 0, 0, 0, 0, 0}; // not equipped = 0, weapon, helm, chestplate, leggings, and boots
    hp = player[0];
    spd = player[1];
    def = player[2];
    base_attack = player[3];
    level= player[4];
    bal = player[5];
    stat_point = player[6];
    exp = player[7];
    exp_required = player[8];
    weapon = player[9];
    helm =  player[10];
    chestplate =  player[11];
    leggings =  player[12];
    boots = player[13];

    // Enemy Stats (HP, Speed, Defense, Base Attack, Level, Money Reward, Experience Reward)
    // THE ONLY ENEMY AS OF THIS MOMENT
    // Everything will change as level changes and with money
    int enemy[7] = {75, 35, 5, 2, 3, 300, 10};
    enemy_hp = enemy[0];
    enemy_spd = enemy[1];
    enemy_def = enemy[2];
    enemy_ba = enemy[3];
    enemy_level = enemy[4];
    enemy_reward = enemy[5];
    exp_gain = player[6];


    system("cls");
    // Check stats, Shop, Battle
    cout << "Choose an Option!\n";
    cout << "1. Shop\n";
    cout << "2. Check stats\n";
    cout << "3. Battle\n";
    cin >> option;
    while (option != 0) {
        system("cls");

        // SHOP OPTION

        if (option == 1) {
            map<int, pair<vector<string>, vector<int>>> items = items_dec();
            item_id = shop();
            if (item_id != 0) {
                cin >> _back;
                if (_back == 1) {
                    system("cls");
                    map<int, pair<vector<string>, vector<int>>>::iterator iter;
                    iter = items.find(item_id);
                    sub_category = iter->second.first.at(3);
                    category = iter->second.first.at(2);
                    name = iter->second.first.at(1);
                    cost = iter->second.second.at(0);
                    if (cost > bal) {
                        cout << "Transaction failed!\nNot Enough Balance!\n" << bal << endl;
                    }
                    else {
                        bal -= cost;
                        cout << name << " successfully bought!\n";
                        cout << "New balance is: " << bal << endl;
                        cout << "Press ENTER to continue.\n";
                        cin.ignore();
                        if (category == "Weapon") {
                            weapon = item_id;
                            if (item_id == 103) {
                                base_attack += 1;
                                spd += 1;
                            }
                            else if (item_id == 102) {
                                base_attack += 3;
                            }
                            else if (item_id == 101) {
                                base_attack += 2;
                            }
                        }
                        else if (sub_category == "Helm") {
                            helm = item_id;
                            def += 1;
                        }
                        else if (sub_category == "Chestplate") {
                            chestplate = item_id;
                            def += 2;
                        }
                        else if (sub_category == "Leggings") {
                            leggings = item_id;
                            def += 2;
                        }
                        else if (sub_category == "Boots") {
                            boots = item_id;
                            def += 1;
                        }
                    }
                    cin.ignore();
                }
                else {
                    shop();
                }
            }
            else {
                system("cls");
                cout << "Choose an Option!\n";
                cout << "1. Shop\n";
                cout << "2. Check stats\n";
                cout << "3. Battle\n";
                cin >> option;
            }
        }

        // CHECK STATS OPTION

        else if (option == 2) {
            check_stats(char_name, level, hp, spd, def, base_attack ,bal, stat_point);
            cout << "\nUse balance to increase stats? (1 for yes and 0 for no)\n";
            cin >> get_sp;

            if (get_sp == 1) {
                system("cls");
                cout << "How much do you want to use? (10 moula : 1 stat point)\n";  // 8 + 2 tax so 10
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
            else {
                system("cls");
                cout << "Choose an Option!\n";
                cout << "1. Shop\n";
                cout << "2. Check stats\n";
                cout << "3. Battle\n";
                cin >> option;
            }
        }
        
        // BATTLE OPTION
        // Fix and or improve
        // To fix: (eto palang alam ko as of this moment)
        // 1. "Your hp" or chp is not properly updated in enemy's damage

        // GO NIYO LANG IF MAY MAS MAGANDA KAYONG WAYS
        // HAVE FUN GUYS!
        // PAG MAY QUESTION CHAT LANG SA GC

        // To improve:
        // After winning get money reward but add "taxes" HAHAHAHHAHAA
        // And add enemy_exp to exp_required and
        // if enemy_exp >= exp_required add 1 level and add 5 stat points

        // If player lost the fight or FORFEIT
        // They lose 90% their current balance

        // Defense implementation
        // Reduces damage (kayo bahala anong ratio, babaan niyo lang syempre baka di naman madamage dahil mataas)

        // Add Choose Enemy 
        // (Pwede muna wag gawin to unless gawa kayo enemies then implement ko yung paglagay ng enemies para madali)
        // (kahit di muna kasi diko pa nalalagyan ng ibang enemies, isip kayo stats ng enemies kung kaya niyo)

        else if (option == 3) {
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

            chp = hp; // Player HP to use for Battling
            echp = enemy_hp; // Enemy max HP
            while (true) {
                if (get_sp == 0) {
                    cin.clear();
                    cin.ignore();
                }

                // Battle Action
                if (player_turn) {
                    system("cls");
                    cout << "Choose an action!\n";
                    cout << "1. Attack\n";
                    cout << "2. Heal\n";
                    cout << "3. Use an Item\n";  // Wala pa to, skip muna
                    cout << "4. Forfeit\n";  // Kung kaya niyo to gawin, GO!
                    cin >> action;

                    // Attack Option
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
                                damage = base_attack * 0.30 * enhancement;
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


                    // Heal Option
                    else if (action == 2) {
                        if (chp > hp * 0.8) { // chp = curent hp ; hp = hp 
                            cout << "You're HP is still above 80%, are you sure?\n";
                            cout << "1 for yes 0 for no\n";
                            cin >> heal;
                            if (heal == 1) {
                                cout << "Heal options (current level " << level << ")\n";
                                cout << " \tCost\tHP Recovery\tRequired Level\n";
                                cout << "1. \t100\t    15\t\t      1\n";
                                cout << "2. \t200\t    40\t\t      5\n";
                                cout << "3. \t400\t    100\t\t      10\n";
                                cout << "4. \t700\t    250\t\t      15\n";
                                cout << "5. \t1000\t    500\t\t      20\n";
                                // cin dito ng chosen option
                                // First is, check kung yung player level is atleast sa "Required Level" ng chosen heal
                                // Second is, check kung may sufficient balance para sa heal
                                // Third is, add the "Hp recovery to chp"
                                // Fourth is, 3/3 lang dapat yung heal per fight so every heal, mababawasan, pag 0 na edi no more heals ang ferson
                            }
                        }
                    }

                    // Forfeit Option
                    else if (action == 4) {

                    }



                // If attack option is successful, enemy's turn na to
                if (success) {
                    enemy_turn = true;
                    player_turn = false;
                    }
                cin.ignore();
                }

                // Enemy Attack na to
                else {
                    damage = (rand() % enemy_ba + 1) * 12.5;
                    cout << "Enemy dealt " << damage << endl;
                    player_turn = true;
                    enemy_turn = false;
                    chp -= damage;
                    cout << "Your HP: " << damage << endl;
                    if (chp <= 0) {
                        cout << "YOU LOST THE FIGHT!\n";
                        cin.clear();
                        cin.ignore();
                        break;
                    }
                    cout << "Press enter to continue!\n";
                    cin.clear();
                    cin.ignore();
                }
            }
        }
        
        else {
            cout << "Invalid option!\n";
            cin.clear();
            cin.ignore();
            return 0;
        }
    }

}
