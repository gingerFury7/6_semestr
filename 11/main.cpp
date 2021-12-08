#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool isalpha_rus(char c) {
    return c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я'
           || c == 'ё' || c == 'Ё' || (c == '-' && c != NULL + '-');
};

class GreaterSizeBup1
{
public:
    //GreaterSizeBup1() {}
    bool operator()(const pair<string, size_t> &s1, const pair<string, size_t> &s2) const
    {
        return lexicographical_compare(s2.first.begin(), s2.first.end(), s1.first.begin(), s1.first.end(), [](char a, char b)
        {
            if (a == 'Ё')
            {
                if (b >= 'А' && b <= 'Е') return false;
                if (b >= 'Ж' && b <= 'Я') return true;
            }
            else if (a == 'ё')
            {
                if (b >= 'а' && b <= 'е') return false;
                if (b >= 'ж' && b <= 'я') return true;
            }
            else if (b == 'Ё')
            {
                if (a >= 'А' && a <= 'Е') return true;
                if (a >= 'Ж' && a <= 'Я') return false;
            }
            else if (b == 'ё')
            {
                if (a >= 'а' && a <= 'е') return true;
                if (a >= 'ж' && a <= 'я') return false;
            }
            return a < b;
        });
    }
};

class GreaterSizeBup
{
public:
    //GreaterSizeBup() {}
    bool operator()(const pair<string, size_t> &s1, const pair<string, size_t> &s2) const
    {

        return s2.second < s1.second;
    }
};

class GreaterSizeBdown
{
public:
    //GreaterSizeBdown() {}
    bool operator()(const pair<string, size_t> &s1, const pair<string, size_t> &s2) const
    {
        return s2.first.size() > s1.first.size();
    }
};



int main() {
    setlocale(LC_ALL, "rus");
    time_t t = time(NULL);
    map<string, size_t> words;
    string w;
    fstream file("file.txt"), out_file("out_file.txt", fstream::out), out_file1("out_file1.txt", fstream::out);
    int it = file.get();//извлекает из входного потока один символ и возвращает его целочисленный код
    while (it != EOF) {
        while (it != EOF && isalpha_rus(it)) {
            w.push_back(it); // Добавление элемента в конец
            it = file.get();
        }
        while (it != EOF  && !isalpha_rus(it = file.get()));
        if (!w.empty())
            ++words[w];
        w.clear();
    }
    if (!words.empty())
        for (auto &_pair : words)//диапазонный оператор (серийный). Справа диапазон, слева переменная,
            //копия элемента диапазона с инициализацией по значению, & создает инициализацию по ссылке.
            out_file << _pair.first << " = " << _pair.second << endl;
    file.close(); out_file.close();
    vector<pair<string, size_t>> line(words.begin(), words.end());
    sort(line.begin(), line.end(), GreaterSizeBup());   //Сортировка по символам
    for (auto &_pair : line)
        out_file1 << _pair.first << " = " << _pair.second << endl;
    out_file1.close();
    cout << "Время:" << (time(NULL) - t) << endl;
    system("pause");
    return 0;
}