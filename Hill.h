#pragma once
#include <vector>
using namespace std;
//#include "Jumper.h"

class Hill
{
public:
    string name, country, type;
    double gatePoints, gateMeters;
    int kpoint, hspoint, pointsForK;
    double maxdist, maxdistRandom;
    double windMetersFront, windMetersBack, windPointsFront, windPointsBack;
    double metersPoints;
    double landDifficulty;
    double startDist, takeoffDist, flightDist, minWindChange, maxWindChange;
    int optimalSkisPosition;
    double skisPositionEffect;
    double takeoffTechniqueMeters, flightTechniqueMeters;
    int optimalTakeoffPower;
    double flightStyleMeters[5];
    double takeoffPowerImportance, judgeDivider;

    int startGate;
    double typicalWind[2], windChange, startWind, windFaulty, leaderPoints, sleepAfterJump;
    bool gateComp, windComp, isJudges, IsshowResults, autoWind;
    void setupJumpers();
    void setStartGate();
    void showHideInfo();
    void showHillInfo();
    void setLeaderPoints();

    //vector<Jumper> jumpers;

    void startup();
    void setType();
};