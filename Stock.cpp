/*
 * Stock class
 */

#include "Stock.h"
#include<fstream>
#include<ctime>
#define timestep 1

using namespace std;

// constructor
Stock::Stock(string _tick, vector <int> _EMA_Times, int _MACD_Time) {

	// initialize tick and times for EMA and MACD
	_tick = tick;
	EMA_Times = _EMA_Times;
	MACD_Time = _MACD_Time;
	start = true;
	
	// initialize EMA vectors
	curEMA.resize(EMA_Times.size);
	myEMA.resize(EMA_Times.size);
	for (std::vector<EMA*>::iterator i = myEMA.begin(), e = myEMA.end();
			i != e, ++i) {
		(*i) = new EMA (???);
	 }
	 
    myMACD = new MACD(???);

	curPrice = -1;
	curEMA = -1;
	curMACD = -1;

	// Create and write to files
	string filename;

	// Price, ofstream name fPrice, filename RIM_Price.txt
	filename = this->tick + "_Price.txt";
	fPrice.open(filename.c_str());
	fPrice << "Time\tPrice" << endl;
	
	// MACD, ofstream name fMACD,  filename RIM_MACD.txt
	filename = this->tick + "_MACD.txt";
	fMACD.open(filename.c_str());
	fMACD << "Time\tMACD" << endl;

	// EMA, ofstream name fEMA[i],  filename RIM_EMA_Time20s.txt
	for (int i=0; i<fEMA.length; ++i) {
		int time_period = EMA_Times.at(i); 
		filename = this->tick + "_EMA_Time" + time_period + "s.txt";
		fEMA.at(i).open(filename.c_str());
		fEMA.at(i) << "Time\tEMA" << endl;
	}
}

Stock::~Stock() {
	delete myMACD;
	for (std::vector<EMA*>::iterator i = myEMA.begin(), e = myEMA.end();
			i != e, ++i) {
		delete(*i);
	 }	 

	// close files
	fPrice.close();
	fMACD.close();
	for (int i=0; i<fEMA.length; ++i) {
		fEMA.at(i).close();
	}	
}

double Stock::getEMA(int index) {
	if ( (index >= curEMA.size) || (index < 0) ) {
		return -1;
	}
	if (curEMA < 0) {
		return -1;
	}
	return curEMA;
//    return rand() % 100;
}

double Stock::getMACD() {
	if (curMACD < 0) {
		return -1;
	return curMACD;
//    return rand() % 100;
}

double Stock::getPrice() {
	return curPrice;
//    return rand() % 100;
}

string Stock::getTick() {
	return tick;
}

void Stock::Start() {
	// our time counter, should be GLOBAL for entire program
	unsinged long long time = 0;

	// multi-threaded? Runs forever
	while (start) { // i.e. while(1)
		// wait 1 sec
		delay(timestep);
		time += timestep;

		curPrice = API GET PRICE;
		// write to file
		fPrice << timestep << "\t" << curPrice << endl;

		curMACD = -1; // invalid
		// if we're at a multiple of MACD_Time
		if (time % MACD_Time == 0) {
			if (MACD->valid()) {
				curMACD = MACD->calculateMACD(price);
				// write to file
				fMACD << timestep << "\t" << curMACD << endl;
			}
		}
			
		for (int i=0; i < myEMA.size; ++i) {
			curEMA.at(i) = -1;
			// if we're at a multiple of EMA_Time(i)
			if (time % EMA_Times.at(i) == 0) {
				if (myEMA.at(i)->valid()) {
					curEMA.at(i) = myEMA.at(i)->calculateEMA(price);
					// write to file
					fEMA.at(i) << timestep << "\t" << curEMA.at(i) << endl;
				}
			}
		}		
	}
}
