/**
 * Contains implementations for classes and functions declared
 * in `helpers.hpp`.
 *
 * Author: Mohit Sakhuja
 */

#include "helpers.hpp"

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
    this->items_in_cart = 0;
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

    cout << BLUE << right << setfill(' ') << setw(20) << "YOUR CART" << RESET << endl;

    cout << BLUE << "*****"
         << right << setfill(' ') << setw(4) << "ID"
         << setw(20) << "Item name"
         << setw(10) << "Cost"
         << setw(10) << "Quantity"
         << setw(15) << "Net cost"
         << left << "  *****"
         << RESET << endl;

    // cout << " *   " << BLUE << "ID " << left << setfill(' ') << setw(13) << "Item name"
    //      << "Cost\t" << "Quantity   Net Cost" << RESET << "\t*\n";
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

    cout << GREEN << right << setfill(' ') << setw(61) << "Total: "
         << RESET << this->bill << endl;

    cout << "\nPress Enter to continue";
    system("read");
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


/**
 * Member function to get the new quantity for a particular item,
 * index of which is received as an argument.
 */
void Order::change_quantity(unsigned int item_id)
{
    clear_screen();

    unsigned int qty;
    cout << "How much of " << this->items[item_id].name << " do you want to buy? ";
    cin >> qty;

    while (qty > this->items[item_id].max_quantity)
    {
        cout << BEEP << "\nThe order quantity for this product is ";
        cout << "limited to " << this->items[item_id].max_quantity << " per customer!" << endl;
        cout << YELLOW << "Please choose a reasonable quantity.\n" << RESET;
        cin >> qty;
    }

    this->items[item_id].quantity = qty;
    items[item_id].net_cost = items[item_id].quantity * items[item_id].cost;
    this->calculate_bill();
    cout << "\n" << this->items[item_id].quantity << " " << this->items[item_id].name << " in cart.\n";
    system("sleep 1");
}





// Produce bill for the current order
void Order::produce_bill(void)
{
    clear_screen();

    cout << "Here's the bill for your order:\n";

    cout << " *   " << BLUE << "ID " << left << setfill(' ') << setw(13) << "Item name"
         << "Cost\t" << "Quantity   Net Cost" << RESET << "\t*\n";
    for (int i = 0, size = items.size(); i < size; i++)
    {
        cout << " *   ";
        cout << right << setfill('0') << setw(2) << items[i].id << "\t"
             << left << setfill(' ') << setw(15) << items[i].name << "\t"
             << right << setfill(' ') << setw(4) << items[i].cost << "\t"
             << setfill('0') << setw(2) << items[i].quantity << "\t"
             << right << setfill(' ') << setw(4) << items[i].net_cost << "\t*\n";
    }

    cout << "Total:\t\t\t\t\t" << this->bill << endl;
    cout << GREEN << "Thank you for shopping with us!" << RESET << endl;
}

/********************* END *********************/




/**************** Definitions for class - Item ****************/

// Constructor for class `Item`
Item::Item(unsigned int id, string name,
    float cost, unsigned int quantity,
    unsigned int max_quantity)
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

/********************* END *********************/




/********************* Friend function declarations *********************/

// Friend of both classes that
// returns the number of items in the cart
unsigned int get_cart_size(Order &order)
{
    order.items_in_cart = 0;
    for (int i = 0, size = order.items.size(); i < size; i++)
    {
        order.items_in_cart += order.items[i].quantity;
    }

    return order.items_in_cart;
}

/********************* END *********************/




/********************* Non-member, non-friend function declarations *********************/

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
    cout << BEEP << RED << "\nThe option you've entered is invalid" << RESET << endl;
    cout << "Please enter a valid option." << endl;
    system("sleep 3");
}


// C-style function to cleanup items
void housekeeping(Item *items)
{
    delete[] items;
}

// Global variables
Order order = Order();

/********************* END *********************/
