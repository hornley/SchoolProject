#include<iostream>
#include<string>
#include <map>
#include<vector>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int total_amount;

map<string, vector<pair<string, int>>> products;

void TIP()
{
    HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 6); //Change color of School Name
    cout<<"                        Technological Institute of The Philippines          \n";
    SetConsoleTextAttribute(hConsole, 7); //Return to while color
    cout<<"                                    Project: TIP LAZADA                \n"; 
    cout << "\n****************************************************************************************\n";
}

void mapping (string product, int &amount, int price) {
    string add_to_cart;
    TIP();
    cout << "\nThe price for " << amount << " " << product << " is P" << price * amount << "." << endl;

    cout << "\nAdd to cart? (type 'yes' if yes, otherwise 'no'.)\n";
    cin >> add_to_cart;
    if (add_to_cart == "no") {
        amount = 0;
    }
   else if (add_to_cart =="yes")
        {
            total_amount += price * amount;
        }
    
}



void addProducts()
{                                                  
    products["Pen"].push_back(make_pair           ("Gel Pen                            ", 21));
    products["Pen"].push_back(make_pair           ("HBW-2000                           ", 15));
    products["Pen"].push_back(make_pair           ("Parker                             ", 17));
    products["Pen"].push_back(make_pair           ("Panda                              ", 13));
    products["Pencil"].push_back(make_pair        ("Mongol                             ", 7));
    products["Pencil"].push_back(make_pair        ("Faber-Castell                      ", 28));    
    products["Paper"].push_back(make_pair         ("Yellow Pad                         ", 25));
    products["Paper"].push_back(make_pair         ("Whole                              ", 35));
    products["Paper"].push_back(make_pair         ("1/2 Yellow Pad                     ", 20));
    products["Paper"].push_back(make_pair         ("Index Card                         ", 10));
    products["Notebook"].push_back(make_pair      ("Spiral Notebook                    ", 45));
    products["Notebook"].push_back(make_pair      ("Leather Notebook                   ", 60));
    products["Notebook"].push_back(make_pair      ("Math Notebook                      ", 30));
    products["Notebook"].push_back(make_pair      ("Music Notebook                     ", 32));
    products["Book"].push_back(make_pair          ("MATLAB Book                        ", 250));
    products["Book"].push_back(make_pair          ("UTS Book                           ", 235));
    products["Book"].push_back(make_pair          ("Number Theory Book                 ", 2480));
    products["Book"].push_back(make_pair          (" Math in Modern World Book         ", 260));
    products["Book"].push_back(make_pair          ("C++ Programming First Year Handbook", 272));
    products["Book"].push_back(make_pair          ("C++ Algorithm First Year Handbook  ", 272));
    
    
}


