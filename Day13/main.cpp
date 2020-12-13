#include "../utils.cpp"
#include <numeric>

using namespace std;

// returns x where (a * x) % b == 1
long long mulInv(long long a, long long b)
{
    long long b0 = b, t, q;
    long long x0 = 0, x1 = 1;
    if (b == 1)
        return 1;
    while (a > 1)
    {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0)
        x1 += b0;
    return x1;
}

long long chineseRemainder(vector<int> n, vector<int> a)
{
    long long p, prod = 1, sum = 0;

    for (int i = 0; i < n.size(); i++)
        prod *= n[i];
    for (int i = 0; i < n.size(); i++)
    {
        long long p = prod / n[i];
        sum += a[i] * mulInv(p, n[i]) * p;
    }

    return sum % prod;
}

int main()
{
    vector<string> data = readData("./input.txt");
    int estimate = stoi(data[0]);
    vector<int> busLines;

    vector<int> remainders;

    int offset = 0;
    for (const auto &bus : split(data[1], ','))
    {
        if (bus[0] != 'x')
        {
            int b = stoi(bus);
            busLines.push_back(b);
            remainders.push_back(b - offset);
        }

        offset++;
    }

    int earliestBus;
    int earliestDeparture = 2 * estimate;
    for (const auto &bus : busLines)
    {
        if (estimate % bus == 0)
        {
            earliestBus = bus;
            break;
        }
        auto departure = ((estimate / bus) + 1) * bus;

        if (departure < earliestDeparture)
        {
            earliestDeparture = departure;
            earliestBus = bus;
        }
    }

    cout << "the answer to part 1 is: " << (earliestBus * (earliestDeparture - estimate)) << endl;
    cout << "the answer to part 2 is: " << chineseRemainder(busLines, remainders) << endl;
}
