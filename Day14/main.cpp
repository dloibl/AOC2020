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

void applyAsMemoryAddressDecoder(unsigned long &value, bitset<36> &address, string &mask, map<unsigned long, unsigned long> &memory, vector<unsigned long> &additions)
{
    bitset<36> temp;
    int k = 0;
    for (int i = 0; i < 36; i++)
    {
        if (mask[i] == '1')
            address.set(35 - i, 1);
        if (mask[i] == 'X')
        {
            address.set(35 - i, 0);

            auto add = temp.set(35 - i, 1).to_ulong();
            for (auto v : additions)
            {
                if (v != 0)
                    additions.push_back(v + add);
            }
            additions.push_back(add);
            temp.set(35 - i, 0);
        }
    }

    auto base = address.to_ulong();
    memory[base] = value;
    for (auto p : additions)
    {
        memory[p + base] = value;
    }
}

int main()
{
    vector<string> data = readData("./input.txt");

    string mask;
    bitset<36> address;
    unsigned long value;
    map<unsigned long, unsigned long> memory;
    vector<unsigned long> additions;
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
                // part1:
                // auto value = bitset<36>(stoi(m[2]));
                // applyMask(value, mask);
                // int address = stoi(m[1]);

                address = bitset<36>(stoul(m[1]));
                value = stoul(m[2]);
                applyAsMemoryAddressDecoder(value, address, mask, memory, additions);
                additions.clear();
                // memory[address] = value.to_ulong();
            }
        }
    }

    unsigned long long result = 0;
    for (pair<unsigned long, unsigned long> val : memory)
        if (val.second != 0)
            result += val.second;

    cout << "the answer to part 2 is: " << result << endl;
}
