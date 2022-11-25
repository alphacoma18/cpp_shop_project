#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>

struct MenuItems
{
    int _id = 0;
    std::string name = "";
    double price = 0.0;
};
struct Customer
{
    double total = 0.0;
    std::vector<MenuItems> orders = {};
};

// Function Prototypes
void init();
void shopBanner();
void exitBanner();

std::map<std::string, std::vector<MenuItems>> initMenuItems();
void displayActions(int &selection, Customer &customer);
void displayMenu(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu);

void displayOrderMenu(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu);
void displayOrder(Customer &customer);
void promptOrder(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> menu, std::string menuType);

void displayCheckout(Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu);
double computeChange(double moneyTendered, double total);

// Helper Function Prototypes
void prompt(int &selection);
void formatMenuItem(int _id, std::string name, double price);
void printBreaks(int n, char c, bool newLine);

int main()
{
    shopBanner();
    init();
    exitBanner();
    return 0;
}
void init()
{
    Customer customer;
    std::map<std::string, std::vector<MenuItems>> menuItems = initMenuItems();

    int selection = -1;
    do
    {
        displayActions(selection, customer);
        switch (selection)
        {
        case 1:
            displayMenu(selection, customer, menuItems);
            break;
        case 2:
            return;
        }
    } while (selection != 2);
    return;
}
std::map<std::string, std::vector<MenuItems>> initMenuItems()
{
    std::vector<MenuItems> FoodItems = {
        {0, "Back", 0.0},
        {1, "Menudo", 99.99},
        {2, "Afritada", 99.99},
        {3, "Adobo", 99.99},
        {4, "Dinakdakan", 149.99},
        {5, "Caldereta", 149.99},
        {6, "Mechado", 199.99},
        {7, "Sisig", 199.99},
        {8, "Kare-Kare", 249.99},
        {9, "Pork Barbecue", 249.99},
        {10, "Lechon", 999.99},
    };
    std::vector<MenuItems> DrinkItems = {
        {0, "Back", 0.0},
        {1, "Chocolate", 29.99},
        {2, "Sago't Gulaman", 29.99},
        {3, "Coffee", 29.99},
        {4, "Iced Tea", 29.99},
        {5, "Coke", 49.99},
        {6, "Sprite", 49.99},
        {7, "Royal", 49.99},
        {8, "Mountain Dew", 99.99},
        {9, "Root Beer", 99.99},
        {10, "Hotdog Water", 149.99},
    };
    std::vector<MenuItems> DessertItems = {
        {0, "Back", 0.0},
        {1, "Biko", 49.99},
        {2, "Suman", 49.99},
        {3, "Polvoron", 49.99},
        {4, "Ice Cream", 99.99},
        {5, "Mais con Yelo", 99.99},
        {6, "Puto", 99.99},
        {7, "Buko Pandan", 99.99},
        {8, "Buko Salad", 149.99},
        {9, "Bibingka", 149.99},
        {10, "Cassava Cake", 199.99},
    };
    return {
        {"Food", FoodItems},
        {"Drink", DrinkItems},
        {"Dessert", DessertItems},
    };
}
void displayActions(int &selection, Customer &customer)
{
    std::cout << "Welcome to KainDerya! What would you like to do?\n";
    std::cout << "1. See Menu\n";
    std::cout << "2. Exit\n";
    prompt(selection);
    if (selection == 2 && customer.orders.size() > 0)
    {
        std::cout << "You have an unpaid order. Please pay first.\n";
        displayActions(selection, customer);
    }
    return;
}
void displayMenu(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu)
{
    while (true)
    {
        std::cout << "\n-- Menu --\n";
        formatMenuItem(1, "See Food Menu", 0.0);
        formatMenuItem(2, "See Drink Menu", 0.0);
        formatMenuItem(3, "See Dessert Menu", 0.0);
        formatMenuItem(4, "Manage Orders", 0.0);
        formatMenuItem(5, "Checkout", 0.0);
        formatMenuItem(6, "Back", 0.0);
        prompt(selection);
        switch (selection)
        {
        case 1:
            displayOrderMenu(selection, customer, menu);
            break;
        case 2:
            displayOrderMenu(selection, customer, menu);
            break;
        case 3:
            displayOrderMenu(selection, customer, menu);
            break;
        case 4:
            displayOrder(customer);
            break;
        case 5:
            displayCheckout(customer, menu);
            selection = 2;
            return;
        case 6:
            return;
        default:
            std::cout << "Invalid input. Please try again.\n";
            displayMenu(selection, customer, menu);
        }
    }
}
void displayOrderMenu(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu)
{
    if (selection == 1)
    {
        promptOrder(selection, customer, menu, "Food");
    }
    if (selection == 2)
    {
        promptOrder(selection, customer, menu, "Drink");
    }
    if (selection == 3)
    {
        promptOrder(selection, customer, menu, "Dessert");
    }
}
void promptOrder(int &selection, Customer &customer, std::map<std::string, std::vector<MenuItems>> menu, std::string menuType)
{
    int orderSelection = -1;
    std::cout << "\n";
    for (auto &item : menu[menuType])
    {
        formatMenuItem(item._id, item.name, item.price);
    }
    while (true)
    {
        prompt(orderSelection);
        if (orderSelection == 0)
            return;
        customer.orders.push_back(menu[menuType][orderSelection]);
        customer.total += menu[menuType][orderSelection].price;
    }
}
void displayOrder(Customer &customer)
{
    printBreaks(30, '=', true);
    std::cout << "-- Orders --\n";
    for (auto &item : customer.orders)
    {
        formatMenuItem(-1, item.name, item.price);
    }
    std::cout << "\n"
              << std::setfill('-') << std::setw(25) << std::left << "Total"
              << "P" << customer.total << "\n";
}
void displayCheckout(Customer &customer, std::map<std::string, std::vector<MenuItems>> &menu)
{
    try
    {
        double payment;
        printBreaks(30, '=', true);
        std::cout << "-- Checkout --\n";
        std::cout << "Total: " << customer.total << "\n";
        std::cout << "Enter payment: ";
        std::cin >> payment;
        if (customer.total > payment)
            throw std::invalid_argument("Insufficient payment. Please try again.");
        std::cout << "Change: " << computeChange(payment, customer.total) << "\n";
        customer.total = 0.0;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        displayCheckout(customer, menu);
    }
}

