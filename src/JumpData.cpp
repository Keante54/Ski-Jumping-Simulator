#include <math.h>
#include <string>
#include <iostream>
#include "JumpData.h"
#include "Random.h"

JumpData::JumpData(Jumper *jumper_, Hill *hill_, Competition *competition_)
{
    jumper = jumper_;
    hill = hill_;
    competition = competition_;
}

JumpData::JumpData()
{
    jumper = nullptr;
    hill = nullptr;
    competition = nullptr;
    takeoffPower = takeoffTechnique = flightTechnique = takeoffPowerDifference = 0;
    distance = points = gateCompensation = windCompensation = totalCompensation = dsq = judgesPoints = 0;
    for (auto &jg : judges)
    {
        jg = 0;
    }
}

JumpData::~JumpData()
{
}

void JumpData::setParameters(Jumper &jp, Hill &hl, Competition &comp)
{
    jumper = &jp;
    hill = &hl;
    competition = &comp;
}

void JumpData::jump()
{
    hill->startup();
    setWind();
    setGate(competition->getStartGate());
    setTakeoffPower();
    setTakeoffTechnique();
    setFlightTechnique();
    setDistance();
    land();
    setJudges();
    setPoints();
    //setDsq();
}

void JumpData::setTakeoffPower()
{
    if (jumper->getTakeoffPowerSkill() > 120)
        jumper->setTakeoffPowerSkill(120);
    else if (jumper->getTakeoffPowerSkill() < 1)
        jumper->setTakeoffPowerSkill(1);

    takeoffPower = jumper->getTakeoffPowerSkill();
    takeoffPower += randomInt(-2, 3);
    takeoffPower = round(takeoffPower);

    if (takeoffPower > 160)
        takeoffPower = 160;
    else if (takeoffPower < 1)
        takeoffPower = 1;
}

void JumpData::setTakeoffTechnique()
{
    if (jumper->getTakeoffTechniqueSkill() > 120)
        jumper->setTakeoffPowerSkill(120);
    else if (jumper->getTakeoffTechniqueSkill() < 1)
        jumper->setTakeoffTechniqueSkill(1);

    takeoffTechnique = (jumper->getTakeoffTechniqueSkill() * 0.88) + (jumper->getForm() * 1.12);
    takeoffTechnique += randomInt(-4, 8);
    takeoffTechnique = round(takeoffTechnique);

    if (takeoffTechnique > 280)
        takeoffTechnique = 280;
    else if (takeoffTechnique < 1)
        takeoffTechnique = 1;
}

void JumpData::setFlightTechnique()
{
    if (jumper->getFlightTechniqueSkill() > 120)
        jumper->setFlightTechniqueSkill(120);
    else if (jumper->getFlightTechniqueSkill() < 1)
        jumper->setFlightTechniqueSkill(1);

    flightTechnique = (jumper->getFlightTechniqueSkill() * 0.80) + (jumper->getForm() * 1.19);

    if (jumper->getFlightStyle() == 0)
        flightTechnique += randomInt(-30, -23);
    else if (jumper->getFlightStyle() == 1)
        flightTechnique += randomInt(-5, 5);
    else if (jumper->getFlightStyle() == 2)
        flightTechnique += randomInt(-6, 6);
    else if (jumper->getFlightStyle() == 3)
        flightTechnique += randomInt(-7, 7);
    else if (jumper->getFlightStyle() == 4)
        flightTechnique += randomInt(-8, 8);

    flightTechnique += randomInt(0, 6);
    flightTechnique = round(flightTechnique);
    if (flightTechnique > 280)
        flightTechnique = 280;
    else if (flightTechnique < 1)
        flightTechnique = 1;
}

void JumpData::setWind()
{
    wind = competition->getStartWind();
    wind += normalRandom(0, competition->getWindChange());
    wind += normalRandom(0, competition->getWindFaulty());
}

void JumpData::setDistance()
{
    distance = hill->getStartDistance();
    distance += gate * hill->getGateMeters();

    if (wind > 0)
        distance += (wind * hill->getFrontWindMeters());
    else if (wind < 0)
        distance += (wind * hill->getBackWindMeters());

    distance -= abs(hill->getOptimalTakeoffPower() - takeoffPower) * hill->getTakeoffPowerImportance();
    distance += takeoffTechnique * hill->getTakeoffTechniqueMeters();
    distance += flightTechnique * hill->getFlightTechniqueMeters();

    for (int i = 0; i < 5; i++)
        if (jumper->getFlightStyle() == i)
            distance += hill->getFlightStyleMeters(i);

    if (distance > hill->getMaxDistance())
        distance = hill->getMaxDistance() + normalRandom(0, hill->getMaxDistanceRange());
    distance = round(distance * 2) / 2;
}

