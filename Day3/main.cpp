#include <regex>
#include "../utils.cpp"

using namespace std;

int main()
{
    vector<string> input = readData("./input.txt");

    int treeCounter = 0;
    for (int i = 0; i < input.size() - 1; i++)
    {
        string line = input[i + 1];
        if (line[((i + 1) * 3) % line.size()] == '#')
            treeCounter++;
    }

    cout << "the answer to part1 is:" << treeCounter << endl;
}
