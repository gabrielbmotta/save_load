#ifndef SAVE_LOAD_PLAINTEXT
#define SAVE_LOAD_PLAINTEXT

#include <string>
#include <fstream>
#include <unordered_map>
#include <type_traits>

namespace Plaintext {

class Loader {
public:
    Loader() = default;
    Loader(const std::string& file);

    void setFile(const std::string& file);

    void loadFromFile(const std::string& file);
    void loadFromFile();
    const std::string& getValue(const std::string& key);

// private:
    std::ifstream _infile;
    std::unordered_map<std::string, std::string> _data;
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
    std::unordered_map<std::string, std::string> _data;
};


template<typename T>
void Saver::setValue(const std::string& key, const T& value){
    if constexpr(std::is_same_v<std::string,T>){
        _data[key] = value; 
    } else {
        _data[key] = std::to_string(value);
    }
}

} // namespace Plaintext

#endif
