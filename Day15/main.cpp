#include "../utils.cpp"
#include <set>
using namespace std;

int main()
{
    vector<string> startingNumbers = split(readData("./input.txt")[0], ',');
    int turn = 1;
    vector<int> spoken;
    for (auto start : startingNumbers)
    {
        spoken.push_back(stoi(start));
        turn++;
    }

    int nextWord;
    while (turn < 2021)
    {
        auto last = spoken.back();
        auto it = find(spoken.rbegin() + 1, spoken.rend(), last);
        nextWord = it == spoken.rend() ? 0 : (turn - 1) - distance(it, spoken.rend());
        spoken.push_back(nextWord);
        turn++;
    }

    cout << "the answer to part 1 is: " << nextWord << endl;
}
