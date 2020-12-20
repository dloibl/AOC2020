#include "../utils.cpp"
#include <vector>
#include <regex>

using namespace std;

struct Tile
{
    string id;

    string edge[4];

    int matchCount = 0;

    Tile() {}

    Tile(string id) : id(id)
    {
    }

    void setEdge(int n, string &line)
    {
        edge[n] = line;
    }

    bool match(Tile other)
    {
        for (string a : edge)
        {
            cout << "a=" << a << endl;
            for (string b : other.edge)
            {
                if (a == b)
                    return true;
                reverse(b.begin(), b.end());
                if (a == b)
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    vector<string> input = readData("./input.txt");
    int N = 10;
    vector<Tile> tiles;

    Tile current;
    int n = 0;
    string left = "";
    string right = "";
    for (auto line : input)
    {
        if (line[0] == 'T')
        {
            current = Tile(line.substr(5, 4));

            left = "";
            right = "";
            n = 0;
        }
        else if (line.size() == 0)
            tiles.push_back(current);
        else
        {
            left += line[0];
            right += line[9];
            if (n == 0)
                current.setEdge(0, line);
            if (n == 9)
            {
                current.setEdge(1, line);
                current.setEdge(2, left);
                current.setEdge(3, right);
            }
            n++;
        }
    }

    for (int i = 0; i < tiles.size(); i++)
        for (int j = i + 1; j < tiles.size(); j++)
        {
            if (tiles[i].match(tiles[j]))
            {
                tiles[i].matchCount++;
                tiles[j].matchCount++;
            }
        }

    long long result = 1;
    for (auto t : tiles)
    {
        if (t.matchCount == 2)
        {
            result *= stoi(t.id);
        }
    }

    cout << "the answer to part 1 is:" << result << endl;
    return 0;
}
