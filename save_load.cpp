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

const std::any& Loader::getValue(const std::string& key)
{
    return _data[key];
}

//==================================================================================================

void Loader::parseLine(const std::string& line)
{
    if(lineIsComment(line) || line.empty()){
       return;
    }

    std::string key, value;
    std::tie(key, value) = splitKeyValue(line);
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
    return (value.size() > 2 && value[0] == '<' && value[1] == '<' && value[2] == '<');
}

//==================================================================================================

void Loader::parseAsString(const std::string& key, const::std::string& value)
{
    auto str_val = value.substr(3);
    
    auto ending = str_val.find(">>>");
    if(ending == std::string::npos){
        parseMultilineString(str_val);
    } else if(ending != 3) {
        str_val = str_val.substr(0,ending); 
    } else {
        str_val = "";
    }
    _data[key] = str_val;
}

//==================================================================================================

void Loader::parseAsInt(const std::string& key, const::std::string& value)
{
    _data[key] = std::atoi(value.c_str());
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

