#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>

/** construct, reading a csv data file */
OrderBook::OrderBook(const std::string& filename) 
{   
    
    //evaluate time for loading csv file
    //set start time 
    auto start = std::chrono::system_clock::now();
	orders = CSVReader::readCSV(filename);

    //set end time after reading 
	auto end = std::chrono::system_clock::now();
    
    //calculate time difference
    std::chrono::duration<double>diff = end - start;
    std::cout << "Time to load CSV File: " << diff.count()<<std::endl;
}


/** return vector of all know products in csv*/
std::vector<std::string> OrderBook::getKnownProducts() 
{

    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;
    for(OrderBookEntry& e : orders) 
    {   
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings
    for(auto const &e : prodMap) 
    {
        products.push_back(e.first);
    }

    return products;
}


/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product,std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e : orders) 
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp) 
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>&orders)
{
    double max = orders[0].price;
    for(OrderBookEntry& e : orders) 
    {
        if(e.price > max)
            max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders) 
{
    double min = orders[0].price;
    for(OrderBookEntry& e : orders) 
    {
        if(e.price < min)
        {
            min = e.price;
        }   
    }
    return min;
}



/* getAvgPrice done by adding all prices in timestamp to sumPrice then divide by order size*/
double OrderBook::getAvgPrice(std::vector<OrderBookEntry> &orders) 
{
    double sumPrice= 0;
    for(OrderBookEntry& e : orders) 
    {
        sumPrice += e.price;
    }
    return sumPrice / orders.size();
}

std::string OrderBook::getEarliestTime() 
{
    return orders[0].timestamp;
}


std::string OrderBook::getNextTime(std::string timestamp) 
{
    std::string next_timestamp = "";
    for(OrderBookEntry& e : orders) 
    {
        if(e.timestamp > timestamp) 
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}


/*  
    getPrevTime done by breaking out of the loop if timestamp is 
    greater than or equal to the current timestamp,we return the previous 
    timestamp which stopped at that point.
*/
std::string OrderBook::getPrevTime(std::string timestamp) 
{
    
    std::string prev_timestamp = "";
    for(OrderBookEntry& e : orders) 
    {   
        if(e.timestamp >= timestamp) 
        {
            break;
        } 
        else 
        {
            prev_timestamp = e.timestamp;
        }
    }

    return prev_timestamp;
}



