#include <iostream>
#include <fstream>
#include<iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
    string name;
    double price;
    int quantity;

    Item() {}

    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}

    void display() const {
        cout << setw(20) << left << name;
        cout << setw(10) << right << setprecision(2) << fixed << price;
        cout << setw(5) << right << quantity;
        cout << setw(10) << right << setprecision(2) << fixed << calculateTotal() << endl;
    }

    double calculateTotal() const {
        return price * quantity;
    }
};

class Supermarket {
private:
    vector<Item> inventory;
    vector<Item> bill;

public:
    Supermarket() {
        readInventoryFromFile();
    }

    void readInventoryFromFile() {
        ifstream file("inventory.txt");

        if (!file.is_open()) {
            cerr << "Error: Unable to open inventory file. Please check the file location and permissions." << endl;
            exit(EXIT_FAILURE);
        }

        string name;
        double price;
        int quantity;

        while (file >> name >> price >> quantity) {
            inventory.push_back(Item(name, price, quantity));
        }

        file.close();
    }

    const vector<Item>& getInventory() const {
        return inventory;
    }

    void addItemToShop() {
        Item newItem;
        cout << "Enter details for the new item:" << endl;
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, newItem.name);
        cout << "Enter price per unit: $";
        cin >> newItem.price;
        cout << "Enter quantity: ";
        cin >> newItem.quantity;

        inventory.push_back(newItem);

        // Update the inventory file
        ofstream file("inventory.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error: Unable to open inventory file for writing. Please check permissions." << endl;
            exit(EXIT_FAILURE);
        }

        file << newItem.name << " " << newItem.price << " " << newItem.quantity << endl;

        file.close();

        cout << "Item added to the shop inventory successfully." << endl;
    }

    void addItemToBill() {
        string itemName;
        int quantity;

        cout << "Enter item name to add to the bill: ";
        cin.ignore();
        getline(cin, itemName);

        auto it = find_if(inventory.begin(), inventory.end(),
                          [&itemName](const Item& item) { return item.name == itemName; });

        if (it != inventory.end()) {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (it->quantity >= quantity) {
                bill.push_back(Item(it->name, it->price, quantity));
                it->quantity -= quantity;
                cout << "Item added to the bill successfully." << endl;
            } else {
                cout << "Error: Item not available in sufficient quantity." << endl;
            }
        } else {
            cout << "Error: Item not found in the shop inventory." << endl;
        }
    }

    void generateBill() const {
        if (bill.empty()) {
            cout << "No items in the bill. Exiting..." << endl;
            return;
        }

        cout << "\n\n";
        cout << setw(20) << left << "Item Name";
        cout << setw(10) << right << "Price($)";
        cout << setw(5) << right << "Qty";
        cout << setw(10) << right << "Total($)" << endl;
        cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;

        double total = 0;

        for (const auto& item : bill) {
            item.display();
            total += item.calculateTotal();
        }

        cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
        cout << setw(35) << right << "Total:" << setw(10) << right << setprecision(2) << fixed << total << endl;

        // Optionally, update the inventory file with the new quantities
        ofstream file("inventory.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to open inventory file for writing. Please check permissions." << endl;
            exit(EXIT_FAILURE);
        }

        for (const auto& item : inventory) {
            file << item.name << " " << item.price << " " << item.quantity << endl;
        }

        file.close();
    }

    void displayTotalStock() const {
        cout << "\nTotal Stock in Shop Inventory:\n";
        cout << setw(20) << left << "Item Name";
        cout << setw(10) << right << "Price($)";
        cout << setw(5) << right << "Qty" << endl;
        cout << setfill('-') << setw(35) << "-" << setfill(' ') << endl;

        for (const auto& item : inventory) {
            cout << setw(20) << left << item.name;
            cout << setw(10) << right << setprecision(2) << fixed << item.price;
            cout << setw(5) << right << item.quantity << endl;
        }
    }
};

int main() {
    Supermarket supermarket;

    while (true) {
        cout << "\nOptions:" << endl;
        cout << "1. Add item to shop inventory" << endl;
        cout << "2. Add item to the bill" << endl;
        cout << "3. Display total stock in shop inventory" << endl;
        cout << "4. Exit and generate total bill" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                supermarket.addItemToShop();
                break;
            case 2:
                supermarket.addItemToBill();
                break;
            case 3:
                supermarket.displayTotalStock();
                break;
            case 4:
                supermarket.generateBill();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
