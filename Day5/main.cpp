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
    int seats[127][7];

    for (string line : readData("./input.txt"))
    {
        int rowId = bisect(line.substr(0, 7), 127);
        int colId = bisect(line.substr(7), 7);
        seats[rowId][colId] = 1;
        int seatId = 8 * rowId + colId;
        highestSeatId = max(highestSeatId, seatId);
    }

    int mySeatId;
    for (int i = 1; i < 119; i++)
        for (int j = 0; j < 7; j++)
            if (seats[i][j] != 1)
                mySeatId = 8 * i + j;

    cout << "the answer to part 1 is: " << highestSeatId << endl;
    cout << "the answer to part 2 is: " << mySeatId << endl;
}