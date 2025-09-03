#include "main.h"

using namespace robos;

PID::PID(double KP, double KI, double KD, double ISTART){

    this->KP = KP;

    this->KI = KI;

    this->KD = KD;

    this->ISTART = ISTART;
}

void PID::Reset(){

    Intergral = 0;

    LastError = 0;

}

double PID::Compute(double Error){

    const double Derivative = Error - LastError;

    Intergral += Error;

    if(sign(Error) != sign(LastError)){

        Intergral = 0;

    }

    LastError = Error;

    return Error * KP + Derivative * KD + Intergral * KI;

}

