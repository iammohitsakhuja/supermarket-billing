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
 * Destructor for this class.
 * Needed to free memory allocated to the vector.
 */
Order::~Order(void)
{
    // Creates a temporary, empty vector and
    // swaps it with the allocated vector.
    vector<Item>().swap(this->items);
}


/**
 * Member function to add an item to the current order.
 */
void Order::add_item(Item item)
{
    items.push_back(item);
}


/**
 * Member function of this class that displays the menu.
 */
void Order::show_menu(void) const
{
    clear_screen();

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

    // Show options
    cout << CYAN << "\nChoose one of the options below:\n" << RESET;
    cout << "1. Enter the ID of the item you would like to buy (0-7)" << endl;
    cout << "2. Enter '10' to view your cart" << endl;
    cout << "3. Enter '20' to checkout" << endl;
    cout << "4. Enter '500' to quit" << endl;
    cout << "\nChoice: ";
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


/**
 * Member function to view the cart.
 */
void Order::view_cart(void)
{
    clear_screen();

    cout << BLUE << "\t\tYOUR CART" << RESET << endl;

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

    cout << "\nTotal:\t\t\t\t\t" << this->bill << endl;

    cout << "\nPress Enter to continue";
    system("read");
}


/**
 * Member function to produce the bill for the current order.
 */
void Order::produce_bill(void)
{
    clear_screen();

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

    cout << "Total:\t\t\t\t\t" << this->bill << endl;
    cout << GREEN << "Thank you for shopping with us!" << RESET << endl;
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
    this->net_cost      = this->cost * this->quantity;
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

/********************* END *********************/




/********************* Friend function declarations *********************/

/**
 * A friend function for both classes
 * that returns the number of items in the cart.
 */
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

/**
 * Non-member, non-friend function
 * which is just used to clear the screen
 */
void clear_screen(void)
{
    std::cout << "\033[2J\n" << "\033[0;0H";
}


/**
 * Non-member, non-friend function
 * which is used to greet the user at startup
 */
void greet(void)
{
    clear_screen();
    cout << GREEN << "Welcome to our supermarket!" << RESET << endl;
    system("sleep 2.5");
}


/**
 * Non-member, non-friend function
 * which is used to tell the user that
 * the entered option is invalid.
 */
void invalid_option(void)
{
    cout << BEEP << RED << "\nThe option you've entered is invalid" << RESET << endl;
    cout << "Please enter a valid option." << endl;
    system("sleep 3");
}


/**
 * Housekeeping function
 */
void housekeeping(Item *items)
{
    delete[] items;
}

/********************* END *********************/
