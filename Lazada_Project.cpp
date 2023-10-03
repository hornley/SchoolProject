#include<iostream>
#include <map>

using namespace std;

void mapping (string product, int &amount, int price) {
    string add_to_cart;

    cout << "The price for " << amount << " " << product << " is P" << price * amount << "." << endl;
    cout << "Add to cart? (type 'yes' if yes, otherwise 'no'.)\n";
    cin >> add_to_cart;
    if (add_to_cart == "no") {
        amount = 0;
    }
}

int main() {
    string decision, add_to_cart, view_cart, product, checkout_option;
    int chosen_category, sub_category, amount, _x;

    int pen, pencil, yellow_pad, notebook, book;
    int shirt, shorts, pants, polo, hat, hoodie;
    float price, totprice;

    map<string, pair<int, int>> cart;

    cout << "Welcome to Lazada!\n";

    cout << "If you wish to shop, type 'yes', otherwise 'no'.\n";
    cin >> decision;
    do {
        if (decision == "yes" || decision == "Yes") {
            system("cls");
            cout << "Choose category\n";
            cout << "1. School suppplies\n";
            cout << "2. Clothes\n";
            cout << "3. Cosmetics\n";
            cout << "4. Gadgets and accessories\n";
            cout << "5. Jewelry\n";
            cout << "0. Cancel\n";
            cin >> chosen_category;

            system("cls");
            switch (chosen_category) {
                case 1:
                    cout << "Choose a school supplies product:\n";
                    cout << "1. Pen\n";
                    cout << "2. Pencil\n";
                    cout << "3. Yellow Pad\n";
                    cout << "4. Notebook\n";
                    cout << "5. Book\n";
                    cout << "0. Cancel\n";
                    cin >> sub_category;

                    switch (sub_category) {
                        case 1:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Pen";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 2:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 10;
                                product = "Pencil";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 3:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 45;
                                product = "YellowPad";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 4:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 70;
                                product = "Notebook";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 5:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 350;
                                product = "Book";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        default:
                            break;
                    }
                break;
                case 2:
                    cout << "Choose a clothing product:\n";
                    cout << "1. Shirt\n";
                    cout << "2. Short\n";
                    cout << "3. Pants\n";
                    cout << "4. Polo\n";
                    cout << "5. Hat\n";
                    cout << "6. Hoodie\n";
                    cout << "0. Cancel\n";
                    cin >> sub_category;

                    switch (sub_category) {
                        case 1:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Shirt";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 2:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Shorts";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 3:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Pants";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 4:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Polo";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 5:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Hat";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        case 6:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> amount;
                            if (amount >= 1) {
                                system("cls");
                                price = 15;
                                product = "Hoodie";
                                mapping(product, amount, price);
                                if (amount < 1) {
                                    break;
                                }
                                cart[product] = {amount, price};
                            }
                            break;
                        default:
                            break;
                    }
                break;
                case 3:
                    cout << "Choose a cosmetics product:\n";
                    cout << "1. ";
                break;
                case 4:
                    cout << "Gadgets and accessories\n";
                break;
                case 5:
                    cout << "Jewelry\n";
                    break;
                default:
                    break;
            }
            cin.clear();
            system("cls");
            cout << "If you wish buy more, type 'yes', otherwise 'no'.\n";
            cin >> decision;
        }
    } while (decision == "yes");
    
    system("cls");
    cout << "View Cart? type 'yes', otherwise 'no'.\n";  // option 1
    cin >> view_cart;

    if (view_cart == "yes") {
        system("cls");
        map<string, pair<int, int>>::iterator iter;
        cout << "Item\t\tAmount\t\tPrice\t\tTotal\n";
        for (iter = cart.begin(); iter != cart.end(); iter++) {
            if (iter->first == "Notebook" || iter->first == "Yellow Pad") {
                totprice = iter->second.first * iter->second.second;
                cout << iter->first << "\t" << iter->second.first << "\t\t" << iter->second.second << "\t\t" << totprice << endl;
            }
            else {
                totprice = iter->second.first * iter->second.second;
                cout << iter->first << "\t\t" << iter->second.first << "\t\t" << iter->second.second << "\t\t" << totprice << endl;
            }
        }
        cout << "Proceed to checkout? (type 'yes', otherwise 'no'.)\n";
        cin >> checkout_option;

        if (checkout_option == "yes") {
            
        }
        // Proceed to Checkout ---> Payment 
        // Payment ---> Payment confirmation

        
    

    }
}
