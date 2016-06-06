/* 
 * File:   johnsonH3.cpp
 * Author: Kenji Johnson
 *
 * Time taken to convert: 4 hours
 *
 */

#include "fraction.h"
#include "SetLimits.h"
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

/* takes a list of mixed numbers from file
 * sorts and outputs list
 */
int main (int argc, char** argv){
    SetLimits();
    vector<fraction> inputList;
    bool first = true;
    fraction sum, diff, prod, quot;
    FILE * in;
    if (argc > 1) in = fopen(argv[1], "r");
    else{
        printf("Needs an input file.\n");
        return 1;
    }
    if (in == NULL){
        printf("Error opening file.\n");
        return 2;
    }
    int wholeTemp = 0;
    int numTemp = 0;
    int denomTemp = 0;
    // get input from in file
    while (fscanf(in, "%d %d/%d", &wholeTemp, &numTemp, &denomTemp) != EOF){
        fraction temp = fraction(wholeTemp, numTemp, denomTemp);
        if(first){
            //set initial values
            sum = temp;
            diff = temp;
            prod = temp;
            quot = temp;
            first = false;
        }
        else{
            //update calculations
            sum += temp;
            diff -= temp;
            prod *= temp;
            quot /= temp;
        }
        inputList.push_back(temp);
    }
    fclose(in);
    
    // print initial calculations
    printf("Before sorting:");
    cout << "\n\tThe sum of the fractions is: " << sum;
    (sum.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe difference of the fractions is: " << diff;
    (diff.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe product of the fractions is: " << prod;
    (prod.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe quotient of the fractions is: " << quot;
    (quot.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    
    // sort
    sort(inputList.begin(), inputList.end());
    
    // recalculate on sorted
    first = true;
    for (int i = 0; i < (int)inputList.size(); i++){
        if(first){
            //set initial values
            diff = inputList[i];
            quot = inputList[i];
            first = false;
        }
        else{
            //update calculations
            diff -= inputList[i];
            quot /= inputList[i];
        }
    }
    printf("\nAfter sorting:");
    cout << "\n\tThe sum of the fractions is: " << sum;
    (sum.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe difference of the fractions is: " << diff;
    (diff.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe product of the fractions is: " << prod;
    (prod.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    cout << "\n\tThe quotient of the fractions is: " << quot;
    (quot.Valid()) ? (cout << " (valid)") : (cout << " (invalid)");
    
    // print sorted list
    cout << endl;
    for (int i = 0; i < (int)inputList.size(); i++){
        cout << inputList[i] << endl;
    }
    
    return 0;
}
