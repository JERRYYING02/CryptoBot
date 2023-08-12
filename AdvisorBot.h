#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class AdvisorBot
{
public:
    AdvisorBot();
    /* Call this to start the sim */
    void init();
   

private:

    std::string currentTime;
    //read csv file with OrderBook
    OrderBook orderBook{"20200601.csv"};

    /* boolean running status */
    bool programRunning;

    /* direct menu after run*/
    void showMenu();

    /*  shows all available commands */
    void showHelp();


    /// @param commandTokens 
    /*  shows function for specific commands */
    void showHelpCmd(const std::string &commandToken);

    /* shows list of all products */
    void Prod();
    



    /// @param commandTokens 
    /* shows minimum bid or ask of product in current timestamp */
    void Min(const std::vector<std::string>&commandTokens);

    /* shows maximum bid or ask of product in current timestamp */
    void Max(const std::vector<std::string>&commandTokens);

    /* shows average ask or bid of product over a period of timestamps */
    void Avg(const std::vector<std::string>&commandTokens);

    /* predicts max or min (ask/bid) of product for next timestamp */
    void Predict(const std::vector<std::string> &commandTokens);


     /// @param timestampNumber 
    /*  step and jump to next or previous timestamp */
    void gotoNextTimeframe();
    void JumpNextTimeframe(std::string& timestampNumber);

    void gotoPrevTimeframe();
    void JumpPrevTimeframe(std::string& timestampNumber);

    //custom commands
    /*  reset timestamp to beginning */
    void reset();
    /* clear screen display to make less crowded */
    void clearScreen();
    /* quit program */
    void exit();

    /* command parsing */
    void processUserOption();

 
};
