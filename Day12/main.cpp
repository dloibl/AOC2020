#include "../utils.cpp"
#include <cmath>

using namespace std;

void move(char &direction, int &a, int &b, int &value)
{
    switch (direction)
    {
    case 'N':
        b += value;
        break;
    case 'S':
        b -= value;
        break;
    case 'E':
        a += value;
        break;
    case 'W':
        a -= value;
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
    int part1x = 0;
    int part1y = 0;
    char facing = 'E';
    int x = 0;
    int y = 0;
    int wx = 10;
    int px, py;
    int wy = 1;
    for (const auto &data : readData("./input.txt"))
    {
        char instruction = data[0];
        int value = stoi(data.substr(1, data.size()));
        if (instruction == 'F')
        {
            move(facing, part1x, part1y, value);
            //part2
            x += value * (wx);
            y += value * (wy);
        }
        else if (instruction == 'L' || instruction == 'R')
        {
            turn(instruction, facing, value);
            // part2
            if ((instruction == 'R' && value == 90) || (instruction == 'L' && value == 270))
            {
                px = (wy);
                py = -(wx);
            }
            else if ((instruction == 'L' && value == 90) || (instruction == 'R' && value == 270))
            {
                px = -(wy);
                py = (wx);
            }
            else if (value == 180)
            {
                px = -(wx);
                py = -(wy);
            }
            wx = px;
            wy = py;
        }
        else
        {
            //part1
            move(instruction, part1x, part1y, value);
            //part2
            move(instruction, wx, wy, value);
        }
    }
    cout << "the answer to part 1 is: " << (abs(part1x) + abs(part1y)) << endl;
    cout << "the answer to part 2 is: " << (abs(x) + abs(y)) << endl;
}