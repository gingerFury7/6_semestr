#include <iostream>

class Ratio
{
protected:
    int chisl;
    int znam;
public:
    Ratio() {};
    ~Ratio() {};
    Ratio (int a = 0, int b = 1){
        if (b == 0){
            throw "0 в знаменателе не допустим";
        }
        else{
            this -> chisl = a;
            this -> znam = b;
        }
    }
    Ratio operator+ (const Ratio &m) const{
        Ratio newRatio;
        newRatio.chisl = this -> chisl * m.znam + this -> znam * m.chisl;
        newRatio.znam = this -> znam * m.znam;
        return newRatio;
    }
    Ratio operator- (Ratio &m){
        Ratio newRatio;
        newRatio.chisl = this -> chisl * m.znam - this -> znam * m.chisl;
        newRatio.znam = this -> znam * m.znam;
        return newRatio;
    }
    Ratio operator* (Ratio &m){
        Ratio newRatio;
        newRatio.chisl = this -> chisl * m.chisl;
        newRatio.znam = this -> znam * m.znam;
        return newRatio;
    }
    Ratio operator/ (Ratio &m){
        Ratio newRatio;
        if ( m.chisl == 0)
        {
            throw "Деление на 0 запрещено";
        };
        newRatio.chisl = this -> chisl * m.znam;
        newRatio.znam = this -> znam * m.chisl;
        return newRatio;
    }
    Ratio& operator+= (Ratio &m){
        this -> chisl = this -> chisl * m.znam + this -> znam   * m.chisl;
        this -> znam *= m.znam;
        return *this;
    }
    friend bool operator > (Ratio &a, Ratio &b){
        return a.chisl * b.znam > b.chisl * a.znam;
    }
    friend bool operator < (Ratio &a, Ratio &b){
        return a.chisl * b.znam < b.chisl * a.znam;
    }
    void print (){
        if (this -> chisl == 0){
            std::cout << "0" << std::endl;
        }
        else if ((this -> chisl * this -> znam) < 0){
            std::cout << "- " << abs(this -> chisl) << " / " << abs(this -> znam) << std::endl;
        }
        else{
            std::cout << this -> chisl << " / " << this -> znam << std::endl;
        }
    }
    void reduction (){
        int ch, zn;
        int nod = 0;
        ch = this -> chisl;
        zn = this -> znam;
        for (int i = 1; (i <= abs(ch)) && (i <= abs(zn)); i++){
            if (!(ch % i) && !(zn % i))
            {   nod = i ;
                this -> chisl = ch / i;
                this -> znam = zn / i;
            }
        }
    }
};

int main (){
    try {
        Ratio a(1, 0);
//        Ratio m(0, 15);
//        a = a / m;
    }
    catch (const char *exeption) {
        std::cout << exeption << std::endl;
    }
    Ratio b(1, 2);
    Ratio c(1,3);
    Ratio d = b + c;
    d.reduction();
    std::cout << "Сложение: ";
    d.print();
    d = b - c;
    d.reduction();
    std::cout << "Вычитание: ";
    d.print();
    d = b * c;
    d.reduction();
    std::cout << "Умножение: ";
    d.print();
    d = b / c;
    d.reduction();
    std::cout << "Деление: ";
    d.print();
    d += b;
    d.reduction();
    std::cout << "Оператор += : ";
    d.print();
    if (d > b){
        std::cout << "d > b" << std::endl;
    }
    else {
        std::cout << " d < b" << std::endl;
    }
    return 0;
}