#include "../utils.cpp"
#include <bitset>
#include <map>

using namespace std;

const regex regexp("mem\\[([0-9]+)\\] = ([0-9]+)");

void applyMask(bitset<36> &value, string &mask)
{
    for (int i = 0; i < 36; i++)
    {
        if (mask[i] == '1')
            value.set(35 - i, 1);
        if (mask[i] == '0')
            value.set(35 - i, 0);
    }
}

int main()
{
    vector<string> data = readData("./input.txt");

    string mask;
    map<int, long> memory;
    for (string line : data)
    {
        if (line.substr(0, 4) == "mask")
        {
            mask = line.substr(7, line.size());
        }
        else
        {
            smatch m;
            if (regex_match(line, m, regexp))
            {
                auto value = bitset<36>(stoi(m[2]));
                applyMask(value, mask);
                int address = stoi(m[1]);
                memory[address] = value.to_ulong();
            }
        }
    }

    long result = 0;
    for (pair<int, long> val : memory)
        if (val.second != 0)
            result += val.second;

    cout << "the answer to part 1 is: " << result << endl;
}
