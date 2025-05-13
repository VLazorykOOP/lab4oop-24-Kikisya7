#include <iostream>
#include <string>
#include <map>

using namespace std;
int CodeError = 0;
class CountryCapital
{
private:
    map<string, string> data;
public:
    void add(const string& country, const string& capital)
    {
        data[country] = capital;
    }
    string operator[](const string& country) const
    {
        auto it = data.find(country);
        if (it != data.end())
        {
            CodeError = 0;
            return it->second;
        } else
        {
            CodeError = 1;
            return "";
        }
    }
    string operator()(const string& country) const
    {
        return (*this)[country];
    }
    friend ostream& operator<<(ostream& out, const CountryCapital& d)
    {
        for (const auto& pair : d.data) {
            out << pair.first << " -> " << pair.second << endl;
        }
        return out;
    }
    friend istream& operator>>(istream& in, CountryCapital& d)
    {
        string country, capital;
        cout << "Input country: ";
        in >> country;
        cout << "Input capital: ";
        in >> capital;
        d.add(country, capital);
        return in;
    }
};
CountryCapital createSampleSet()
{
    CountryCapital d;
    d.add("Ukraine", "Kyiv");
    d.add("USA", "Washington");
    d.add("Great Britain", "London");
    d.add("Japan", "Tokyo");
    d.add("France", "Paris");
    return d;
}
int main()
{
    CountryCapital dict = createSampleSet();
    cout << "Countries list:\n" << dict;
    while (true)
    {
        string query;
        cout << "\nInput country (or 'exit'): ";
        cin >> query;
        if (query == "exit") break;
        string capital = dict[query];
        if (CodeError == 0)
            cout << "Capital: " << capital << endl;
        else
            cout << "Country not found!" << endl;
        cout << "\nAdd country? (yes/no): ";
        string answer;
        cin >> answer;
        if (answer == "yes" || answer == "Yes")
        {
            cin >> dict;
            cout << "\nCountries list:\n" << dict;
        }
    }
    return 0;
}
