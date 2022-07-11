#pragma once
#include <string>
#include <iostream>

class Hill
{
private:

    std::string name, country;
    int kPoint, hsPoint;

    double maxDistance, maxDistanceRange;

    double gatePoints, gateMeters;
    double frontWindPoints, frontWindMeters, backWindPoints, backWindMeters;
    double pointsForKPoint, pointsForMeters;

    double startDistance;
    double landingDifficulty;

    double takeoffTechniqueMeters, flightTechniqueMeters;
    int optimalTakeoffPower;
    double takeoffPowerImportance;
    double flightStyleMeters[5];
    int judgeDivider;

public:
    Hill(std::string name_, std::string country_, int kPoint_, int hsPoint_, double maxDistance_, double gatePoints_, double frontWindPoints_, double startDistance_, double takeoffTechniqueMeters_, double flightTechniqueMeters_, int optimalTakeoffPower_, double takeoffPowerImportance_);
    Hill();
    ~Hill();

    friend std::ostream &operator<<(std::ostream &os, const Hill &hill);

    void startup();

    std::string getName() const { return name; }
    std::string getCountry() const { return country; }
    int getKPoint() const { return kPoint; }
    int getHsPoint() const { return hsPoint; }
    double getMaxDistance() const { return maxDistance; }
    double getMaxDistanceRange() const { return maxDistanceRange; }
    double getGatePoints() const { return gatePoints; }
    double getGateMeters() const { return gatePoints / pointsForMeters; }
    double getFrontWindPoints() const { return frontWindPoints; }
    double getFrontWindMeters() const { return frontWindPoints / pointsForMeters; }
    double getBackWindPoints() const { return backWindPoints; }
    double getBackWindMeters() const { return backWindPoints / pointsForMeters; }
    double getPointsForKPoint() const { return pointsForKPoint; }
    double getPointsForMeters() const { return pointsForMeters; }
    double getStartDistance() const { return startDistance; }
    int getLandingDifficulty() const { return landingDifficulty; }
    double getTakeoffTechniqueMeters() const { return takeoffTechniqueMeters; }
    double getFlightTechniqueMeters() const { return flightTechniqueMeters; }
    int getOptimalTakeoffPower() const { return optimalTakeoffPower; }
    double getTakeoffPowerImportance() const { return takeoffPowerImportance; }
    double getFlightStyleMeters(const int &n) const { return flightStyleMeters[n]; }
    int getJudgeDivider() const { return judgeDivider; }
};