int main() {
    string decision, add_to_cart, view_cart, product, checkout_option, productChosen;
    int chosen_category, sub_category, amount, _xa;

    int pen, pencil, yellow_pad, notebook, book;
    int shirt, shorts, pants, polo, hat, hoodie;
    float price, totprice;

    int paymentMethod;
    addProducts();

    map<string, pair<int, int>> cart;

    system("cls");
    TIP();
    cout << "Welcome to TIP Lazada!\n";

    cout << "If you wish to shop, type 'yes', otherwise 'no'.\n";
    cin >> decision;
    do {
        if (decision == "yes" || decision == "Yes") {
            vector<string> oms;
            vector<int> omsim;
            system("cls");
            TIP();
            cout << "Choose category\n";
            cout << "1. Pen\n";
            cout << "2. Pencil\n";
            cout << "3. Paper\n";
            cout << "4. Notebook\n";
            cout << "5. Book\n";
            cout << "0. Cancel\n";
            cin >> chosen_category;
            cout << "\n****************************************************************************************\n\n";

            system("cls");
            switch (chosen_category) {
                case 1:
                    product = "Pen";
                    _xa = 1;
                    TIP();
                    cout << "Choose a pen product:\n";
                    for (auto iter = products["Pen"].begin(); iter != products["Pen"].end(); iter++)
                    {
                        cout << _xa << ". " << iter->first << endl;
                        oms.push_back(iter->first);
                        omsim.push_back(iter->second);
                        _xa++;
                    }
                    cout << "0. Cancel\n";
                    cin >> sub_category;
                    
                    system("cls");
                    TIP();
                    cout << "Category:\t" << product << endl;
                    cout << "Product:\t" << oms[sub_category - 1] << endl;
                    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

                    cout << "\nHow many? (type '0' to cancel)\n";
                    cin >> amount;
                    if (amount >= 1) {
                        system("cls");
                        price = omsim[sub_category - 1];
                        mapping(product, amount, price);
                        if (amount < 1) {
                            break;
                        }
                        cart[oms[sub_category - 1]] = {amount, price};
                    }
                break;
                
                  case 2:
                    product = "Pencil";
                    _xa = 1;
                    TIP();
                    cout << "Choose a pencil product:\n";
                    for (auto iter = products[product].begin(); iter != products[product].end(); iter++)
                    {
                        cout << _xa << ". " << iter->first << endl;
                        oms.push_back(iter->first);
                        omsim.push_back(iter->second);
                        _xa++;
                    }
                    cout << "0. Cancel\n";
                    cin >> sub_category;

                    system("cls");
                    TIP();
                    cout << "Category:\t" << product << endl;
                    cout << "Product:\t" << oms[sub_category - 1] << endl;
                    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

                    cout << "\nHow many? (type '0' to cancel)\n";
                    cin >> amount;
                    if (amount >= 1) {
                        system("cls");
                        price = omsim[sub_category - 1];
                        mapping(product, amount, price);
                        if (amount < 1) {
                            break;
                        }
                        cart[oms[sub_category - 1]] = {amount, price};
                    }
                break;

                
                //Josiah Case 3 update

                case 3:
                    product = "Paper";
                    _xa = 1;
                    TIP();
                    cout << "Choose a paper product:\n";
                    for (auto iter = products[product].begin(); iter != products[product].end(); iter++)
                    {
                        cout << _xa << ". " << iter->first << endl;
                        oms.push_back(iter->first);
                        omsim.push_back(iter->second);
                        _xa++;
                    }
                    cout << "0. Cancel\n";
                    cin >> sub_category;

                    system("cls");
                    TIP();
                    cout << "Category:\t" << product << endl;
                    cout << "Product:\t" << oms[sub_category - 1] << endl;
                    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

                    cout << "\nHow many? (type '0' to cancel)\n";
                    cin >> amount;
                    if (amount >= 1) {
                        system("cls");
                        price = omsim[sub_category - 1];
                        mapping(product, amount, price);
                        if (amount < 1) {
                            break;
                        }
                        cart[oms[sub_category - 1]] = {amount, price};
                    }
                break;

                // Josiah - Case 4
                case 4:
                    TIP();
                    cout << "Choose a Notebook product:\n";
                    product = "Notebook";
                    _xa = 1;
                    for (auto iter = products[product].begin(); iter != products[product].end(); iter++)
                    {
                        cout << _xa << ". " << iter->first << endl;
                        oms.push_back(iter->first);
                        omsim.push_back(iter->second);
                        _xa++;
                    }
                    cout << "0. Cancel\n";
                    cin >> sub_category;
                    
                    system("cls");
                    TIP();
                    cout << "Category:\t" << product << endl;
                    cout << "Product:\t" << oms[sub_category - 1] << endl;
                    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

                    cout << "\nHow many? (type '0' to cancel)\n";
                    cin >> amount;
                    if (amount >= 1) {
                        system("cls");
                        price = omsim[sub_category - 1];
                        mapping(product, amount, price);
                        if (amount < 1) {
                            break;
                        }
                        cart[oms[sub_category - 1]] = {amount, price};
                    }
                break; // No break;
                
                // Arjie - Case 5

                case 5:
                    TIP();
                    cout << "Choose a Book\n";
                    product = "Book";
                    _xa = 1;
                    cout << "Choose a Book product:\n";
                    for (auto iter = products["Book"].begin(); iter != products["Book"].end(); iter++)
                    {
                        cout << _xa << ". " << iter->first << endl;
                        oms.push_back(iter->first);
                        omsim.push_back(iter->second);
                        _xa++;
                    }
                    cout << "0. Cancel\n";
                    cin >> sub_category;
                    
                    system("cls");
                    TIP();
                    cout << "Category:\t" << product << endl;
                    cout << "Product:\t" << oms[sub_category - 1] << endl;
                    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

                    cout << "\nHow many? (type '0' to cancel)\n";
                    cin >> amount;
                    if (amount >= 1) {
                        system("cls");
                        price = omsim[sub_category - 1];
                        mapping(product, amount, price);
                        if (amount < 1) {
                            break;
                        }
                        cart[oms[sub_category - 1]] = {amount, price};
                    }
                    break;
                default:
                    break;
            }
            cin.clear();
            system("cls");
            TIP();
            cout << "If you wish buy more, type 'yes', otherwise 'no'.\n";
            cin >> decision;

            
        }
    } while (decision == "yes");
    
    system("cls");
    TIP();
    cout << "View Cart? type 'yes', otherwise 'no'.\n";  // option 1
    cin >> view_cart;

    if (view_cart == "yes") {
        system("cls");
        map<string, pair<int, int>>::iterator iter;
        TIP();
        cout << "                Item                 \t\tAmount\t\tPrice\t\tTotal\n";
        cout << "****************************************************************************************\n\n";
        for (iter = cart.begin(); iter != cart.end(); iter++) 
        {
            if (iter->first == "Notebook" || iter->first == "Yellow Pad")
            {
                totprice = iter->second.first * iter->second.second;
                cout << iter->first << "\t  " << iter->second.first << "\t\t  " << iter->second.second << "\t\t  " << totprice << endl;
            }
            else 
            {
                totprice = iter->second.first * iter->second.second;
                cout << iter->first << "\t\t  " << iter->second.first << "\t\t  " << iter->second.second << "\t\t  " << totprice << endl;
            }
        }
        cout << "\n****************************************************************************************\n";
        cout << "\t\t\t\t\t\t\t\t  Overall amount: P" << total_amount << endl;
        cout << "\nProceed to checkout? (type 'yes', otherwise 'no'.)\n";
        cin >> checkout_option;

        if (checkout_option == "yes")
        {
            cout << "Checkout\n";
            cout << "What is your payment method?\n";
            cout << "1. Cash\n";
            cout << "2. Card\n";
            cin >> paymentMethod;
        }
        // Proceed to Checkout ---> Payment 
        // Payment ---> Payment confirmation

        
    

    }
}
