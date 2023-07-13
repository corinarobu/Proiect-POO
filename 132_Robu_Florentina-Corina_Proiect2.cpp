#include <iostream>
#include <vector>
#include <cstring>
#include <list>
using namespace std;

////////////---------- clasa interfata/ abstracta
class Interface {
public:
  virtual istream& citire(istream&) = 0;
  virtual ostream& afisare(ostream&) const = 0;
};

/////////// ------------- clasa de baza Masini
class Masini: public Interface {
protected:
  int an;
  vector <long long> km;  // poz 0 e nr minim, iar poz 1 numarul maxim de km acceptati
  string marca;
  string tip_caroserie;

public:
   int getAn() { return this->an;}
   string getMarca() {return this->marca;}
   string getTipCaroserie(){return this->tip_caroserie;};

  Masini(int an,const vector <long long> km, string marca, string tip_caroserie);
  Masini(const Masini& obj);
  Masini& operator = (const Masini& obj);

  friend istream& operator >> (istream &in, Masini &obj);
  friend ostream& operator << (ostream &out, const Masini &obj);


    istream& citire(istream& in) {
      cout << "Introduceti anul fabricatiei : " ;
      in >> this->an;

      if(!this->km.empty()) this->km.clear();
      cout << "Introduceti numarul minim de km ";
      this->km.push_back(*(new long long()));
      in >> this->km.back();
      cout << "Introduceti numarul maxim de km ";
      this->km.push_back(*(new long long()));
      in >> this->km.back();

      cout << "Introduceti marca masinii : ";
      in >> this->marca;
      cout <<"Introduceti tipul caroseriei :" ;
      in >> this->tip_caroserie;

      return in;
    }

    ostream& afisare(ostream& out )const {
       out << "Generatie " << this->an;
       out <<endl<< "Interval de km acceptati: ";
       for(int i = 0; i < this->km.size(); i++) out << this->km[i] << " ";
       out << endl << "Marca masina :" << this->marca;
       out << endl << "Tip de caroserie: " << this->tip_caroserie << endl;

       return out;
    }

    bool operator == (const Masini& obj) {
      int ok = 1;
      for(int i = 0; i < this->km.size(); i++)
        if(this->km[i] != obj.km[i]) ok = 0;
      if(this->an == obj.an &&
       this->marca == obj.marca && this->tip_caroserie == obj.tip_caroserie && ok == 1) return 1;
       return 0;
    }

    virtual int afisTip() = 0;
    virtual ~Masini(){}
};

Masini::Masini(int an = 0,const vector <long long> km = {}, string marca = "",string tip_caroserie = "") {
  this->an = an;
  this->km = km;
  this->marca = marca;
  this-> tip_caroserie = tip_caroserie;
}

Masini::Masini(const Masini& obj) {
  this->an = obj.an;
  this->km = obj.km;
  this->marca = obj.marca;
  this->tip_caroserie = obj.tip_caroserie;
}

Masini& Masini::operator = (const Masini& obj ){
  if(this != &obj) {
    this->an =  obj.an;
    this->km = obj.km;
    this->marca = obj.marca;
    this->tip_caroserie = obj.tip_caroserie;
  }
  return *this;
}

istream& operator >> (istream& in, Masini &obj) {
  return obj.citire(in);
}

ostream& operator << (ostream& out, const Masini & obj) {
  return obj.afisare(out);
}


////////// ---- clasa Electrica
class Electrica: virtual public Masini {
  // ca sa fie vizibil in Hibrid
protected:
  long capactiate_baterie;

public:
   long getCapacitateBaterie(){return this->capactiate_baterie;};

    Electrica(int an = 0, const vector <long long> km = {} , string marca = "", string tip_caroserie = "", long capactiate_baterie = 0);
    Electrica(const Electrica& obj);
    Electrica& operator = (const Electrica& obj);

    istream& citire(istream& in) {
      this->Masini::citire(in);
      cout << "Introduceti capactiatea bateriei : ";
      in >> this->capactiate_baterie;

      return in;
    }

    ostream& afisare(ostream& out) const {
      this->Masini::afisare(out);
      out << "Capacitatea bateriei este de : " << this->capactiate_baterie;
      out << endl;
      return out;
    }

    bool operator == (const Electrica& obj){
      if( Masini::operator == (obj) && this->capactiate_baterie == obj.capactiate_baterie) return 1;
      return 0;
    }

    int afisTip() {
      return 0;
  }

  ~Electrica(){}
};

Electrica::Electrica(int an, const vector <long long> km, string marca, string tip_caroserie , long capactiate_baterie):
Masini(an, km, marca, tip_caroserie) {
  this->capactiate_baterie = capactiate_baterie;
};

