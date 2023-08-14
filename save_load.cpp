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
    if(!_infile.is_open()){
        return;
    }

    std::string line;
    while(std::getline(_infile, line)){
        parseLine(line);
    }
}

//==================================================================================================
void Loader::loadSelectionFromFile(const std::string& file, const std::vector<std::string>& keys)
{
    setFile(file);
    loadSelectionFromFile(keys);
}

//==================================================================================================
void Loader::loadSelectionFromFile(const std::vector<std::string>& keys)
{
    if(!_infile.is_open()){
        return;
    }

    std::string line;
    while(std::getline(_infile, line)){
        auto key = line.substr(0, line.find('='));
        if(std::find(keys.begin(), keys.end(), key) != keys.end()){
            std::cout << "KEY: " << key << std::endl;
            parseLine(line);
        }
    }
}

//==================================================================================================

const std::any& Loader::getValue(const std::string& key)
{
    return _data[key];
}

//==================================================================================================

int Loader::getInt(const std::string& key)
{
    return std::any_cast<int>(getValue(key));
}

//==================================================================================================

std::string Loader::getStr(const std::string& key)
{
    return std::any_cast<std::string>(getValue(key));
}

//==================================================================================================

void Loader::parseLine(const std::string& line)
{
    if(lineIsComment(line) || line.empty()){
       return;
    }

    std::string key, value;
    std::tie(key, value) = splitKeyValue(line);
    std::cout << "KEY: " << key << "| VAL: " << value << std::endl;
    if(key.empty() || value.empty()){
        return;
    }

    if(valueIsString(value)){
        parseAsString(key, value);
    } else{
        parseAsInt(key, value);
    }
}

//==================================================================================================

std::pair<std::string, std::string> Loader::splitKeyValue(const std::string& line)
{
    auto equal = line.find("=");
    if(equal == std::string::npos || equal == line.size() - 1 || equal == 0){
        return{"",""};
    }
    return {line.substr(0, equal), line.substr(equal + 1)};
}

//==================================================================================================

bool Loader::lineIsComment(const std::string& line)
{
    return (line.size() > 2 && line[0] == '#' && line[1] == '#' && line[2] == '#');
}

//==================================================================================================

bool Loader::valueIsString(const std::string& value)
{
    return (value.length() > 2 && value[0] == '<' && value[1] == '<' && value[2] == '<');
}

//==================================================================================================

void Loader::parseAsString(const std::string& key, const::std::string& value)
{
    auto str_val = value.substr(3);
    
    auto ending = str_val.find(">>>");
    if(ending == std::string::npos){
        std::cout << "1\n";
        parseMultilineString(str_val);
    } else if(ending != 0) {
        std::cout << "2\n";
        str_val = str_val.substr(0,ending); 
    } else {
        std::cout << "3\n";
        str_val = "";
    }
    _data[key] = str_val;
    std::cout << "ADDED: " << key << " as " << str_val << std::endl;
}

//==================================================================================================

void Loader::parseAsInt(const std::string& key, const::std::string& value)
{
    _data[key] = std::stoi(value);
    std::cout << "ADDED: " << key << " as " << value << std::endl;
}

//==================================================================================================

void Loader::parseMultilineString(std::string& str)
{
    std::string line;
    std::getline(_infile, line);

    auto ending = line.find(">>>");
    if(ending == std::string::npos){
        str += " " + line;
        parseMultilineString(str);
    } else if(ending != 0) {
        str += " " + line.substr(0, ending);
    }
}

//==================================================================================================

Saver::Saver(const std::string& file)
: _outfile(file)
{
    std::cout << "File path:" << file << "\n";
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
        std::cout << "PANIC!!!";
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

