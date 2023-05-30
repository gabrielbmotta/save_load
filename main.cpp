#include "save_load.h"

#include <iostream>

int main(){
    std::cout << "Testing.\n";
    Plaintext::Loader loader("testfile.txt");
    loader.loadFromFile();
   
    for(const auto& el : loader._data){
        std::cout << el.first << " ---- ";
        if(el.first == "ELEMENT1"){
            std::cout << std::any_cast<int>(el.second) << "\n";
        }else{
            std::cout << std::any_cast<std::string>(el.second) << "\n";
        }
    }

    Plaintext::Saver saver("my_test_file2.txt");
    saver.setValue("ONE", 55);
    saver.setValue("TWO", "A string.");
    saver.setValue("THREE","A multi-\nline\nstring.");

    saver.saveToFile();

    return 0;
}
