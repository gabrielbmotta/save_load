#include "save_load.h"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <cstdlib>

using Plaintext::Loader;
using Plaintext::Saver;

//==================================================================================================

bool isInt(const std::string& str){
    for(const auto& c : str){
        if(!std::isdigit(c)){
            return false;
        }
    }
    return true;
}

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
        if(line.size() > 2 && line[0] == '#' && line[1] == '#' && line[2] == '#'){
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
                if(isInt(data)){
                    _data[key] = std::atoi(data.c_str());
                }
            }
        }
    }
}

//==================================================================================================

const std::any& Loader::getValue(const std::string& key)
{
    return _data[key];
}

//==================================================================================================

Saver::Saver(const std::string& file)
: _outfile(file)
{
    
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
    if(!_outfile.is_open()){
        return;
    }

    for(const auto& element : _data){
        _outfile << element.first << "=" << element.second << "\n";
    }
}

//==================================================================================================

void Saver::setValue(const std::string& key, int value)
{
    _data[key] = std::to_string(value);
}

//==================================================================================================

void Saver::setValue(const std::string& key, const std::string& value)
{
    _data[key] = "<<<" + value + ">>>"; 
}

