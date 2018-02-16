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

using namespace std;

class Order;

class Item
{
    private:
        unsigned int number;
        string name;
        float cost;
        unsigned int quantity;
        unsigned int max_quantity;
        float net_cost;

        // friend class that wants to access private data of this class
        friend class Order;

    public:
        Item(unsigned int number, string name,
            float cost, unsigned int quantity = 0,
            unsigned int max_quantity = 5);

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
    private:
        unsigned int id;
        unsigned int items_in_cart;
        string customer_name;
        double bill;
        vector<Item> items;

    public:
        Order(void);
        Order(unsigned int id, string customer_name);
        ~Order(void);
        void add_item(Item item);
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
void invalid_option(void);
void housekeeping(Item *items);

#endif