#include "../utils.cpp"

using namespace std;

int bisect(string input, int end)
{
    int a = 0;
    int b = end;
    int i = 0;
    while (a != b)
    {
        int next = (a + b) / 2;
        if ((input[i] == 'F') || (input[i] == 'L'))
            b = next;
        else
            a = next + 1;
        i++;
    }
    return a;
}

int main()
{
    int highestSeatId = 0;
    for (string line : readData("./input.txt"))
    {
        int seatId = 8 * bisect(line.substr(0, 7), 127) + bisect(line.substr(7), 7);
        highestSeatId = max(highestSeatId, seatId);
    }

    cout << "the answer to part 1 is: " << highestSeatId;
}