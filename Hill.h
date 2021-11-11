#pragma once
#include <vector>
using namespace std;
#include <iomanip>

class Hill
{
public:
    string name, country;
    double gatePoints, gateMeters;
    int kpoint, hspoint, pointsForK;
    double maxdist, maxdistRandom;
    double windMetersFront, windMetersBack, windPointsFront, windPointsBack;
    double metersPoints;
    double landDifficulty;
    double startDist, takeoffDist, flightDist, minWindChange, maxWindChange;
    double takeoffTechniqueMeters, flightTechniqueMeters;
    int optimalTakeoffPower;
    double flightStyleMeters[5];
    double takeoffPowerImportance, judgeDivider;

    int startGate;
    double typicalWind[2], windChange, startWind, windFaulty, leaderPoints, sleepAfterJump;
    bool gateComp, windComp, isJudges, IsshowResults, autoWind;
    void startup();
};