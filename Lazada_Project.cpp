#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
// #include <windows.h>

using namespace std;

int total_amount;

map<string, vector<pair<string, int>>> products;
map<string, pair<int, int>> cart;
map<string, int> discounts;

void TIP();
void mapping(string product, int &amount, int price);
void addData();
float viewCart();
void shop();
float compute(float balance, float total_price);
void receipt(float balance, float total_price, float change);
float discount(float total_price);

int main() {
    string decision, view_cart, checkout_option, discount_option;
    float total_price, balance, change;
    int paymentMethod, cardMethod, cardNumber;

    addData();
    system("cls");
    TIP();
    cout << "Welcome to StudEssentials!\n";

    cout << "If you wish to shop, type 'yes', otherwise 'no'.\n";
    cin >> decision;
    if (decision == "yes") {
        shop();
    } else {
        return 0;
    }
    
    system("cls");
    TIP();
    cout << "View Cart? type 'yes', otherwise 'no'.\n";  // option 1
    cin >> view_cart;

    if (view_cart == "yes") {
        total_price = viewCart();
        cout << "\nProceed to checkout? (type 'yes', otherwise 'no'.)\n";
        cin >> checkout_option;

        if (checkout_option == "yes") {
            system("cls");
            cout << "Checkout\n";
            cout << "What is your payment method?\n";
            cout << "1. Cash\n";
            cout << "2. Card\n";
            cout << "0. Cancel\n";
            cin >> paymentMethod;
            if (paymentMethod == 1) {
                system("cls");
                total_price *= 0.075 * total_price;
                cout << "Total Amount to pay: " << total_price << endl;
                cout << "Do you want to apply a discount code? (type 'yes', otherwise 'no'.)\n";
                cin >> discount_option;
                if (discount_option == "yes")
                {
                    total_price = discount(total_price);
                }
                cout << "Please input your money \n";
                cin.cls();
                cin >> balance;
                if (balance < total_price) {
                    cout << "\nInsufficient Money!\nUnable to proceed\n";
                } else {
                    change = compute(balance, total_price);
                }
                receipt(balance, total_price, change);
            }
            else if (paymentMethod == 2)
            {
                system("cls");
                
                cout << "Please enter your Bank card (just type random numbers)\n";
                cin >> cardNumber;
                cout << "Please select one\n";
                cout << "1. Cash card\n";
                cout << "2. Savings\n";
                cout << "0. Cancel\n";
                cin.cls();
                cin >> cardMethod;
                
                if (cardMethod == 1)
                {
                cout << "\nPlease enter your money\n";
                cin >> balance;
                if(balance < total_price)
                {
                    cout << "\nInsufficient Money!\nUnable to proceed\n";
                }
                else
                {
                    cout << "Computing";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                    cout << "\nplease wait";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                    cout << ".";
                    cout.flush();
                    sleep(1);
                }
                }
            }
            else
            {
                cout << "Cancelling payment...\n";
            }
        }
    }
}


void TIP()
{
    // HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, 6); //Change color of School Name
    cout<<"                        Technological Institute of The Philippines          \n";
    // SetConsoleTextAttribute(hConsole, 7); //Return to while color
    cout<<"                Project: StudEssentials: A Simple Purchasing or POS System                \n"; 
    cout << "\n****************************************************************************************\n";
}

void mapping (string product, int &amount, int price) {
    string add_to_cart;
    TIP();
    cout << "\nThe price for " << amount << " " << product << " is P" << price * amount << "." << endl;

    cout << "\nAdd to cart? (type 'yes' if yes, otherwise 'no'.)\n";
    cin >> add_to_cart;
    if (add_to_cart == "no") 
    {
        amount = 0;
    }
    else if (add_to_cart =="yes")
    {
        total_amount += price * amount;
    }
    
}

void addData()
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

    discounts.insert( {"STUDENT", 10} );
}

float viewCart()
{
    float totprice;
    system("cls");
    TIP();
    cout << "                Item                 \t\tAmount\t\tPrice\t\tTotal\n";
    cout << "****************************************************************************************\n\n";
    map<string, pair<int, int>>::iterator iter;
    for (iter = cart.begin(); iter != cart.end(); iter++) {
        totprice = iter->second.first * iter->second.second;
        cout << iter->first << "\t\t  " << iter->second.first << "\t\t  " << iter->second.second << "\t\t  " << totprice << endl;
    }
    cout << "\n****************************************************************************************\n";
    cout << "\t\t\t\t\t\t\t\t  Overall amount: P" << total_amount << endl;
    return total_amount;
}

void shop()
{
    int chosen_category, sub_category, amount, _xa;
    float price;
    string product, decision;
    do {
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
        cin.cls();
        system("cls");
        TIP();
        cout << "If you wish buy more, type 'yes', otherwise 'no'.\n";
        cin >> decision;
    } while (decision == "yes");
}

float compute(float balance, float total_price)
{
    float change;
    system("cls");
    // cout << "Balance: " << balance << endl;
    // cout << "Total amount to pay: " << total_price << endl;

    cout << "Processing payment";
    cout.flush();
    sleep(1);
    cout << ".";
    cout.flush();
    sleep(1);
    cout << ".";
    cout.flush();
    sleep(1);
    cout << ".";
    cout.flush();
    sleep(1);
    change = balance - total_price ;
    cout << "\n\nYour change is: " << change << endl;

    return change;
}

void receipt(float balance, float total_price, float change)
{
    cout << "Please wait for your receipt\n";
    
    cout << "StudEssentials\n";
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "TIP Quezon City\n";
    cout << "Store Contact Number: +639123456789\n";
    cout << "Date and Time of purchase: " << dt << endl;
    viewCart();
    cout << "VAT: " << endl;

}

float discount(float total_price)
{
    string code;
    int code_amount = 1;
    int temp;
    do {
        temp = code_amount;
        system("cls");
        cout << "Enter your discount/voucher code\n";
        cout << "Code " << code_amount << ": ";
        cout << "Type 'done' to finish adding discount/voucher code\n";
        cin >> code;
        if (code == "done") { break; }
        map<string, int>::iterator iter;
        for (iter = discounts.begin(); iter != discounts.end(); iter++) {
            if (code == iter->first) {
                total_price *= (iter->second/100);
                code_amount++;
                cout << "Successfully used " << code << " giving you a " << iter->second << "\% discount\n";
                cout.flush();
                sleep(1);
            }
        }
        if (temp == code_amount) {
            cout << "Invalid Code!\n";
        }
    } while (code_amount <= 3);

    return total_price;
}
