
#include <iostream>
#include <vector>
#include "AdvisorBot.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"

// advisorBot constructor
AdvisorBot::AdvisorBot()
{
   
}

//init introduces program after running the code 
void AdvisorBot::init()
{   
    //set current time to csv data first timestamp when program starts
    currentTime = orderBook.getEarliestTime();
   
    //printing welcome message
    std::cout << "Hi ,This is AdvisorBot. "<<std::endl;
    std::cout << "I am your Cryptocurrency Trading Bot" << std::endl;
 
    //set programRunning status to start advisorBot
    programRunning=true;
    while(programRunning==true) 
    {   
        showMenu();
        processUserOption();
    }

}


//show the main menu
void AdvisorBot::showMenu()
{   
    std::cout << "\n\n\n\n\n "<<std::endl;
    std::cout << "=====================================================\n" << std::endl;
    std::cout << "Please enter -help- to view all available commands\n";
}

//show general commands
void AdvisorBot::showHelp()
{
    std::cout << "Commands: " << std::endl;
    std::cout << "help, help <cmd>, \nprod, min, max,\navg, predict, time,step <forward/back>,\njump <forward/back> <number of timestamps>,\nreset,clear,exit"<<std::endl;
}


//show help for specific commands (e.g help prod)
void AdvisorBot::showHelpCmd(const std::string &commandToken) 
{   
    //instruct how to use help command
    if(commandToken == "help") 
    {
        std::cout << commandToken << " (shows all available commands) " << std::endl;
        std::cout << "User > help" << std::endl;
    }

    //instruct how to use prod command
    else if(commandToken == "prod") 
    {
        std::cout << commandToken << " (shows list of all products)" << std::endl;
        std::cout << "User > prod" << std::endl;
    }

    //instruct how to use min command
    else if(commandToken == "min") 
    {
        std::cout << commandToken << " (shows minimum bid or ask of product in current timestamp)" << std::endl;
        std::cout << "Infotype: min <product> <bid/ask>" << std::endl;
        std::cout << "User > min ETH/BTC ask" << std::endl;
    }


    //instruct how to use max command
    else if(commandToken == "max") 
    {
        std::cout << commandToken << " (shows maximum bid or ask of product in current timestamp)" << std::endl;
        std::cout << "Infotype: max <product> <bid/ask>" << std::endl;
        std::cout << "User > max ETH/BTC ask" << std::endl;
    }


    //instruct how to use avg command
    else if(commandToken == "avg") 
    {
        std::cout << commandToken << " (shows average ask or bid of product over a period of timestamps)" << std::endl;
        std::cout << "Infotype: avg <product bid/ask> <number of timestamps>" << std::endl;
        std::cout << "User > avg ETH/BTC ask 10" << std::endl;
    }

    //instruct how to use predict command
    else if(commandToken == "predict") 
    {
        std::cout << commandToken << " (predicts max or min (ask/bid) of product for next timestamp)" << std::endl;
        std::cout << "Infotype: predict <max/min> <product> <bid/ask>" << std::endl;
        std::cout << "User > predict max ETH/BTC ask" << std::endl;
    }

    //instruct how to use time command
    else if(commandToken == "time") 
    {
        std::cout << commandToken << " (show current timestamp)" << std::endl;
        std::cout << "User > time" << std::endl;
    }

    //instruct how to use step command
    else if(commandToken == "step") 
    {
        std::cout << "(step to next or previous timestamp)" << std::endl;
        std::cout << "Infotype: step <forward/back>" << std::endl;
        std::cout << "User > step forward" << std::endl;
    }
    //instruct how to use jump command
    else if(commandToken =="jump")
    {
        std::cout << "(jump next or previous multiple timestamps)"<< std::endl;
        std::cout << "Infotype: jump <forward/back> <number of timestamp>" << std::endl;
        std::cout << "User > jump forward 3" << std::endl;
    }

    //instruct how to use reset command
    else if(commandToken == "reset")
    {
        std::cout << "(Enter reset to reset to first timestamp)" << std::endl;
        std::cout << "User > reset" << std::endl;

    }
    //instruct how to use clear command
    else if(commandToken == "clear")
    {
        std::cout << "(Enter clear to clear screen of current program)" << std::endl;
        std::cout << "User > clear" << std::endl;
    }

    //instruct how to use exit command
    else if(commandToken == "exit")
    {
        std::cout << "(Enter exit to quit current program)" << std::endl;
        std::cout << "User > exit" << std::endl;

    }

    //if input commandToken does not match then print error
    else
    {
        std::cout << "AdvisorBot::showHelpCmd(error): invalid command input" << std::endl;
    }
    
}


