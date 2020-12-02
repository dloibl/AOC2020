#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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