#include <iostream>
#include <string>
using namespace std;

// ! ||--------------------------------------------------------------------------------||
// ! ||                           основной родительский класс                          ||
// ! ||--------------------------------------------------------------------------------||

class Microorganisms {
    string name;
    long int size; // в нанометрах
    static long int min_size;
public:
    Microorganisms(string name = "Unknown", long int size = 0) {
        if (size < min_size)
            min_size = size;
        this->name = name;
        this->size = size;
    }

    int get_size() {return size;}
    static int get_min_size() {return min_size;}
    string get_name() {return name;}

    virtual void get_info() {
        cout << "Name: " << name << endl;
        cout << "Size: " << size << endl;
    }

    virtual string get_cell_wall_composition() {
        return "Unknown";
    }
};

long int Microorganisms::min_size = 5;

// ! ||--------------------------------------------------------------------------------||
// ! ||                                    подклассы                                   ||
// ! ||--------------------------------------------------------------------------------||

class Viruses:public Microorganisms {
    int is_dangerous;
public:
    Viruses(string name, long int size, int is_dangerous = 1):Microorganisms(name,size){
        if (is_dangerous < 0 && is_dangerous > 1) this->is_dangerous = 1;
        else this->is_dangerous = is_dangerous;
    }

    void get_info() {
        Microorganisms::get_info();
        cout << "Is dangerous: " << is_dangerous << endl;
    }

    string get_cell_wall_composition() {return Microorganisms::get_cell_wall_composition();}
};  

class Prokaryotes:public Microorganisms {
    int metabolism;
public:
    Prokaryotes(string name, long int size, int metabolism):Microorganisms(name,size){
        this->metabolism = metabolism;
    }

    void get_info() {
        Microorganisms::get_info();
        cout << "Metabolism: " << metabolism << endl;
    }

    string get_cell_wall_composition() {return Microorganisms::get_cell_wall_composition();}
};

class Eukaryotes:public Microorganisms {
    int reproduction;
public:
    Eukaryotes(string name, long int size, int reproduction):Microorganisms(name,size){
        this->reproduction = reproduction;
    }

    void get_info() {
        Microorganisms::get_info();
        cout << "Reproduction: " << reproduction << endl;
    }

    string get_cell_wall_composition() {return Microorganisms::get_cell_wall_composition();}
};

// ! ||--------------------------------------------------------------------------------||
// ! ||                                  подподклассы                                  ||
// ! ||--------------------------------------------------------------------------------||
class Bacteria:public Prokaryotes {
    int gram_stain;
public:
    Bacteria(string name, long int size, int metabolism, int gram_stain):Prokaryotes(name,size,metabolism){
        this->gram_stain = gram_stain;
    }

    void get_info() {
        Prokaryotes::get_info();
        cout << "Gram stain: " << gram_stain << endl;
    }

    string get_cell_wall_composition() {
        return "Peptidoglycan";
    }
};

class Archaea:public Prokaryotes {
    int membrane_structure;
public:
    Archaea(string name, long int size, int metabolism, int membrane_structure):Prokaryotes(name,size,metabolism){
        this->membrane_structure = membrane_structure;
    }

    void get_info() {
        Prokaryotes::get_info();
        cout << "Membrane structure: " << membrane_structure << endl;
    }

    string get_cell_wall_composition() {
        return "Pseudopeptidoglycan";
    }
};


class Animals: public Eukaryotes {
    int is_multicellular;
public:
    Animals(string name, long int size, int reproduction, int is_multicellular):Eukaryotes(name, size, reproduction) {
            this->is_multicellular = is_multicellular;
    }

    void get_info() {
        Eukaryotes::get_info();
        cout << "Is multicellular: " << is_multicellular << endl;
    }
    
    string get_cell_wall_composition() {return Microorganisms::get_cell_wall_composition();}
};

class Plants: public Eukaryotes {
    int is_higher_realms;
public:
    Plants(string name, long int size, int reproduction, int is_higher_realms):Eukaryotes(name, size, reproduction) {
            this->is_higher_realms = is_higher_realms;
    }

    void get_info() {
        Eukaryotes::get_info();
        cout << "Is higher realms: " << is_higher_realms << endl;
    }
    
    string get_cell_wall_composition() {
        return "Cellulose";
    }
};

class Mushrooms: public Eukaryotes {
    int is_multicellular;
public:
    Mushrooms(string name, long int size, int reproduction, int is_multicellular):Eukaryotes(name, size, reproduction) {
            this->is_multicellular = is_multicellular;
    }

    void get_info() {
        Eukaryotes::get_info();
        cout << "Is multicellular: " << is_multicellular << endl;
    }

    string get_cell_wall_composition() {
        return "Chitin";
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

    Viruses* virus = new Viruses("Virus", 100);
    Viruses* virus2 = new Viruses("Jolin", 1, 1);

    cout << virus->get_name() << endl;
    cout << virus->get_size() << endl;
    cout << virus2->get_min_size() << endl;
    cout << endl;

    virus->get_info();
    cout << virus->get_cell_wall_composition() << endl;
    cout << endl;

    virus2->get_info();
    cout << endl;

    Animals* lion = new Animals("Lion", 250000000000, 1, 1);
    lion->get_info();
    cout << lion->get_cell_wall_composition() << endl;
    cout << endl;

    Plants* mimoze = new Plants("Mimoze", 100000000000, 1, 1);
    mimoze->get_info();
    cout << mimoze->get_cell_wall_composition() << endl;

    
    return 0;
}