#pragma once
#include <iostream>
#include "Hill.h"
using namespace std;

struct Injury
{
    string name;
    short chance;
};

class Jumper
{
public:
    string name, surname, nationality;
    int takeoffPowerS, takeoffTechniqueS;
    int takeoffPower, takeoffTechnique;
    int flightStyle;
    int flightTechniqueS, flightTechnique;
    int landSkill, landType;
    double landRating, takeoffPowerDiff;
    int form;
    int gate, gateDiff;
    double distance, toBeat;
    double judges[5], minJudge, maxJudge, wind, windB, windBonus, judgeRating, judgesPoints, judgesAll;
    double points, compensationGate, compensationWind;
    bool dsq;
    string dsqReason;
    int importance;
    int position;
    Hill hill;

    Injury injury;
    vector <Injury> injList;

    void setup();
    void setTakeoffPower();
    void setTakeoffTechnique();
    void setFlightTechnique();
    void setGateAndWindMeters();
    void setPoints();
    void land();
    void showResult();
    void showHideInfo();
    void showDistanceAndToBeat();
    void basicDistance();
    void setToBeat();
    void jump();
    void setHill(Hill &h);
    void saveToTxt(string filename);
    void saveToCsv(string filename);
    void setDsq();
};