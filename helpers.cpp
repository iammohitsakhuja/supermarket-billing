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


/**************** Definitions for class - Order ****************/

/**
 * Default constructor for this class
 */
Order::Order(void)
{
    this->id            = 0;
    this->items_in_cart = 0;
    this->customer_name = "Customer";
    this->bill          = 0;
}


/**
 * Parameterized constructor for this class
 */
Order::Order(unsigned int id, string customer_name)
{
    this->id            = id;
    this->items_in_cart = 0;
    this->customer_name = customer_name;
    this->bill          = 0;
}


/**
 * Member function to add an item to the current order.
 */
void Order::add_item(Item item)
{
    items.push_back(item);
}


/**
 * Member function to show all items that have been added to the current bill.
 */
void Order::show_items(void)
{
    for (int i = 0, size = items.size(); i < size; i++)
    {
        cout << items[i].name << endl;
    }
}


/**
 * Member function of this class that displays the current
 * state of the user's cart.
 */
void Order::show_menu(void)
{
    clear_screen();
    // A little bit of greeting.
    cout << GREEN << "Welcome to our supermarket!" << RESET << endl;
    system("sleep 2");

    // Display the menu in a formatted manner.
    cout << "Here's the list of items we have:\n";
    cout << " *   " << BLUE << "ID " << left << setfill(' ') << setw(13) << "Item name"
         << "Quantity\t" << "Cost" << RESET << "\t*\n";
    for (int i = 0, size = items.size(); i < size; i++)
    {
        cout << " *   ";
        cout << right << setfill('0') << setw(2) << items[i].number << "\t"
             << left << setfill(' ') << setw(15) << items[i].name << "\t"
             << setfill('0') << setw(2) << items[i].quantity << "\t"
             << right << setfill(' ') << setw(4) << items[i].cost << "\t*\n";
    }

    // Ask for the user's choice.
    cout << "\nWhat would you like to buy?\n"
         << CYAN << "Please enter the ID of that item.\n" << RESET;

    // Options change depending upon the state of the cart.
    if (items_in_cart > 0)
    {
        cout << "Enter \"-1\" to " << GREEN << "checkout" << RESET
             << " or \"-2\" to " << RED << "quit" << RESET << ".\n";
    }
    else
    {
        cout << "Or enter \"-2\" to " << RED << "quit" << RESET <<".\n";
    }
}


/**
 * Member function to calculate the bill.
 */
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
    unsigned int qty;
    cout << "How much of " << this->items[item_id].name << " do you want to buy? ";
    cin >> qty;

    while (qty > this->items[item_id].max_quantity)
    {
        cout << BEEP << "The order quantity for this product is ";
        cout << "limited to " << this->items[item_id].max_quantity << " per customer!\n";
        system("sleep 1");
        cout << YELLOW << "Please choose a reasonable quantity.\n" << RESET;
        cin >> qty;
    }

    this->items[item_id].quantity = qty;
    this->items[item_id].net_cost = this->items[id].calculate_net_cost();
    cout << "\n" << this->items[item_id].quantity << " " << this->items[item_id].name << " in cart.\n";
    this->calculate_bill();
    system("sleep 1");
}


/**
 * Member function to produce the bill for the current order.
 */
void Order::produce_bill(void)
{
    cout << "Here's the bill for your order:\n";
    cout << " *   " << BLUE << "ID " << left << setfill(' ') << setw(13) << "Item name"
         << "Cost\t" << "Quantity   Net Cost" << RESET << "\t*\n";
    for (int i = 0, size = items.size(); i < size; i++)
    {
        cout << " *   ";
        cout << right << setfill('0') << setw(2) << items[i].number << "\t"
             << left << setfill(' ') << setw(15) << items[i].name << "\t"
             << right << setfill(' ') << setw(4) << items[i].cost << "\t"
             << setfill('0') << setw(2) << items[i].quantity << "\t"
             << right << setfill(' ') << setw(4) << items[i].net_cost << "\t*\n";
    }

    cout << "Total:\t\t\t" << this->bill << endl;
    cout << GREEN << "Thank you for shopping with us!" << RESET << endl;
}


/**
 * A friend function for this class
 * that returns the number of items in the cart.
 */
unsigned int get_cart_size(Order &order)
{
    order.items_in_cart = 0;
    for (int i = 0; i < order.items.size(); i++)
    {
        order.items_in_cart += order.items[i].quantity;
    }

    return order.items_in_cart;
}

/********************* END *********************/

















/**************** Definitions for class - Item ****************/

/**
 * Constructor for this class,
 * having some default arguments declared in the header file.
 */
Item::Item(unsigned int number, string name,
    float cost, unsigned int quantity,
    unsigned int max_quantity)
{
    this->number        = number;
    this->name          = name;
    this->cost          = cost;
    this->quantity      = quantity;
    this->max_quantity  = max_quantity;
    this->net_cost      = calculate_net_cost();
}

/**
 * Overloaded assignment operator for this class.
 */
void Item::operator = (Item &item)
{
    this->number        = item.number;
    this->name          = item.name;
    this->cost          = item.cost;
    this->quantity      = item.quantity;
    this->max_quantity  = item.max_quantity;
    this->net_cost      = item.net_cost;
}


/**
 * Explicitly declared inline function
 * that returns the total cost for an item
 */
inline float Item::calculate_net_cost(void)
{
    return this->cost * this->quantity;
}

/********************* END *********************/


/**
 * Non-member, non-friend function
 * which is just used to clear the screen
 */
void clear_screen(void)
{
    std::cout << "\033[2J\n" << "\033[0;0H";
}

/**
 * Housekeeping function
 */
void housekeeping(Item *items)
{
    delete[] items;
}
