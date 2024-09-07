#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <iomanip> 
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill(): Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

int addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("E:/Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
                cout << "\tItem Added Successfully!" << endl;
            }
            out.close();
            Sleep(3000);
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack to Main Menu!" << endl;
            Sleep(3000);
        }
    }
    return 0;
}

void viewItems() {
    system("cls");
    cout << "\tAvailable Items:" << endl;
    cout << "\t----------------" << endl;

    ifstream in("E:/Bill.txt");
    string line;
    while (getline(in, line)) {
        cout << "\t" << line << endl;
    }
    in.close();
    Sleep(5000);
}

int printBill() {
    system("cls");
    int count = 0;
    bool close = false;
    vector<string> soldItems;
    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Apply Discount" << endl;
        cout << "\t3. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("E:/Bill.txt");
            ofstream out("E:/Bill Temp.txt");
            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << " | " << itemRate << " | " << quant << " | " << amount << endl;
                        int newQuant = itemQuant - quant;
                        count += amount;

                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                        soldItems.push_back(itemName + " : " + to_string(itemRate) + " : " + to_string(quant) + " : " + to_string(amount));
                    } else {
                        cout << "\tSorry, " << item << " is Out of Stock!" << endl;
                    }
                } else {
                    out << line << endl;
                }
            }
            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }
            out.close();
            in.close();
            remove("E:/Bill.txt");
            rename("E:/Bill Temp.txt", "E:/Bill.txt");
        } else if (choice == 2) {
            float discount;
            cout << "\tEnter Discount Percentage: ";
            cin >> discount;
            count -= (count * discount / 100);
            cout << "\tDiscount Applied Successfully!" << endl;
            Sleep(2000);
        } else if (choice == 3) {
            close = true;
            cout << "\tCounting Total Bill..." << endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout << "\tTotal Bill ----------------- : " << count << endl;
    cout << "\tThanks for Shopping!" << endl;
    Sleep(5000);

    // Generate Report
    ofstream report("E:/Sales_Report.txt", ios::app);
    if (report.is_open()) {
        report << "Item | Rate | Quantity Sold | Amount" << endl;
        for (const auto& soldItem : soldItems) {
            report << soldItem << endl;
        }
        report << "Total Sales: " << count << endl;
        report.close();
    } else {
        cout << "\tError: Could not generate report!" << endl;
    }

    return count;
}

int main() {
    Bill b;
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome to Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. View Available Items" << endl;
        cout << "\t3. Print Bill" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItem(b);
            Sleep(3000);
        } else if (val == 2) {
            viewItems();
        } else if (val == 3) {
            printBill();
        } else if (val == 4) {
            system("cls");
            exit = true;
            cout << "\tGoodbye!" << endl;
            Sleep(3000);
        }
    }
    return 0;
}
