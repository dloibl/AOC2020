#include "../utils.cpp"
#include <set>

using namespace std;

int main()
{
    vector<string> input = readData("./input.txt");

    int numberValid = 0;
    set<string> tokens;
    for (string line : input)
    {
        if (line.length() == 0)
        {
            if (tokens.size() == 7)
                numberValid++;

            tokens.clear();
        }
        else
        {
            vector<string> keyValues = split(line, ' ');
            for (string entry : keyValues)
            {
                string key = split(entry, ':')[0];
                if (key != "cid")
                    tokens.insert(key);
            }
        }
    }

    cout << "the answer to part1 is: " << numberValid << endl;
}
