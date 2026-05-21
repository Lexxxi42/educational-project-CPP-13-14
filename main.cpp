#include <iostream>
#include <string>
using namespace std;

// ! ||--------------------------------------------------------------------------------||
// ! ||                           основной родительский класс                          ||
// ! ||--------------------------------------------------------------------------------||
class Microorganisms {
    string name;
    int size;
    static int min_size;
public:
    Microorganisms(string name = "Unknown", int size = 0) {
        if (size < min_size)
            min_size = size;
        this->name = name;
        this->size = size;
    }
    int get_size() {return size;}
    static int get_min_size() {return min_size;}
    string get_name() {return name;}
};

int Microorganisms::min_size = 5;
// ! ||--------------------------------------------------------------------------------||
// ! ||                                    подклассы                                   ||
// ! ||--------------------------------------------------------------------------------||
class Viruses:public Microorganisms {
    int is_dangerous;
public:
    Viruses(string name, int size, int is_dangerous):Microorganisms(name,size){
        this->is_dangerous = is_dangerous;
    }
};  

class Prokaryotes:public Microorganisms {
    int metabolism;
public:
    Prokaryotes(string name, int size, int metabolism):Microorganisms(name,size){
        this->metabolism = metabolism;
    }
};

class Eukaryotes:public Microorganisms {
    int reproduction;
public:
    Eukaryotes(string name, int size, int reproduction):Microorganisms(name,size){
        this->reproduction = reproduction;
    }
};
// ! ||--------------------------------------------------------------------------------||
// ! ||                                  подподклассы                                  ||
// ! ||--------------------------------------------------------------------------------||
class Bacteria:public Prokaryotes {
    int gram_stain;
public:
    Bacteria(string name, int size, int metabolism, int gram_stain):Prokaryotes(name,size,metabolism){
        this->gram_stain = gram_stain;
    }
};

class Archaea:public Prokaryotes {
    int membrane_structure;
public:
    Archaea(string name, int size, int metabolism, int membrane_structure):Prokaryotes(name,size,metabolism){
        this->membrane_structure = membrane_structure;
    }
};


class Animals: public Eukaryotes {
    int is_multicellular;
public:
    Animals(string name, int size, int reproduction, int is_multicellular):Eukaryotes(name, size, reproduction) {
            this->is_multicellular = is_multicellular;
    }
};

class Plants: public Eukaryotes {
    int is_higher_realms;
public:
    Plants(string name, int size, int reproduction, int is_higher_realms):Eukaryotes(name, size, reproduction) {
            this->is_higher_realms = is_higher_realms;
    }
};

class Mushrooms: public Eukaryotes {
    int is_multicellular;
public:
    Mushrooms(string name, int size, int reproduction, int is_multicellular):Eukaryotes(name, size, reproduction) {
            this->is_multicellular = is_multicellular;
    }
};

// ! ||--------------------------------------------------------------------------------||
// ! ||                                  классы списка                                 ||
// ! ||--------------------------------------------------------------------------------||

class Uzel {
public:
    string el;
    Uzel* pt;

    Uzel(const string& element, Uzel* pointer = nullptr):
        el(element), pt(pointer) {}
};

class List {
    Uzel* pt_hd;
public:
    List(): pt_hd(nullptr) {}

    void print() {
        print(pt_hd);
    }

    void print(Uzel* pt) {
        if (pt == nullptr) return;
        print(pt->pt);
        cout << pt->el << endl;
    }

    void add(string val) {
        pt_hd = new Uzel(val, pt_hd);
    }

    void operator--(int) {
        if (pt_hd != nullptr) {
            Uzel* deleted = pt_hd;
            pt_hd = pt_hd->pt;
            delete deleted;}
        
    }

};
// ! ||--------------------------------------------------------------------------------||
// ! ||                               основная программа                               ||
// ! ||--------------------------------------------------------------------------------||
int main(){
    List list;
    list.add("Test");
    list.add("Test1");
    list.add("Test2");
    list--;
    list.print();

    Viruses* virus = new Viruses("Virus", 100, 1);
    Viruses* virus2 = new Viruses("Jolin", 1, 1);
    cout << virus->get_name() << endl;
    cout << virus->get_size() << endl;
    cout << virus2->get_min_size() << endl;
    return 0;
}