//show help for specific commands (e.g help prod)
void AdvisorBot::processUserOption()
{   
    //get userOption from input
    std::string userOption;
    std::getline(std::cin, userOption);

    //tokenize input from user to load commands with blank spaces
    std::vector<std::string> commandTokens = CSVReader::tokenize(userOption, ' ');
    
    // commandTokens size is how many parts a command contain 
    if(commandTokens.size() == 1 && commandTokens[0] == "help") 
    {
        showHelp();
    }
    else if(commandTokens.size() == 2 && commandTokens[0] == "help") 
    {   
        //pass in the first command string 
        showHelpCmd(commandTokens[1]);
    }
    else if(commandTokens.size() == 1 && commandTokens[0] == "prod") 
    {
        Prod();
    }
    else if(commandTokens.size() == 3 && commandTokens[0] == "min") 
    {
        Min(commandTokens);
    }
    else if(commandTokens.size() == 3 && commandTokens[0] == "max" ) 
    {
        Max(commandTokens);
    }
    else if(commandTokens.size() == 4 && commandTokens[0] == "avg" ) 
    {
        Avg(commandTokens);
    }
    else if(commandTokens.size() == 4 && commandTokens[0] == "predict" ) 
    {
        Predict(commandTokens);
    }
    else if(commandTokens.size() == 1 && commandTokens[0] == "time" ) 
    {   
        if(currentTime.empty())
        {
            std::cout<< " timestamp is not found,step<forward/back>" <<std::endl;
        }
        else
        std::cout << "Current time is : " << currentTime << std::endl;
    }

    else if(commandTokens.size() == 1 && commandTokens[0] == "step" ) 
    {   
        gotoNextTimeframe();
        //if empty time have to step or jump forward
        if(currentTime.empty())
        {
            std::cout<< "invalid command please step forward/back only";
        }
    }
    

    else if(commandTokens.size() == 2 && commandTokens[0] == "step") 
    {   
        //check if input is step forward or back
        if(commandTokens[1] == "forward") 
        {
            gotoNextTimeframe();
        } 
        
        else if(commandTokens[1] == "back") 
        {
            gotoPrevTimeframe();
        } 
        else
        {
            std::cout<< "invalid command please jump forward/back only";
        }
    }

    else if(commandTokens.size() == 3 && commandTokens[0] == "jump") 
    {   
        //check if input is jump forward or back
        if(commandTokens[1] == "forward") 
        {
            JumpNextTimeframe(commandTokens[2]);
        } 
        else if(commandTokens[1] == "back") 
        {
            JumpPrevTimeframe(commandTokens[2]);
        } 
        else
        {
            std::cout<< "invalid command please jump forward/back only";
        }
    }
    
    //call reset command to reset time to beginning
    else if(commandTokens.size() == 1 && commandTokens[0] == "reset") 
    {
        reset();
    }

    //call clearscreen to clear output of screen
    else if(commandTokens.size() == 1 && commandTokens[0] == "clear" ) 
    {
        clearScreen();
    }

    //call clearscreen to exit program
    else if(commandTokens.size() == 1 && commandTokens[0] == "exit") 
    {
        exit();
    }
    else
    {
        std::cout << "AdvisorBot::processUserOption(error) : invalid command" << std::endl;
    }
    
}

/* shows list of all products */
void AdvisorBot::Prod()
{   
    //use getKnownProducts to list products
    std::vector<std::string> products = orderBook.getKnownProducts();
    std::cout << "Available pair products: "<< std::endl;
    
    //print all products
    for(const std::string& p : products) 
    {   
        std::cout << p << std::endl;
        
    }

}

