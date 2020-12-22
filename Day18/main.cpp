#include "../utils.cpp"
#include <vector>

using namespace std;

long long calc(vector<long long> &operand, vector<char> &op)
{
    if (op.size() == 0)
        return 1;
    if (op.size() == 1 && op[0] == '*')
        return operand[0] * operand[1];
    if (op.size() == 1 && op[0] == '+')
        return operand[0] + operand[1];

    for (int idx = 0; idx < op.size(); idx++)
    {
        if (op[idx] == '*')
        {
            if (idx == 0)
            {
                vector<long long> sub(operand.begin() + 1, operand.end());
                vector<char> subOp(op.begin() + 1, op.end());
                return operand[0] * calc(sub, subOp);
            }
            else if (idx == op.size() - 1)
            {
                vector<long long> sub(operand.begin(), operand.end() - 1);
                vector<char> subOp(op.begin(), op.end() - 1);
                return calc(sub, subOp) * operand[idx + 1];
            }
            vector<long long> sub(operand.begin(), operand.begin() + idx + 1);
            vector<char> subOp(op.begin(), op.begin() + idx);
            vector<long long> subA(operand.begin() + idx + 1, operand.end());
            vector<char> subOpA(op.begin() + idx + 1, op.end());

            return calc(sub, subOp) * calc(subA, subOpA);
        }
    }

    long long result = 0;
    for (long idx = 0; idx < operand.size(); idx++)
    {
        result += operand[idx];
    }
    return result;
}

bool islong(char a)
{
    return isdigit(a);
}

long long eval(string &expr)
{
    long long result = 0;
    vector<long long> operand;
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

    long long a = 0;
    for (auto expr : input)
    {
        a = eval(expr);
        // cout << expr << " = " << a << endl;
        result += a;
    }
    cout << "the answer to part 1 is: " << result << endl;
}
