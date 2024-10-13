#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

class Inventory {
protected:
    string items[100][5]; // [ID, Name, Category, Quantity, Price]
    int itemCount = 0;

public:
    virtual void addItem() = 0;
    virtual void updateItem() = 0;
    virtual void removeItem() = 0;
    virtual void displayItemsByCategory() = 0;
    virtual void displayAllItems() = 0;
    virtual void searchItem() = 0;
    virtual void sortItem() = 0;
    virtual void displayLowStockItems() = 0;
};

class Items : public Inventory {
private:
    string categories[3] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"};

public:

    void displayHeader(){
        cout << string(76, '-') << endl;
        cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
        cout << string(76, '-') << endl;
    }
    
    void displayItem(string items[][5], int i, double price, string category){
        double p = price;
        string c = category;
        c = toUpperCase(c);
        c = getCategoryInput(c);

        cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << p << left << setw(20) << c << endl;
    }
    
    string toUpperCase(string input){
        for (char &c : input) {
            c = toupper(c);
        }
        return input;
    }

    bool hasSpace(string input){

        bool space = false;

        for (char c : input){
            if (c == ' '){
                space = true;
            }
        }


        return space;
    }

    bool isEmpty(string input){

        bool isEmpty = false;

            if (input.length() == 0) {
                isEmpty = true;
            }

        return isEmpty;
    }

    bool hasSpecialChar(const string& input) {
        for (char c : input) {
            if (!isalnum(c)) {
                return true;
            }
        }
        return false;
    }

    string validateYesNoInput() {
        string choice;
        bool valid = false;

        while (!valid) {
            cout << "Do you want to try again? (Y/N): ";
            getline(cin, choice);
            choice = toUpperCase(choice);

            if (isEmpty(choice)){
                cout << "Invalid input! Empty inputs are not allowed." << endl;
            }
            else if (hasSpace(choice)){
                cout << "Invalid input! Spaces are not allowed." << endl;
            }
            else if (choice == "Y" || choice == "N") {
                valid = true;
            } else {
                cout << "Invalid input! Please enter 'Y' or 'N'." << endl;
            }
        }

        return choice;
    }

    string validateCategoryInput() {
        string categoryInput;
        do {
            cout << "Enter category (Clothing, Electronics, Entertainment): ";
            getline(cin, categoryInput);

            categoryInput = toUpperCase(categoryInput);

            if (isEmpty(categoryInput)){
                cout << "Invalid Input! Empty inputs are not allowed." << endl;
            }
            else if (hasSpace(categoryInput)){
                cout << "Invalid Input! Spaces are not allowed." << endl;
            }
            else if (hasSpecialChar(categoryInput)){
                cout << "Invalid Input! Special characgters are not allowed." << endl;
            }
            else if (categoryInput != "CLOTHING" && categoryInput != "ELECTRONICS" && categoryInput != "ENTERTAINMENT") {
                cout << "Invalid category! Please enter one of the following: Clothing, Electronics, Entertainment." << endl;
            }

        } while (categoryInput != "CLOTHING" && categoryInput != "ELECTRONICS" && categoryInput != "ENTERTAINMENT");

        return categoryInput;
    }
    
