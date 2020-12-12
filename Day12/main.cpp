#include "../utils.cpp"
#include <cmath>

using namespace std;

void move(char &direction, int &x, int &y, int &value)
{
    switch (direction)
    {
    case 'N':
        y += value;
        break;
    case 'S':
        y -= value;
        break;
    case 'E':
        x += value;
        break;
    case 'W':
        x -= value;
        break;
    }
}

void turn(char &direction, char &facing, int &value)
{
    int degree = facing == 'E' ? 0 : facing == 'S' ? 90 : facing == 'W' ? 180 : 270;

    if (direction == 'L')
        degree = (360 + degree - value) % 360;
    if (direction == 'R')
        degree = (degree + value) % 360;

    facing = degree == 0 ? 'E' : degree == 90 ? 'S' : degree == 180 ? 'W' : 'N';
}

int main()
{
    int x = 0;
    int y = 0;
    char facing = 'E';
    for (const auto &data : readData("./input.txt"))
    {
        char instruction = data[0];
        int value = stoi(data.substr(1, data.size()));
        if (instruction == 'F')
            move(facing, x, y, value);
        else if (instruction == 'L' || instruction == 'R')
            turn(instruction, facing, value);
        else
            move(instruction, x, y, value);
    }

    cout << "the answer to part 1 is: " << (abs(x) + abs(y)) << endl;
}