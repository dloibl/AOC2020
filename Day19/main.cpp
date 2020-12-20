#include "../utils.cpp"
#include <map>
#include <regex>

using namespace std;

const regex unresolved(".*([0-9]+).*");
smatch base_match;
void parse(string &line, map<string, string> &rules)
{
    if (line.size() == 0)
        return;

    vector<string> part = split(line, ':');
    rules[part[0]] = trim(part[1]);
}

void resolveRule(string key, map<string, string> &rules)
{
    string rule = rules[key];

    for (auto pair : rules)
    {
        if (pair.first != key)
        {
            rules[key] = regex_replace(rules[key], regex(pair.first), "(" + pair.second + ")");
        }
    }
}

void resolve(map<string, string> &rules)
{
    for (auto rule : rules)
    {
        resolveRule(rule.first, rules);
        if ()
    }
}

int main()
{
    vector<string> input = readData("./input.txt");
    map<string, string> rules;

    for (string line : input)
    {
        if (line.size() == 0 || line == "END")
        {
            break;
        }
        else
        {
            parse(line, rules);
        }
    }

    for (int i = 0; i < 2; i++)
        resolve(rules);

    cout << rules["0"];
    return 0;
}