void JumpData::land()
{
    int rd, rd1, rd2;

    landRating = (jumper->getLandingSkill() * 1.2) + normalRandom(0, 5);
    if (landRating > 80)
        landRating = 80;
    else if (landRating < 1)
        landRating = 1;

    rd = (landRating - 65);
    rd1 = (((hill->getMaxDistance() - distance) * 3.7) * hill->getLandingDifficulty()) + rd;
    if (rd1 < 2)
        rd1 = 2;

    rd2 = randomInt(1, rd1);

    if (rd2 == rd1)
        landType = Fall;
    else
    {
        rd = (landRating - 65);
        rd1 = (((hill->getMaxDistance() - distance) * 3.7) * hill->getLandingDifficulty()) + rd;
        if (rd1 < 2)
            rd1 = 2;

        rd2 = randomInt(1, rd1);

        if (rd2 == rd1)
        {
            landType = Propped;
        }
        else
        {
            rd = (landRating - 64);
            rd1 = (((hill->getMaxDistance() - distance) * 1.92) * hill->getLandingDifficulty()) + rd;
            if (rd1 < 2)
                rd1 = 2;

            rd2 = randomInt(1, rd1);

            if (rd2 == rd1)
            {
                landType = Both;
            }
            else
                landType = Telemark;
        }
    }
}

void JumpData::setJudges()
{
    double judgeRating = 15.6;
    judgeRating += jumper->getLandingSkill() / 20;
    judgeRating += (distance - hill->getKPoint()) / hill->getJudgeDivider();

    if (landType == Telemark)
        judgeRating += normalRandom(-0.5, 0.5);
    else if (landType == Both)
        judgeRating -= (2 + normalRandom(-0.5, 0.5));
    else if (landType == Propped)
        judgeRating -= (7 + normalRandom(-0.5, 0.5));
    else if (landType == Fall)
        judgeRating -= (9 + normalRandom(-0.5, 0.5));

    judgeRating = round(judgeRating * 2) / 2;

    for (auto &jg : judges)
    {
        int rd = randomInt(1, 5);
        jg = judgeRating;

        if (rd == 1)
            jg += (-0.5);
        else if (rd == 5)
            jg += (0.5);

        rd = randomInt(1, 20);
        if (rd == 1)
            jg += (-1);
        else if (rd == 2)
            jg += (1);

        // if (jg > 20)
        // jg = 20;

        // else if (jg < 1)
        //   jg = 1;
    }
    double minJudge = judges[0];
    double maxJudge = judges[0];
    for (auto const &jg : judges)
    {
        if (jg < minJudge)
            minJudge = jg;
        if (jg > maxJudge)
            maxJudge = jg;
    }
    for (auto const &jg : judges)
    {
        judgesPoints += jg;
    }
    judgesPoints -= (minJudge + maxJudge);
}

void JumpData::setPoints()
{
    if (competition->getIsWindComp() == true)
    {
        if (wind < 0)
            windCompensation = -wind * hill->getBackWindPoints();
        else if (wind > 0)
            windCompensation = -wind * hill->getFrontWindPoints();
        else if (wind == 0)
            windCompensation = 0;
    }
    if (competition->getIsGateComp() == true)
        gateCompensation = getGateDifference() * hill->getGatePoints();

    points = hill->getPointsForKPoint() + (hill->getPointsForMeters() * (distance - hill->getKPoint()));

    if (competition->getIsJudges() == true)
        points += judgesPoints;
    if (competition->getIsGateComp() == true)
        points += gateCompensation;
    if (competition->getIsWindComp() == true)
        points += windCompensation;

    if (points < 0)
        points = 0;
}

void JumpData::setDsq()
{
    int rd = randomInt(1, 130);
    if (rd == 1)
        dsq = true;
    else
        dsq = false;

    if (dsq == true)
    {
        *this = JumpData();
        rd = randomInt(1, 15);

        if (rd >= 1 && rd <= 2)
            dsqReason = "Za krotkie narty";
        else if (rd >= 3 && rd <= 4)
            dsqReason = "Za dlugie narty";
        else if (rd >= 5 || rd <= 11)
            dsqReason = "Kombinezon";
        else if (rd == 12)
            dsqReason = "Za szybkie wystartowanie";
        else if (rd == 13)
            dsqReason = "Za pozne wystartowanie";
        else if (rd >= 14 || rd <= 15)
            dsqReason = "Buty";
    }
}

void JumpData::showResults()
{
    using namespace std;
    cout << jumper->getName() << " " << jumper->getSurname() << " (" << jumper->getNationality() << ")\n";
    cout << "Odlegˆo˜†: " << distance;
    cout << " (Belka: " << gate << ") (";
    if ((-getGateDifference()) > 0)
    {
        colorText(2, "+");
        colorText(2, to_string(-getGateDifference()));
    }
    if ((-getGateDifference()) == 0)
    {
        colorText(7, "+0");
    }
    if ((-getGateDifference()) < 0)
    {
        colorText(4, to_string(-getGateDifference()));
    }
    cout << ")\n|";

    for (const auto &jg : judges)
    {
        cout << jg << "|";
    }
    cout << "\n";
}

int JumpData::getGateDifference() const { return competition->getStartGate() - gate; }
