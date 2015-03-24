#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#include "UnitTest++/src/UnitTest++.h"

#include "AAA_riesenie.h"

namespace {
 RIMSKA_KALKULACKA kalkulacka;

 SUITE(Testy_RimskaKalkulacka) {
	TEST(test_ZakladnyVypocet_1) {
		CHECK_EQUAL("II", kalkulacka.kalkulackaRimska("I + I"));
	}
 }

 SUITE(Testy_RozsirenaRimskaKalkulacka) {
	TEST(test_RozsirenaRimskaKalkulacka_1) {
		CHECK_EQUAL("MP", kalkulacka.kalkulackaRimska("MMM + M"));
	}
 }

 SUITE(Testy_CisloMimo) {
	TEST(test_CisloMimo_1) {
		CHECK_EQUAL(CISLO_MIMO, kalkulacka.kalkulackaRimska("MMDC/O"));
	}
 }

 SUITE(Testy_ZlyVyraz) {
	TEST(test_ZlyVyraz_1) {
		CHECK_EQUAL(ZLY_VYRAZ, kalkulacka.kalkulackaRimska("MMDC-*MD"));
	}
 }
}