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
        // represents the cost of one item
        float cost;
        unsigned int quantity;
        // represents the maximum quantity of the item that a customer can order
        unsigned int max_quantity;
        // represents the total cost for an item
        float net_cost;

        // private member function
        float calculate_net_cost(void);

        // friend class that wants to access private data of this class
        friend class Order;

    // TODO
    public:
        // parameterized constructor
        Item(unsigned int number, string name,
            float cost, unsigned int quantity = 0,
            unsigned int max_quantity = 5);

        // overloaded assignment operator
        void operator = (Item &item);

        // common friend function for both classes,
        // needed here to access the `quantity` of an item
        friend unsigned int get_cart_size(Order &order);

        // Destructor
        ~Item(void)
        {
            return ;
        }

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
        void add_item(Item item);
        void show_items(void);
        void show_menu(void);
        void change_quantity(unsigned int item_id);
        void produce_bill(void);
        void calculate_bill(void);

        // common friend function for both classes
        friend unsigned int get_cart_size(Order &order);
};



// class Grocery: public Item
// {
//     // TODO
// };

// class KitchenProducts: public Item
// {
//     // TODO
// };

// class Appliances: public Item
// {
//     // TODO
// };

// class Clothing: public Item
// {
//     // TODO
// };

void clear_screen(void);
void housekeeping(Item *items);

#endif