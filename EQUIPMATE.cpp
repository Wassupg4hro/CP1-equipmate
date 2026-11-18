#include <iostream>
#include <string>
using namespace std;

bool isValidDateFormat(const string& date) {

    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {

        if (i == 4 || i == 7) {
            continue;
        }

        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    return true;
}

int main() {

    string eqName[5] = {"Chair", "Table", "Speaker", "Whiteboard", "Microphone"};
    int eqStock[5] = {5, 3, 4, 2, 6};
    int userBorrowedQty[5] = {0, 0, 0, 0, 0};

    const int MAX = 100;
    int borrowedEquip[MAX];
    int borrowedQty[MAX];
    int returnedQty[MAX] = {0};
    string returnDate[MAX];
    string actualReturnDate[MAX];
    int recordCount = 0;

    string borrower, contact, information;
    int dashboardChoice = 1;
    int systemChoice = -1;
    int equipChoice;

    cout << "\n===== EQUIPMATE LOGIN =====\n";

    do {
        cout << "Enter Borrower's Full Name: ";
        getline(cin, borrower);

        if (borrower.empty()) {
            cout << "Invalid input! Name cannot be empty.\n";
        }

    } while (borrower.empty());

    do {
        cout << "Enter Borrower's Contact Information: ";
        getline(cin, contact);

        if (contact.empty()) {
            cout << "Invalid input! Contact information cannot be empty.\n";
        }

    } while (contact.empty());

    do {
        cout << "Enter Borrower's LRN(Learner Reference Number): ";
        getline(cin, information);

        if (information.empty()) {
            cout << "Invalid input! LRN cannot be empty.\n";
        }

    } while (information.empty());

    cout << "\nWelcome, " << borrower << "!\n";

    do {


        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            dashboardChoice = -1;
            cout << "Invalid input! Please enter numbers only.\n";
            continue;
        }

        switch (dashboardChoice) {

            case 1: {

                do {

                    cout << "\n===== EQUIPMENT BORROWING SYSTEM =====\n";
                    cout << "1. View Available Equipment\n";
                    cout << "2. Borrow Equipment\n";
                    cout << "3. Return Borrowed Equipment\n";
                    cout << "4. View Your Records\n";
                    cout << "0. Back to Dashboard\n";
                    cout << "Enter your choice: ";
                    cin >> systemChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        systemChoice = -1;
                        cout << "Invalid input! Please enter numbers only.\n";
                        continue;
                    }

                    switch (systemChoice) {

                        case 1: {

                            cout << "\n===== AVAILABLE EQUIPMENT =====\n";

                            for (int i = 0; i < 5; i++) {
                                cout << i + 1 << ". " << eqName[i]
                                     << " (Available Stock: " << eqStock[i] << ")\n";
                            }

                            cout << "\nEnter equipment number to view (1-5): ";
                            cin >> equipChoice;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input! Please enter numbers only.\n";
                                break;
                            }

                            if (equipChoice >= 1 && equipChoice <= 5) {

                                int index = equipChoice - 1;

                                cout << "\n===== EQUIPMENT DETAILS =====\n";
                                cout << "Equipment Name: " << eqName[index] << endl;
                                cout << "Available Stock: " << eqStock[index] << endl;
                                cout << "Currently Borrowed: " << userBorrowedQty[index] << endl;

                            } else {

                                cout << "Invalid equipment choice.\n";
                            }

                            break;
                        }


                        case 2: {

                            int eqNum, qty;
                            bool validSelection = false;

                            cout << "\n===== BORROWING INSTRUCTIONS =====\n";
                            cout << "1. Select the equipment you want to borrow.\n";
                            cout << "2. Enter the quantity.\n";
                            cout << "3. Provide your expected return date.\n";
                            cout << "4. Return the equipment on or before the due date.\n";

                            while (!validSelection) {

                                cout << "\n===== AVAILABLE EQUIPMENT =====\n";

                                for (int i = 0; i < 5; i++) {
                                    cout << i + 1 << ". " << eqName[i]
                                         << " (Stock: " << eqStock[i] << ")\n";
                                }

                                cout << "Enter equipment number (1-5): ";
                                cin >> eqNum;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Invalid input! Please enter numbers only.\n";
                                    continue;
                                }

                                if (eqNum < 1 || eqNum > 5) {
                                    cout << "Invalid equipment number.\n";
                                    continue;
                                }

                                int index = eqNum - 1;

                                if (eqStock[index] <= 0) {
                                    cout << "That equipment is unavailable.\n";
                                    continue;
                                }

                                cout << "Enter quantity (1-" << eqStock[index] << "): ";
                                cin >> qty;

                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Invalid input! Please enter numbers only.\n";
                                    continue;
                                }

                                if (qty <= 0) {
                                    cout << "Invalid quantity! Please enter a number greater than zero.\n";
                                    continue;
                                }

                                if (qty > eqStock[index]) {
                                    cout << "Not enough stock available!\n";
                                    continue;
                                }

                                if (recordCount >= MAX) {
                                    cout << "Borrowing record limit reached.\n";
                                    break;
                                }

                                bool validDate = false;

                                while (!validDate) {

                                    cout << "Enter expected return date (YYYY-MM-DD): ";
                                    cin >> returnDate[recordCount];

                                    if (isValidDateFormat(returnDate[recordCount])) {
                                        validDate = true;
                                    } else {
                                        cout << "Invalid date format! Please use YYYY-MM-DD.\n";
                                    }
                                }

                                borrowedEquip[recordCount] = index;
                                borrowedQty[recordCount] = qty;
                                returnedQty[recordCount] = 0;
                                actualReturnDate[recordCount] = "Not yet returned";

                                eqStock[index] -= qty;
                                userBorrowedQty[index] += qty;

                                recordCount++;

                                cout << "\nBorrowing recorded successfully!\n";
                                cout << "Borrower: " << borrower << endl;
                                cout << "Equipment: " << eqName[index] << endl;
                                cout << "Quantity: " << qty << endl;

                                validSelection = true;
                            }

                            break;
                        }


                        case 3: {

                            int totalBorrowed = 0;

                            cout << "\n===== RETURN MENU =====\n";

                            for (int i = 0; i < recordCount; i++) {

                                if (returnedQty[i] < borrowedQty[i]) {

                                    cout << i + 1 << ". "
                                         << eqName[borrowedEquip[i]]
                                         << " (Remaining: "
                                         << borrowedQty[i] - returnedQty[i]
                                         << ", Return Date: "
                                         << returnDate[i] << ")\n";

                                    totalBorrowed++;
                                }
                            }

                            if (totalBorrowed == 0) {
                                cout << "There is no borrowed equipment to return.\n";
                                break;
                            }

                            int returnChoice;

                            cout << "\nEnter record number to return (0 to go back): ";
                            cin >> returnChoice;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input! Please enter numbers only.\n";
                                break;
                            }

                            if (returnChoice == 0) {
                                cout << "Returning to equipment menu.\n";
                                break;
                            }

                            if (returnChoice < 1 || returnChoice > recordCount ||
                                returnedQty[returnChoice - 1] >= borrowedQty[returnChoice - 1]) {

                                cout << "Invalid selection.\n";
                                break;
                            }

                            int index = returnChoice - 1;
                            int equipIndex = borrowedEquip[index];

                            int remaining = borrowedQty[index] - returnedQty[index];

                            int returnQty;

                            cout << "Enter quantity to return (1-" << remaining << "): ";
                            cin >> returnQty;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input! Please enter numbers only.\n";
                                break;
                            }

                            if (returnQty < 1 || returnQty > remaining) {
                                cout << "Invalid return quantity.\n";
                                break;
                            }

                            string enteredActualDate;
                            bool validDate = false;

                            while (!validDate) {

                                cout << "Enter actual return date (YYYY-MM-DD): ";
                                cin >> enteredActualDate;

                                if (isValidDateFormat(enteredActualDate)) {
                                    validDate = true;
                                } else {
                                    cout << "Invalid date format! Please use YYYY-MM-DD.\n";
                                }
                            }

                            eqStock[equipIndex] += returnQty;
                            userBorrowedQty[equipIndex] -= returnQty;
                            returnedQty[index] += returnQty;
                            actualReturnDate[index] = enteredActualDate;

                            cout << "\nReturned successfully!\n";

                            if (actualReturnDate[index] > returnDate[index]) {
                                cout << "Returning date Overdue! Thank you.\n";
                            }
                            else {
                                cout << "=====Thank you.====\n";
                            }

                            break;
                        }


                        case 4: {

                            bool found = false;
                            string today;

                            cout << "\n===== YOUR BORROWING RECORDS =====\n";

                            if (recordCount == 0) {
                                cout << "No borrowed equipment found.\n";
                                break;
                            }

                            bool validDate = false;

                            while (!validDate) {

                                cout << "Enter today's date (YYYY-MM-DD): ";
                                cin >> today;

                                if (isValidDateFormat(today)) {
                                    validDate = true;
                                } else {
                                    cout << "Invalid date format! Please use YYYY-MM-DD.\n";
                                }
                            }

                            for (int i = 0; i < recordCount; i++) {

                                cout << "\nRecord No.: " << i + 1;

                                cout << "\nBorrowed Equipment: "
                                     << eqName[borrowedEquip[i]];

                                cout << "\nQuantity: "
                                     << borrowedQty[i];

                                cout << "\nReturn Date: "
                                     << returnDate[i];

                                cout << "\nActual Return Date: "
                                     << actualReturnDate[i];

                                if (returnedQty[i] == borrowedQty[i]) {

                                    cout << "\nStatus: Returned";

                                    if (actualReturnDate[i] > returnDate[i]) {
                                        cout << "\nOverdue: Yes";
                                    } else {
                                        cout << "\nOverdue: No";
                                    }

                                } else {

                                    if (returnedQty[i] > 0) {
                                        cout << "\nStatus: Partially Returned";
                                    } else {
                                        cout << "\nStatus: Borrowed";
                                    }

                                    if (today > returnDate[i]) {
                                        cout << "\nOverdue: Yes";
                                    } else {
                                        cout << "\nOverdue: No";
                                    }
                                }

                                cout << "\n-----------------------------\n";

                                found = true;
                            }

                            break;
                        }


                        case 0:

                            cout << "Exiting Equipment Borrowing System...\n";
                            break;


                        default:

                            cout << "Invalid choice. Please try again.\n";
                    }

                } while (systemChoice != 0);

                break;
            }


            case 2: {

                cout << "\n===== MY BORROWED EQUIPMENTS =====\n";
                cout << "Borrower Name: " << borrower << endl;
                cout << "Contact Information: " << contact << endl;

                if (recordCount == 0) {

                    cout << "No borrowing records found.\n";
                    break;
                }

                string today;

                bool validDate = false;

                while (!validDate) {

                    cout << "\nEnter today's date (YYYY-MM-DD): ";
                    cin >> today;

                    if (isValidDateFormat(today)) {
                        validDate = true;
                    } else {
                        cout << "Invalid date format! Please use YYYY-MM-DD.\n";
                    }
                }

                for (int i = 0; i < recordCount; i++) {

                    cout << "\nRecord No.: " << i + 1;

                    cout << "\nEquipment Name: "
                         << eqName[borrowedEquip[i]];

                    cout << "\nQuantity: "
                         << borrowedQty[i];

                    cout << "\nReturned Quantity: "
                         << returnedQty[i];

                    cout << "\nExpected Return Date: "
                         << returnDate[i];

                    cout << "\nActual Return Date: "
                         << actualReturnDate[i];

                    if (returnedQty[i] == borrowedQty[i]) {

                        cout << "\nStatus: Returned";

                        if (actualReturnDate[i] > returnDate[i]) {
                            cout << "\nOverdue: Yes";
                        } else {
                            cout << "\nOverdue: No";
                        }

                    } else {

                        if (returnedQty[i] > 0) {
                            cout << "\nStatus: Partially Returned";
                        } else {
                            cout << "\nStatus: Borrowed";
                        }

                        if (today > returnDate[i]) {
                            cout << "\nOverdue: Yes";
                        } else {
                            cout << "\nOverdue: No";
                        }
                    }

                    cout << "\n-----------------------------\n";
                }

                break;
            }


            case 0:

                cout << "\nLogging out...\n";
                cout << "Thank you for using EquipMate, " << borrower << "!\n";
                break;


            default:

                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (false);

    return 0;
}