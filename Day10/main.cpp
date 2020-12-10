#include "../utils.cpp"

using namespace std;

int main()
{
    vector<string> instructions = readData("./input.txt");
    vector<int> adapter(instructions.size());
    for (int i = 0; i < instructions.size(); i++)
    {
        adapter[i] = stoi(instructions[i]);
    }
    sort(adapter.begin(), adapter.end());

    int ones = 0;
    int threes = 1;
    int last = 0;
    for (const auto &a : adapter)
    {
        cout << "a:" << a << "last:" << last << endl;
        if (a - last == 1)
        {
            ones++;
        }
        if (a - last == 3)
        {
            threes++;
        }
        last = a;
    }

    cout << "the answer to part 1 is: " << (ones * threes) << endl;
}
