#include "../utils.cpp"
#include <regex>
#include <map>
#include <set>

using namespace std;

struct Bag
{
    string name;
    vector<Bag> contains;

    Bag(string name)
    {
        this->name = name;
    }

    void addBag(Bag &other)
    {
        this->contains.push_back(other);
    }

    int size()
    {
        return this->contains.size();
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
        for (Bag other : bag.contains)
        {
            if (other.name == key)
            {
                result.insert(bag.name);
                searchBags(bags, result, bag.name);
            }
        }
    }
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
            string normalized = regex_replace(containsBag, regex("[0-9]"), "");
            normalized = trim(normalized);
            if (normalized != "no other")
            {
                maybeCreateBag(bags, normalized);
                bags.at(currentBag).addBag(bags.at(normalized));
            }
        }
    }

    set<string> result;

    searchBags(bags, result);

    cout << "the answer to part 1 is: " << result.size() << endl;
}