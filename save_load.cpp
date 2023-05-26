#include "save_load.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using Plaintext::Loader;
using Plaintext::Saver;

//==================================================================================================

Loader::Loader(const std::string& file)
:_infile(file)
{
    
}

//==================================================================================================

void Loader::setFile(const std::string &file)
{
    _infile.open(file);
}

//==================================================================================================

void Loader::loadFromFile(const std::string& file)
{
    setFile(file);
    loadFromFile();
}

//==================================================================================================

void Loader::loadFromFile()
{
    std::cout << "1\n";
    if(!_infile.is_open()){
        return;
    }

    std::cout << "2\n";
    std::string line;

    bool mid_input = false;
    std::string carryover_data;
    std::string carryover_key;

    while(std::getline(_infile, line)){
        std::cout << "[READ IN] " << line << "\n";
        if(line.size() > 3 && line[0] == '#' && line[1] == '#' && line[2] == '#'){
            continue;
        }
        if(mid_input){
            std::cout << "In mid input\n";
            auto ending = line.find(">>>");
            if(ending == std::string::npos){
                carryover_data += " " + line;
                continue;
            } else if(ending != 0) {
                carryover_data += " " + line.substr(0, ending);
            }
            _data[carryover_key] = carryover_data;
            carryover_data.clear();
            carryover_key.clear();
            mid_input = false;
        } else {
            std::cout << "Not in mid input\n";
            auto equal = line.find("=");
            if(equal == std::string::npos || equal == line.size() - 1){
                std::cout << "HERE!\n";
                return;
            }
            auto key = line.substr(0, equal);
            auto data = line.substr(equal + 1);
            if(data.size() > 3 && data[0] == '<' && data[1] == '<' && data[2] == '<'){
                data = data.substr(3);
                auto ending = data.find(">>>");
                if(ending == std::string::npos){
                    carryover_data = std::move(data);
                    carryover_key = std::move(key);
                    mid_input = true;
                    continue;
                } else if(ending != 3) {
                    data = data.substr(0,ending); 
                } else {
                    data = "";
                }
                _data[key] = data;
            } else if(!data.empty()){
                _data[key] = data;
            }
        }
    }
}

//==================================================================================================

const std::string& Loader::getValue(const std::string& key)
{
    return _data[key];
}

//==================================================================================================

void Saver::setFile(const std::string& file)
{
    _outfile.open(file);
}

//==================================================================================================
    
void Saver::saveToFile(const std::string& file)
{
    setFile(file);
    saveToFile();
}

//==================================================================================================
    
void Saver::saveToFile()
{

}


