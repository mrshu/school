#include <iostream>
#include <sstream>
#include<map>
using namespace std;

//#include "riesenie.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

#define odcitaj(kolko,Rimska,out) for (int ts = kolko; cislo >= ts; cislo -= kolko) {out = out + Rimska;}

#define special(kolko,Rimska,out)   if (cislo >= kolko) {  out = out + Rimska;   cislo -= kolko;}

std::map<char, int> rmap ;

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
      if (actual == 0 && vyr.length() != 1){return -1;}
      if ( vyr.at(i) == last){
	if ( last == 'V'|| last == 'L' || last == 'D' || last == 'P' || last == 'R' || last == 'T' || last == 'W' || last == 'Z' || last == 'F'){return -1;}
      } 
	
       if (spcase == true){
	int min2val = rmap.at(vyr.at(i-2));
	if (min2val<=actual) {return -1;} 
      }
      
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
  long long int konverziaRimskych(const string &rimskeCislo);
  string konvertNaRimske( long long int cislo);
  long long int kalkulackaArabska(char oper, long long int op1, long long int op2);
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
    rmap.insert ( std::pair<char,int>('O',0) );
    rmap.insert ( std::pair<char,int>('I',1) );
    rmap.insert ( std::pair<char,int>('V',5) );
    rmap.insert ( std::pair<char,int>('X',10) );
    rmap.insert ( std::pair<char,int>('L',50) );
    rmap.insert ( std::pair<char,int>('C',100) );
    rmap.insert ( std::pair<char,int>('D',500) );
    rmap.insert ( std::pair<char,int>('M',1000) );
    rmap.insert ( std::pair<char,int>('P',5000) );
    rmap.insert ( std::pair<char,int>('Q',10000) );
    rmap.insert ( std::pair<char,int>('R',50000) );
    rmap.insert ( std::pair<char,int>('S',100000) );
    rmap.insert ( std::pair<char,int>('T',500000) );
    rmap.insert ( std::pair<char,int>('U',1000000) );
    rmap.insert ( std::pair<char,int>('W',5000000) );
    rmap.insert ( std::pair<char,int>('Y',10000000) );
    rmap.insert ( std::pair<char,int>('Z',50000000) );
    rmap.insert ( std::pair<char,int>('E',100000000) );
    rmap.insert ( std::pair<char,int>('F',500000000) );
    rmap.insert ( std::pair<char,int>('G',1000000000) );
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
        if ( vyr.at(i) == '-'  && found_operator == true && zap_2 == false && vyr2=="") {zap_2 = true;  continue; }		// checks - of  second argument
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
        if (vyr2=="" ){return ZLY_VYRAZ;}
    int check = checkRoman(vyr1);
    check += checkRoman(vyr2);
    if (check != 0) {return ZLY_VYRAZ;}
      
    if (found_operator == false){return ZLY_VYRAZ;}
    long long int cis1= konverziaRimskych(vyr1);
    if (zap_1 == true) {cis1 = -cis1; }
    long long int cis2=konverziaRimskych(vyr2);
    if (zap_2 == true) {cis2 = -cis2; }
    if (cis2 == 0 && op == '/'){ return CISLO_MIMO; }
    long long int result = kalkulackaArabska(op,cis1,cis2);
    string toret = konvertNaRimske(result);
  return toret;
}



long long int RIMSKA_KALKULACKA::konverziaRimskych(const string &rimskeCislo) {
  long long int acc = 0;
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




string RIMSKA_KALKULACKA::konvertNaRimske( long long int cislo) {
  if(cislo<=-4000000000ll || cislo>=4000000000ll){
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


 long long int RIMSKA_KALKULACKA::kalkulackaArabska(char oper, long long int op1,long long int op2) {
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
	
    if(oper == '&'){ 
      if (op1 > 0 && op2 > 0){ return 1; }
      else { return 0; }
    } 
    if(oper == '|'){
      if (op1 > 0 || op2 > 1){ return 1; }
      else { return 0; }
    }
  return DUMMY_INT;
}
