#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct ProductData
{
    int pCode;
    string pName;
    double price;
    int qty;
};

int displayMenu();
void addProduct(int pCode, string pName, double price, int qty);
void updateQty(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data);
void writeData(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data, bool found);
void updatePrice(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data);
double calculateBill(string itemName, int quantity, double &totalBill, ProductData &P, vector<ProductData> &data);
void setCredentials();
bool verifyCredentials(string &username, string &password);
void updateCredentials();
void signup();
bool signin(string &username, string &password);

int main()
{
    int option;
    cout << "1. Sign Up\n2. Sign In\nChoose an option: ";
    cin >> option;

    if (option == 1)
    {
        ifstream file("credentials.txt");
        if (file)
        {
            cout << "An account already exists! Please Sign In." << endl;
            file.close();
        }
        else
        {
            signup();
        }
    }

    string username, password;
    if (!signin(username, password))
    {
        cout << "Invalid Credentials!!!!.......Exiting......." << endl;
        cout << "Thanks For Using our Software!\n";
        return 0;
    }

    cout << "Login successful!" << endl;
    char choice1;
    cout << "Do you want to update your credentials? (y/n): ";
    cin >> choice1;
    if (choice1 == 'y' || choice1 == 'Y')
    {
        updateCredentials();
    }

    int choice;
    ProductData P;
    vector<ProductData> data;
    int qty, pCode;
    string pName;
    double price;

    do
    {
        choice1 = displayMenu();
        switch (choice1)
        {
        case 1:
        {
            int quantity;
            double totalBill = 0;
            string itemName;
            cout << "Enter item Name For Bill: ";
            cin >> itemName;
            cout << "Quantity Buyed: ";
            cin >> quantity;
            calculateBill(itemName, quantity, totalBill, P, data);
            break;
        }
        case 2:
            addProduct(pCode, pName, price, qty);
            break;
        case 3:
            updateQty(pCode, pName, price, qty, P, data);
            break;
        case 4:
            updatePrice(pCode, pName, price, qty, P, data);
            break;
        case 5:
            cout << "Thank You for Using our Software!" << endl;
            return 0;
        default:
            break;
        }
    } while (choice1 != 5);

    return 0;
}

void signup()
{
    cout << "Sign up to create an account" << endl;
    setCredentials();
}

bool signin(string &username, string &password)
{
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    return verifyCredentials(username, password);
}
int displayMenu()
{
    int select;
    cout << "------------------------------------MENU-------------------------------------\n"
         << "1. Bill Calculation\n"
         << "2. Add New Product\n"
         << "3. Update Quantity\n"
         << "4. Update Price\n"
         << "5.  Exit\n\n"
         << "Select Your Task (1-5)\n";
    cin >> select;
    return select;
}
void addProduct(int pCode, string pName, double price, int qty)
{
    ofstream fout("products.txt", ios::app);
    if (!fout)
    {
        cout << "Error opening file!" << endl;
    }
    else
    {
        cout << "Enter Details of the Product\n";
        cout << "Enter the Code of Product\n";
        cin >> pCode;
        fout << pCode << "\t";
        cout << "Enter the Name of Product\n";
        cin.ignore();
        getline(cin, pName);
        fout << pName << "\t\t";
        cout << "Enter the Price of Product\n";
        cin >> price;
        fout << price << "\t";
        cout << "Enter the Quantity of Product\n";
        cin >> qty;
        fout << qty << "\n";
        fout.close();
        cout << "Product Added Successfully!\n\n";
    }
}
void writeData(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data, bool found)
{

    if (!found)
    {
        cout << "Product not found!" << endl;
        return;
    }

    ofstream fout("products.txt");
    if (!fout)
    {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < data.size(); i++)
    {
        fout << data[i].pCode << "\t" << data[i].pName << "\t" << data[i].price << "\t" << data[i].qty << "\n";
    }
    fout.close();
}
void updateQty(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data)
{
    ifstream fin("products.txt");
    if (!fin)
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    data.clear();

    while (fin >> P.pCode >> P.pName >> P.price >> P.qty)
    {
        data.push_back(P);
    }
    fin.close();

    int updateQty;
    cout << "Enter the Product Code to update quantity: ";
    cin >> updateQty;

    bool found = false;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].pCode == updateQty)
        {
            cout << "Enter the new quantity: ";
            cin >> data[i].qty;
            found = true;
            break;
        }
    }
    writeData(pCode, pName, price, qty, P, data, found);
    cout << "Product quantity updated successfully!\n\n"
         << endl;
}

