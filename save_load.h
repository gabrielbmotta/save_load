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

    void loadSelectionFromFile(const std::string& file, const std::vector<std::string>& keys);
    void loadSelectionFromFile(const std::vector<std::string>& keys);

    const std::any& getValue(const std::string& key);
    int getInt(const std::string& key);
    std::string getStr(const std::string& key);

private:
    void parseLine(const std::string& line);
    void parseAsString(const std::string& key, const::std::string& value);
    void parseAsInt(const std::string& key, const::std::string& value);
    void parseMultilineString(std::string& str);

    std::pair<std::string, std::string> splitKeyValue(const std::string& line);
    
    bool lineIsComment(const std::string& line);
    bool valueIsString(const std::string& value);

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

    void setValue(const std::string& key, int value);
    void setValue(const std::string& key, const std::string& value);

private:
    std::ofstream _outfile;
    std::unordered_map<std::string, std::string> _data;
};

} // namespace Plaintext

#endif
