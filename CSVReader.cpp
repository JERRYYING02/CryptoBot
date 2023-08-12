/* 
  resourced from merkelrex end topic template 
*/

#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

CSVReader::CSVReader()
{
    
}

/*Optimization:converting csv to string,storing into memory make data parsing faster as in readCSV we getline from stringstream */
std::string CSVReader::CSVToString(const std::string& csvFilename)
{   
    std::ifstream csvFile(csvFilename);
    std::stringstream ss;
    ss << csvFile.rdbuf(); //read stream buffer
    std::string content =ss.str();
    return content;
}


std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& csvFilename)
{   
    //create string stream for getline to read
    std::string convertedString = CSVToString(csvFilename);
    std::istringstream sstream(convertedString);

    std::vector<OrderBookEntry> entries; //call a new entries vector
    
    std::ifstream csvFile{csvFilename}; 

    std::string line;
    if(csvFile.is_open())
    {
        //instead of reading input from file we read the loaded sstream
        while(std::getline(sstream, line))
        {
            try 
            {   
                //from strings into OrderBookEntry so it can be assign to specific data types
                OrderBookEntry obe = stringsToOBE(tokenize(line, ','));
                entries.push_back(obe);
                
            }
            catch(const std::exception& e)
            {
                // std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }
    }
        
    //show entries read
    std::cout << "CSVReader::readCSV read : " << entries.size() << " entries"  << std::endl;
    return entries; 
}



//tokenize algorithms resourced from MerkleRex end topic
std::vector<std::string> CSVReader::tokenize(const std::string& csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    }
    while(end > 0);

   return tokens; 
}

//convert string to order book entry
OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>&tokens)
{
    double price, amount;

    if (tokens.size() != 5) 
    {
        throw std::exception{};
    }
    // we have 5 tokens
    try 
    {
        price = std::stod(tokens[3]); //price is csv line's 3rd index
        amount = std::stod(tokens[4]);//amount is csv line's 4th index
    }
    catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl;
        throw;        
    }


    //arrange OrderBookEntry into this structure
    OrderBookEntry obe{price, 
                        amount, 
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe; 
}

OrderBookEntry CSVReader::stringsToOBE(const std::string& priceString,
                        const std::string& amountString,
                        const std::string& timestamp,
                        const std::string& product,
                        const OrderBookType orderType) 
{

    double price, amount;
    try 
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float price! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float amount! " << amountString << std::endl;
        throw;
    }

    return OrderBookEntry(price, amount, timestamp, product, orderType);
}
      
