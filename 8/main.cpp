#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

struct Film{
    int id;
    string name;
    int votes;

    Film(){
        id = 0;
        votes = 0;
    }
};

struct Viewer {
    string name;
    int rating;
    vector<int> FavouriteFilms;

    Viewer(){
        FavouriteFilms.resize(3);
        rating = 0;
    }
};

class GetFilm {
private:
    int FilmCount;
public:
    GetFilm(){
        FilmCount = 0;
    }
    Film operator() (){
        Film f;
        cin.ignore();
        f.id = ++FilmCount;
        cout << "Фильм №" << f.id << ": " << endl << flush;
        getline(cin, f.name);
        cout << f.name << endl << flush;
        return f;
    }
};

class GetViewer {
public:
    Viewer operator() (){
        Viewer v;
        cin.ignore();
        cout << "Имя: ";
        getline(cin, v.name);
        cout << "Любимые фильмы:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << "-е место: ";
            cin >> v.FavouriteFilms[i];
        }
        cout << endl;
        return v;
    }
};

class CalculatedViewerRating{
private:
    vector<int> TopFilms;
public:
    CalculatedViewerRating(const vector<int> &v){
        TopFilms = v;
    }
    void operator() (Viewer &v)
    {
        int i = 0;
        for_each( v.FavouriteFilms.begin(), v.FavouriteFilms.end(), [=, &v, &i](int filmNum) {	// цикл по любимым фильмам зрителя
            auto fp = find(TopFilms.begin(), TopFilms.end(), filmNum);				// ищем любимый фильм в топе
            if (fp != TopFilms.end())
            {													// если фильм найден
                int j = distance(TopFilms.begin(), fp);		// вычисляем место в списке
                if (i == j)										// если место угадано точно
                    v.rating += 3;								// начисляем 2 балла
                else if (abs(i - j) == 1)											// иначе
                    v.rating += 2; // начисляем 1 балл
                else{
                    v.rating += 1;
                }
            }
            i++;
        });
    }
};

int main() {
    int NumbersFilms;
    cout << "Введите количество фильмов: ";
    cin >> NumbersFilms;
    vector<Film> films(NumbersFilms);
    cout << endl;

    cout << "Введите названия фильмов: " << endl;
    generate(films.begin(), films.end(), GetFilm());
    cout << endl;

    int NumbersViewers;
    cout << "Введите количество зрителей: ";
    cin >> NumbersViewers;
    list<Viewer> viewers(NumbersViewers);

    cout << "Введите информацию о зрителях: " << endl;
    generate(viewers.begin(), viewers.end(), GetViewer());
    cout << endl;


    for_each(viewers.begin(), viewers.end(), [&films](const Viewer &vi){
        for_each(vi.FavouriteFilms.begin(), vi.FavouriteFilms.end(), [&films](int filmsNum){
            if ((filmsNum > 0) && (filmsNum != films.size())){
                films[filmsNum - 1].votes++;
            };
        });
    });

    sort(films.begin(), films.end(), [](const Film &f1 , const Film &f2) -> bool {
        return f1.votes > f2.votes;
    });
    films.resize(3);
    int i = 1;
    cout << "Топ 3 фильма:" << endl;
    for_each(films.begin(), films.end(), [&i](const Film &f){
        cout << i++ << "-е место: " << f.name << " (" << f.votes << " голоса(ов)" << endl;
    });
    cout << endl;

    vector<int> topFilms(films.size());
    transform(films.begin(), films.end(), topFilms.begin(), [](const Film &f){
        return f.id;
    });

    for_each(viewers.begin(), viewers.end(), CalculatedViewerRating(topFilms));

    viewers.sort([](const Viewer v1, const Viewer v2) -> bool {
        return v1.rating > v2.rating;
    });
    viewers.resize(3);
    int j = 1;
    cout << "Топ 3 зрителя:" << endl;
    for_each(viewers.begin(), viewers.end(), [&j](const Viewer &v){
        cout << j++ << "-е место: " << v.name << " (" << v.rating << " балла(ов)" << endl;
    });
}
