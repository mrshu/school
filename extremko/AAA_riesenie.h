#ifndef _RIESENIE_H_
#define _RIESENIE_H_
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

