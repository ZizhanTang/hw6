#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        // Convert each letter/digit to a number between 0 and 35
        std::vector<HASH_INDEX_T> digits;
        for (char c : k) {
            if (c >= 'a' && c <= 'z') {
                digits.push_back(c - 'a');
            } else if (c >= '0' && c <= '9') {
                digits.push_back(c - '0' + 26);
            } else if (c >= 'A' && c <= 'Z') {
                digits.push_back(c - 'A');
            }
        }
        
        // Split the digits into groups of 6 and convert each group to an integer
        std::vector<unsigned long long> w(5, 0);
        int i = digits.size() - 1;
        for (int j = 4; j >= 0 && i >= 0; j--) {
            unsigned long long power = 1;
            for (int k = 0; k < 6 && i >= 0; k++, i--) {
                w[j] += digits[i] * power;
                power *= 36;
            }
        }
        
        // Compute the final hash value using the rValues
        HASH_INDEX_T result = 0;
        for (int i = 0; i < 5; i++) {
            result += rValues[i] * w[i];
        }
        
        return result;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        } else if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
        } else if (letter >= 'A' && letter <= 'Z') {
            return letter - 'A';
        } else {
            // Handle invalid characters
            return 0;
        }

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
