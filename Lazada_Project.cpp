#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
// #include <windows.h>

using namespace std;

int total_amount;
string paymentyarn, Codes[3];
float VAT_amount, discounted_amount, subtotal;

map<string, vector<pair<string, int>>> products;
map<string, pair<int, int>> cart;
map<string, float> discounts;

void TIP();
void mapping(string product, int &amount, int price);
void addData();
float viewCart();
void shop();
void receipt(float balance, float total_price, float change);
float discount(float &total_price);
void cardInfo();
int categoryShop(string product);

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
                VAT_amount = 0.075 * total_price;
                subtotal = total_price;
                total_price += VAT_amount;
                cout << "Total Amount to pay: " << total_price << endl;
                cout << "Do you want to apply a discount code? (type 'yes', otherwise 'no'.)\n";
                cin >> discount_option;
                if (discount_option == "yes")
                {
                    discount(total_price);
                    system("cls");
                    cout << "Total Amount to pay: " << total_price << endl;
                }
                cout << "Please input your money \n";
                cin.clear();
                cin >> balance;
                if (balance < total_price) {
                    cout << "\nInsufficient Money!\nUnable to proceed\n";
                } else {
                    change = balance - total_price;
                    paymentyarn = "Cash";
                    receipt(balance, total_price, change);
                }
            }
            else if (paymentMethod == 2) {
                system("cls");
                
                cardInfo();

                cout << "Please select one\n";
                cout << "1. Cash card\n";
                cout << "2. Savings\n";
                cout << "0. Cancel\n";
                cin >> cardMethod;
                
                system("cls");
                VAT_amount = 0.075 * total_price;
                subtotal = total_price;
                total_price += VAT_amount;
                cout << "Total Amount to pay: " << total_price << endl;
                cout << "Do you want to apply a discount code? (type 'yes', otherwise 'no'.)\n";
                cin >> discount_option;
                if (discount_option == "yes")
                {
                    discount(total_price);
                    system("cls");
                    cout << "Total Amount to pay: " << total_price << endl;
                }
                cout << "Please input your money\n";
                cin.clear();
                cin >> balance;
                if (balance < total_price) {
                    cout << "\nInsufficient Money!\nUnable to proceed\n";
                } else {
                    change = balance - total_price;
                    paymentyarn = "Card";
                    receipt(balance, total_price, change);
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
                break;
            case 2:
                product = "Pencil";
                break;
            case 3:
                product = "Paper";
                break;
            case 4:
                product = "Notebook";
                break;
            case 5:
                product = "Book";
                break;
            default:
                break;
        }
        if (chosen_category >= 1 && chosen_category <= 5) {
            categoryShop(product);
        }
        cin.clear();
        system("cls");
        TIP();
        cout << "If you wish buy more, type 'yes', otherwise 'no'.\n";
        cin >> decision;
    } while (decision == "yes");
}

void receipt(float balance, float total_price, float change)
{
    string hi;
    for (string i: Codes)
    {
        hi += i;
        hi += " ";
    }
    cout << "Please wait for your receipt\n";
    system("cls");
    cout << "StudEssentials\n";
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "TIP Quezon City\n";
    cout << "Store Contact Number: +639123456789\n";
    cout << "Date and Time of purchase: " << dt << endl;
    cout << "Subtotal:     " << subtotal              << endl;
    cout << "VAT:          " << VAT_amount            << endl;
    cout << "New Subtotal: " << subtotal + VAT_amount << endl;
    cout << "Discount:     " << discounted_amount     << endl;
    cout << "Codes:        " << hi                    << "\n\n";
    cout << "Balance:      " << balance               << endl;
    cout << "Total:        " << total_price           << endl;
    cout << "Change:       " << change                << endl;
    cout << "Paid with:    " << paymentyarn           << endl;
}

float discount(float &total_price)
{
    string code, add;
    int code_amount = 1;
    int temp;
    float discount_ammount, percentage;
    bool applied;
    do {
        add = "";
        applied = false;
        temp = code_amount;
        system("cls");
        cout << "Enter your discount/voucher code\n";
        cout << "Code " << code_amount << ": ";
        cout << "Type 'done' to finish adding discount/voucher code\n";
        cin >> code;
        if (code == "done") { break; }
        map<string, float>::iterator iter;
        for (iter = discounts.begin(); iter != discounts.end(); iter++) {
            if (code == iter->first) {
                for (string i: Codes) {
                    if (i == code) {
                        cout << "That code is already applied!\n";
                        sleep(2);
                        add = "yes";
                        applied = true;
                    } else {
                        percentage = 1 - (iter->second/100);
                        discount_ammount = total_price * (iter->second/100);
                        total_price *= percentage;
                        discounted_amount += discount_ammount;
                        Codes[code_amount - 1] = code;
                        code_amount++;
                        cout << "Successfully used " << code << " giving you a " << iter->second << "\% discount\n";
                        cout << "Type 'yes' if you want to another code\n";
                        cin.clear();
                        cin >> add;
                    }
                    break;
                }
            }
        }
        if (temp == code_amount && !applied) {
            cout << "Invalid Code!\n";
            sleep(2);
            add = "yes";
        }
    } while (code_amount <= 3 && add == "yes");

    return total_price;
}

void cardInfo()
{
    string cardnumber, expirydate, cvv;
    cout << "Enter Card Number: ";
    cin >> cardnumber;
    cout << "Enter Card's Expiry Date: ";
    cin >> expirydate;
    cout << "Enter Card's CVV: ";
    cin >> cvv;
    system("cls");
}

int categoryShop(string product)
{
    int chosen_category, sub_category, amount, _xa = 1;
    float price;
    vector<string> oms;
    vector<int> omsim;

    TIP();
    cout << "Choose a " << product << " product:\n";
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
            return 0;
        }
        cart[oms[sub_category - 1]] = {amount, price};
    }
    return 0;
}
