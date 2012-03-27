/*
 * Stock class
 */

#ifndef STOCK_H
#define STOCK_H

#include "MACD.h"
#include "EMA.h"
#include <string>

// Dummy stock class
class Stock{
    public:
        Stock(string tick, std::vector <int> EMA_Times, int MACD_time);
	 	~Stock();
        double getEMA(int index);
        double getMACD();
        double getPrice();
        std::string getTick();
	   
	private:
	    std::string tick;

		// Time steps
		std::vector <int> EMA_Times;
		int MACD_Time;
		
		std::vector <EMA *> myEMA;
		MACD * myMACD;

		std::ofstream fPrice;
		std::ofstream fMACD;
		std::vector <std::ofstream> fEMA;
		
		
		std::vector <double> curEMA;
		double curMACD;
		double curPrice;

		bool start;
};

#endif