Electrica::Electrica(const Electrica& obj):Masini(obj) {
  this->capactiate_baterie = capactiate_baterie;
};

Electrica& Electrica:: operator = (const Electrica& obj) {
  if(this!= &obj) {
    Masini::operator=(obj);
    this->capactiate_baterie = capactiate_baterie;
  }
  return *this;
};

/////////////// -- clasa Combustie_interna
class Combustie_interna: virtual public Masini {
protected:
  string combustibil;
  int capactiate_motor;
public:
  string getCombustibil(){return this->combustibil;};
  int getCapacitateMotor(){return this->capactiate_motor;};

  Combustie_interna(int an,const vector <long long> km, string marca, string tip_caroserie, string combustibil, int capactiate_motor);
  Combustie_interna(const Combustie_interna& obj);
  Combustie_interna& operator = (const Combustie_interna& obj);

  istream& citire(istream& in) {
    this->Masini::citire(in);
    cout << "Introduceti tipul combustibilului : ";
    in >> this->combustibil;
    cout <<"Introduceti capacitatea motorului : ";
    in >> this->capactiate_motor;

    return in;
  }

  ostream& afisare(ostream& out) const {
    this->Masini::afisare(out);
    out << "Comustililul este " << this->combustibil;
    out << endl << "Capacitatea motorului este de " << this->capactiate_motor;
   out << endl;
    return out;
  }

  bool operator == (const Combustie_interna& obj ){
    if(Masini::operator == (obj) && this->capactiate_motor == obj.capactiate_motor && this->combustibil == obj.combustibil) return 1;
    return 0;
  }

  int afisTip() {
    return 1;
  }

  ~Combustie_interna(){}
};

Combustie_interna::Combustie_interna(int an = 0, const vector <long long> km = {}, string marca = "", string tip_caroserie= "", string combustibil = "", int capactiate_motor = 0) :
Masini(an, km, marca, tip_caroserie) {
  this->combustibil = combustibil;
  this->capactiate_motor = capactiate_motor;
}

Combustie_interna::Combustie_interna(const Combustie_interna& obj):Masini(obj) {
  this->combustibil = combustibil;
  this->capactiate_motor= capactiate_motor;
}

Combustie_interna& Combustie_interna::operator = (const Combustie_interna& obj) {
  if(this!= &obj) {
    Masini::operator = (obj);
    this->combustibil =combustibil ;
    this->capactiate_motor = capactiate_motor;
  }
  return *this;
}

///////////// -- clasa Hibrid
class Hibrid: public Electrica, public Combustie_interna {
  bool smecherie;

public:
  Hibrid(int an = 0, const vector <long long> km = {} , string marca = "", string tip_caroserie = "", long capactiate_baterie = 0, string combustibil = "", int capactiate_motor = 0, bool smecherie = true):
  Masini(an, km, marca, tip_caroserie), Electrica(an , km , marca, tip_caroserie, capactiate_baterie), Combustie_interna(an,km,marca,tip_caroserie,combustibil, capactiate_motor) {
    this->smecherie = smecherie;
  }

  Hibrid(const Hibrid& obj): Masini(obj), Electrica(obj), Combustie_interna(obj) {
    this->smecherie = obj.smecherie;
  }

  Hibrid& operator = (const Hibrid& obj) {
    if(this != &obj) {
      Electrica::operator = (obj);
      Combustie_interna::operator = (obj);
      this->smecherie = obj.smecherie;
    }
    return *this;
  }

  istream& citire(istream& in) {
    Electrica::citire(in);

    cout << "Introduceti tipul combustibilului : ";
    in >> this->combustibil;
    cout <<"Introduceti capacitatea motorului : ";
    in >> this->capactiate_motor;

    cout << "E smechera ? [1 = true / 0 = false] ";
    in >> this->smecherie;

    return in;

  };

  ostream& afisare(ostream& out) const {
    Electrica::afisare(out);

    out << "Comustililul este " << this->combustibil;
    out << endl << "Capacitatea motorului este de " << this->capactiate_motor;
    out << endl << "Smecherie " << this->smecherie;
    out << endl;
    return out;
  };

  bool operator == (const Hibrid& obj) {
    if(Electrica::operator == (obj) && this->capactiate_motor == obj.capactiate_motor && this->combustibil == obj.combustibil &&
      this->smecherie == obj.smecherie)
      return 1;
    return 0;
   }

  int afisTip() {
    return Electrica::afisTip()+2;
  }

  ~Hibrid(){}

};

////////////// ------- clasa inventar
class Item_inventar {
  bool stoc;
  Masini* masina;
public:
  void setStoc(bool i) {this->stoc = i;};

  bool getStoc(){return this->stoc;};

