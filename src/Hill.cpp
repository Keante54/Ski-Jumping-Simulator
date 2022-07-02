#include "Hill.h"

int Hill::objectsCount = 0;

Hill::Hill()
{
    name = country = "";
    kPoint = hsPoint = maxDistance = maxDistanceRange = gatePoints = gateMeters = frontWindPoints = frontWindMeters = 0;
    backWindPoints = backWindMeters = pointsForKPoint = pointsForMeters = 0;
    startDistance = landingDifficulty = takeoffTechniqueMeters = flightTechniqueMeters = 0;
    optimalTakeoffPower = takeoffPowerImportance = 0;
    for (auto &fsm : flightStyleMeters)
        fsm = 0;
    objectsCount++;
}

Hill::Hill(std::string name_, std::string country_, int kPoint_, int hsPoint_, double maxDistance_, double gatePoints_, double frontWindPoints_, double startDistance_, double takeoffTechniqueMeters_, double flightTechniqueMeters_, int optimalTakeoffPower_, double takeoffPowerImportance_)
{
    name = name_;
    country = country_;
    kPoint = kPoint_;
    hsPoint = hsPoint_;
    maxDistance = maxDistance_;
    gatePoints = gatePoints_;
    frontWindPoints = frontWindPoints_;
    startDistance = startDistance_;
    takeoffTechniqueMeters = takeoffTechniqueMeters_;
    flightTechniqueMeters = flightTechniqueMeters_;
    optimalTakeoffPower = optimalTakeoffPower_;
    takeoffPowerImportance = takeoffPowerImportance_;
    objectsCount++;
}

Hill::Hill(const Hill &hill)
{
    objectsCount++;
}
Hill &Hill::operator=(const Hill &hill)
{
    objectsCount++;
    return *this;
}

Hill::~Hill()
{
    objectsCount--;
}

std::ostream &operator<<(std::ostream &os, const Hill &hill)
{
    os << hill.getName() << " K" << hill.getKPoint() << " HS" << hill.getHsPoint();
    return os;
}

void Hill::startup()
{
    pointsForKPoint = 60;
    if (kPoint <= 25)
        pointsForMeters = 4.8;
    else if (kPoint <= 30)
        pointsForMeters = 4.4;
    else if (kPoint <= 34)
        pointsForMeters = 4.;
    else if (kPoint <= 39)
        pointsForMeters = 3.6;
    else if (kPoint <= 49)
        pointsForMeters = 3.2;
    else if (kPoint <= 59)
        pointsForMeters = 2.8;
    else if (kPoint <= 69)
        pointsForMeters = 2.4;
    else if (kPoint <= 79)
        pointsForMeters = 2.2;
    else if (kPoint <= 99)
        pointsForMeters = 2.0;
    else if (kPoint <= 169)
        pointsForMeters = 1.8;
    else if (kPoint >= 170)
    {
        pointsForMeters = 1.2;
        pointsForKPoint = 120;
    }

    maxDistanceRange = (maxDistance - kPoint) / 23;
    judgeDivider = kPoint / 7;
    landingDifficulty = 180 / (kPoint * 1.02);
    flightStyleMeters[0] = (-13) - ((kPoint - 100) / 7);
    flightStyleMeters[1] = (15.5) - ((kPoint - 100) / 7.2);
    flightStyleMeters[2] = (14) - ((kPoint - 100) / 6);
    flightStyleMeters[3] = (13.2) - ((kPoint - 100) / 5.3);
    flightStyleMeters[4] = (12) - ((kPoint - 100) / 4.5);

    backWindPoints = frontWindPoints * 1.21;
}