#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"

#include <string>
#include <array>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>

class Jumper;
class Hill;
class Competition;

class JumpData
{
private:
    int ID;
    static int objectsCount;
    void setID() { ID = objectsCount - 1; }

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
    std::array<double, 5> judges;
    double judgesPoints;
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
    int jumperID;
    int hillID;
    int competitionID;

    void setJumperID() { jumperID = jumper->getID(); }
    void setHillID();
    void setCompetitionID();

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
    JumpData(const JumpData &jumpData);
     JumpData & operator=(const JumpData &jumpData);
    ~JumpData();

    bool operator>(const JumpData &jumpData) const { return points > jumpData.points; }

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
    double getTotalCompensation() const { return totalCompensation; }
    bool getDsq() const { return dsq; }
    std::string getDsqReason() const { return dsqReason; }
    int getGateDifference() const;
    Jumper *getJumper() const { return jumper; }

    void setGate(const int &arg) { gate = arg; }

    // symulacja skoku
    void setParameters(Jumper &jp, Hill &hl, Competition &comp);
    void jump();

    void showResults();

    private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar &ID;
            ar &takeoffPower;
            ar &takeoffTechnique;
            ar &flightTechnique;
            ar &landType;
            ar &landRating;
            ar &takeoffPowerDifference;
            ar &distance;
            ar &points;
            ar &judges;
            ar &judgesPoints;
            ar &gateCompensation;
            ar &windCompensation;
            ar &totalCompensation;
            ar &jumperID;
            ar &hillID;
            ar &competitionID;
            ar &dsq;
            ar &dsqReason;
            ar &gate;
            ar &wind;
        }
};