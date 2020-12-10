#include "../utils.cpp"
#include <math.h>

using namespace std;

int countInvalid(int n)
{
    if (n < 3)
    {
        return 0;
    }
    if (n == 3)
    {
        return 1;
    }

    int result = 0;
    for (int i = 1; n + 1 - i >= 3; i++)
    {
        result += i * (n + 1 - i);
    }
    return result;
}

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
    int threes = 0;
    int last = 0;
    long combinations = 1;
    int iter = 0;
    int onesInARow = 0;
    for (const auto &a : adapter)
    {
        if (a - last == 1)
        {
            ones++;
            if (iter < adapter.size() && adapter[iter + 1] - a == 1)
            {
                onesInARow++;
            }
        }
        if (a - last == 3 || iter == adapter.size() - 1)
        {
            combinations *= pow(2, onesInARow) - countInvalid(onesInARow);
            onesInARow = 0;
        }
        threes++;
        last = a;
        iter++;
    }

    cout << "the answer to part 1 is: " << (ones * threes) << endl;
    cout << "the answer to part 2 is: " << combinations << endl;
}