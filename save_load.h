#ifndef SAVE_LOAD_PLAINTEXT
#define SAVE_LOAD_PLAINTEXT

#include <string>
#include <fstream>
#include <unordered_map>

namespace Plaintext {

class Loader {
public:
    Loader() = default;
    Loader(const std::string& file);

    void setFile(const std::string& file);

    void loadFromFile(const std::string& file);
    void loadFromFile();

private:
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
    void setValue(const std::string& key, const T& value){
        _data[key] = std::to_string(value);
    }
    template<>
    void setValue(const std::string& key, const std::string& value){
        _data[key] = value; 
    }
private:
    std::ofstream _outfile;
    std::unordered_map<std::string, std::string> _data;
};

} // namespace Plaintext

#endif
