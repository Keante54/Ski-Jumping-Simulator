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
    judgeDivider = (kpoint) / 7;
    landDifficulty = 180 / (kpoint * 1.02);
    flightStyleMeters[0] = -13 - ((kpoint - 100) / 7);
    flightStyleMeters[1] = 15.5 + ((kpoint - 100) / 7.2);
    flightStyleMeters[2] = 14 + ((kpoint - 100) / 6);
    flightStyleMeters[3] = 13.2 + ((kpoint - 100) / 5.3);
    flightStyleMeters[4] = 12 + ((kpoint - 100) / 4.5);

    windMetersFront = windPointsFront / metersPoints;
    windPointsBack = percent(121, windPointsFront);
    windMetersBack = windPointsBack / metersPoints;
    gateMeters= gatePoints / metersPoints;

}