    string validateItemIDInputSrUp(int itemCount, string items[][5]) {
        string inputID;
        bool validID = false;

        while (!validID) {
            cout << endl << "Input Item ID (no spaces: e.g. ID001): ";
            getline(cin, inputID);

            inputID = toUpperCase(inputID);

            if (isEmpty(inputID)) {
                cout << "Invalid Input! Empty inputs are not allowed." << endl;
                continue; 
            } 
            else if (hasSpace(inputID)) {
                cout << "Invalid Input! Spaces are not allowed." << endl;
                continue;
            }
            else if (hasSpecialChar(inputID)) {
                cout << "Invalid Input! Special characters are not allowed." << endl;
                continue;
            }

            bool exists = false;
            for (int i = 0; i < itemCount; i++) {
                if (inputID == items[i][0]) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                cout << "Invalid ID! Item not found." << endl;
                string choice = validateYesNoInput();
                if (choice == "Y") {
                    continue;
                } else {
                    return "";
                }
            } else {
                validID = true;
            }
        }

        return inputID;
    }

int validateQuantityInput(int currentQuantity) {
    string quantityInput;
    int newQuantity;
    bool validQuantity = false;

    do {
        cout << "Input value for Quantity: ";
        getline(cin, quantityInput);

        if (isEmpty(quantityInput)) {
            cout << "Invalid Input! Empty inputs are not allowed." << endl;
            continue;
        }

        if (hasSpace(quantityInput)) {
            cout << "Invalid input! No spaces allowed." << endl;
            continue;
        }

        bool isNumeric = true;
        for (char c : quantityInput) {
            if (!isdigit(c)) {
                isNumeric = false;
                break;
            }
        }

        if (!isNumeric) {
            cout << "Invalid input! Only enter positive integers." << endl;
            continue;
        }

        newQuantity = stoi(quantityInput);

        if (newQuantity == currentQuantity) {
            cout << "Input must not be equal to the current quantity!" << endl;
            continue;
        }

        validQuantity = true;

    } while (!validQuantity);

    return newQuantity;
}

double validatePriceInput(string currentPrice) {
    string priceInput;
    double newPrice;
    bool validPrice = false;

    while (!validPrice) {
        cout << "Input value for Price: ";
        getline(cin, priceInput);
        
        if (isEmpty(priceInput)) {
            cout << "Invalid Input! Empty inputs are not allowed." << endl;
            continue;
        }
        
        if (hasSpace(priceInput)) {
            cout << "Invalid Input! Spaces are not allowed." << endl;
            continue;
        }

        bool validPriceInput = true;
        bool decimalPointFound = false;

        for (char c : priceInput) {
            if (c == '.') {
                if (decimalPointFound) {
                    validPriceInput = false;
                    break;
                }
                decimalPointFound = true;
            } else if (!isdigit(c)) {
                validPriceInput = false;
                break;
            }
        }

        if (validPriceInput) {
            newPrice = stod(priceInput);

            if (newPrice > 0 && newPrice != stod(currentPrice)) {
                validPrice = true; 
            } else if (newPrice == stod(currentPrice)) {
                cout << "Invalid input! Price cannot be the same as the current value." << endl;
            } else {
                cout << "Invalid input! Price must be greater than zero." << endl;
            }
        } else {
            cout << "Invalid input! Please enter a valid number." << endl;
        }
    }

    return newPrice;
}
    
string validateNewItemIDInput(int itemCount, string items[][5]) {
    string id;
    bool validID;

    do {
        validID = true;
        cout << "Input Item ID (alphanumeric, no spaces: e.g. ID001): ";
        getline(cin, id);

        id = toUpperCase(id);

        if (isEmpty(id)) {
            cout << "Empty inputs are not allowed." << endl;
            validID = false;
        }
        else if (hasSpace(id)){
            cout << "Invalid input! Spaces are not allowed." << endl;
            validID = false;
        }
        else if (hasSpecialChar(id)){
            cout << "Invalid input! Special characters are not allowed." << endl;
            validID = false;
        }
        bool exists = false;
        for (int i = 0; i < itemCount; i++) {
            if (id == items[i][0]) {
                exists = true;
                break;
            }
        }

        if (exists) {
            cout << "Invalid ID! This ID is already taken." << endl;
            validID = false;
        }

    } while (!validID);

    return id;
}

string validateNewItemNameInput() {
    string name;
    bool validName;

    do {
        validName = true;
        cout << "Input Item Name: ";
        getline(cin, name);

        if (isEmpty(name)) {
            cout << "Empty inputs are not allowed." << endl;
            validName = false;
        }

    } while (!validName);

    return name;
}

    string getCategoryInput(const string& category) {
        int categoryNum;
        string categoryInput;

        if (category == "CLOTHING") {
            categoryNum = 1;
        } else if (category == "ELECTRONICS") {
            categoryNum = 2;
        } else {
            categoryNum = 3;
        }

        switch (categoryNum) {
            case 1:
                categoryInput = "Clothing";
                break;
            case 2:
                categoryInput = "Electronics";
                break;
            case 3:
                categoryInput = "Entertainment";
                break;
        }

        return categoryInput;
    }

    void setItemDetails(int index, string id, string name, string category, int quantity, double price) {
        items[index][0] = id;
        items[index][1] = name;
        items[index][2] = category;
        items[index][3] = to_string(quantity);
        items[index][4] = to_string(price);
    }

    void addItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tAdd Item" << endl;
        cout << string(76, '-') << endl << endl;

        string category = validateCategoryInput();

