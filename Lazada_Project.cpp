#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#if defined(_WIN32) || defined(WIN32)
	#define System "windows"
	#include <windows.h>
#elif __APPLE__
	#define System "mac"
#else
	#define System ""
#endif

using namespace std;

float total_amount;
string paymentyarn, Codes[3];
float VAT_amount, discounted_amount, subtotal;

map<string, vector<pair<string, float>>> products;
map<string, pair<int, float>> cart;
map<string, float> discounts;

void clear();
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
    clear();
    TIP();
    cout << "Welcome to StudEssentials!\n";

    cout << "If you wish to shop, type 'yes', otherwise 'no'.\n";
    cin >> decision;
    if (decision == "yes") {
        shop();
    } else {
        return 0;
    }
    
    clear();
    TIP();
    cout << "View Cart? type 'yes', otherwise 'no'.\n";  // option 1
    cin >> view_cart;

    if (view_cart == "yes") {
        total_price = viewCart();
        cout << "\nProceed to checkout? (type 'yes', otherwise 'no'.)\n";
        cin >> checkout_option;

        if (checkout_option == "yes") {
            clear();
			TIP();
            cout << "Checkout\n";
            cout << "What is your payment method?\n";
            cout << "1. Cash\n";
            cout << "2. Card\n";
            cout << "0. Cancel\n";
            cin >> paymentMethod;
            if (paymentMethod == 1) {
                clear();
				TIP();
                VAT_amount = 0.075 * total_price;
                subtotal = total_price;
                total_price += VAT_amount;
                cout << "Total Amount to pay: " << total_price << " (" << subtotal << " + " << VAT_amount << ")" << endl;
                cout << "Do you want to apply a discount code? (type 'yes', otherwise 'no'.)\n";
                cin >> discount_option;
                if (discount_option == "yes")
                {
                    discount(total_price);
                    clear();
					TIP();
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
                clear();
                cardInfo();

				TIP();
                cout << "Please select one\n";
                cout << "1. Cash card\n";
                cout << "2. Savings\n";
                cout << "0. Cancel\n";
                cin >> cardMethod;
                
                clear();
				TIP();
                VAT_amount = 0.075 * total_price;
                subtotal = total_price;
                total_price += VAT_amount;
                cout << "Total Amount to pay: " << total_price << endl;
                cout << "Do you want to apply a discount code? (type 'yes', otherwise 'no'.)\n";
                cin >> discount_option;
                if (discount_option == "yes")
                {
                    discount(total_price);
                    clear();
					TIP();
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
				clear();
				TIP();
                cout << "Cancelling payment...\n";
            }
        }
    }
}

void clear()
{
	if (strcmp( System, "windows" ) == 0) {
		system("cls");
	} else if (strcmp( System, "mac" ) == 0) {
		system("clear");
	} else { }
}

void TIP()
{
	if (strcmp( System, "windows" ) == 0) {
		#if defined(_WIN32) || defined(WIN32)
			HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 6); //Change color of School Name
			cout<<"                        Technological Institute of The Philippines          \n";
			SetConsoleTextAttribute(hConsole, 7); //Return to while color
			cout<<"                Project: StudEssentials: A Simple Purchasing or POS System                \n"; 
			cout << "\n****************************************************************************************\n";
		#endif
	} else {
		cout<<"                        Technological Institute of The Philippines          \n";
		cout<<"                Project: StudEssentials: A Simple Purchasing or POS System                \n"; 
		cout << "\n****************************************************************************************\n";
	}
}

void mapping (string product, int &amount, float price) {
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
    products["Pen"].push_back(make_pair           ("Gel Pen                            ", 9.99));
    products["Pen"].push_back(make_pair           ("HBW-2000                           ", 14.99));
    products["Pen"].push_back(make_pair           ("Parker                             ", 17.99));
    products["Pen"].push_back(make_pair           ("Panda                              ", 13.25));
    products["Pen"].push_back(make_pair           ("Pilot                              ", 14.59));
    products["Pen"].push_back(make_pair           ("Calligraphy Pen                    ", 39.99));
    products["Pen"].push_back(make_pair           ("Montblanc (Luxury Pen)             ", 24999.59));
    products["Pencil"].push_back(make_pair        ("Mongol                             ", 7.99));
    products["Pencil"].push_back(make_pair        ("Faber-Castell                      ", 27.99));    
    products["Pencil"].push_back(make_pair        ("Carbon Pencil                      ", 24.59));
    products["Pencil"].push_back(make_pair        ("Graphite Pencil                    ", 30));
    products["Pencil"].push_back(make_pair        ("Berol Pencil                       ", 54.99));
    products["Paper"].push_back(make_pair         ("Yellow Pad                         ", 25));
    products["Paper"].push_back(make_pair         ("Whole                              ", 35));
    products["Paper"].push_back(make_pair         ("Yellow Pad                         ", 50));
    products["Paper"].push_back(make_pair         ("1/2 Yellow Pad                     ", 24));
    products["Paper"].push_back(make_pair         ("1/4 Yellow Pad                     ", 15));
    products["Paper"].push_back(make_pair         ("Index Card                         ", 23));
    products["Paper"].push_back(make_pair         ("Short Bondpaper                    ", 2));
    products["Paper"].push_back(make_pair         ("Long Bondpaper                     ", 3));
    products["Notebook"].push_back(make_pair      ("Spiral Notebook                    ", 45));
    products["Notebook"].push_back(make_pair      ("Leather Notebook                   ", 60));
    products["Notebook"].push_back(make_pair      ("Math Notebook                      ", 30));
    products["Notebook"].push_back(make_pair      ("Music Notebook                     ", 32));
    products["Notebook"].push_back(make_pair      ("Small Notebook                     ", 24.49));
    products["Book"].push_back(make_pair          ("MATLAB Book                        ", 250));
    products["Book"].push_back(make_pair          ("UTS Book                           ", 235));
    products["Book"].push_back(make_pair          ("Number Theory Book                 ", 249.25));
    products["Book"].push_back(make_pair          ("Math in Modern World Book          ", 289.99));
    products["Book"].push_back(make_pair          ("C++ Programming First Year Handbook", 349.59));
    products["Book"].push_back(make_pair          ("C++ Algorithm First Year Handbook  ", 349.59));
    products["Book"].push_back(make_pair          ("Mastering C++ Programming Language ", 549.49));
    products["Book"].push_back(make_pair          ("Data Science with Python           ", 459.39));

    discounts.insert( {"STUDENT", 15} );
    discounts.insert( {"ENDOFSY", 25} );
    discounts.insert( {"NEWUSER", 25} );
    discounts.insert( {"DAILY", 10} );
    discounts.insert( {"T1WIN", 50} );
    discounts.insert( {"ZEUSMVP", 30} );
}

