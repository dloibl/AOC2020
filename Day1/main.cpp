#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

int main()
{
    vector<string> input = readData("./input.txt");
    long result = 1;

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            int first = stoi(input[i]);
            int second = stoi(input[j]);
            if (first + second >= 2020)
            {
                if (first + second == 2020)
                {
                    cout << "the answer to part one is: " << first * second << endl;
                }
            }

            for (int k = j + 1; k < input.size(); k++)
            {
                int third = stoi(input[k]);
                if (first + second + third == 2020)
                {
                    cout << "the answer to part two is: " << first * second * third << endl;
                }
            }
        }
    }
}
