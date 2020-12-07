#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

static vector<string> readData(string filePath)
{
    vector<string> data;
    string line;
    ifstream file(filePath);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            data.push_back(line);
        }
        file.close();
    }
    return data;
}

#include <string>

static vector<string> split(const string &str, char delimeter = ' ')
{
    vector<string> words;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimeter))
        words.push_back(token);
    return words;
}

static vector<string> split(const string &str, string delimeterRegex)
{
    regex regexp(delimeterRegex);
    vector<string> out(
        sregex_token_iterator(str.begin(), str.end(), regexp, -1),
        sregex_token_iterator());
    return out;
}

const char *WHITESPACE = " \t\n\r\f\v";

// trim from end of string (right)
static std::string &rtrim(std::string &s, const char *t = WHITESPACE)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
static std::string &ltrim(std::string &s, const char *t = WHITESPACE)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
static std::string &trim(std::string &s, const char *t = WHITESPACE)
{
    return ltrim(rtrim(s, t), t);
}