        bool categoryFound = false;
        for (int i = 0; i < 3; i++) {
            if (category == categories[i]) {
                categoryFound = true;

                if (itemCount < 100) {
                    string id, name;
                    int quantity;
                    double price;

                    cout << endl << "Item Details" << endl;

                    id = validateNewItemIDInput(itemCount, items);

                    name = validateNewItemNameInput();

                    quantity = validateQuantityInput(0);

                    price = validatePriceInput("0.00");

                    setItemDetails(itemCount, id, name, category, quantity, price);
                    itemCount++;

                    system("cls");

                    cout << endl << string(76, '-') << endl << "\t\t\t Item added successfully!" << endl;
                    
                    displayHeader();

                    string categoryInput = getCategoryInput(category);

                    cout << fixed << setprecision(2) << left << setw(10) << id << left << setw(25) << name << left << setw(12) << quantity << "P" << left << setw(15) << price << left << setw(20) << categoryInput << endl;
                    
                    cout << string(76, '-') << endl;

                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                } else {
                    cout << endl << "Inventory is full, cannot add more items!" << endl;
                }
                break;
            }
        }
    }

void updateItem() override {
    cout << string(76, '-') << endl;
    cout << "\t\t\t\tUpdate Item" << endl;
    cout << string(76, '-') << endl;

    string inputID;
    string category;

    if (itemCount == 0) {
        cout << endl << "There are no items in the inventory!" << endl;
        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
        return;
    }

    displayHeader();

    for (int i = 0; i < itemCount; i++) {
        string categoryInput = items[i][2]; 
        category = getCategoryInput(categoryInput);
        double price = stod(items[i][4]);

        displayItem(items, i, price, category);
    }

    bool validID = false;

    while (!validID) {
        cout << string(76, '-') << endl;

        inputID = validateItemIDInputSrUp(itemCount, items);
        
        if (inputID.empty()) {
            cout << endl << "Returning to Main Menu.." << endl;
            system("pause");
            system("cls");
            return;
        }

        for (int i = 0; i < itemCount; i++) {
            if (inputID == items[i][0]) {
                validID = true;

                string userChoice;
                bool validQP = false;

                do {
                    cout << endl << "Do you want to update the quantity or the price? (input Q or P): ";
                    getline(cin, userChoice);

                    userChoice = toUpperCase(userChoice);

                    if (isEmpty(userChoice)) {
                        cout << "Invalid input! Empty inputs are not allowed." << endl;
                    }
                    else if (hasSpace(userChoice)) {
                        cout << "Invalid input! Spaces are not allowed." << endl;
                    }
                    else if (hasSpecialChar(userChoice)) {
                        cout << "Invalid input! Special characters are not allowed." << endl;
                    }
                    else if (userChoice != "Q" && userChoice != "P") {
                        cout << "Enter 'Q' for Quantity or 'P' for Price only!" << endl;
                    }
                    else {
                        validQP = true;
                    }
                } while (!validQP);

                if (userChoice == "Q") {
                    string qty = items[i][3];
                    int newQuantity = validateQuantityInput(stoi(qty));

                    string oldQuantity = items[i][3];
                    items[i][3] = to_string(newQuantity);

                    cout << endl << "Quantity of Item " << items[i][1] << " is updated from " << oldQuantity << " to " << newQuantity << endl << endl;
                } else {
                    double newPrice = validatePriceInput(items[i][4]);

                    string oldPrice = items[i][4];
                    items[i][4] = to_string(newPrice);
                    cout << fixed << setprecision(2) << endl << "Price of Item " << items[i][1] << " is updated from P" << stod(oldPrice) << " to P" << newPrice << endl << endl;
                }

                displayHeader();

                string updatedCategoryInput = items[i][2];
                string updatedCategory = getCategoryInput(updatedCategoryInput);

                double price = stod(items[i][4]);

                cout << string(76, '-') << endl;
                displayItem(items, i, price, updatedCategory);

                cout << string(76, '-') << endl;
                cout << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }
        }
    }
}

