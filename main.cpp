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

    string get_cell_wall_composition() {return "Capsid (not cell wall)";}
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

    string get_cell_wall_composition() {return "Varies";}
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

    string get_cell_wall_composition() {return "Varies";}
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
    
    string get_cell_wall_composition() {return "No cell wall";}
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

template<typename T>
void printel(T& el) {
    cout << "----------------------------------------" << endl;
    cout << el << endl;
}
void printel(Microorganisms* el) {
    cout << "----------------------------------------" << endl;
    el->get_info();
}

// ! ||--------------------------------------------------------------------------------||
// ! ||                                  классы списка                                 ||
// ! ||--------------------------------------------------------------------------------||
template<class U>
class Uzel {
public:
    U el;
    Uzel<U>* pt;

    Uzel(const U& element, Uzel<U>* pointer = nullptr):
        el(element), pt(pointer) {}
};

template<class L>
class List {
    Uzel<L>* pt_hd;
    int size;
public:
    List(): pt_hd(nullptr), size(0) {}

    void print() {
        print(pt_hd);
    }

    void print(Uzel<L>* pt) {
        if (pt == nullptr) return;
        printel(pt->el);
        print(pt->pt);
    }

    void operator+(const L& val) {
        Uzel<L>* added = new Uzel<L>(val);
        
        if (pt_hd == nullptr) pt_hd = added;
        else {
            Uzel<L>* curr = pt_hd;
            while (curr->pt != nullptr) {
                curr = curr->pt;
            }
            curr->pt = added;
        }
        size++;
    }

    void operator--(int) {
        if (pt_hd == nullptr) return;
        else if (pt_hd->pt == nullptr) {
            delete pt_hd;
            pt_hd = nullptr;
        }
        else {
            Uzel<L>* deleted = pt_hd;
            while (deleted->pt->pt != nullptr) {
                deleted = deleted->pt;
            }
            delete deleted->pt;
            deleted->pt = nullptr;
        }    
        size--;
    }

    bool operator!=(const List<L>& enemy) const {
        if (size != enemy.size) return true;
        Uzel<L>* curr = pt_hd;
        Uzel<L>* curr_enemy = enemy.pt_hd;
        while (curr != nullptr && curr_enemy != nullptr) {
            if(curr->el != curr_enemy->el) return true;
            curr = curr->pt;
            curr_enemy = curr_enemy->pt;
        }
        return false;
    }

};

// ! ||--------------------------------------------------------------------------------||
// ! ||                               основная программа                               ||
// ! ||--------------------------------------------------------------------------------||
int main(){
    List<string> list;
    list + "Test1";
    list + "Test2";
    list + "Test3";

    List<string> list1;
    list1 + "Test1";
    list1 + "Test2";

    cout << (list!=list1) << endl;

    List<string> list2;
    list2 + "Test1";
    list2 + "Test2";
    list2 + "Test3";
    
    cout << (list!=list2) << endl;

    List<char> char_list;
    char_list + 'A';
    char_list + 'B';
    char_list + 'C';
    char_list + 'D';
    
    char_list.print();
    char_list--;
    char_list.print();

    List<Microorganisms*> organisms;

    Viruses* cov = new Viruses("SARS-CoV-2", 100);
    Bacteria* coli = new Bacteria("Jolin", 2000, 1, 1);
    Animals* lion = new Animals("Lion", 250000000000, 1, 1);
    Plants* mimoze = new Plants("Mimoze", 100000000000, 1, 1);

    organisms + cov;
    organisms + coli;
    organisms + lion;
    organisms + mimoze;

    organisms.print();

    
    return 0;
}