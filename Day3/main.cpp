#include <regex>
#include "../utils.cpp"

using namespace std;

int countTrees(vector<string> &input, int stepRight, int stepDown)
{
    int treeCounter = 0;
    int moveRight = 0;
    for (int i = stepDown; i < input.size(); i += stepDown)
    {
        string line = input[i];
        moveRight += stepRight;
        if (line[moveRight % line.size()] == '#')
            treeCounter++;
    }
    return treeCounter;
}

int main()
{
    vector<string> input = readData("./input.txt");

    int right1down1 = countTrees(input, 1, 1);
    int right3down1 = countTrees(input, 3, 1);
    int right5down1 = countTrees(input, 5, 1);
    int right7down1 = countTrees(input, 7, 1);
    int right1down2 = countTrees(input, 1, 2);

    long resultPart2 = (long)right1down1 * (long)right3down1 * (long)right5down1 * (long)right7down1 * (long)right1down2;
    cout << "the answer to part1 is: " << right1down2 << endl;
    cout << "the answer to part2 is: " << resultPart2 << endl;
}