double computeChange(double moneyTendered, double total)
{
    return moneyTendered - total;
}

// Helper functions
void prompt(int &selection)
{
    try
    {
        std::cout << "Enter your choice: ";
        std::cin >> selection;
        if (std::cin.fail())
            throw std::invalid_argument("Invalid input. Please try again.");
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        prompt(selection);
    }
}
void formatMenuItem(int _id, std::string name, double price)
{
    if (_id == -1)
    {
        std::cout << std::setfill('-') << std::setw(25) << std::left << name << "P" << price << "\n";
        return;
    }
    if (price == 0.0)
    {
        std::cout << "[" << _id << "] " << std::setfill(' ') << std::setw(15) << std::left << name << "\n";
        return;
    }
    std::cout << "[" << _id << "] " << std::setfill('-') << std::setw(15) << std::left << name << std::setw(10) << std::right << "P" << price << "\n";
}
void printBreaks(int n, char c, bool newLine)
{
    std::cout << std::string(n, c);
    if (newLine)
        std::cout << "\n";
}

void shopBanner()
{
    std::cout << "___       __    ______                                 ________      \n";
    std::cout << "__ |     / /_______  /__________________ ________      ___  __/_____ \n";
    std::cout << "__ | /| / /_  _ \\_  /_  ___/  __ \\_  __ `__ \\  _ \\     __  /  _  __ \\\n";
    std::cout << "__ |/ |/ / /  __/  / / /__ / /_/ /  / / / / /  __/     _  /   / /_/ /\n";
    std::cout << "____/|__/  \\___//_/  \\___/ \\____//_/ /_/ /_/\\___/      /_/    \\____/ \n";

    std::cout << "______ __      _____       ________                           ______ \n";
    std::cout << "___  //_/_____ ___(_)_________  __ \\________________  _______ ___  / \n";
    std::cout << "__  ,<  _  __ `/_  /__  __ \\_  / / /  _ \\_  ___/_  / / /  __ `/_  /  \n";
    std::cout << "_  /| | / /_/ /_  / _  / / /  /_/ //  __/  /   _  /_/ // /_/ / /_/   \n";
    std::cout << "/_/ |_| \\__,_/ /_/  /_/ /_//_____/ \\___//_/    _\\__, / \\__,_/ (_)    \n";
    std::cout << "                                               /____/\n";
    printBreaks(80, '_', true);
}

void exitBanner()
{
    std::string contributors[4] = {"Alpha Romer Coma", "Ian Sioson", "Job Isaac Ong", "John Mark Mayo"};
    printBreaks(80, '_', true);
    std::cout << " /$$$$$$$$ /$$                           /$$             /$$     /$$\n";
    std::cout << "|__  $$__/| $$                          | $$            |  $$   /$$/\n";
    std::cout << "   | $$   | $$$$$$$   /$$$$$$  /$$$$$$$ | $$   /$$       \\  $$ /$$//$$$$$$  /$$   /$$\n";
    std::cout << "   | $$   | $$__  $$ |____  $$| $$__  $$| $$  /$$/        \\  $$$$//$$__  $$| $$  | $$\n";
    std::cout << "   | $$   | $$  \\ $$  /$$$$$$$| $$  \\ $$| $$$$$$/          \\  $$/| $$  \\ $$| $$  | $$\n";
    std::cout << "   | $$   | $$  | $$ /$$__  $$| $$  | $$| $$_  $$           | $$ | $$  | $$| $$  | $$\n";
    std::cout << "   | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$ \\  $$          | $$ |  $$$$$$/|  $$$$$$/\n";
    std::cout << "   |__/   |__/  |__/ \\_______/|__/  |__/|__/  \\__/          |__/  \\______/  \\______/\n";
    printBreaks(80, '_', true);
    std::cout << "Contributors\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << i + 1 << ". " << contributors[i] << "\n";
    }
    printBreaks(80, '_', true);
    std::cout << "Course: CCS0003L - Computer Programming 1\n";
    std::cout << "Instructor: Prof. Reginald Cheng\n";
    std::cout << "Date: 2022-11-24\n";
    printBreaks(80, '_', false);
}