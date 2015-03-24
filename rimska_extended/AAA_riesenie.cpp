#include <iostream>
#include <sstream>

using namespace std;

//#include "riesenie.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

#define odcitaj(kolko,Rimska,out) for (int ts = kolko; cislo >= ts; cislo -= kolko) {out = out + Rimska;}

#define special(kolko,Rimska,out)   if (cislo >= kolko) {  out = out + Rimska;   cislo -= kolko;}


class RIMSKA_KALKULACKA {
  int konverziaRimskych(const string &rimskeCislo);
  string konvertNaRimske(int cislo);
  int kalkulackaArabska(char oper, int op1, int op2);
 public:
  string kalkulackaRimska(const string &vyraz);
};

const bool DUMMY_BOOL = false;
const int DUMMY_INT = 0;
const string DUMMY_STRING = "";

const string CISLO_MIMO = "Cislo mimo povolenych hodnot";
const string ZLY_VYRAZ = "Zly vstupny vyraz";
#endif

string RIMSKA_KALKULACKA::kalkulackaRimska(const string &vyr) {
    string vyr1 = "";
    char op = 'N';
    string vyr2= "";
    bool found_operator = false;
    bool zap_1 = false;
    bool zap_2 = false;
    bool got_first = false;
    for(int i = 0; i< vyr.length(); i++){
        if (vyr.at(i)== ' ') {continue;}
        if ( vyr.at(i) == '-'  && got_first == false && zap_1 == false ){ zap_1 = true;  continue; }
        //TODO dalsie operatory
        if (vyr.at(i) == '+'||  vyr.at(i) == '-' || vyr.at(i) == '/' || vyr.at(i) == '*' || vyr.at(i) == '>'  || vyr.at(i) == '<' || vyr.at(i) == '=' || vyr.at(i) == '&' || vyr.at(i) == '|'     ){
            if (found_operator == true){return ZLY_VYRAZ;}
            op = vyr.at(i);
            found_operator = true;
            got_first = true;
            continue;
            }
        if ( vyr.at(i) == '-'  && got_first == true && zap_2 == false ){ zap_2 = true; continue;   }
        if ( vyr.at(i) == 'I' || vyr.at(i) == 'V' || vyr.at(i) == 'X' || vyr.at(i) == 'L'  || vyr.at(i) == 'C'  || vyr.at(i) == 'D'  || vyr.at(i) == 'M' || vyr.at(i) == 'P' || vyr.at(i) == 'Q' || vyr.at(i) == 'R' || vyr.at(i) == 'S' || vyr.at(i) == 'T' || vyr.at(i) == 'U' || vyr.at(i) == 'W'|| vyr.at(i) == 'Y' || vyr.at(i) == 'Z'|| vyr.at(i) == 'E' || vyr.at(i) == 'F' || vyr.at(i) == 'G')  {
            stringstream ss;
            char c;
            string  str;
            c =  vyr.at(i);
            ss<< c;
            ss>>str;
            if (found_operator == false){  vyr1.append(str); }
            else {              vyr2.append(str); }
            }
        else{ return ZLY_VYRAZ;}
        }
    if (found_operator == false){return ZLY_VYRAZ;}
    int cis1= konverziaRimskych(vyr1);
    if (zap_1 == true) {cis1 = -cis1; }
    int cis2=konverziaRimskych(vyr2);
    if (zap_2 == true) {cis2 = -cis2; }
    int result = kalkulackaArabska(op,cis1,cis2);
    string toret = konvertNaRimske(result);
  return toret;
}
int RIMSKA_KALKULACKA::konverziaRimskych(const string &rimskeCislo) {

  return DUMMY_INT;

}


string RIMSKA_KALKULACKA::konvertNaRimske(int cislo) {
  if(cislo<=-4000000000l || cislo>=4000000000l){
      return CISLO_MIMO;
  }

  string out = "";

  if (cislo == 0) {
    return "O";
  }

  odcitaj(1000000000, "G", out);
  special(900000000, "EG",out);

  odcitaj(500000000, "F", out);
  special(400000000, "EF",out);

  odcitaj(100000000, "E", out);
  special(90000000, "YE",out);

  odcitaj(50000000, "Z", out);
  special(40000000, "YZ",out);

  odcitaj(10000000, "Y", out);
  special(9000000, "UY",out);

  odcitaj(5000000, "W", out);
  special(4000000, "UW",out);

  odcitaj(1000000, "U", out);
  special(900000, "SU",out);

  odcitaj(500000, "T", out);
  special(400000, "ST",out);

  odcitaj(100000, "S", out);
  special(90000, "QS",out);

  odcitaj(50000, "R", out);
  special(40000, "QR",out);

  odcitaj(10000, "Q", out);
  special(9000, "MQ",out);

  odcitaj(5000, "P", out);
  special(4000, "MP",out);

  odcitaj(1000, "M", out);
  special(900, "CM",out);

  odcitaj(500, "D", out);
  special(400, "CD",out);

  odcitaj(100, "C", out);
   special(90, "XC",out);

  odcitaj(50, "L", out);
   special(40, "XL",out);

  odcitaj(10, "X", out);
   special(9, "IX",out);

  odcitaj(5, "V", out);
   special(4, "IV",out);

  odcitaj(1, "I", out);

  return out;
}


int RIMSKA_KALKULACKA::kalkulackaArabska(char oper, int op1, int op2) {
    if(oper == '+'){ return (op1 + op2) ;}
    if(oper == '-'){ return (op1 - op2) ;}
    if(oper == '*'){ return (op1 * op2) ;}
    if(oper == '/'){ return (op1 / op2) ;}
  return DUMMY_INT;
}
