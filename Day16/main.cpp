#include "../utils.cpp"
#include <regex>
#include <vector>
using namespace std;

const regex rule(".*: ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");

int main()
{
    vector<string> ticket = readData("./input.txt");
    vector<pair<int, int>> ranges;
    int l = 0;
    string line = ticket[l++];
    while (line.size() != 0)
    {
        smatch m;
        if (regex_match(line, m, rule))
        {
            ranges.push_back(pair(stoi(m[1]), stoi(m[2])));
            ranges.push_back(pair(stoi(m[3]), stoi(m[4])));
        }
        line = ticket[l++];
    }

    while (line != "nearby tickets:")
    {
        line = ticket[l++];
    }

    int invalidCount = 0;
    int valid = false;
    while (l < ticket.size())
    {
        line = ticket[l++];

        for (auto value : split(line, ','))
        {
            valid = false;
            auto v = stoi(value);
            for (auto r : ranges)
            {
                if (r.first <= v && v <= r.second)
                {
                    valid = true;
                    break;
                }
            }
            if (!valid)
                invalidCount += v;
        }
    }

    cout << "the answer to part 1 is: " << invalidCount << endl;
}
