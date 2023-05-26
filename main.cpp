#include "save_load.h"

#include <iostream>

int main(){
    std::cout << "Testing.\n";
    Plaintext::Loader loader("testfile.txt");
    loader.loadFromFile();
   
    for(const auto& el : loader._data){
        std::cout << el.first <<" - " << el.second << "\n";
    }

    return 0;
}
