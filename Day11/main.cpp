#include "../utils.cpp"

using namespace std;

class SeatMap
{
public:
    vector<string> data;
    vector<string> next;
    int occupiedSeats, cols, rows;
    string strategy;

    SeatMap(vector<string> &data, string strategy)
    {
        this->data = data;
        this->rows = data.size();
        this->cols = data[0].size();
        vector<string> cop(data);
        this->next = cop;
        this->occupiedSeats = 0;
        this->strategy = strategy;
    }

    void run()
    {
        int round = 0;
        int lastOccupiedSeats = -1;
        while (lastOccupiedSeats != occupiedSeats)
        {
            lastOccupiedSeats = occupiedSeats;
            move();
            // print();
            round++;
        }
    }

    void move()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (isFloor(i, j))
                {
                    continue;
                }
                if (isEmpty(i, j) && getCountingOccupiedNeighbors(i, j) == 0)
                {
                    next[i][j] = '#';
                    occupiedSeats++;
                }
                else if (isOccupied(i, j) && getCountingOccupiedNeighbors(i, j) >= getOccupiedKeyNumber())
                {
                    next[i][j] = 'L';
                    occupiedSeats--;
                }
            }
        }
        data = next;
    }

    int getOccupiedKeyNumber()
    {
        return strategy == "visible" ? 5 : 4;
    }

    int getCountingOccupiedNeighbors(int &i, int &j)
    {
        return strategy == "visible" ? getNumbersOccupiedSeatsInSight(i, j) : getNumberOccupiedNeighbors(i, j);
    }

    int getNumberOccupiedNeighbors(int i, int j)
    {
        int occ = 0;
        for (int a = i - 1; a <= i + 1; a++)
            for (int b = j - 1; b <= j + 1; b++)
            {
                if (a == i && b == j)
                    continue;
                if (a >= 0 && b >= 0 && a < rows && b < cols && isOccupied(a, b))
                    occ++;
            }

        return occ;
    }

    int getNumbersOccupiedSeatsInSight(int i, int j)
    {
        if (occupiedSeats == 0)
        {
            return 0;
        }

        int occ = 0;

        int down, right;

        // up
        down = i - 1;
        right = j;
        while (down >= 0)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            down--;
        }

        // up right
        down = i - 1;
        right = j + 1;
        while (down >= 0 && right < cols)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            down--;
            right++;
        }

        // right
        down = i;
        right = j + 1;
        while (right < cols)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            right++;
        }

        // right down
        down = i + 1;
        right = j + 1;
        while (right < cols && down < rows)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            right++;
            down++;
        }

        // down
        down = i + 1;
        right = j;
        while (down < rows)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            down++;
        }

        // down left
        down = i + 1;
        right = j - 1;
        while (right >= 0 && down < rows)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            down++;
            right--;
        }

        // left
        down = i;
        right = j - 1;
        while (right >= 0)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            right--;
        }

        // left up
        down = i - 1;
        right = j - 1;
        while (right >= 0 && down >= 0)
        {
            if (isEmpty(down, right))
                break;
            if (isOccupied(down, right))
            {
                occ++;
                if (occ >= occupiedSeats)
                    return occ;
                break;
            }
            right--;
            down--;
        }

        return occ;
    }

    bool isFloor(int i, int j)
    {
        return data[i][j] == '.';
    }

    bool isOccupied(int i, int j)
    {
        return data[i][j] == '#';
    }

    bool isEmpty(int i, int j)
    {
        return data[i][j] == 'L';
    }

    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            cout << data[i] << endl;
        }
    }
};

int main()
{
    vector<string> data = readData("./input.txt");
    SeatMap map1 = SeatMap(data, "neighbor");
    map1.run();
    cout << "the answer to part 1 is: " << map1.occupiedSeats << endl;

    data = readData("./input.txt");
    SeatMap map2 = SeatMap(data, "visible");
    map2.run();
    cout << "the answer to part 2 is: " << map2.occupiedSeats << endl;
}