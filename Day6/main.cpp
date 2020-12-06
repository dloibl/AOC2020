#include "../utils.cpp"
#include <set>

using namespace std;

int main()
{
    int yesAnswers = 0;
    set<char> answersInGroup;
    for (string line : readData("./input.txt"))
    {
        if (line.length() == 0)
        {
            yesAnswers += answersInGroup.size();
            answersInGroup.clear();
        }
        else
        {
            for (char answer : line)
                answersInGroup.insert(answer);
        }
    }

    cout << "the answer to part 1 is: " << yesAnswers << endl;
}