void updatePrice(int pCode, string pName, double price, int qty, ProductData &P, vector<ProductData> &data)
{
    ifstream fin("products.txt");
    if (!fin)
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    data.clear();

    while (fin >> P.pCode >> P.pName >> P.price >> P.qty)
    {
        data.push_back(P);
    }
    fin.close();
    int updatePrc;
    cout << "Enter the Product Code to update Price: ";
    cin >> updatePrc;
    bool found = false;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].pCode == updatePrc)
        {
            cout << "Enter the new Price: ";
            cin >> data[i].price;
            found = true;
            break;
        }
    }
    writeData(pCode, pName, price, qty, P, data, found);
    cout << "Product Price updated successfully!\n\n"
         << endl;
}

double calculateBill(string itemName, int quantity, double &totalBill, ProductData &P, vector<ProductData> &data)
{
    char choice;
    double tax;

    string itmName;
    int Qty;
    double currentItm;
    ifstream file("products.txt");

    // Exception handling for file opening
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    string productID, productName, productQuantityStr, priceStr;
    bool found = false;

    while (file >> productID >> productName >> priceStr >> productQuantityStr)
    {
        int productQuantity = atoi(productQuantityStr.c_str());
        double price = atof(priceStr.c_str());

        if (productName == itemName)
        {
            found = true;
            // Exception handling for insufficient stock
            if (quantity <= productQuantity)
            {
                currentItm = price * quantity;
                totalBill = totalBill + currentItm;
                ifstream fin("products.txt");
                if (!fin)
                {
                    cout << "Error opening file for reading!" << endl;
                    return 0;
                }

                data.clear();

                while (fin >> P.pCode >> P.pName >> P.price >> P.qty)
                {
                    data.push_back(P);
                }
                fin.close();
                for (int i = 0; i < data.size(); i++)
                {
                    if (data[i].pName == itemName)
                    {

                        data[i].qty -= quantity;
                        break;
                    }
                }
                ofstream fout("products.txt");
                if (!fout)
                {
                    cout << "Error opening file for writing!" << endl;
                    return 0;
                }

                for (int i = 0; i < data.size(); i++)
                {
                    fout << data[i].pCode << "\t" << data[i].pName << "\t" << data[i].price << "\t" << data[i].qty << "\n";
                }
                fout.close();
                cout << endl
                     << endl
                     << "---------------------------------------------------------------------------" << endl;
                cout << "Product Name\tQuantity Buyed\t\tPrice\t\tTotal Bill" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << productName << "\t\t\t " << quantity << "\t\t" << price << "\t\t" << currentItm << endl
                     << endl
                     << endl;
            }
            else
            {
                cout << "Insufficient stock for " << itemName << "! Available quantity: " << productQuantity << endl;
            }
            break;
        }
    }

    // Exception handling for item not found
    if (!found)
    {
        cout << "Item " << itemName << " not found in the inventory!" << endl;
    }

    cout << "Want to Add More Item[y] OR Want To Get Total BILL[n]:  ";
    cin >> choice;
    if (choice == 'n' || choice == 'N')
    {
        cout << "GST------->@16%\n\nCalculating.........\nWait A little.......\n\n";
        tax = totalBill * 16 / 100;
        totalBill += tax;
        cout << "The Total Bill Is: " << totalBill << endl
             << endl;
    }
    else if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter item Name For Bill: ";
        cin >> itmName;
        cout << "Quantity " << " Buyed: ";
        cin >> Qty;
        calculateBill(itmName, Qty, totalBill, P, data);
    }
    file.close();
    return found ? totalBill : 0;
}

void setCredentials()
{
    string username, password;
    ofstream file("credentials.txt");

    if (!file)
    {
        cerr << "Error opening file to save credentials!" << endl;
        return;
    }
    cout << "Set your username: ";
    cin >> username;
    cout << "Set your password: ";
    cin >> password;
    file << username << endl;
    file << password << endl;
    file.close();
    cout << "Credentials saved successfully!" << endl;
}

bool verifyCredentials(string &username, string &password)
{
    string savedUsername, savedPassword;
    ifstream file("credentials.txt");

    if (!file)
    {
        cerr << "Error opening file for verification!" << endl;
        return false;
    }

    getline(file, savedUsername);
    getline(file, savedPassword);
    file.close();
    return (username == savedUsername && password == savedPassword);
}

void updateCredentials()
{
    cout << "Updating credentials..." << endl;
    setCredentials();
}
