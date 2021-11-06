#include "Hill.h"

void Hill::startup()
{
    pointsForK = 60;
    if (kpoint <= 25)
        metersPoints = 4.8;
    else if (kpoint <= 30)
        metersPoints = 4.4;
    else if (kpoint <= 34)
        metersPoints = 4;
    else if (kpoint <= 39)
        metersPoints = 3.6;
    else if (kpoint <= 49)
        metersPoints = 3.2;
    else if (kpoint <= 59)
        metersPoints = 2.8;
    else if (kpoint <= 69)
        metersPoints = 2.4;
    else if (kpoint <= 79)
        metersPoints = 2.2;
    else if (kpoint <= 99)
        metersPoints = 2.0;
    else if (kpoint <= 169)
        metersPoints = 1.8;
    else if (kpoint >= 170)
    {
        metersPoints = 1.2;
        pointsForK = 120;
    }

    maxdistRandom = (maxdist - kpoint) / 23;
    judgeDivider = (kpoint) / 7.42;
    landDifficulty = 155;
}

void Hill::setType()
{
    if (kpoint <= 0)
        type = "brak danych";
    if (kpoint <= 44)
        type = "mała";
    if (kpoint <= 74)
        type = "średnia";
    if (kpoint <= 99)
        type = "normalna";
    if (kpoint <= 169)
        type = "duża";
    else
        type = "mamucia";
}

void Hill::setStartGate()
{
    cout << "Belka startowa: ";
    cin >> startGate;
}

void Hill::showHideInfo()
{
    cout << "Przeliczniki za belke: " << (bool)gateComp << endl
         << "Przeliczniki za wiatr: " << (bool)windComp << endl
         << "Noty sędziowskie: " << (bool)isJudges << endl
         << "Zakres wiatru: " << typicalWind[0] << " - " << typicalWind[1] << endl
         << "Podstawowy wiatr: " << startWind << endl
         << "Falszywosc przeliczników: " << windFaulty << endl;
}

void Hill::showHillInfo()
{
    cout << name << " K" << kpoint << " "
         << " HS" << hspoint << endl;
    cout << "Punkty za belke (metry): " << gatePoints << " (" << gateMeters << ")" << endl;
    cout << "Punkty za wiatr tylni (metry): " << windPointsBack << "(" << windMetersBack << ")";
}