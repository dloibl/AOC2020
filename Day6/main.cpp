#include "../utils.cpp"
#include <set>
#include <map>

using namespace std;

int main()
{
    int numberAnyoneAnsweredYes = 0;
    int numberEveryoneAnsweredYes = 0;
    map<char, int> answers;
    int numberPersonsInGroup = 0;
    for (string line : readData("./input.txt"))
    {
        if (line.length() == 0)
        {
            numberAnyoneAnsweredYes += answers.size();

            for (map<char, int>::iterator i = answers.begin(); i != answers.end(); i++)
            {
                if (i->second == numberPersonsInGroup)
                    numberEveryoneAnsweredYes++;
            }

            answers.clear();
            numberPersonsInGroup = 0;
        }
        else
        {
            for (char answer : line)
            {
                map<char, int>::iterator it = answers.find(answer);
                if (it == answers.end())
                    answers.insert(pair<char, int>(answer, 1));
                it->second++;
            }
            numberPersonsInGroup++;
        }
    }

    cout << "the answer to part 1 is: " << numberAnyoneAnsweredYes << endl;
    cout << "the answer to part 2 is: " << numberEveryoneAnsweredYes << endl;
}