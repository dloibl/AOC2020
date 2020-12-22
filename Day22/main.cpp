#include "../utils.cpp"
#include <deque>

using namespace std;

struct Player
{
    string id;
    deque<int> cards;

    void addCard(int value)
    {
        cards.push_back(value);
    }

    int drawTopCard()
    {
        auto card = cards.front();
        cards.pop_front();
        return card;
    }

    void win(int &a, int &b)
    {
        cards.push_back(a);
        cards.push_back(b);
    }

    bool empty()
    {
        return cards.size() == 0;
    }

    void print()
    {
        cout << id << ":";
        for (auto i : cards)
        {
            cout << i << ",";
        }
        cout << endl;
    }

    int getScore()
    {
        int result = 0;
        int n = cards.size();
        for (auto i : cards)
        {
            result += i * (n--);
        }
        return result;
    }
};

int play(Player a, Player b)
{
    while (!(a.empty() || b.empty()))
    {
        auto cardA = a.drawTopCard();
        auto cardB = b.drawTopCard();
        if (cardA > cardB)
            a.win(cardA, cardB);
        else
            b.win(cardB, cardA);
    }

    return a.empty() ? b.getScore() : a.getScore();
}

int main()
{
    vector<string> input = readData("./input.txt");
    Player players[2];
    int p = 0;
    for (auto line : input)
    {
        if (line[0] == 'P')
            players[p].id = line;
        else if (line.size() == 0)
            p++;
        else
            players[p].addCard(stoi(line));
    }

    cout << "then answer to part 1 is:" << play(players[0], players[1]);

    return 0;
}
