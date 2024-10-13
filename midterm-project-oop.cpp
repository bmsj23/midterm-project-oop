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
    string categories[3] = {"clothing", "electronics", "entertainment"};

public:
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

        string category;
        bool categoryFound = false;

        do {
            cout << "Input the category of the item (Clothing, Electronics, Entertainment): ";
            getline(cin, category);

            for (char &c : category) {
                c = tolower(c);
            }

            if (category != "clothing" && category != "electronics" && category != "entertainment") {
                cout << endl << "Clothing, Electronics, and Entertainment are the only categories accepted!" << endl << endl;
            }
        } while (category != "clothing" && category != "electronics" && category != "entertainment");

        for (int i = 0; i < 3; i++) {

            if (category == categories[i]) {
                categoryFound = true;

                if (itemCount < 100) {
                    string id, name;
                    int quantity;
                    double price;
                    bool validID = false;

                    cout << endl << "Item Details" << endl;

                    do {
                        validID = true;
                        cout << endl << "Input Item ID (alphanumeric, no spaces: e.g. ID001): ";
                        cin.clear();
                        cin.sync();

                        getline(cin, id);

                        for (char &c : id) {
                            c = toupper(c);
                        }

                        for (int i = 0; i < id.length(); i++) {
                            if (id[i] == ' ') {
                                cout << "Invalid ID! No spaces allowed." << endl;
                                validID = false;
                                break;
                            }
                            else if (!isalnum(id[i])) {
                                cout << "Invalid ID! Only alphanumeric characters are allowed." << endl;
                                validID = false;
                                break;
                            }
                        }

                        if (validID) {
                            for (int i = 0; i < itemCount; i++) {
                                if (items[i][0] == id) {
                                    cout << "This ID already exists! Please enter a unique ID." << endl;
                                    validID = false;
                                    break;
                                }
                            }
                        }

                    } while (!validID);

                    cout << endl << "Input Item Name: ";
                    getline(cin, name);

                    bool validInput = false;

                    do {
                        string quantityInput;
                        validInput = true;

                        cout << endl << "Input Item Quantity: ";
                        getline(cin, quantityInput);

                        for (char c : quantityInput) {
                            if (c == ' ') {
                                cout << "Invalid input! No spaces allowed." << endl;
                                validInput = false;
                                break;
                            }
                            else if (!isdigit(c)) {
                                cout << "Invalid input! Enter numbers only." << endl;
                                validInput = false;
                                break;
                            }
                        }

                        if (validInput) {
                            quantity = stoi(quantityInput);
                            if (quantity <= 0) {
                                cout << "Invalid input! Quantity must be greater than zero." << endl;
                                validInput = false;
                            }
                        }

                    } while (!validInput);

                    string priceInput;
                    
                    do {
                        validInput = true;
                        bool decimalPointFound = false;

                        cout << endl << "Input Item Price: ";
                        getline(cin, priceInput);

                        for (char c : priceInput) {
                            if (c == ' ') {
                                cout << "Invalid input! No spaces allowed." << endl;
                                validInput = false;
                                break;
                            }
                            else if (c == '.') {
                                if (decimalPointFound) {
                                    validInput = false;
                                    break;
                                }
                                decimalPointFound = true;
                            }
                            else if (!isdigit(c)) {
                                cout << "Invalid input! Enter numbers only." << endl;
                                validInput = false;
                                break;
                            }
                        }

                        if (validInput) {
                            price = stod(priceInput);
                            if (price <= 0) {
                                cout << "Invalid input! Price must be greater than zero." << endl;
                                validInput = false;
                            }
                        }

                    } while (!validInput);

                    setItemDetails(itemCount, id, name, category, quantity, price);
                    itemCount++;

                    system("cls");

                    cout << endl << string(76, '-') << endl << "\t\t\t Item added successfully!" << endl << string(76, '-') << endl;

                    cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;

                    string categoryInput;
                    int categoryNum;

                    if (category == "clothing") {
                        categoryNum = 1;
                    }
                    else if (category == "electronics") {
                        categoryNum = 2;
                    }
                    else {
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


                    cout << fixed << setprecision(2) << left << setw(10) << id << left << setw(25) << name << left << setw(12) << items[i][3] << "P" << left << setw(15) << priceInput << left << setw(20) << categoryInput << endl;
                    cout << string(76, '-') << endl;
                    
                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                }
                else {
                    cout << endl << "Inventory is full, cannot add more items!" << endl;
                }
                break;
            }
        }

        if (!categoryFound) {
            cout << "Category " << category << " does not exist!" << endl;
        }
    }

    void updateItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tUpdate Item" << endl;
        cout << string(76, '-') << endl;

        string inputID;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
        cout << string(76, '-') << endl;

        for (int i = 0; i < itemCount; i++) {
                string category;
                int categoryNum;

                if (items[i][2] == "clothing") {
                    categoryNum = 1;
                }
                else if (items[i][2] == "electronics") {
                    categoryNum = 2;
                }
                else {
                    categoryNum = 3;
                }

                switch (categoryNum) {
                case 1:
                    category = "Clothing";
                    break;
                case 2:
                    category = "Electronics";
                    break;
                case 3:
                    category = "Entertainment";
                    break;
                }

                double price = stod(items[i][4]);

                cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;
        }

        bool validID = false;

        while (!validID) {
            cout << string(76, '-') << endl;

            cout << "Input the ID of the item you wish to update: ";
            getline(cin, inputID);

            for (char &c : inputID) {
                c = toupper(c);
            }

            bool hasSpace = false;
            for (char c : inputID) {
                if (c == ' ') {
                    hasSpace = true;
                    break;
                }
            }

            if (hasSpace) {
                cout << "Invalid input! No spaces allowed." << endl;
                continue;
            }

            for (int i = 0; i < itemCount; i++) {
                if (inputID == items[i][0]) {
                    validID = true;

                    string userChoice;

                    cout << endl << "Do you want to update the quantity or the price? (input Q or P): ";
                    getline(cin, userChoice); 

                    for (char &c : userChoice) {
                        c = toupper(c);
                    }

                    while (userChoice != "Q" && userChoice != "P") {
                        cout << "Enter 'Q' for Quantity or 'P' for Price only!" << endl;

                        cout << "Do you want to update the quantity or the price? (input Q or P): ";
                        getline(cin, userChoice);

                        for (char &c : userChoice) {
                            c = toupper(c);
                        }
                    }

                    if (userChoice == "Q") {

                        string quantityInput;
                        int newQuantity;
                        bool validQuantity = false;

                        while (!validQuantity) {
                            cout << endl << "Input new value for Quantity: ";
                            getline(cin, quantityInput);

                            bool isNumeric = true;
                            hasSpace = false;
                            for (char c : quantityInput) {
                                if (!isdigit(c)) {
                                    isNumeric = false;
                                }
                                if (c == ' ') {
                                    hasSpace = true;
                                }
                            }

                            if (hasSpace) {
                                cout << "Invalid input! No spaces allowed." << endl;
                            }
                            else if (isNumeric && quantityInput.length() > 0) {
                                newQuantity = stoi(quantityInput);
                                if (newQuantity > 0) {
       
                                    if (newQuantity == stoi(items[i][3])) {
                                        cout << "Invalid input! Quantity cannot be the same as the current value." << endl;
                                    }
                                    else {
                                        validQuantity = true;
                                    }
                                }
                                else {
                                    cout << "Invalid input! Quantity must be greater than zero." << endl;
                                }
                            }
                            else {
                                cout << "Invalid input! Please enter a positive integer." << endl;
                            }
                        }

                        string oldQuantity = items[i][3];
                        items[i][3] = to_string(newQuantity);

                        cout << endl << "Quantity of Item " << items[i][1] << " is updated from " << oldQuantity << " to " << newQuantity << endl << endl;
                    }
                    else {
                        string priceInput;
                        double newPrice;
                        bool validPrice = false;

                        while (!validPrice) {
                            cout << endl << "Input new value for Price: ";
                            getline(cin, priceInput);

                            bool validPriceInput = true;
                            bool decimalPointFound = false;

                            for (char c : priceInput) {
                                if (c == '.') {
                                    if (decimalPointFound) {
                                        validPriceInput = false;
                                        break;
                                    }
                                    decimalPointFound = true;
                                }
                                else if (!isdigit(c)) {
                                    validPriceInput = false;
                                    break;
                                }
                            }

                            if (validPriceInput && priceInput.length() > 0) {
                                newPrice = stod(priceInput);
                                if (newPrice > 0) {
                                
                                    if (newPrice == stod(items[i][4])) {
                                        cout << "Invalid input! Price cannot be the same as the current value." << endl;
                                    }
                                    else {
                                        validPrice = true;
                                    }
                                }
                                else {
                                    cout << "Invalid input! Price must be greater than zero." << endl;
                                }
                            }
                            else {
                                cout << "Invalid input! Please enter a valid number." << endl;
                            }
                        }

                        string oldPrice = items[i][4];
                        items[i][4] = to_string(newPrice);
                        cout << fixed << setprecision(2) << endl << "Price of Item " << items[i][1] << " is updated from P" << stod(oldPrice) << " to P" << newPrice << endl << endl;
                    }
            
                    cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;

                    string category;
                    int categoryNum;

                    if (items[i][2] == "clothing") {
                        categoryNum = 1;
                    }
                    else if (items[i][2] == "electronics") {
                        categoryNum = 2;
                    }
                    else {
                        categoryNum = 3;
                    }

                    switch (categoryNum) {
                    case 1:
                        category = "Clothing";
                        break;
                    case 2:
                        category = "Electronics";
                        break;
                    case 3:
                        category = "Entertainment";
                        break;
                    }

                    double price = stod(items[i][4]);

                    
                    cout << string(76, '-') << endl;
                    cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;

                    cout << string(76, '-') << endl;
                    cout << "Returning to Main Menu..." << endl;
                    system("pause");
                    system("cls");
                    return; 
                }
            }

            cout << endl << "Invalid ID!" << endl;
            
            char tryAgain;

            cout << "Do you want to try again? (Y/N): ";
            cin >> tryAgain;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            tryAgain = toupper(tryAgain);
            
            if (tryAgain != 'Y') {
                
                cout << endl << "Returning to Main Menu.." << endl;
                system("pause");
                system("cls");
                return;
            }
        }
    }

    void removeItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tRemove Item" << endl;
        cout << string(76, '-') << endl;

        string inputID;
        bool validID = false;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(12) << "Price" << left << setw(15) << "Category" << endl;
        cout << string(76, '-') << endl;

        for (int i = 0; i < itemCount; i++) {
            double price = stod(items[i][4]);

            cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << price << "   " << left << setw(15) << items[i][2] << endl;
        }

        while (!validID) {
            cout << string(76, '-') << endl;
            cout << "Input the ID of the item you wish to remove: ";
            cin >> inputID;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (char &c : inputID) {
                c = toupper(c);
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

                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return;
                }
            }

            cout << endl << "Invalid ID!" << endl;

            char tryAgain;
            cout << "Do you want to try again? (Y/N): ";
            cin >> tryAgain;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (toupper(tryAgain) == 'Y') {
                validID = false;
            }
            else {
                cout << endl << "Returning to Main Menu.." << endl;
                system("pause");
                system("cls");
                return;
            }
        }
    }

    void displayItemsByCategory() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\tDisplay Items by Category" << endl;
        cout << string(76, '-') << endl << endl;

        string inputCategory;

        if (itemCount == 0) {
            cout << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        do
        {
            cout << "Enter category (Clothing, Electronics, Entertainment): ";
            getline(cin, inputCategory);

            for (char &c : inputCategory) {
                c = tolower(c);
            }
            if (inputCategory != "clothing" && inputCategory != "electronics" && inputCategory != "entertainment") {
                cout << endl << "Clothing, Electronics, and Enteratainment are the only categories accepted!" << endl << endl;
            }
        } while (inputCategory != "clothing" && inputCategory != "electronics" && inputCategory != "entertainment");

        bool categoryFound = false;
        cout << fixed << setprecision(2);

        for (int i = 0; i < 3; i++) {
            if (inputCategory == categories[i]) {
                categoryFound = true;
                bool itemFound = false;
                system("cls");

                for (int j = 0; j < itemCount; j++) {
                    if (items[j][2] == inputCategory) {
                        if (!itemFound) {
                            cout << string(76, '-') << endl << "\t\t      Displaying Items by Category" << endl << string(76, '-') << endl;

                            cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                            cout << string(76, '-') << endl;

                            itemFound = true;
                        }

                        string category;
                        int categoryNum;

                        if (items[j][2] == "clothing") {
                            categoryNum = 1;
                        }
                        else if (items[j][2] == "electronics") {
                            categoryNum = 2;
                        }
                        else {
                            categoryNum = 3;
                        }

                        switch (categoryNum) {
                        case 1:
                            category = "Clothing";
                            break;
                        case 2:
                            category = "Electronics";
                            break;
                        case 3:
                            category = "Entertainment";
                            break;
                        }

                        double price = stod(items[j][4]);

                        cout << fixed << setprecision(2) << left << setw(10) << items[j][0] << left << setw(25) << items[j][1] << left << setw(12) << items[j][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;
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

        if (!categoryFound) {
            cout << "Invalid category!" << endl;
        }

        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }

    void displayAllItems() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\t All Items" << endl;
        cout << string(76, '-') << endl;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }
        else {
            cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
            cout << string(76, '-') << endl;

            for (int i = 0; i < itemCount; i++) {
                string category;
                int categoryNum;

                if (items[i][2] == "clothing") {
                    categoryNum = 1;
                }
                else if (items[i][2] == "electronics") {
                    categoryNum = 2;
                }
                else {
                    categoryNum = 3;
                }

                switch (categoryNum) {
                case 1:
                    category = "Clothing";
                    break;
                case 2:
                    category = "Electronics";
                    break;
                case 3:
                    category = "Entertainment";
                    break;
                }

                double price = stod(items[i][4]);

                cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;
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
        string inputID;

        if (itemCount == 0) {
            cout << "There are no items in the inventory!" << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        bool itemIDFound = false;

        while (!itemIDFound) {
            cout << "Input the ID of the item you wish to search: ";
            cin >> inputID;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (char &c : inputID) {
                c = toupper(c);
            }

            for (int i = 0; i < itemCount; i++) {
                if (inputID == items[i][0]) {
                    itemIDFound = true;

                    system("cls");

                    cout << string(76, '-') << endl;
                    cout << "\t\t\t\tSearch Item" << endl;
                    cout << string(76, '-') << endl;

                    cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;

                    string category;
                    int categoryNum;

                    if (items[i][2] == "clothing") {
                        categoryNum = 1;
                    }
                    else if (items[i][2] == "electronics") {
                        categoryNum = 2;
                    }
                    else {
                        categoryNum = 3;
                    }

                    switch (categoryNum) {
                    case 1:
                        category = "Clothing";
                        break;
                    case 2:
                        category = "Electronics";
                        break;
                    case 3:
                        category = "Entertainment";
                        break;
                    }

                    double price = stod(items[i][4]);

                    cout << fixed << setprecision(2)<< left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;

                    cout << string(76, '-') << endl;

                    break;
                }
            }

            if (!itemIDFound) {
                char tryAgain = 'N';
                cout << "Item not found! Do you want to try again? (Y/N): ";
                cin >> tryAgain;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (toupper(tryAgain) == 'Y') {
                    continue;
                }
                else if (toupper(tryAgain) == 'N') {
                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return; 
                }
                else {
                    cout << endl << "Only enter 'Y' or 'N'!" << endl << endl;
                }
            }
        }

        cout << endl << "Returning to Main Menu..." << endl;
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
                
            if (sortChoice.length() != 1 ||
                (sortChoice[0] != 'Q' && sortChoice[0] != 'P' && sortChoice[0] != 'q' && sortChoice[0] != 'p')) {
                cout << endl << "Only enter 'Q' for Quantity and 'P' for Price!" << endl;
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
            cin >> orderChoice;

            if (orderChoice.length() != 1 ||
                (orderChoice[0] != 'A' && orderChoice[0] != 'D' && orderChoice[0] != 'a' && orderChoice[0] != 'd')) {
                cout << endl << "Only enter 'A' for Ascending and 'D' for Descending!" << endl;
            }
            else {
                orderChoice = toupper(orderChoice[0]);
                ascending = (orderChoice == "A"); // Set ascending based on input
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

        cout << "Items sorted successfully!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        displayAllItems();
    }

    void displayLowStockItems() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t    Low Stock Items" << endl;
        bool found = false;

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
                    cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;
                    found = true;
                }

                string category;
                int categoryNum;

                if (items[i][2] == "clothing") {
                    categoryNum = 1;
                }
                else if (items[i][2] == "electronics") {
                    categoryNum = 2;
                }
                else {
                    categoryNum = 3;
                }

                switch (categoryNum) {
                case 1:
                    category = "Clothing";
                    break;
                case 2:
                    category = "Electronics";
                    break;
                case 3:
                    category = "Entertainment";
                    break;
                }

                double price = stod(items[i][4]);

                cout << fixed << setprecision(2) << left << setw(10) << items[i][0] << left << setw(25) << items[i][1] << left << setw(12) << items[i][3] << "P" << left << setw(15) << price << left << setw(20) << category << endl;
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
