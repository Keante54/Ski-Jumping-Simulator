#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"

#include <string>
#include <array>

class Jumper;
class Hill;
class Competition;

class JumpData
{
private:
    // dane skoczka
    int takeoffPower,
        takeoffTechnique, flightTechnique;
    int landType, landRating;
    int takeoffPowerDifference;

    // dane skoku
    double distance, points;
    std::array<double, 5> judges;
    double judgesPoints;
    double gateCompensation, windCompensation;
    double totalCompensation;
    bool dsq;
    std::string dsqReason;

    int gate, coachGate;
    bool isCoachGate;
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

    void resetJumpParams();

public:
    JumpData(Jumper *jumper_, Hill *hill_, Competition *competition_);
    JumpData();
    ~JumpData();

    enum LandType
    {
        Telemark = 1,
        Both,
        Propped,
        Fall
    };

    bool operator>(const JumpData &jumpData) const { return points > jumpData.points; }

    // dane skoczka
    int getTakeoffPower() const { return takeoffPower; }
    int getTakeoffTechnique() const { return takeoffTechnique; }
    int getFlightTechnique() const { return flightTechnique; }
    int getLandType() const { return landType; }
    int getLandRating() const { return landRating; }
    int getTakeoffPowerDifference() const { return takeoffPowerDifference; }
    int getGate() const { return gate; }
    int getCoachGate() const { return coachGate; }
    bool getIsCoachGate() const { return isCoachGate; }
    double getWind() const { return wind; }

    // dane skokus
    double getDistance() const { return distance; }
    double getPoints() const { return points; }
    const std::array<double, 5> & getJudges() const { return judges; }
    double getJudgesPoints() const { return judgesPoints; }
    double getGateCompensation() const { return gateCompensation; }
    double getWindCompensation() const { return windCompensation; }
    double getTotalCompensation() const { return totalCompensation; }
    bool getDsq() const { return dsq; }
    std::string getDsqReason() const { return dsqReason; }
    int getGateDifference() const;
    Jumper *getJumper() const { return jumper; }

    void setGate(int arg) { gate = arg; }
    void setCoachGate(int arg) { coachGate = arg; }
    void setIsCoachGate(bool arg) { isCoachGate = arg; }

    // symulacja skoku
    void setParameters(Jumper &jp, Hill &hl, Competition &comp);
    void jump();

    void showResults();
    void showResultsForSingleJump();
};