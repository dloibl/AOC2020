#include "../utils.cpp"
#include <vector>
#include <array>

using namespace std;

typedef array<array<array<array<bool, 20>, 20>, 20>, 20> Cube;

int countActiveNeighbors(Cube &cube, int &x, int &y, int &z, int &w)
{
    int count = 0;
    for (int i = z - 1; i <= z + 1; i++)
        for (int j = x - 1; j <= x + 1; j++)
            for (int l = y - 1; l <= y + 1; l++)
                for (int k = w - 1; k <= w + 1; k++)
                    if (!(i == z && j == x && l == y && k == w) && cube[i][k][j][l] == 1)
                        count++;
    return count;
}

int main()
{
    vector<string> input = readData("./input.txt");

    int startS = 8;
    int N = 12 + startS;
    int center = N / 2;
    int offset = startS / 2;
    Cube cube;
    Cube next;

    for (int z = 0; z < N; z++)
        for (int x = 0; x < N; x++)
            for (int y = 0; y < N; y++)
                for (int w = 0; w < N; w++)
                {
                    cube[z][x][y][w] = 0;
                    next[z][x][y][w] = 0;
                }

    int activeNeighbors = 0;
    int a = 0;
    for (auto line : input)
    {
        for (int b = 0; b < line.size(); b++)
        {
            if (line[b] == '#')
            {
                cube[center][center][b + (center - offset)][a + (center - offset)] = 1;
            }
        }
        a++;
    }

    for (int cycle = 1; cycle < 7; cycle++)
    {
        for (int z = center - cycle; z <= center + cycle; z++)
        {
            for (int w = center - cycle; w <= center + cycle; w++)
            {
                for (int y = center - offset - cycle; y <= center + offset + cycle; y++)
                {
                    for (int x = center - offset - cycle; x <= center + offset + cycle; x++)
                    {
                        activeNeighbors = countActiveNeighbors(cube, x, y, z, w);

                        if (cube[z][w][x][y])
                        {
                            if (activeNeighbors == 3 || activeNeighbors == 2)
                                next[z][w][x][y] = 1;
                            else
                            {
                                next[z][w][x][y] = 0;
                            }
                        }
                        else
                        {
                            if (activeNeighbors == 3)
                            {
                                next[z][w][x][y] = 1;
                            }
                            else
                                next[z][w][x][y] = 0;
                        }
                    }
                }
            }
        }
        cube = next;
    }

    int activeCounter = 0;
    for (int z = 0; z < N; z++)
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                for (int w = 0; w < N; w++)
                    activeCounter += cube[z][w][x][y];

    cout << "the answer to part 2 is: " << activeCounter << endl;
}