float viewCart()
{
    float totprice;
    clear();
    TIP();
    cout << "                Item                 \t\tAmount\t\tPrice\t\tTotal\n";
    cout << "****************************************************************************************\n\n";
    map<string, pair<int, float>>::iterator iter;
    for (iter = cart.begin(); iter != cart.end(); iter++) {
        totprice = iter->second.first * iter->second.second;
        cout << iter->first << "\t\t  " << iter->second.first << "\t\t" << iter->second.second << "\t\t" << totprice << endl;
    }
    cout << "\n****************************************************************************************\n";
    cout << "\t\t\t\t\t\t\t Overall amount: P" << total_amount << endl;
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
        clear();
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

        clear();
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
        clear();
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
    clear();
	TIP();
    cout <<"***************************************************\n";
    cout << "StudEssentials\n";
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "TIP Quezon City\n";
    cout << "Store Contact Number: +639123456789\n";
    cout << "Date and Time of purchase: " << dt << endl;
    cout <<"***************************************************\n";
    cout << "Subtotal:     " << subtotal              << endl;
    cout << "VAT:          " << VAT_amount            << endl;
    cout << "New Subtotal: " << subtotal + VAT_amount << endl;
    cout << "Discount:     " << discounted_amount     << endl;
    cout << "Codes:        " << hi                    << "\n\n";
    cout << "Balance:      " << balance               << endl;
    cout << "Total:        " << total_price           << endl;
    cout << "Change:       " << change                << endl;
    cout << "Paid with:    " << paymentyarn           << endl;
    cout <<"***************************************************\n";
    cout <<"          Thank you for shopping with us!          \n";
    cout <<"***************************************************";
}

float discount(float &total_price)
{
    string code;
    int code_amount = 1;
    int temp;
    float discount_ammount, percentage;
    bool applied;
    do {
        applied = false;
        temp = code_amount;
        clear();
		TIP();
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
                        applied = true;
                    } else {
                        percentage = 1 - (iter->second/100);
                        discount_ammount = total_price * (iter->second/100);
                        total_price *= percentage;
                        discounted_amount += discount_ammount;
                        Codes[code_amount - 1] = code;
                        code_amount++;
                        cout << "Successfully used " << code << " giving you a " << iter->second << "\% discount\n";
						sleep(2);
                    }
                    break;
                }
            }
        }
        if (temp == code_amount && !applied) {
            cout << "Invalid Code!\n";
            sleep(2);
        }
    } while (code_amount <= 3);

    return total_price;
}

void cardInfo()
{
	TIP();
    string cardnumber, expirydate, cvv;
    cout << "Enter Card Number: ";
    cin >> cardnumber;
    cout << "Enter Card's Expiry Date: ";
    cin >> expirydate;
    cout << "Enter Card's CVV: ";
    cin >> cvv;
    clear();
}

int categoryShop(string product)
{
    int chosen_category, sub_category, amount, _xa = 1;
    float price;
    vector<string> oms;
    vector<float> omsim;

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
    
    clear();
    TIP();
    cout << "Category:\t" << product << endl;
    cout << "Product:\t" << oms[sub_category - 1] << endl;
    cout << "Price:\t\t" << omsim[sub_category - 1] << endl;

    cout << "\nHow many? (type '0' to cancel)\n";
    cin >> amount;
    if (amount >= 1) {
        clear();
        price = omsim[sub_category - 1];
        mapping(product, amount, price);
        if (amount < 1) {
            return 0;
        }
        cart[oms[sub_category - 1]] = {amount, price};
    }
    return 0;
}
