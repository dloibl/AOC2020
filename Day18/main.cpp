#include "../utils.cpp"
#include <vector>

using namespace std;

long calc(vector<long> &operand, vector<char> &op)
{
    long result = operand[0];
    for (long idx = 0; idx < op.size(); idx++)
    {
        if (op[idx] == '+')
            result += operand[idx + 1];
        else
            result *= operand[idx + 1];
    }
    return result;
}

bool islong(char a)
{
    return isdigit(a);
}

long eval(string &expr)
{
    long result = 0;
    vector<long> operand;
    vector<char> op;
    char a;
    string sub;
    long openBracketIdx = 0;
    long bracketCount = 0;
    for (long i = 0; i < expr.size(); i++)
    {
        a = expr[i];
        if (islong(a))
        {
            if (bracketCount)
            {
                continue;
            }
            operand.push_back(stoi(string(1, a)));
        }
        if (a == ' ')
        {
            continue;
        }
        if (a == '+' || a == '*')
        {
            if (bracketCount)
            {
                continue;
            }
            op.push_back(a);
        }
        if (a == '(')
        {
            bracketCount++;
            if (bracketCount == 1)
            {
                openBracketIdx = i;
            }
        }
        if (a == ')')
        {
            bracketCount--;
            if (bracketCount == 0)
            {
                sub = expr.substr(openBracketIdx + 1, i - openBracketIdx - 1);
                operand.push_back(eval(sub));
            }
        }
    }
    if (bracketCount)
    {
        cout << "oops" << bracketCount;
    }
    return calc(operand, op);
}

int main()
{
    vector<string> input = readData("./input.txt");
    long long result = 0;
    for (auto expr : input)
    {
        result += eval(expr);
    }
    cout << "the answer to part 1 is: " << result << endl;
}
