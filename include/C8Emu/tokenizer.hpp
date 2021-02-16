#pragma once

#include <map>
#include <string>

#include "exceptions.hpp"

template<class Key, class Value>
class Tokenizer final {
private:
    std::map<Key, Value> _tokens;       // Map of tokens

public:
    /**
     * Parsing C array and create pairs
     * @param size - size of the array
     * @param array - the array of 
     */
    void parse(const int, char**);

    /**
     * Find a value which corresponds to the given key
     * @param key - a key
     * @return - a value, corresponding to the key
     */
    Value getValue(Key);
};

template<class Key, class Value>
void Tokenizer<Key, Value>::parse(const int size, char** array) {
    std::string token;           // Temporary variable for storing tokens

    // TODO : check if empty

	// Iterate over an array of arguments
	for (char** p_token = &(array[1]); p_token != &(array[size]); ++p_token) {
		// Cast a char array to a string
		token = std::string(*p_token);

		//Make a map out of the argument
		_tokens.insert(make_pair((Key)token.substr(0, token.find("=")), \
			(Value)token.substr(token.find("=") + 1, token.size())));
	}
}

template<class Key, class Value>
Value Tokenizer<Key, Value>::getValue(Key key) {
    typename std::map<Key, Value>::iterator iter;           // Temporary iterator used to find keys inside of an std::map
    Value result;                                           // Result of the function's work

    // Find a filename in arguments
    iter = _tokens.find(key);
    
    // Check if filename was specified
    if (iter == _tokens.end()) throw Exception(TNOTFOUND);
    
    // Save the value
    result = iter->second;

    return result;
}