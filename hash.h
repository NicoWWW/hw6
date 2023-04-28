#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				int length = k.size();
				int curr[length] = {0};
				for (int i=0; i<length; i++){
					curr[i] = letterDigitToNumber(k[i]);
				}

				unsigned long long w[5] = {0};
				for (int i=0; i<5; i++){
					w[4-i] = 0;
					for (int j=0; j<6; j++){
						if(length-(j+(6*i))-1 >= 0){
							w[4-i] += pow(36,j)*curr[length-(j+(6*i))-1];
						}
						else{
							w[4-i] += 0;
						}
					}
				}

				HASH_INDEX_T value=0;
				for (int i=0; i<5; i++){
					value += (w[i]*rValues[i]);
				}

				return value;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				/*
				unsigned int count = 0;
				char temp = tolower(letter);
				for (char hi = 'a'; hi <= 'z'; hi++){
					if (temp == hi){
						return count;
					}
					count++;
				}
				for (char hi = '0'; hi <= '9'; hi++){
					if (temp == hi){
						return count;
					}
					count++;
				}*/
				HASH_INDEX_T number;
				char temp = letter;
				if (letter >= 'A' && letter <= 'Z'){
					temp = tolower(letter);
				}
				if (temp >= 'a' && temp <= 'z'){
					number = (int)temp - 97;
				}
				else if (temp >= '0' && temp <= '9'){
					number = (int)temp -22;
				}
				return number;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
