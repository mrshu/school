#include <iostream>
#include <sstream>
#include<map>
using namespace std;

//#include "riesenie.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

#define odcitaj(kolko,Rimska,out) for (int ts = kolko; cislo >= ts; cislo -= kolko) {out = out + Rimska;}

#define special(kolko,Rimska,out)   if (cislo >= kolko) {  out = out + Rimska;   cislo -= kolko;}

std::map<char, int> rmap = {
  { 'O', 0},
  { 'I', 1},
  { 'V', 5},
  { 'X', 10},
  { 'L', 50},
  { 'C', 100},
  { 'D', 500},
  { 'M', 1000},
  { 'P', 5000},
  { 'Q', 10000},
  { 'R', 50000},
  { 'S', 100000},
  { 'T', 500000},
  { 'U', 1000000},
  { 'W', 5000000},
  { 'Y', 10000000},
  { 'Z', 50000000},
  { 'E', 100000000},
  { 'F', 500000000},
  { 'G', 1000000000}
};


int checkRoman(string vyr){
    char last = 'A';
    int lastval = -1;
    int streak = 0;
    int actual;
    bool spcase =false;
    for(int i = 0 ; i<vyr.length(); i++){
      if ( last == vyr.at(i) ){ streak++ ;}
      else{ streak = 0; }
      if ( streak == 3 ) { return -1; }
      actual = rmap.at(vyr.at(i));
      
      if ( actual > lastval && lastval != -1){
	double ratio =  actual / lastval;
	if ( ratio == 5 || ratio == 10) { 
	  if (spcase == true){ return -1; }
	  spcase = true;
	  continue; 
	  }
	  else{ return -1; }
	}
      else { spcase = false;}
      
      last = vyr.at(i);
      lastval = actual;
    }
  return 0;
}

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
    bool got_first_letter = false;
    for(int i = 0; i< vyr.length(); i++){
        if (vyr.at(i)== ' ') {continue;} 
        
        if ( vyr.at(i) == '-'  && got_first_letter == false && zap_1 == false ){ zap_1 = true;  continue; } 	//chcecks - of  first argument
        if ( vyr.at(i) == '-'  && got_first_letter == false && zap_1 == true  ){ return ZLY_VYRAZ;  } 		// checks -- of first argument 
        if ( vyr.at(i) == '-'  && found_operator == true && zap_2 == false) {zap_2 = true;  continue; }		// checks - of  second argument
	if ( vyr.at(i) == '-'  &&  zap_2 == true  ){ return ZLY_VYRAZ;  } 					// chcecks -- of second argument  
	
        if (vyr.at(i) == '+'||  vyr.at(i) == '-' || vyr.at(i) == '/' || vyr.at(i) == '*' || vyr.at(i) == '>'  || vyr.at(i) == '<' || vyr.at(i) == '=' || vyr.at(i) == '&' || vyr.at(i) == '|'){
	    if (got_first_letter == false){return ZLY_VYRAZ;} 							// checks for existence of first argument
            if (found_operator == true){return ZLY_VYRAZ;}							// checks for double argument
            op = vyr.at(i);
            found_operator = true;
            continue;
            }
             
        if ( vyr.at(i) == 'I' || vyr.at(i) == 'V' || vyr.at(i) == 'X' || vyr.at(i) == 'L'  || vyr.at(i) == 'C'  || vyr.at(i) == 'D'  || vyr.at(i) == 'M' || vyr.at(i) == 'P' || vyr.at(i) == 'Q' || vyr.at(i) == 'R' || vyr.at(i) == 'S' || vyr.at(i) == 'T' || vyr.at(i) == 'U' || vyr.at(i) == 'W'|| vyr.at(i) == 'Y' || vyr.at(i) == 'Z'|| vyr.at(i) == 'E' || vyr.at(i) == 'F' || vyr.at(i) == 'G' || vyr.at(i)=='O' )  {
	    got_first_letter =true;
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
        if (op == 'N') {return ZLY_VYRAZ;}
        
    int check = checkRoman(vyr1);
    check += checkRoman(vyr2);
    if (check != 0) {return ZLY_VYRAZ;}
      
    if (found_operator == false){return ZLY_VYRAZ;}
    int cis1= konverziaRimskych(vyr1);
    if (zap_1 == true) {cis1 = -cis1; }
    int cis2=konverziaRimskych(vyr2);
    if (zap_2 == true) {cis2 = -cis2; }
    if (cis2 == 0 && op == '/'){ return CISLO_MIMO; }
    int result = kalkulackaArabska(op,cis1,cis2);
    string toret = konvertNaRimske(result);
  return toret;
}



int RIMSKA_KALKULACKA::konverziaRimskych(const string &rimskeCislo) {
  int acc = 0;
  int actual;
  int lastval = 0;
  for(int  i = 0; i<rimskeCislo.length(); i++){
    actual = rmap.at(rimskeCislo.at(i));
    acc+=actual;
    if( lastval < actual ){ acc -= 2*lastval;   }
    lastval = actual;
  }
  return acc;
}




string RIMSKA_KALKULACKA::konvertNaRimske(int cislo) {
  if(cislo<=-4000000000l || cislo>=4000000000l){
      return CISLO_MIMO;
  }

  string out = "";
  if (cislo == 0) {
    return "O";
  }
  
  if (cislo < 0){ 
    out = out +"-" ;
    cislo = cislo *-1;
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
    if(oper == '>'){ 
	if (op1 > op2) { return 1;}
	else 	{ return 0;}
	}
    if(oper == '<'){ 
	if (op1 < op2) { return 1;}
	else 	{ return 0;}
	}
    if(oper == '='){ 
	if (op1 == op2) { return 1;}
	else 	{ return 0;}
	}
	
    if(oper == '&'){ return 0 ;} // output should be 1 or 0 for any number, WTF?
    if(oper == '|'){ return 1 ;} // 
  return DUMMY_INT;
}
