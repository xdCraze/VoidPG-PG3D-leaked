#pragma once

#include <fstream>
#include <vector>
#include <string>

class FileHandling
{
public:
    const char* Directory;

    FileHandling(const char* dir)
    {
        Directory = dir;
        std::fstream file(dir, std::ios::in);
        std::string line;
        while (std::getline(file, line)) _lines.emplace_back(line);
        file.close();

        for (int i = 0; i < _lines.size(); i++) {
            _fileData += _lines[i] + "\n";
        }
        if (!_fileData.empty()) _fileData.pop_back();
    }

    std::string operator()()
    {
        return _fileData.empty() ? "empty" : _fileData;
    }

    std::string operator[](int line)
    {
        if (_lines.empty()) return "empty";
        try {
            return (line == 0) ? _lines[line] : _lines[line - 1];
        }
        catch (std::length_error e) {
            return "empty";
        }
        catch (std::exception e) {
            return "empty";
        }
    }

    const size_t lines() { return _lines.size(); };
    void operator()(std::string data) { _fileData = data; }
    void Write(std::string data) { (*this)(data); }
    void Append(std::string data) { _fileData += data; }      // write from last line
    void AppendStart(std::string data) { data += _fileData; _fileData = data; } // write from line 1
    bool Delete() { return std::remove(Directory) == 0; }
    void Apply()
    {
        std::ofstream file(Directory);
        file << _fileData;
        file.close();
    }
private:
    std::vector<std::string> _lines;
    std::string _fileData = "";
};