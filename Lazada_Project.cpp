#include<iostream>
#include <map>

using namespace std;
int main() {
    string decision, add_to_cart, view_cart;
    int chosen_category, sub_category, amount, _x;

    int pen, pencil, yellow_pad, notebook, book;
    float price;

    map<string, int> cart;

    cout << "Welcome to Lazada!\n";


    cout << "If you wish to shop, type 'yes', otherwise 'no'.\n";
    cin >> decision;
    do {
        if (decision == "yes" || decision == "Yes") {
            system("cls");
            cout << "Choose category\n";
            cout << "1. School suppplies\n";
            cout << "2. Clothes\n";
            cout << "3. Shoes\n";
            cout << "4. Gadgets and accessories\n";
            cout << "5. Jewelry\n";
            cin >> chosen_category;

            system("cls");
            switch (chosen_category) {
                case 1:
                    cout << "Choose a product:\n";
                    cout << "1. Pen\n";
                    cout << "4. Pencil\n";
                    cout << "2. Yellow Pad\n";
                    cout << "3. Notebook\n";
                    cout << "5. Book\n";
                    cin >> sub_category;

                    switch (sub_category) {
                        case 1:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> pen;
                            if (pen >= 1) {
                                price = pen * 10;
                                cout << "The price for " << pen << " pen is P" << price << endl;
                                cout << "Add to cart? (type 'yes' if yes, otherwise 'no'.)\n";
                                cin >> add_to_cart;
                                if (add_to_cart == "no") {
                                    pen = 0;
                                    break;
                                }
                                cart["Pen"] = pen; 
                            }
                            break;
                        case 2:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> pencil;
                            break;
                        case 3:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> yellow_pad;
                            break;
                        case 4:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> notebook;
                            break;
                        case 5:
                            cout << "How many? (type '0' to cancel)\n";
                            cin >> book;
                            break;
                        default:
                            break;
                            // system("cls");
                            // cout << "INVALID INPUT!\n";
                            // return 0;
                    }
                break;
                case 2:
                    cout << "2. Clothes\n";
                break;
                case 3:
                    cout << "3. Shoes\n";
                break;
                case 4:
                    cout << "4. Gadgets and accessories\n";
                break;
                case 5:
                    cout << "5. Jewelry\n";
                    break;
                default:
                    break;
                    // system("cls");
                    // cout << "INVALID INPUT!\n";
                    // return 0;
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

    map<string, int>::iterator iter;
    for (iter = cart.begin(); iter != cart.end(); iter++) {
        cout << iter->first << " - " << iter->second << endl;
    }
}
