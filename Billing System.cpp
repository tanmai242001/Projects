#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h> // Use this for usleep on macOS and Linux
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) { }

    void setItem(string item) {
        Item = item;
    }

    void setRate(int rate) {
        Rate = rate;
    }

    void setQuant(int quant) {
        Quantity = quant;
    }

    string getItem() {
        return Item;
    }

    int getRate() {
        return Rate;
    }

    int getQuant() {
        return Quantity;
    }
};

void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1.Add." << endl;
        cout << "\t2.Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("clear"); // Use "clear" for macOS/Linux instead of "cls"
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            usleep(3000000); // Sleep for 3 seconds
        } else if (choice == 2) {
            system("clear");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            usleep(3000000); // Sleep for 3 seconds
        }
    }
}

void printBill() {
    system("clear");
    int count = 0;
    bool close = false;
    while (!close) {
        system("clear");
        int choice;
        cout << "\t1.Add Bill." << endl;
        cout << "\t2.Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("Bill.txt");
            ofstream out("Bill Temp.txt");

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
                        cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amount;

                        out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl;
                    } else {
                        cout << "\tSorry, " << item << " Ended!" << endl;
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
            remove("Bill.txt");
            rename("Bill Temp.txt", "Bill.txt");
        } else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
        usleep(3000000); // Sleep for 3 seconds
    }
    system("clear");
    cout << endl << endl;
    cout << "\t Total Bill ----------------- : " << count << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    usleep(5000000); // Sleep for 5 seconds
}

int main() {
    Bill b;

    bool exit = false;
    while (!exit) {
        system("clear");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1.Add Item." << endl;
        cout << "\t\t2.Print Bill." << endl;
        cout << "\t\t3.Exit." << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("clear");
            addItem(b);
            usleep(3000000); // Sleep for 3 seconds
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            system("clear");
            exit = true;
            cout << "\tGood Luck!" << endl;
            usleep(3000000); // Sleep for 3 seconds
        }
    }
}
// g++ "/Users/tanmaisri/Downloads/Billing System.cpp" -o "/Users/tanmaisri/Downloads/Billing System" && "/Users/tanmaisri/Downloads/Billing System"
