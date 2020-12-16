#include "../utils.cpp"
#include <regex>
#include <vector>
using namespace std;

const regex rule("(.*): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");

struct Rule
{
    string id;
    pair<int, int> a;
    pair<int, int> b;
    vector<int> column;

    Rule(string id, int m1, int m2, int m3, int m4)
    {
        this->id = id;
        this->a = pair(m1, m2);
        this->b = pair(m3, m4);
    }

    bool isValid(int n)
    {
        return (a.first <= n && n <= a.second) || (b.first <= n && n <= b.second);
    }

    void mightBeColumn(int n)
    {
        column.push_back(n);
    }

    bool unique()
    {
        return column.size() == 1;
    }

    int getCol()
    {
        return column[0];
    }

    void cannotBe(int col)
    {
        column.erase(remove(column.begin(), column.end(), col), column.end());
    }
};

int main()
{
    vector<string> ticket = readData("./input.txt");
    vector<Rule> ranges;
    int l = 0;
    string line = ticket[l++];
    while (line.size() != 0)
    {
        smatch m;
        if (regex_match(line, m, rule))
        {
            ranges.push_back(Rule(m[1], stoi(m[2]), stoi(m[3]), stoi(m[4]), stoi(m[5])));
        }
        line = ticket[l++];
    }
    l++;
    string myTicket = ticket[l];
    l += 3;

    int invalidCount = 0;
    int valid = false;
    int ticketValid = true;
    vector<string> validTickets;
    while (l < ticket.size())
    {
        line = ticket[l++];

        ticketValid = true;
        for (auto value : split(line, ','))
        {
            valid = false;
            auto v = stoi(value);
            for (auto r : ranges)
            {
                if (r.isValid(v))
                {
                    valid = true;
                    break;
                }
            }
            if (!valid)
            {
                invalidCount += v;
                ticketValid = false;
            }
        }
        if (ticketValid)
            validTickets.push_back(line);
    }

    validTickets.push_back(myTicket);
    bool allValid = true;
    for (auto &r : ranges)
    {
        for (int i = 0; i < ranges.size(); i++)
        {
            allValid = true;
            for (auto pTicket : validTickets)
            {

                if (!r.isValid(stoi(split(pTicket, ',')[i])))
                {
                    allValid = false;
                    break;
                }
            }
            if (allValid)
            {
                r.mightBeColumn(i);
            }
        }
    }

    sort(ranges.begin(), ranges.end(), [](const Rule &lhs, const Rule &rhs) {
        return lhs.column.size() < rhs.column.size();
    });

    long resultPart2 = 1;
    for (auto &rl : ranges)
    {
        if (rl.unique())
            for (auto &other : ranges)
                if (rl.id != other.id)
                    other.cannotBe(rl.getCol());

        cout << rl.id << "=" << rl.getCol() << endl;
        if (rl.id.substr(0, 9) == "departure")
            resultPart2 *= stol(split(myTicket, ',')[rl.getCol()]);
    }

    cout << "the answer to part 1 is: " << invalidCount << endl;
    cout << "the answer to part 2 is: " << resultPart2 << endl;
}
