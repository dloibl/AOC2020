#include <regex>
#include "../utils.cpp"

using namespace std;

const regex regexp("([0-9]+)-([0-9]+) ([a-z]): (.*)");

struct PolicyPasswordLine
{
    int min;
    int max;
    char letter;
    string password;

    PolicyPasswordLine() {}

    PolicyPasswordLine(string line)
    {
        smatch matches;
        if (regex_search(line, matches, regexp))
        {
            min = stoi(matches[1]);
            max = stoi(matches[2]);
            letter = matches[3].str()[0];
            password = matches[4].str();
        }
    }

    bool isValid()
    {
        int occurances = count(password.begin(), password.end(), letter);
        return occurances >= min && occurances <= max;
    }

    bool isValidWithNewPolicy()
    {
        char a = password[min - 1];
        char b = password[max - 1];
        return (a == letter || b == letter) && (a != b);
    }
};

int main()
{
    vector<string> input = readData("./input.txt");

    int validCounter = 0;
    int validPartTwoCounter = 0;
    for (string line : input)
    {
        PolicyPasswordLine policy = PolicyPasswordLine(line);
        if (policy.isValid())
            validCounter++;
        if (policy.isValidWithNewPolicy())
            validPartTwoCounter++;
    }

    cout << "the answer for part 1 is: " << validCounter << endl;
    cout << "the answer for part 2 is: " << validPartTwoCounter << endl;
}