/* shows minimum bid or ask of product in current timestamp using getLowPrice */
void AdvisorBot::Min(const std::vector<std::string>&commandTokens) 
{   
    //assign command inputs to product,orderType variable
    std::string product = commandTokens[1];  
    OrderBookType orderType;
    orderType = OrderBookEntry::stringToOrderBookType(commandTokens[2]); 

    std::vector<OrderBookEntry> entries; 

    //check if it is a product 
    std::vector<std::string> ProductList = orderBook.getKnownProducts();
    for(std::string &p : ProductList) 
    {
        if(p == product) 
        {   
            break; //if found product break out of if 
            return;
        }
        // if until the last element of vector,the products still cannot be found
        else if(p == ProductList.back())
        {   
            if(p!=product)
            {
                std::cout << "AdvisorBot::Min(error) invalid product" << std::endl;
                return;
                
            }
        }
    }

    
    //get entries
    entries = orderBook.getOrders(orderType, product, currentTime);

    //show min ask and bid with checking orderType using getLowPrice
    if(orderType == OrderBookType::ask) 
    {
        std::cout << "The min ask for " << product <<" is : "<< OrderBook::getLowPrice(entries) << std::endl;
    } 
    else if(orderType == OrderBookType::bid)
    {   
        std::cout << "The min bid for " << product <<" is : "<< OrderBook::getLowPrice(entries) << std::endl;
    }
    //if no order found return unknown orderType
    else
    {
        std::cout<< "AdvisorBot::Min(error): it is an unknown orderType"<<std::endl;
    }
    
}



/*
Max same as Min but change to getHighPrice
*/

/* shows maximum bid or ask of product in current timestamp */
void AdvisorBot::Max(const std::vector<std::string>&commandTokens) 
{   
    //assign command inputs to product,orderType variable 
    std::string product = commandTokens[1];  
    OrderBookType orderType;
    orderType = OrderBookEntry::stringToOrderBookType(commandTokens[2]); 

    //create storing entry
    std::vector<OrderBookEntry> entries; 

    //check if it is a product 
    std::vector<std::string> ProductList = orderBook.getKnownProducts();
    for(std::string &p : ProductList) 
    {
        if(p == product) 
        {   
            break; 
            return;
        }
        // if until the last element of vector,the products still cannot be found
        else if(p == ProductList.back())
        {   
            if(p!=product)
            {
                std::cout << "AdvisorBot::Max(error) invalid product" << std::endl;
                return;
            }
        }
    }

    
    //get entries
    entries = orderBook.getOrders(orderType, product, currentTime);

    //show max ask and bid with checking orderType using getHighPrice
    if(orderType == OrderBookType::ask) 
    {
        std::cout << "The max ask for " << product <<" is : "<< OrderBook::getHighPrice(entries) << std::endl;
    } 
    else if(orderType == OrderBookType::bid)
    {   
        std::cout << "The min bid for " << product <<" is : "<< OrderBook::getHighPrice(entries) << std::endl;
    }
    else
    {
        std::cout<< "AdvisorBot::Max(error): it is an unknown orderType"<<std::endl;
    }
    
}


/* shows average ask or bid of product over a period of timestamps */
void AdvisorBot::Avg(const std::vector<std::string>&commandTokens) 
{   
    
    std::string product = commandTokens[1]; 
    //check if it is a product 
    std::vector<std::string> ProductList = orderBook.getKnownProducts();
    for(std::string &p : ProductList) 
    {
        if(p == product) 
        {   
            break; //if product found break out if 
            return;
        }
        else if(p == ProductList.back())
        {   
            if(p!=product)
            {
                std::cout << "AdvisorBot::Avg(error) invalid product" << std::endl;
                return;
            }
        }
    }

    
    OrderBookType orderType; 
    //organize orderType with stringtoOrderBookType
    orderType = OrderBookEntry::stringToOrderBookType(commandTokens[2]);
    
    //print error if not ask or bid
    if(orderType == OrderBookType::unknown) 
    {
        std::cout << "AdvisorBot::Avg (error) : it is an unknown orderType" << std::endl;
    }

    
    std::string timestamp = currentTime;
    if(timestamp.empty()) 
    {
        std::cout << "AdvisorBot::Avg has no timestamp record,therefore no price" << std::endl; 
    }


    //take the user input timestamp
    int inputTimestamp = 0;
    try 
    {
        inputTimestamp = std::stoi(commandTokens[3]); // token at [3] e.g avg ETH/BTC ask (5) is the number of timestamp
    }
    catch(const std::exception& e)
    {   
       
        std::cout << "AdvisorBot::Avg (error):enter integer for a period of timestamp to find avg" << std::endl;
        return;
    }

    //get all other timestamps to compare and add their avg to SumAverage
    double sumAverage = 0;
    for(int i = 0; i < inputTimestamp; i++) 
    {   
        //get number of entries by number of timestamps
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, timestamp);
        if(timestamp.empty()) 
        {
            std::cout << "Number of timestamp does not match entries found,step/jump forward to get more entries" << std::endl;
            return;
        }
        //get avg price of a timestamp
        double average = OrderBook::getAvgPrice(entries);

        //print individual averages
        std::cout << "Price on time " << timestamp << ": " << average << std::endl;
        //sum all averages
        sumAverage += average;
        //get previous times in descending order
        timestamp = orderBook.getPrevTime(timestamp);
    }

    //calculate total average price with every timestamps
    std::cout<<""<<std::endl;
    std::cout << "Average "<< product <<" "<< commandTokens[2] <<" over last "<< inputTimestamp <<" time steps : "<< sumAverage / inputTimestamp << std::endl;

}


