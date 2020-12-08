#include "../utils.cpp"
#include <set>

using namespace std;

int run(vector<string> &ops, vector<int> &args, set<int> &visited, int &size, int &cursor)
{
    int accumulator = 0;
    int arg;
    string op;
    while (visited.find(cursor) == visited.end())
    {
        visited.insert(cursor);
        op = ops[cursor];
        arg = args[cursor];
        if (op == "nop")
        {
            cursor++;
        }
        else if (op == "jmp")
        {
            cursor += arg;
        }
        else if (op == "acc")
        {
            accumulator += arg;
            cursor++;
        }
        if (cursor == size - 1)
        {
            return accumulator;
        }
    }
    return accumulator;
}

int main()
{
    int accumulator = 0;
    vector<string> instructions = readData("./input.txt");
    set<int> visited;
    string oldOp;
    vector<string> ops;
    vector<int> args;
    int size = instructions.size();
    int cursor = 0;
    for (string line : instructions)
    {
        vector<string> parts = split(line, ' ');
        string op = parts[0];
        ops.push_back(op);
        args.push_back(stoi(parts[1]));
    }

    int answerToQuestion1 = run(ops, args, visited, size, cursor);

    for (int round = 0; round < size - 1; round++)
    {
        if (ops[round] == "acc")
            continue;

        oldOp = ops[round];
        ops[round] = oldOp == "nop" ? "jmp" : "nop";
        visited.clear();
        cursor = 0;
        accumulator = run(ops, args, visited, size, cursor);
        ops[round] = oldOp;

        if (cursor == size - 1)
            break;
    }

    cout << "the answer to part 1 is: " << answerToQuestion1 << endl;
    cout << "the answer to part 2 is: " << accumulator << endl;
}