  friend istream& operator >> (istream& in, Item_inventar& obj) {
    cout << "1. Masina electrica" << endl;
    cout << "2. Masina cu combustie interna " << endl;
    cout << "3. Masina hibrid" << endl;
    int k;
    cin >> k;
    if(k==1) {
      obj.masina = new Electrica();
    }
    if(k == 2) obj.masina = new Combustie_interna();
    if(k == 3) obj.masina = new Hibrid();
    in >> *obj.masina;

    cout << "Introduceti stoc: ";
    in >> obj.stoc;
    cout << endl;

    return in;
  }

  friend ostream& operator << (ostream& out, const Item_inventar& obj){
    out << "Masina" << endl << *obj.masina;
    out << "In stoc :" << obj.stoc;
     out << endl;
    return out;
  }

  Masini* getMasina(){return this->masina;};

};

//////////////// ---- clasa interactiva
class Inchiriere{
   list <Item_inventar> inventar;
   list <Masini*> masini_inchiriate;
   list <Masini*> masini_disponibile;
 public:
   void addInventar(); 
   void showInventar();
   void inchiriazaMasina(); 
   void inchiriazaMasinaCombustieInterna();
   void inchiriazaMasinaElectrica();
   void inchiriazaMasinaHibrid();
   void updateMasinaInchiriata(int &p);
   void showMasiniInchiriate();
   void showMasiniDisponibile();
   void InapoiazaMasinaInchiriata();
};

void Inchiriere::addInventar() {
  Item_inventar i;
  cin >> i;
  inventar.push_back(i);
  masini_disponibile.push_back(i.getMasina());
}

void Inchiriere::showInventar() {
  for( auto it = inventar.begin(); it != inventar.end(); it++) cout << *it << endl;
}

void Inchiriere::inchiriazaMasina() {
  cout <<"1. Masina electrica" << endl << "2. Masina cu combustie interna" << endl << "3. Masina hibrid" << endl;
  int a;
  cin >> a;
  if(a  == 1) Inchiriere::inchiriazaMasinaElectrica();
  if(a == 2) Inchiriere::inchiriazaMasinaCombustieInterna();
  if(a == 3) Inchiriere::inchiriazaMasinaHibrid();
}

void Inchiriere::inchiriazaMasinaElectrica(){
  Electrica e;
  cin >> e;
  int ok = 0;
  for( auto it = inventar.begin(); it != inventar.end(); it++){
    if((*it->getMasina()).afisTip() == 0) {
        if(e == dynamic_cast<Electrica&>(*(it->getMasina())) && (*it).getStoc()) {
          ok = 1;
          masini_inchiriate.push_back(it->getMasina());
          (*it).setStoc(0); // il scot din stoc
          masini_disponibile.remove(it->getMasina());
        }
      }
    }
    if(ok==0) cout << "Masina nu este disponibila"<< endl;
};

void Inchiriere::inchiriazaMasinaCombustieInterna(){
  Combustie_interna c;
  cin >> c;
  int ok = 0;
    for( auto it = inventar.begin(); it != inventar.end(); it++){
      if((*(it->getMasina())).afisTip()== 1){
          if(c == dynamic_cast<Combustie_interna&>(*(it->getMasina())) && (*it).getStoc()) {
            ok = 1;
            masini_inchiriate.push_back(it->getMasina());
            (*it).setStoc(0);
            masini_disponibile.remove(it->getMasina());
          }
        }
    }
    if(ok == 0) cout << "Masina nu este disponibila"<< endl;
};

void Inchiriere::inchiriazaMasinaHibrid() {
  Hibrid h;
  cin >> h;
  int ok = 0;
  for( auto it = inventar.begin(); it != inventar.end(); it++){
    if((*it->getMasina()).afisTip() == 2) {
        if(h == dynamic_cast<Hibrid&>(*(it->getMasina())) && (*it).getStoc()) {
          ok = 1;
          masini_inchiriate.push_back(it->getMasina());
          (*it).setStoc(0); // il scot din stoc
          masini_disponibile.remove(it->getMasina());
        }
      }
    }

    if(ok==0) cout << "Masina nu este disponibila"<< endl;
}

void Inchiriere::showMasiniInchiriate() {
  for(auto i = masini_inchiriate.begin(); i != masini_inchiriate.end(); i++) cout << **i << endl;
}

void Inchiriere::showMasiniDisponibile() {
  for(auto i = masini_disponibile.begin(); i != masini_disponibile.end(); i++ ) {
    cout << **i << endl;
  }
}