/* predicts max or min (ask/bid) of product for next timestamp */
void AdvisorBot::Predict(const std::vector<std::string>&commandTokens) 
{
    //check if entered parameters is max or min
    std::string priceType;
    if(commandTokens[1] == "max") 
    {
        priceType = "max";
    } 
    else if(commandTokens[1] == "min") 
    {
        priceType = "min";
    }  
    else
    {
        std::cout << "AdvisorBot::Predict (error): please enter max or min only" << std::endl;
        return;
    }
   
    std::string product = commandTokens[2];
    std::vector<std::string> ProductList = orderBook.getKnownProducts();
    for(std::string &p : ProductList) 
    {
        if(p == product) 
        {   
            break; //break out if
            return;
        }
        else if(p == ProductList.back())
        {   
            if(p!=product)
            {
                std::cout << "AdvisorBot::Predict(error) invalid product" << std::endl;
                return;
            }
        }
    }
    // OrderBookType orderType;
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(commandTokens[3]);

    //check for unknown OrderType 
    if(orderType == OrderBookType::unknown) 
    {
        std::cout << "AdvisorBot::Predict (error): it is an unknown orderType" << std::endl;
        return;
    }
    //initialize prices so we can update its value later
    double prevPrice = 0;
    double currPrice = 0;

    //two entries with different timestamp to store current and prev price
    std::vector<OrderBookEntry> entries;
    std::vector<OrderBookEntry> entries2;
    std::string timestamp = currentTime;
    std::string timestamp2 = orderBook.getPrevTime(timestamp); ;
  
    //entries for current timestamp
    entries = orderBook.getOrders(orderType, product, timestamp);
    //entries for previous timestamp 
    entries2 = orderBook.getOrders(orderType, product,timestamp2 );

    //assign current price by priceType
    if(currPrice == 0) 
    {   
        //check if timeStamp is empty meaning no string of timestamp retrieved, 
        // tell user to step forward as user at beginning of timestamp with limited timestamp to predict.
    
        if(timestamp.empty()) 
        {   
            std::cout << "AdvisorBot::Predict (error) : Currently on the beginning of timestamp\nstep forward to make prediction as now limited timestamps to compare" << std::endl;
            return;
        }
        
        if(priceType== "max") 
        {  
            currPrice = OrderBook::getHighPrice(entries);
            
        } 
        else if(priceType == "min") 
        {   
            currPrice = OrderBook::getLowPrice(entries);
        }
    }

    //assign previous price by priceType
    if(prevPrice == 0)
    {        
        if(timestamp2.empty()) 
        {
            std::cout << "AdvisorBot::Predict (error) : Currently on the beginning of timestamp\nstep forward to make prediction as now limited timestamps to compare" << std::endl;
            return;
        }

        if(priceType == "max") 
        {   
            
            prevPrice = OrderBook::getHighPrice(entries2);
        } 
        else if(priceType == "min") 
        {   
            prevPrice = OrderBook::getLowPrice(entries2);
        }
 
    }

    std::cout << "Previous price at "<< timestamp2<<" is : " << prevPrice<<std::endl;
    std::cout << "Current  price at "<< timestamp <<" is : " <<  currPrice<<std::endl;

    // predict using moving average
    // EMA(current) = ((Price(current) – EMA (prev)) x Multiplier) + EMA(prev)
    std::cout << "The exponential moving average predicts the next " << priceType << " " << product << " " << commandTokens[3] << " " << "price is : "<< ((currPrice - prevPrice) * -5 / 10) + currPrice <<std::endl ;
   
}


