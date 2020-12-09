#include "../utils.cpp"
#include <set>

using namespace std;

int main()
{
    vector<string> instructions = readData("./input.txt");
    vector<long long> numbers(instructions.size());
    for (int i = 0; i < instructions.size(); i++)
    {
        numbers[i] = stoull(instructions[i]);
    }

    unsigned long long current;
    int n = 25;
    bool valid = false;
    while (n < instructions.size())
    {
        current = numbers[n];
        for (int a = n - 25; a < n; a++)
        {
            if (numbers[a] >= current)
                continue;

            for (int b = a + 1; b < n; b++)
            {
                if (numbers[b] >= current || numbers[a] == numbers[b])
                    continue;
                if (numbers[a] + numbers[b] == current)
                {
                    valid = true;
                    break;
                }
            }
            if (valid)
                break;
        }

        n++;
        if (valid)
            valid = false;
        else
            break;
    }

    cout << "the answer to part 1 is: " << current << endl;

    unsigned long long remaining = current;
    int start = n - 1;
    int k = start;
    while ((remaining != 0) || (start == 0))
    {
        if (numbers[k] >= current || numbers[k] > remaining)
        {
            remaining = current;
            start--;
            k = start;
        }
        else
        {
            remaining -= numbers[k];
        }
        k--;
    }

    unsigned long long min = numbers[start];
    unsigned long long max = 0;
    for (int i = k + 1; i < start; i++)
    {
        min = min < numbers[i] ? min : numbers[i];
        max = max > numbers[i] ? max : numbers[i];
    }

    cout << "the answer to part 2 is: " << (min + max) << endl;
}