void removeItem() override {
    cout << string(76, '-') << endl;
    cout << "\t\t\t\tRemove Item" << endl;
    
    cout << string(76, '-') << endl;

    if (itemCount == 0) {
        cout << "There are no items in the inventory!" << endl << endl;
        cout << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
        return;
    }

    displayHeader();

    for (int i = 0; i < itemCount; i++) {
        string category = items[i][2];
        double price = stod(items[i][4]);
        displayItem(items, i, price, category);
    }

    bool validID = false;

    while (!validID) {
        cout << string(76, '-') << endl;

        string inputID = validateItemIDInputSrUp(itemCount, items);
        
        if (isEmpty(inputID)) {
            cout << "Returning to Main Menu.." << endl;
            system("pause");
            system("cls");
            return;
        }

        for (int i = 0; i < itemCount; i++) {
            if (inputID == items[i][0]) {
                validID = true;
                string itemName = items[i][1];

                for (int j = i; j < itemCount - 1; j++) {
                    for (int k = 0; k < 5; k++) {
                        items[j][k] = items[j + 1][k];
                    }
                }
                itemCount--;

                cout << endl << "Item " << itemName << " has been removed from the inventory." << endl;
                cout << "Returning to Main Menu.." << endl;
                system("pause");
                system("cls");
                return;
            }
        }

        cout << "Invalid ID! Item not found." << endl;
    }
}

    void displayItemsByCategory() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\tDisplay Items by Category" << endl;
        cout << string(76, '-') << endl << endl;

        string categoryInput;

        if (itemCount == 0) {
            cout << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        categoryInput = validateCategoryInput();

        bool categoryFound = false;
        cout << fixed << setprecision(2);

        for (int i = 0; i < 3; i++) {
            if (categoryInput == categories[i]) {
                categoryFound = true;
                bool itemFound = false;
                system("cls");

                for (int j = 0; j < itemCount; j++) {
                    if (items[j][2] == categoryInput) {
                        if (!itemFound) {
                            cout << string(76, '-') << endl << "\t\t      Displaying Items by Category" << endl << string(76, '-') << endl;

                            displayHeader();

                            itemFound = true;
                        }

                        string category;
                        int categoryNum;

                        category = getCategoryInput(categoryInput);

                        double price = stod(items[j][4]);

                        displayItem(items, j, price, category);
                    }
                }

                cout << string(76, '-') << endl;

                if (!itemFound) {
                    cout << "\t\t No items found in this category!" << endl;
                    cout << string(76, '-') << endl;
                }
                break;
            }
        }

        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }

    void displayAllItems() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\t All Items" << endl;
        cout << string(76, '-') << endl;

        string category;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        else {
            displayHeader();

            for (int i = 0; i < itemCount; i++) {

                double price = stod(items[i][4]);
                string itemCategory = items[i][2];

                category = getCategoryInput(itemCategory);

                displayItem(items, i, price, category);

            }
        }
        cout << string(76, '-') << endl;
        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }

    void searchItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tSearch Item" << endl;
        cout << string(76, '-') << endl << endl;

        if (itemCount == 0) {
            cout << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        bool continueSearching = true;

        while (continueSearching) {
            string inputID = validateItemIDInputSrUp(itemCount, items);
            
            if (isEmpty(inputID)) {
                cout << endl << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }

            bool itemFound = false;
            for (int i = 0; i < itemCount; i++) {
                if (inputID == items[i][0]) {
                    itemFound = true;
                    system("cls");
                    cout << string(76, '-') << endl;
                    cout << "\t\t\t\tSearch Item" << endl;
                    displayHeader();

                    string itemCategory = items[i][2];
                    double price = stod(items[i][4]);
                    displayItem(items, i, price, itemCategory);

                    cout << string(76, '-') << endl;
                    cout << endl << "Returning to Main Menu..." << endl;
                    system("pause");
                    system("cls");
                    return;
                }
            }

            cout << "Invalid ID! Item not found." << endl << endl;
            string choice = validateYesNoInput();
            if (choice == "N") {
                continueSearching = false;
            }
        }

        cout << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }

    void sortItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tSort Items" << endl;
        cout << string(76, '-') << endl << endl;
        string sortChoice;

        if (itemCount == 0) {
            cout << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        bool validInputQP = false;

        while (!validInputQP) {
            cout << "Sort by quantity (Q) or price (P)? ";
            getline(cin, sortChoice);
                
            if (isEmpty(sortChoice)){
                    cout << "Invalid input! Empty inputs are not allowed." << endl;
                    continue;
                }
            else if (hasSpace(sortChoice)){
                    cout << "Invalid input! Spaces are not allowed." << endl;
                    continue;
                }
            else if (hasSpecialChar(sortChoice)){
                    cout << "Invalid input! Special characters are not allowed." << endl;
                    continue;
                }
            
            else if (sortChoice.length() != 1 || (sortChoice[0] != 'Q' && sortChoice[0] != 'P' && sortChoice[0] != 'q' && sortChoice[0] != 'p')) {
                cout << endl << "Only enter 'Q' for Quantity and 'P' for Price!" << endl;
                continue;
            }
            else {
                sortChoice = toupper(sortChoice[0]);
                validInputQP = true;
            }
        }

        bool ascending = true;
        string orderChoice;
        bool validInputAD = false;

        while (!validInputAD) {
            cout << "Do you want to sort in ascending (A) or descending (D) order?: ";
            getline(cin, orderChoice);

            if (isEmpty(orderChoice)){
                cout << "Invalid input! Empty inputs are not allowed." << endl;
            }
            else if (hasSpace(orderChoice)){
                cout << "Invalid input! Spaces are not allowed." << endl;
            }
            else if (hasSpecialChar(orderChoice)){
                cout << "Invalid input! Special characters are not allowed." << endl;
            }
            else if (orderChoice.length() != 1 || (orderChoice[0] != 'A' && orderChoice[0] != 'D' && orderChoice[0] != 'a' && orderChoice[0] != 'd')) {
                cout << endl << "Only enter 'A' for Ascending and 'D' for Descending!" << endl;
            }
            else {
                orderChoice = toupper(orderChoice[0]);
                ascending = (orderChoice == "A");
                validInputAD = true;
            }
        }

        // Sorting logic (Bubble Sort)
        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                bool swapCondition = false;

                if (sortChoice == "Q") {
                    // Quantity sorting
                    swapCondition = ascending ? (stoi(items[j][3]) > stoi(items[j + 1][3])) : (stoi(items[j][3]) < stoi(items[j + 1][3]));
                }
                else if (sortChoice == "P") {
                    // Price sorting
                    swapCondition = ascending ? (stod(items[j][4]) > stod(items[j + 1][4])) : (stod(items[j][4]) < stod(items[j + 1][4]));
                }

                if (swapCondition) {
                    // Swap items
                    for (int k = 0; k < 5; k++) {
                        string temp = items[j][k];
                        items[j][k] = items[j + 1][k];
                        items[j + 1][k] = temp;
                    }
                }
            }
        }

        string sortBy = (sortChoice == "Q") ? "Quantity" : "Price";
        string orderBy = ascending ? "Ascending" : "Descending";

        cout << "Items sorted successfully by " << sortBy << " in " << orderBy << " order!" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        displayAllItems();
    }

    void displayLowStockItems() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t    Low Stock Items" << endl;
        bool found = false;
        string category;

        if (itemCount == 0) {
            cout << string(76, '-') << endl;
            cout << endl << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << string(76, '-') << endl;

        for (int i = 0; i < itemCount; i++) {
            if (stoi(items[i][3]) <= 5) {
                if (!found) {
                    displayHeader();

                    found = true;
                }

                string itemCategory = items[i][2];
                
                category = getCategoryInput(itemCategory);

                double price = stod(items[i][4]);

                displayItem(items, i, price, category);
            }
        }
        if (!found) {
            cout << "\t\t\tNo low stock items found!" << endl;
        }

        cout << string(76, '-') << endl;
        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }
};