/*  step forward(once) timestamp */
void AdvisorBot::gotoNextTimeframe() 
{
    std::cout << "Stepping to next timeframe..." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);

    //if empty means we are at end of timestamp so return into first timestamp
    if(currentTime.empty()) 
    {
        currentTime=orderBook.getEarliestTime();
    }
    else
    std::cout << "New time at: " << currentTime << std::endl;
}

/*  jump forward(multiple) timestamp */
void AdvisorBot::JumpNextTimeframe(std::string&timestampNumber)
{   
     //take the user input timestamp
    int inputTimestamp = 0;
    try 
    {
       inputTimestamp = std::stoi(timestampNumber);
        for(int i = 0; i < inputTimestamp; i++) 
        {
            currentTime = orderBook.getNextTime(currentTime);
        }
        std::cout << "Jumping to next "<< inputTimestamp  <<" timeframes..." << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cout << "AdvisorBot::JumpNextTimeframe (error): input has to be integer type :" << timestampNumber  << std::endl;
    }
    //if empty means we are at end of timestamp so return into first timestamp
    if(currentTime.empty()) 
    {
        currentTime=orderBook.getEarliestTime();
    }
    else
    std::cout << "New timestamp: " << currentTime << std::endl;
}

/*  step back(once) timestamp */
void AdvisorBot::gotoPrevTimeframe() 
{
    std::cout << "Stepping to previous timeframe..." << std::endl;
    currentTime = orderBook.getPrevTime(currentTime);
    //instruct user no more previous timestamp when reach beginning of timestamp
    if(currentTime.empty()) 
    {
        std::cout << "We are at beginning of timestamp" << std::endl;
        std::cout << "There is no previous timestamp" << std::endl;
        std::cout << "Please step/jump <forward>" << std::endl;
    }
    else
    std::cout << "New time at: " << currentTime << std::endl;
}

/*  jump back(multiple) timestamp */
void AdvisorBot::JumpPrevTimeframe(std::string&timestampNumber)
{   
    //take the user input timestamp
    int inputTimestamp = 0;
    try 
    {
        inputTimestamp = std::stoi(timestampNumber);
        for(int i = 0; i < inputTimestamp; i++) 
        {
            currentTime = orderBook.getPrevTime(currentTime);
    
        }
        std::cout << "Jumping to previous "<< inputTimestamp  <<" timeframes..." << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cout << "AdvisorBot::JumpNextTimeframe (error) : input has to be integer type :" << timestampNumber  << std::endl;
    }

    //instruct user no more previous timestamp when reach beginning of timestamp
    if(currentTime.empty()) 
    {
        std::cout << "We are at beginning of timestamp" << std::endl;
        std::cout << "There is no previous timestamp" << std::endl;
        std::cout << "Please step/jump <forward>" << std::endl;
    }
    else
    std::cout << "New timestamp: " << currentTime << std::endl;
}
/*  reset timestamp to beginning */
void AdvisorBot::reset()
{
	currentTime = orderBook.getEarliestTime();
	std::cout << "Time is reset to: " << currentTime << std::endl;
}

/* clear screen */
void AdvisorBot::clearScreen()
{   
    system("clear||cls");
}


//exit program setting programRunning status to false
void AdvisorBot::exit()
{   
    std::cout <<""<<std::endl;
    std::cout << ""<<std::endl;
    std::cout << ""<<std::endl;
    std::cout<<"       Thanks for using AdvisorBot !   "<<std::endl;
    std::cout <<""<<std::endl;
    std::cout << ""<<std::endl;
    std::cout << ""<<std::endl;
    //set programRunning to false when user exit program
    programRunning=false;
}