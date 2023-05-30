#ifndef SAVE_LOAD_PLAINTEXT
#define SAVE_LOAD_PLAINTEXT

#include <string>
#include <fstream>
#include <unordered_map>
#include <type_traits>
#include <any>

namespace Plaintext {

class Loader {
public:
    Loader() = default;
    Loader(const std::string& file);

    void setFile(const std::string& file);

    void loadFromFile(const std::string& file);
    void loadFromFile();
    const std::any& getValue(const std::string& key);

// private:
    std::ifstream _infile;
    std::unordered_map<std::string, std::any> _data;
};

class Saver {
public:
    Saver() = default;
    Saver(const std::string& file);

    void setFile(const std::string& file);
    
    void saveToFile(const std::string& file);
    void saveToFile();

    template<typename T>
    void setValue(const std::string& key, const T& value);

private:
    std::ofstream _outfile;
    std::unordered_map<std::string, std::any> _data;
};


template<typename T>
void Saver::setValue(const std::string& key, const T& value){
    _data[key] = value; 
}

} // namespace Plaintext

#endif