int main() {

    Items inventory;
    int choice;
    string input;

    system("cls");

    do {

        cout << "Main Menu" << endl << endl;
        cout << "1 - Add Item" << endl;
        cout << "2 - Update Item" << endl;
        cout << "3 - Remove Item" << endl;
        cout << "4 - Display Items by Category" << endl;
        cout << "5 - Display All Items" << endl;
        cout << "6 - Search Item" << endl;
        cout << "7 - Sort Items" << endl;
        cout << "8 - Display Low Stock Items" << endl;
        cout << "9 - Exit" << endl;

        cout << endl << "Enter your choice (1-9): ";
        getline(cin, input);


        if (input.length() == 1 && isdigit(input[0]) && input[0] >= '1' && input[0] <= '9') {
            choice = input[0] - '0';
        }
        else {
            cout << endl << "Invalid input! Please enter a single number between 1 and 9 without spaces." << endl;
            system("pause");
            system("cls");
            continue;
        }


        switch (choice) {
        case 1:
            system("cls");
            inventory.addItem();
            break;
        case 2:
            system("cls");
            inventory.updateItem();
            break;
        case 3:
            system("cls");
            inventory.removeItem();
            break;
        case 4:
            system("cls");
            inventory.displayItemsByCategory();
            break;
        case 5:
            system("cls");
            inventory.displayAllItems();
            break;
        case 6:
            system("cls");
            inventory.searchItem();
            break;
        case 7:
            system("cls");
            inventory.sortItem();
            break;
        case 8:
            system("cls");
            inventory.displayLowStockItems();
            break;
        case 9:
            cout << endl << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << endl << "Invalid choice! Please enter a number between 1 and 9." << endl;
        }

        cout << endl;
    } while (choice != 9);

    return 0;
}