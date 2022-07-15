#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "JumpData.h"
#include "Random.h"

JumpData::JumpData(Jumper *jumper_, Hill *hill_, Competition *competition_)
{
    jumper = jumper_;
    hill = hill_;
    competition = competition_;
    takeoffPower = takeoffTechnique = flightTechnique = takeoffPowerDifference = 0;
    distance = points = gateCompensation = windCompensation = totalCompensation = dsq = judgesPoints = 0;
    for (auto &jg : judges)
    {
        jg = 0;
    }
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
    setGate(competition->getActualGate());
    setTakeoffPower();
    setTakeoffTechnique();
    setFlightTechnique();
    setDistance();
    land();
    setJudges();
    setDsq();
    setPoints();
}

void JumpData::setTakeoffPower()
{
    if (jumper->getTakeoffPowerSkill() > 120)
        jumper->setTakeoffPowerSkill(120);
    else if (jumper->getTakeoffPowerSkill() < 1)
        jumper->setTakeoffPowerSkill(1);

    takeoffPower = jumper->getTakeoffPowerSkill();
    takeoffPower += randomInt(-3, 3);
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
    takeoffTechnique += randomInt(-8, 10);
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
        flightTechnique += randomInt(-7, 7);
    else if (jumper->getFlightStyle() == 2)
        flightTechnique += randomInt(-8, 8);
    else if (jumper->getFlightStyle() == 3)
        flightTechnique += randomInt(-9, 9);
    else if (jumper->getFlightStyle() == 4)
        flightTechnique += randomInt(-10, 10);

    flightTechnique += randomInt(0, 5);
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

    rd = (landRating - 54);
    rd1 = (((hill->getMaxDistance() - distance) * 3.7) * hill->getLandingDifficulty()) + rd;
    if (rd1 < 2)
        rd1 = 2;

    rd2 = randomInt(1, rd1);

    if (rd2 == rd1)
        landType = Fall;
    else
    {
        rd = (landRating - 54);
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
            rd = (landRating - 54);
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

    totalCompensation = gateCompensation + windCompensation;

    if (points < 0)
        points = 0;
}

void JumpData::setDsq()
{
    if (competition->getType() == Competition::MultipleJumps)
    {
        int rd = randomInt(1, 120);
        if (rd == 1)
            dsq = true;
        else
            dsq = false;

        if (dsq == true)
        {
            resetJumpParams();
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
}

void JumpData::resetJumpParams()
{
    takeoffPower = takeoffTechnique = flightTechnique = landType = landRating = takeoffPowerDifference = 0;
    distance = points = judgesPoints = gateCompensation = windCompensation = totalCompensation = gate = wind = 0;
    for (auto &jg : judges)
        jg = 0;
}

void JumpData::showResults()
{
    if (!dsq)
    {
        using namespace std;
        cout << "\n\n"
             << jumper->getName() << " " << jumper->getSurname() << " (" << jumper->getNationality() << ")\n";
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
        cout << ")\n";
        cout << fixed << setprecision(1);
        cout << "Punkty: " << points << "\n";
        cout << setprecision(1);
        cout << "|";
        for (const auto &jg : judges)
        {
            cout << jg << "|";
        }
        cout << "\n";

        cout << fixed << setprecision(2);
        if (wind < 0)
        {
            cout << "Wiatr: ";
            colorText(12, wind);
        }
        else if (wind > 0)
        {
            cout << "Wiatr: ";
            colorText(10, wind);
        }
        else
        {
            cout << "Wiatr: ";
            colorText(7, wind);
        }
        cout << "\n";
        cout << fixed << setprecision(1);
        if (gateCompensation < 0)
        {
            cout << "Punkty za belk©: ";
            colorText(12, gateCompensation);
        }
        else if (gateCompensation > 0)
        {
            cout << "Punkty za belk©: ";
            colorText(10, gateCompensation);
        }
        else
        {
            cout << "Punkty za belk©: ";
            colorText(7, gateCompensation);
        }
        cout << "\n";
        cout << fixed << setprecision(1);
        if (windCompensation < 0)
        {
            cout << "Punkty za wiatr: ";
            colorText(12, windCompensation);
        }
        else if (windCompensation > 0)
        {
            cout << "Punkty za wiatr: ";
            colorText(10, windCompensation);
        }
        else
        {
            cout << "Punkty za wiatr: ";
            colorText(7, windCompensation);
        }
        cout << "\n";
        cout << fixed << setprecision(1);
        if (totalCompensation < 0)
        {
            cout << "¥cznie: ";
            colorText(12, totalCompensation);
        }
        else if (totalCompensation > 0)
        {
            cout << "¥cznie: ";
            colorText(10, totalCompensation);
        }
        else
        {
            cout << "¥cznie: ";
            colorText(7, totalCompensation);
        }
        cout << fixed << "\n";

        cout << "Skok zakoäczony: ";
        if (landType == 1)
            colorText(11, "telemarkiem");
        else if (landType == 2)
            colorText(3, "l¥dowaniem na dwie nogi");
        else if (landType == 3)
            colorText(5, "podp¢rk¥");
        else if (landType == 4)
            colorText(12, "upadkiem");
        cout << "\n";
    }
    else
    {
        colorText(12, "\nDyskwalifikacja!!!");
        colorText(15, ", Pow¢d: ");
        colorText(13, dsqReason);
        std::cout<<"\n";
    }
}

int JumpData::getGateDifference() const { return competition->getStartGate() - gate; }

void JumpData::showResultsForSingleJump()
{
    using std::cout;
    using std::fixed;
    using std::setprecision;

    colorText(7, jumper->getName() + " " + jumper->getSurname() + " (" + jumper->getNationality() + ")");
    colorText(15, " --> ");
    cout << fixed << setprecision(1);
    colorText(3, getDistance());
    colorText(3, "m");
    cout << " (";
    cout << fixed << setprecision(1);
    colorText(6, getPoints());
    colorText(6, "pkt");
    cout << ")";
    colorText(15, " --> ");
    if (competition->getIsJudges())
    {
        colorText(7, "|");
        for (const auto &jg : judges)
        {
            colorText(12, jg);
            colorText(7, "|");
        }
        colorText(15, ", ");
    }
    cout << fixed << setprecision(2);
    colorText(2, getWind());
    colorText(2, "m/s");
    colorText(7, ", ");

    if (competition->getIsWindComp() || competition->getIsGateComp())
    {
        cout << fixed << setprecision(1);
        colorText(7, "Rekompensata: ");
        colorText(5, getWindCompensation());
        cout << "\n";
    }
    else
        cout << "\n";
}