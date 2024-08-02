/*CS102 Group project
Project title:-Online Bank Management system
Group member:Shreyas(2201CB58),Sakshi(2201MC36),Shashi(2201EE64),View(2201MM35),
Yashkrit(2201ME76),Aman(2201CB70),Sukrit(2201ME69),Yuvansh(2201ME77),Pranitha(2201PH21)*/

#include <iostream>                                    // Include libraries
#include <string>                                     
#include <cctype>                                      
#include <vector>                                      

using namespace std;

/* Function prototypes */
void displayDatabase();
void databaseAccess();
void start();
bool isStringOnlyIntegers(const string &str);
bool isValidPassword(const string &password);

struct Account {
    string username;
    int age;
    string gender;
    string passcode;
    string phone;
    string mail;
    int balance;

    Account() : age(0), balance(0) {}
};

vector<Account> user(100);                            
int b1 = 0, nou = 0;
char a1, a2, a3;
string masterkey;

bool isStringOnlyIntegers(const string &str)          // Function to check if string contains only integers
{
    for (char ch : str) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

bool isValidPassword(const string &password)          // Function to check if the password is valid
{
    if (password.length() < 8)
        return false;

    bool hasInteger = false;
    bool hasSymbol = false;

    for (char ch : password) {
        if (isdigit(ch))
            hasInteger = true;
        else if (!isalnum(ch))
            hasSymbol = true;
    }

    return hasInteger && hasSymbol;                   // Return true for valid password, otherwise false
}

void displayDatabase()                                // Function to display user accounts details
{
    for (int i = 0; i < user.size(); i++) {
        if (user[i].username != "NEXT") {
            cout << "Account " << i + 1 << ": username: " << user[i].username
                 << ", age: " << user[i].age
                 << ", gender: " << user[i].gender
                 << ", passcode: " << user[i].passcode
                 << ", phone number: " << user[i].phone
                 << ", mail id: " << user[i].mail
                 << ", account balance: ₹" << user[i].balance << "\n";
        } else {
            break;
        }
    }
}

void databaseAccess()                                 // Function to access bank database
{
    if (b1 < 3) {
        string s1;
        cout << "Enter masterkey: ";
        cin >> s1;
        if (s1 == masterkey) {                        // Checking if the entered masterkey is correct
            cout << "Unlocked\n";
            displayDatabase();                        // Calling displayDatabase function if masterkey is correct
            cout << "Enter 'm' to go to main page\n";
            char h;
            cin >> h;
            if (h == 'm')
                start();                              // Continue to main menu
        } else {
            cout << "Wrong password\n";
            b1++;
            databaseAccess();                         // Call function again
        }
    } else if (b1 == 3) {                             // Employee can enter wrong password at most 3 times
        cout << "Too many incorrect attempts\n";
        exit(0);                                      // After maximum limit, program will terminate
    }
}

void start()
{
    masterkey = "AbcdEfg";                            // Creating masterkey; required to access database
    cout << "\nHI! WELCOME TO HDFC BANK\nPress 'e' if you're an employee or 'c' if you're a customer. Press 't' to exit  ";
    cin >> a1;

    if (a1 == 'e') {                                  // EMPLOYEE SEGMENT
        cout << "Enter 'a' to access database\nEnter 'b' to go back\n\n";
        cin >> a2;
        if (a2 == 'b')
            start();
        else if (a2 == 'a')
            databaseAccess();
    } else if (a1 == 't') {                           // EXIT
        cout << "\nThank you for visiting HDFC bank, have a lovely day\n";
        exit(0);
    } else if (a1 == 'c') {                           // CUSTOMER SEGMENT
        cout << "\nWELCOME\n";
        cout << "Enter 'o' to open a bank account\nEnter 'a' to access the existing account\nEnter 'b' to go back\n\n";
        cin >> a3;
        if (a3 == 'o') {                              // Open a new bank account
            user[nou].balance = 0;
            char confirmation;
            cout << "\nEnter username (preferably your full name): ";
            cin.ignore();
            getline(cin, user[nou].username);

            while (true) {
                int x = 0;
                for (int i = 0; i < nou; i++) {
                    if (user[i].username == user[nou].username) {
                        x++;
                    }
                }
                if (x != 0) {                         // If username already exists
                    cout << "\nAccount with this username already exists.";
                    cout << "\nEnter a different username: ";
                    getline(cin, user[nou].username);
                } else {
                    break;
                }
            }

            cout << "Enter age: ";
            cin >> user[nou].age;                    
            cout << "Enter gender\nPress 'm' for male\nPress 'f' for female\n";
            cin >> user[nou].gender;                 
            while (user[nou].gender != "m" && user[nou].gender != "f") {
                cout << "Enter a valid gender: ";
                cin >> user[nou].gender;
            }

            cout << "Enter passcode for the account (It must have at least 1 integer, 1 symbol and must be at least 8 characters long): ";
            cin >> user[nou].passcode;               
            while (!isValidPassword(user[nou].passcode)) {
                cout << "Enter a valid password: ";
                cin >> user[nou].passcode;
            }

            cout << "Link your phone number to your account number: ";
            cin >> user[nou].phone;                  
            while (user[nou].phone.length() != 10 || !isStringOnlyIntegers(user[nou].phone)) {
                cout << "Enter a valid phone number: ";
                cin >> user[nou].phone;
            }

            cout << "Link your email to your account: ";
            cin >> user[nou].mail;                 

            cout << "Would you like to deposit some money? y/n\n";
            cin >> confirmation;                     
            while (confirmation != 'y' && confirmation != 'n') {
                cout << "Type y or n: ";
                cin >> confirmation;
            }
            if (confirmation == 'y') {
                cout << "Enter amount to be deposited: ₹";
                cin >> user[nou].balance;
            }

            nou++;
            user[nou].username = "NEXT";
            cout << "\nYour bank account has been opened. Thank you for choosing HDFC bank!\n";
            start();
        } else if (a3 == 'b') {
            start();                                 // Execution continues from main menu
        } else if (a3 == 'a') {                      // To access an existing account by the user
            string name, pass;
            int index = -1, b3 = 0;
            cout << "Enter username: ";
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < user.size(); i++) {
                if (user[i].username == name) {      // Checking if the username exists
                    index = i;
                    b3++;
                    break;
                }
            }

            if (b3 != 0) {                           // Username exists
                cout << "Enter passcode: ";
                cin >> pass;

                if (user[index].passcode == pass) {  // Checking if the password is correct
                    char v;
                    cout << "\n\nUnlocked\n";
                    cout << "username: " << user[index].username
                         << "\nage: " << user[index].age
                         << "\ngender: " << user[index].gender
                         << "\npasscode: " << user[index].passcode
                         << "\nphone number: " << user[index].phone
                         << "\nmail id: " << user[index].mail
                         << "\naccount balance: ₹" << user[index].balance << "\n";
                    cout << "Enter 'w' to withdraw money, 'd' to deposit money, 'e' to edit account details, 'b' to go to start\n";
                    cin >> v;
                    if (v == 'b')
                        start();
                    else if (v == 'd') {             // Deposit money
                        int v1;
                        cout << "Enter amount: ₹";
                        cin >> v1;
                        user[index].balance += v1;
                        cout << "Your current balance is ₹" << user[index].balance << "\n";
                        start();
                    } else if (v == 'w') {           // Withdraw money
                        int v1;
                        cout << "Enter amount: ₹";
                        cin >> v1;
                        if (v1 <= user[index].balance) {
                            user[index].balance -= v1;
                            cout << "₹" << v1 << " has been debited from your account.\n";
                            cout << "Your current balance is ₹" << user[index].balance << "\n";
                        } else {
                            cout << "Insufficient balance\n";
                        }
                        start();
                    } else if (v == 'e') {           // Edit account details
                        cout << "You can edit your phone number, email and passcode\n";
                        cout << "Enter 'p' to change phone number\nEnter 'm' to change email\nEnter 'c' to change passcode\n";
                        char v2;
                        cin >> v2;
                        if (v2 == 'p') {             // Edit phone number
                            cout << "Enter new phone number: ";
                            cin >> user[index].phone;
                            while (user[index].phone.length() != 10 || !isStringOnlyIntegers(user[index].phone)) {
                                cout << "Enter a valid phone number: ";
                                cin >> user[index].phone;
                            }
                            cout << "Phone number successfully updated!\n";
                        } else if (v2 == 'm') {      // Edit email
                            cout << "Enter new mail id: ";
                            cin >> user[index].mail;
                            cout << "Email successfully updated!\n";
                        } else if (v2 == 'c') {      // Edit passcode
                            cout << "Enter new passcode: ";
                            cin >> user[index].passcode;
                            while (!isValidPassword(user[index].passcode)) {
                                cout << "Enter a valid password: ";
                                cin >> user[index].passcode;
                            }
                            cout << "Passcode successfully updated!\n";
                        }
                        start();
                    }
                } else {                             // Incorrect password
                    cout << "Incorrect passcode!\n";
                    start();
                }
            } else {                                 // Username does not exist
                cout << "No account with this username exists!\n";
                start();
            }
        }
    } else {
        cout << "Please type either 'e' or 'c' or 't'\n";
        start();
    }
}

int main()
{
    user[0].username = "NEXT";                      // Initializing the username with a default value
    start();                                        // Start the program
    return 0;
}
