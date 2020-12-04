#include "../utils.cpp"
#include <regex>
#include <map>

using namespace std;

const string BIRTH_DATE = "byr";
const string ISSUE_DATE = "iyr";
const string EXPIRATION_DATE = "eyr";
const string HEIGHT = "hgt";
const string HAIR_COLOR = "hcl";
const string EYE_COLOR = "ecl";
const string PASSPORT_ID = "pid";
const string COUNTRY_ID = "cid";

const regex isColor("#[0-9a-f]{6}");
const regex isPassportId("[0-9]{9}");

bool isValidPassportId(string passportId)
{
    return regex_match(passportId, isPassportId);
}

bool isValidEyeColor(string color)
{
    if (color == "amb")
        return true;
    if (color == "blu")
        return true;
    if (color == "brn")
        return true;
    if (color == "gry")
        return true;
    if (color == "grn")
        return true;
    if (color == "hzl")
        return true;
    if (color == "oth")
        return true;
    return false;
}

bool isValidHairColor(string color)
{
    return regex_match(color, isColor);
}

bool isValidHeight(string height)
{
    string unit = height.substr(height.length() - 2, 2);
    int value = stoi(height.substr(0, height.length() - 2));
    return unit == "cm" ? value >= 150 && value <= 193 : unit == "in" ? value >= 59 && value <= 76 : false;
}

bool isDateBetween(string dateStr, int start, int end)
{
    int date = stoi(dateStr);
    return date >= start && date <= end;
}

bool isDataValid(map<string, string> &data)
{
    if (data.size() < 7)
        return false;

    try
    {
        return isDateBetween(data.at(BIRTH_DATE), 1920, 2020)         //
               && isDateBetween(data.at(ISSUE_DATE), 2010, 2020)      //
               && isDateBetween(data.at(EXPIRATION_DATE), 2020, 2030) //
               && isValidHeight(data.at(HEIGHT))                      //
               && isValidHairColor(data.at(HAIR_COLOR))               //
               && isValidEyeColor(data.at(EYE_COLOR))                 //
               && isValidPassportId(data.at(PASSPORT_ID));            //
    }
    catch (...)
    {
        return false;
    }
}

int main()
{
    vector<string> input = readData("./input.txt");

    int numberValid = 0;
    int numberDataValid = 0;
    map<string, string> tokens;
    string passport;
    for (string line : input)
    {
        if (line.length() == 0)
        {
            if (tokens.size() == 7)
                numberValid++;
            if (isDataValid(tokens))
                numberDataValid++;

            tokens.clear();
        }
        else
        {
            vector<string> keyValues = split(line, ' ');
            for (string entry : keyValues)
            {
                vector<string> keyValue = split(entry, ':');
                if (keyValue[0] != COUNTRY_ID)
                    tokens.insert(pair<string, string>(keyValue[0], keyValue[1]));
            }
        }
    }

    cout << "the answer to part1 is: " << numberValid << endl;
    cout << "the answer to part2 is: " << numberDataValid << endl;
}
