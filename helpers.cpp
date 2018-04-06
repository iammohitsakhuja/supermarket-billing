/**
 * Contains implementations for classes and functions declared
 * in `helpers.hpp`.
 *
 * Author: Mohit Sakhuja
 */

#include "helpers.hpp"
#include "sqlite_wrapper.hpp"
#include <iomanip>

// Some colors and sounds.
#define BEEP    "\a"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define ESC     "\x1b["

// Constructor for class `Order`
Order::Order(string customer_name)
{
    this->id            = 0;
    this->customer_name = customer_name;
    this->bill          = 0;
}

// Destructor for class `Order`
Order::~Order(void)
{
    // Creates a temporary, empty vector and
    // swaps it with the allocated vector
    vector<Item>().swap(this->items);
}

// Member function of `Order` class to display the menu
void Order::show_menu(void) const
{
    clear_screen();

    // Display the column headings in a formatted manner
    cout << "Here's the list of items we have:\n";
    cout << BLUE << "*****"
         << right << setfill(' ') << setw(4) << "ID"
         << setw(20) << "Item name"
         << setw(10) << "Cost"
         << left << "  *****"
         << RESET << endl;

    // Display the menu items in a formatted manner
    for (int i = 0, size = items.size(); i < size; i++)
    {
        cout << "     "
             << right << setfill(' ') << setw(4) << items[i].id
             << setw(20) << items[i].name
             << setw(10) << items[i].cost
             << RESET << endl;
    }

    // Show options
    cout << CYAN << "\nChoose one of the options below:\n" << RESET;
    cout << "1. Enter the ID of the item you would like to buy" << endl;
    cout << "2. Enter '" << VIEW_CART << "' to view your cart" << endl;
    cout << "3. Enter '" << CHECKOUT << "' to checkout" << endl;
    cout << "4. Enter '" << QUIT << "' to quit" << endl;
    cout << "\nChoice: ";
}

// Display the cart items
void Order::view_cart(void)
{
    clear_screen();

    // Show headings
    cout << BLUE << right << setfill(' ') << setw(38) << "YOUR CART" << RESET << endl;

    cout << BLUE << "*****"
         << right << setfill(' ') << setw(4) << "ID"
         << setw(20) << "Item name"
         << setw(10) << "Cost"
         << setw(10) << "Quantity"
         << setw(15) << "Net cost"
         << left << "  *****"
         << RESET << endl;

    // Show only items added into cart
    for (int i = 0, size = items.size(); i < size; i++)
    {
        if (items[i].quantity > 0)
        {
            cout << "     "
                 << right << setfill(' ') << setw(4) << items[i].id
                 << setw(20) << items[i].name
                 << setw(10) << items[i].cost
                 << setw(10) << items[i].quantity
                 << setw(15) << items[i].net_cost
                 << RESET << endl;
        }
    }

    cout << GREEN << "\n\nTotal: " << RESET << this->bill << endl;

    cout << "\nPress Enter to continue\n";
    system("read");
}

// Change quantity for a particular item
void Order::change_quantity(unsigned int item_id)
{
    clear_screen();

    // Get the index for the current item id
    item_id--;

    // Ask the user about the quantity for that item
    unsigned int qty;
    cout << "How much of " << items[item_id].name << " do you want to buy? ";
    cin >> qty;

    // Make sure the quantity for that item is available
    while (qty > items[item_id].max_quantity)
    {
        clear_screen();

        cout << BEEP << "\nThe order quantity for "
             << items[item_id].name << " is limited to "
             << items[item_id].max_quantity << " units per customer!\n"
             << YELLOW << "Please choose a reasonable quantity.\n\n"
             << RESET;
        cout << "How much of " << items[item_id].name << " do you want to buy? ";
        cin >> qty;
    }

    // Set the quantity and net cost of the item accordingly
    items[item_id].quantity = qty;
    items[item_id].net_cost = items[item_id].quantity * items[item_id].cost;

    // Maintain a track of new bill
    calculate_bill();

    cout << "\n" << items[item_id].quantity << " units of " << items[item_id].name << " in cart.\n";
    system("sleep 2");
}

// Member function of `Order` class to calculate bill
void Order::calculate_bill(void)
{
    this->bill = 0;
    for (int i = 0, size = items.size(); i < size; i++)
    {
        this->bill += items[i].net_cost;
    }
}

