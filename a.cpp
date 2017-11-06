#include <iostream>
using namespace std;
#include <cmath>
#include <cassert>
#include <string.h>
//#include <tgmath>
//#include <math>
/*
 * SIMPLE:
 * FV = PV * (1+R)^T (ordinary)
 * PV = FV / (1+R)^T
 * r = (FV/PV)^(1/t) -1
 * t = ln(FV/PV) / ln(1+r)
 *
 * ANNUITY
 * PVA = (C / r) * (1-(1/(1+r)^t))
 * C = (PVA * r) / (1-(1/(1+r)^t))
 */

//CHECK:
// cpp maths, floating point and exponents

float calcFV(float pv, float r, int t){
   return (pv * std::pow((1+r), t));
}

float calcPV(float fv, float r, int t){
   return (fv / std::pow(1+r,t));
}

float calcRate(float fv, float pv, int t){
   return (std::pow((fv / pv), (1.0f/t)) - 1);
}

//float because we could either round up or down (context dependent)
float calcPeriod(float fv, float pv, float r){
   return log(fv/pv) / log(1+r);
}


/*
 * A N N U I T I E S
 */
float calcPVA(float c, float r, int t){
   return (c / r) * (1-(1/std::pow((1+r),t)));
}

//CA = Coupon payment of an Annuity
float calcCouponPVA(float pva, float r, int t){
   return (pva * r) / (1-(1/std::pow((1+r),t)));
}

float calcFVA(float c, float r, int t){
   return c * (std::pow((1+r),t)/r);
}

float calcCouponFVA(float fva, float r, int t){
   return (fva * r) / (std::pow((1+r),t) - 1);
}

float calcTAPVA(float pv, float c, float r){
   return log((c/(c-(r*pv)))) / log(1+r);
}

float calcTAFVA(float fv, float c, float r){
   return log(1+((r*fv)/c)) / log(1+r);
}

float calcEAR(float apr, int m){
   return std::pow((1+(apr/m)),m)-1;
}

float calcAPR(float ear, int m){
   return m * (std::pow((1+ear),1/m) -1);
}

//annuity due
float calcPVADue(float c, float r, int t){
   return (1+r) * c * ((1-(1/(std::pow(1+r,t))))/r);
}

float calcFVADue(float c, float r, int t){
   return (1+r) * c * ((std::pow(1+r,t) - 1)/r);
}

float calcTADuePVA(float pva, float c, float r){
   return log((c*(1+r))/(c*(1+r)-r*pva)) / log(1+r);
}

float calcTADueFVA(float fva, float c, float r){
   return log(1+((r*fva)/((1+r)*c)))/log(1+r);
}





//perpetuity

float calcPerpPV(float c, float r){
   return c/r;
}

float calcPerpRROR(float pv, float c){
   return (c / pv);
}

//growing perpetuity

float calcGPerpPV(float c, float r, float g){
   return (c/(r-g));
}

float calcGPerpRROR(float pv, float c, float g){
   return (c/pv)+g;
}

/** Runs tests for the calculator
 *
 * @return 0 if failed, 1 if successful
 */
int test(){

   try {

   cout << "Testing FV Calculator" << endl;
   assert(calcFV(1000.0f, 0.1f, 0) == 1000.0f);
   assert(calcFV(1000.0f, 0.1f, 1) == 1100.0f);
   assert( ((int) calcFV(1000.0f, 0.2f, 5)) == 2488);
   cout << "Done!" << endl;

   cout << "Testing PV Calculator" << endl;
   assert(calcPV(1000.0f, 0.1f, 0) == 1000.0f);
   assert(calcPV(1000.0f, 1.0f, 1) == 500.0f);
   assert(calcPV(1000.0f, 1.0f, 5) == 31.25f);
   cout << "Done!" << endl;

   cout << "Testing interest rate calculator" << endl;
   assert(calcRate(1000.0f, 1000.0f, 1) == 0.0f);
   assert(((int) calcRate(4000.0f, 1000.0f, 2)) == 1);
   //should be equivalent to 20.11%
   assert(((int)(calcRate(2500.0f, 1000.0f, 5) * 10000)) == 2011);  
   cout << "Done!" << endl;


   cout << "Tests completed successfully!" << endl;
   
   return 1;

   } catch(...){
      return 0;
   }
}

int main(int argc, char** argv){
   
   //if we have arguments
   if(argc > 1){
      for(int i=1;i<argc;i++){
         if(strcmp(argv[i],"-t") == 0){
            return test();
         }
      }
   }
   
   cout << "Starting GUI..." << endl;
   
}










