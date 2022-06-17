#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"

#include <string>

class Jumper;
class Hill;
class Competition;

class JumpData
{
private:
    enum LandType
    {
        Telemark = 1,
        Both,
        Propped,
        Fall
    };
    // dane skoczka
    int takeoffPower,
        takeoffTechnique, flightTechnique;
    int landType, landRating;
    int takeoffPowerDifference;

    // dane skoku
    double distance, points;
    double judges[5], judgesPoints;
    double gateCompensation, windCompensation;
    double totalCompensation;
    bool dsq;
    std::string dsqReason;

    int gate;
    double wind;

    // wska«niki na parametry skoku
    Jumper *jumper;
    Hill *hill;
    Competition *competition;

    // symulacja skoku
    void setTakeoffPower();
    void setTakeoffTechnique();
    void setFlightTechnique();
    void setWind();
    void setDistance();
    void land();
    void setJudges();
    void setPoints();
    void setDsq();

public:
    JumpData(Jumper *jumper_, Hill *hill_, Competition *competition_);
    JumpData();
    ~JumpData();

    bool operator>(const JumpData &jumpData) const { return points > jumpData.points; }
    bool operator<(const JumpData &jumpData) const { return points < jumpData.points; }

    // dane skoczka
    int getTakeoffPower() const { return takeoffPower; }
    int getTakeoffTechnique() const { return takeoffTechnique; }
    int getFlightTechnique() const { return flightTechnique; }
    int getLandType() const { return landType; }
    int getLandRating() const { return landRating; }
    int getTakeoffPowerDifference() const { return takeoffPowerDifference; }
    int getGate() const { return gate; }
    double getWind() const { return wind; }

    // dane skoku
    double getDistance() const { return distance; }
    double getPoints() const { return points; }
    double getJudges(const int &n) const { return judges[n]; }
    double getJudgesPoints() const { return judgesPoints; }
    double getGateCompensation() const { return gateCompensation; }
    double getWindCompensation() const { return windCompensation; }
    double getTotalCompensatin() const { return totalCompensation; }
    bool getDsq() const { return dsq; }
    std::string getDsqReason() const { return dsqReason; }
    int getGateDifference() const;
    Jumper *getJumper() const { return jumper; }

    void setGate(const int &arg) { gate = arg; }

    // symulacja skoku
    void setParameters(Jumper &jp, Hill &hl, Competition &comp);
    void jump();

    void showResults();
};