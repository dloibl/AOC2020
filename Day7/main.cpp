#include "../utils.cpp"
#include <regex>
#include <map>
#include <set>

using namespace std;

const regex aNumber("([0-9]+)");

struct Bag
{
    string name;
    map<string, int> contains;

    Bag(string name)
    {
        this->name = name;
    }

    void addBag(string &other, int count)
    {
        this->contains.insert(pair<string, int>(other, count));
    }
};

void maybeCreateBag(map<string, Bag> &bags, string &key)
{
    map<string, Bag>::iterator it = bags.find(key);
    if (it == bags.end())
    {
        Bag bag = Bag(key);
        bags.insert(pair<string, Bag>(key, bag));
    }
}

void searchBags(map<string, Bag> &bags, set<string> &result, string key = "shiny gold")
{
    for (map<string, Bag>::iterator i = bags.begin(); i != bags.end(); i++)
    {
        Bag bag = i->second;
        map<string, int>::iterator iter = bag.contains.find(key);
        if (iter != bag.contains.end())
        {
            result.insert(bag.name);
            searchBags(bags, result, bag.name);
        }
    }
}

int countBags(map<string, Bag> &bags, string key = "shiny gold")
{
    Bag bag = bags.at(key);

    if (bag.contains.size() == 0)
    {
        return 1;
    }

    int nested = 0;
    for (map<string, int>::iterator i = bag.contains.begin(); i != bag.contains.end(); i++)
    {
        int mult = i->second;
        string next = i->first;
        nested += mult * countBags(bags, next);
    }
    return nested + 1;
}

int main()
{
    map<string, Bag> bags;
    for (string line : readData("./input.txt"))
    {
        string trimmed = regex_replace(line, regex("bag(s)?|\\."), "");
        vector<string> parts = split(trimmed, "contain");
        string currentBag = trim(parts[0]);

        string contains = parts[1];

        maybeCreateBag(bags, currentBag);

        for (string containsBag : split(contains, ','))
        {
            smatch matches;
            int count;
            if (regex_search(containsBag, matches, aNumber))
            {
                count = stoi(matches[1]);
            }

            string normalized = regex_replace(containsBag, aNumber, "");
            normalized = trim(normalized);
            if (normalized != "no other")
            {
                maybeCreateBag(bags, normalized);
                bags.at(currentBag).addBag(normalized, count);
            }
        }
    }

    set<string> resultPart1;
    searchBags(bags, resultPart1);

    // part 2:
    int resultPart2 = countBags(bags) - 1;

    cout << "the answer to part 1 is: " << resultPart1.size() << endl;
    cout << "the answer to part 2 is: " << resultPart2 << endl;
}