void Inchiriere::updateMasinaInchiriata(int &p) {
  cout << "Introdu masina luata "<< endl << "1. Masina electrica" << endl << "2. Masina cu combustie interna"<< endl << "3. Masina hibrid" << endl;

  int k;
  cin >> k;
  if(k==1) {
    masini_disponibile.push_back(new Electrica());
    cin >> *this->masini_disponibile.back();

    int v = 0;
    for( auto it = inventar.begin(); it != inventar.end(); it++){
      if((*it->getMasina()).afisTip() == 0) {
          if(*this->masini_disponibile.back() == (*it->getMasina()) && (*it).getStoc() == 0) {
            masini_inchiriate.remove(it->getMasina());
            (*it).setStoc(1);
            v = 1;
            p = 1;
            break;
          }
        }
      }

      if(v == 0) {
        // masina introdusa nu era inchiriata, (clientul a mintit) deci neavand acea masina pe care o inapoiaza, nu trebuia bagata in masini_disponibile
        for( auto it = masini_disponibile.begin(); it != masini_disponibile.end(); it++){
          if((**it).afisTip() == 0) {
              if(*this->masini_disponibile.back() == **it) {
                masini_disponibile.remove(*it);
                p = 0;
                break;
              }
            }
          }
       }
  }

if(k == 2) {
    masini_disponibile.push_back(new Combustie_interna());
    cin >> *this->masini_disponibile.back();


  int v= 0;
    for( auto it = inventar.begin(); it != inventar.end(); it++){
      if((*it->getMasina()).afisTip() == 1) {
          if(*this->masini_disponibile.back() == (*it->getMasina()) && (*it).getStoc() == 0) {
            masini_inchiriate.remove(it->getMasina());
            v = 1;
            p = 1;
            (*it).setStoc(1);
            break;
          }
        }
      }

      if(v == 0) {
        for( auto it = masini_disponibile.begin(); it != masini_disponibile.end(); it++){
          if((**it).afisTip() == 1) {
              if(*this->masini_disponibile.back() == **it) {
                masini_disponibile.remove(*it);
                p =0;
                break;
              }
            }
          }
      }
  }


  if(k==3) {
    masini_disponibile.push_back(new Hibrid());
    cin >> *this->masini_disponibile.back();

    int v = 0;
    for( auto it = inventar.begin(); it != inventar.end(); it++){
      if((*it->getMasina()).afisTip() == 2) {
          if(*this->masini_disponibile.back() == (*it->getMasina()) && (*it).getStoc() == 0) {
            masini_inchiriate.remove(it->getMasina());
            (*it).setStoc(1);
            v = 1;
            p = 1;
            break;
          }
        }
      }

      if(v == 0) {
        // masina introdusa nu era inchiriata, (clientul a mintit) deci neavand acea masina pe care o inapoiaza, nu trebuia bagata in masini_disponibile
        for( auto it = masini_disponibile.begin(); it != masini_disponibile.end(); it++){
          if((**it).afisTip() == 2) {
              if(*this->masini_disponibile.back() == **it) {
                masini_disponibile.remove(*it);
                p = 0;
                break;
              }
            }
          }
       }
  }

};

void Inchiriere::InapoiazaMasinaInchiriata() {
   int p =0;
   Inchiriere::updateMasinaInchiriata(p);
   if(p == 0) cout <<endl << "Masina nu este inchiriata de la noi :( " << endl<< endl;
   else cout << endl << "Multumim! Sper ca v-a placut :) " << endl << endl;
}

int main() {

 Inchiriere b;
   int k = 1;
  while(k == 1){
    cout << "1. Add inventar" << endl;
    cout << "2. Show inventar" << endl;
    cout << "3. Inchiriaza masina "<< endl;
    cout << "4. Show masini inchirate" << endl;
    cout << "5. Show masini disponibile" << endl;
    cout << "6. Update masina inchiriata" << endl;
    cout << "7. Inapoiaza masina inchiriata" << endl;
    cout << "8. Stop" << endl;
    int comanda;
    cin >> comanda;
    switch (comanda) {
      case 1: {
        b.addInventar();
        break;
      }

      case 2: {
        b.showInventar();
        break;
      }

      case 3: {
        b.inchiriazaMasina();
        break;
      }

      case 4: {
        b.showMasiniInchiriate();
        break;
      }

      case 5: {
        b.showMasiniDisponibile();
        break;
      }

      case 6: {
        int p = 0;
          b.updateMasinaInchiriata(p); 
          if( p == 1 ){ 
            cout << "Alege o masina noua";
            b.inchiriazaMasina();
          }
          else cout << "Masina introdusa nu este inchiriata de la noi :(" << endl;
          break;
      }

      case 7: {
        b.InapoiazaMasinaInchiriata();
        break;
      }

      case 8:
         {
           k = 0;
           break;
         }
    }
  }

  return 0;
}
