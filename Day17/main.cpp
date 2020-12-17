#include "../utils.cpp"
#include <vector>
#include <array>

using namespace std;

typedef array<array<array<bool, 20>, 20>, 20> Cube;

int countActiveNeighbors(Cube &cube, int &x, int &y, int &z)
{
    int count = 0;
    for (int i = z - 1; i <= z + 1; i++)
        for (int j = x - 1; j <= x + 1; j++)
            for (int l = y - 1; l <= y + 1; l++)
                if (!(i == z && j == x && l == y) && cube[i][j][l] == 1)
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
    {
        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y < N; y++)
            {
                cube[z][x][y] = 0;
                next[z][x][y] = 0;
            }
        }
    }

    int activeNeighbors = 0;
    int a = 0;
    for (auto line : input)
    {
        cout << line << endl;
        for (int b = 0; b < line.size(); b++)
        {
            if (line[b] == '#')
            {
                cube[center][b + (center - offset)][a + (center - offset)] = 1;
            }
        }
        a++;
    }

    for (int cycle = 1; cycle < 7; cycle++)
    {
        //cout << "cycle=" << cycle << endl<< endl;
        for (int z = center - cycle; z <= center + cycle; z++)
        {
            //cout << "z=" << z << endl;
            for (int y = center - offset - cycle; y <= center + offset + cycle; y++)
            {
                for (int x = center - offset - cycle; x <= center + offset + cycle; x++)
                {
                    cout << (cube[z][x][y] ? '#' : '.');

                    activeNeighbors = countActiveNeighbors(cube, x, y, z);
                    //cout << "z,x,y" << z << "," << x << "," << y << " #=" << cube[z][x][y] << "  n:" << activeNeighbors << endl;

                    if (cube[z][x][y])
                    {
                        if (activeNeighbors == 3 || activeNeighbors == 2)
                            next[z][x][y] = 1;
                        else
                        {
                            next[z][x][y] = 0;
                        }
                    }
                    else
                    {
                        if (activeNeighbors == 3)
                        {
                            next[z][x][y] = 1;
                        }
                        else
                            next[z][x][y] = 0;
                    }
                }
                cout << endl;
            }
        }
        cube = next;
    }

    int activeCounter = 0;
    for (int z = 0; z < N; z++)
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                activeCounter += cube[z][x][y];

    cout << "the answer to part 1 is: " << activeCounter << endl;
}
