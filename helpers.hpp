/** Contains function and class declarations for main.cpp
 *
 * The implementations for these functions and classes are present in
 * `helpers.cpp`
 *
 * Author: Mohit Sakhuja
 */

#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <cstdlib>

#define VIEW_CART 1000
#define CHECKOUT  2000
#define QUIT      5000

using namespace std;

class Order;

class Item
{
    public:
        // Data members
        unsigned int id;
        string name;
        float cost;
        unsigned int quantity;
        unsigned int max_quantity;
        float net_cost;

        // Member functions
        Item(unsigned int id, string name, float cost, unsigned int quantity, unsigned int max_quantity);
        void operator = (Item &item);
        ~Item(void)
        {
            return ;
        }

        // common friend function for both classes,
        // needed here to access the `quantity` of an item
        friend unsigned int get_cart_size(Order &order);
};

class Order
{
    public:
        // Data members
        unsigned int id;
        unsigned int items_in_cart;
        string customer_name;
        float bill;
        vector<Item> items;

        // Member functions
        Order(string customer_name = "Customer");
        ~Order(void);
        void show_menu(void) const;
        void change_quantity(unsigned int item_id);
        void produce_bill(void);
        void calculate_bill(void);
        void view_cart(void);

        // common friend function for both classes
        friend unsigned int get_cart_size(Order &order);
};

void clear_screen(void);
void greet(void);
void get_customer_name(void);
void invalid_option(void);
void housekeeping(Item *items);

extern Order order;

#endif