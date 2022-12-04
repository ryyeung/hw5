// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(
    const std::string& in,
    const std::set<char> floating, 
    const std::set<std::string>& dict, 
    unsigned int index, std::set<std::string> possible);

/*
Approach: 
find all words with given string in and floating chars
fill in rest of letters with all letters and check if english language word

*/
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating, 
    const std::set<std::string>& dict)
{
    std::set<char> floating_set(floating.begin(), floating.end()); //floating set copy
    std::set<std::string> possible;
   
    wordle_helper(in,floating_set, dict, 0, possible);
    return possible; //answer set
}

void wordle_helper(
    const std::string& in,
    const std::set<char> floating_set, 
    const std::set<std::string>& dict, 
    unsigned int index, std::set<std::string> possible){
    
    std::string current = in; //copy of string
    
    //alphabet set
    std::string alpha = "abcdefghijklmnopqrstuvwxyz";
    const std::set<char> alphabet(alpha.begin(),alpha.end());
    //iterator
    std::set<char>::iterator alpha_iterate;
    std::set<char>::iterator curr_floating_iterate;
    std::set<char> curr_floating(floating_set.begin(), floating_set.end()); //copy of floating set
    

    //base case, if reach end of index 
    if(index == in.length()){
        //get to end of index and checkk, make sure floating is empty 
        if(dict.find(current) != dict.end() ){ //check if English word
            possible.insert(current);
        }
        return;
    }
    if(current[index] == '-'){ //empty location  
        //iterate floating letters
        for(curr_floating_iterate = floating_set.begin();
        curr_floating_iterate != floating_set.end(); ++curr_floating_iterate){ 
            current[index] = *curr_floating_iterate; //add letter
            
            //remove floating 
            std::set<char>::iterator iterate;
            iterate = curr_floating.find(*curr_floating_iterate);
            if(iterate != curr_floating.end()){
                curr_floating.erase(iterate);
            }

            wordle_helper(current, curr_floating, dict, index+1, possible); //recursive call, move one space 
            std::set<char> curr_floating(floating_set.begin(), floating_set.end()); //make original set again 
        } 
            
        //check alphabet
        for(alpha_iterate = alphabet.begin(); 
        alpha_iterate != alphabet.end(); ++alpha_iterate){ //iterate thru alphabet set
                current[index] = *alpha_iterate; //try alphabet letter 
                wordle_helper(current, floating_set, dict, index+1, possible); //recurse
        }
    }
    return;
}



 