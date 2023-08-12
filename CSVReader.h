/* 
  resourced from merkelrex end topic template 
*/

#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
     CSVReader();
     
     /* Optimization: technique of const and pass by reference to make data as read-only*/
     /* Optimization: converting csv to string,making data parsing faster from memory */
     static std::string CSVToString(const std::string& csvFilename);
     static std::vector<OrderBookEntry> readCSV(const std::string& csvFile);
     static std::vector<std::string> tokenize(const std::string& csvLine, char separator);
     
     
     //added const and reference to optimum performance(no over-writing on memory)
     static OrderBookEntry stringsToOBE(const std::string& price,
                                        const std::string& amount,
                                        const std::string& timestamp,
                                        const std::string& product,
                                        const OrderBookType OrderBookType);
    private:
    //function overload to find (strings) only
    static OrderBookEntry stringsToOBE(const std::vector<std::string>& strings);
     
}; 
