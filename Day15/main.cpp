#include "../utils.cpp"
#include <map>

using namespace std;

int main()
{
    vector<string> startingNumbers = split(readData("./input.txt")[0], ',');
    map<int, pair<int, int>> spoken;
    int part1Word;
    int turn = 1;
    int nextWord;
    int lastWord;
    for (auto start : startingNumbers)
    {
        auto w = stoi(start);
        spoken[w] = pair(turn, 0);
        cout << "t:" << turn << " = " << w << endl;
        lastWord = w;
        turn++;
    }

    pair<int, int> last;
    pair<int, int> next;

    while (turn < 30000001)
    {
        if (turn == 2021)
        {
            part1Word = lastWord;
        }

        last = spoken[lastWord];
        nextWord = !last.second ? 0 : last.second - last.first;
        next = spoken[nextWord];
        if (!next.first)
        {
            spoken[nextWord] = pair(turn, 0);
        }
        else
        {
            if (next.second)
                spoken[nextWord].first = next.second;
            spoken[nextWord].second = turn;
        }

        lastWord = nextWord;
        turn++;
    }

    cout << "the answer to part 1 is: " << part1Word << endl;
    cout << "the answer to part 2 is: " << nextWord << endl;
}