// Produce bill for the current order and save transaction to database
void Order::produce_bill(void) throw (int)
{
    clear_screen();

    try
    {
        save_and_quit();
    }
    catch (int error)
    {
        throw;
    }

    // Show headings
    cout << BLUE << right << setfill(' ') << setw(33) << "YOUR BILL" << RESET << endl;

    cout << BLUE << "*****"
         << right << setfill(' ')
         << setw(15) << "Item name"
         << setw(10) << "Cost"
         << setw(10) << "Quantity"
         << setw(15) << "Net cost"
         << left << "  *****"
         << RESET << endl;

    // Display only the items purchased
    for (int i = 0, size = items.size(); i < size; i++)
    {
        if (items[i].quantity > 0)
        {
            cout << "     "
                 << right << setfill(' ')
                 << setw(15) << items[i].name
                 << setw(10) << items[i].cost
                 << setw(10) << items[i].quantity
                 << setw(15) << items[i].net_cost
                 << RESET << endl;
        }
    }

    cout << GREEN << "\n\nTotal: " << RESET << this->bill << endl;

    cout << "\nThank you " << MAGENTA << this->customer_name
         << RESET << ", for shopping with us!\n" << endl;
}

// Save and quit after producing the bill
void save_and_quit(void) throw (int)
{
    // Insert entries into `orders` table
    try
    {
        for (int i = 0, size = order.items.size(); i < size; i++)
        {
            if (order.items[i].quantity > 0)
            {
                db_order.execute("INSERT INTO %s VALUES(%d, \"%s\", %d, %d);", "orders", order.id, (order.customer_name).c_str(), order.items[i].id, order.items[i].quantity);
            }
        }
    }
    catch (int error)
    {
        throw;
    }

    // Update `items` table
    try
    {
        for (int i = 0, size = order.items.size(); i < size; i++)
        {
            if (order.items[i].quantity > 0)
            {
                // Calculate remaining quantity
                int quantity_left = order.items[i].max_quantity - order.items[i].quantity;

                // Update database
                db_items.execute("UPDATE %s SET %s = %d WHERE %s = %d;", "items", "quantity", quantity_left, "item_id", order.items[i].id);
            }
        }
    }
    catch (int error)
    {
        // If updating `items` table fails, remove the entries inserted into `orders` table
        try
        {
            db_order.execute("DELETE FROM %s WHERE %s = %d;", "orders", "order_id", order.id);
        }
        catch (int err)
        {
            cerr << "Error code: " << err << endl;
            cerr << "Error undo-ing last transaction on table `orders`" << endl;
            cerr << "Error: " << db_order.errmsg << endl;
        }

        throw error;
    }
}

// Constructor for class `Item`
Item::Item(unsigned int id, string name, float cost, unsigned int quantity, unsigned int max_quantity)
{
    this->id            = id;
    this->name          = name;
    this->cost          = cost;
    this->quantity      = quantity;
    this->max_quantity  = max_quantity;
    this->net_cost      = this->cost * this->quantity;
}

// Copies an item object to another
void Item::operator = (Item &item)
{
    this->id            = item.id;
    this->name          = item.name;
    this->cost          = item.cost;
    this->quantity      = item.quantity;
    this->max_quantity  = item.max_quantity;
    this->net_cost      = item.net_cost;
}

// C-style function to clear the screen
void clear_screen(void)
{
    std::cout << "\033[2J\n" << "\033[0;0H";
}

// C-style function to greet the user at startup
void greet(void)
{
    clear_screen();
    cout << GREEN << "Welcome to our supermarket!" << RESET << endl;
    system("sleep 2.5");
    clear_screen();
}

// C-style function to get customer's name
void get_customer_name(void)
{
    cout << "Please enter customer's name: ";
    getline(cin, order.customer_name);
    cout << GREEN << "Welcome, " << order.customer_name << RESET << endl;
    system("sleep 2");
    clear_screen();
}

// C-style function to tell the user that the entered option is invalid
void invalid_option(void)
{
    clear_screen();

    cout << BEEP << RED << "\nThe option you've entered is invalid" << RESET << endl;
    cout << "Please enter a valid option." << endl;
    system("sleep 3");
}

// Global variables
Order order = Order();
