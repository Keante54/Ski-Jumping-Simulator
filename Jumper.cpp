#include "Jumper.h"
#include "other.h"

void Jumper::setup()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    colorText(15, name + " " + surname + " (" + nationality + ")\n");
    SetConsoleTextAttribute(hcon, 7);
}

void Jumper::jump()
{
    hill.startup();

    wind += normalRandom(0, hill.windChange);
    windB = wind + normalRandom(0, hill.windFaulty);

    setTakeoffPower();
    setTakeoffTechnique();
    setFlightTechnique();
    setGateAndWindMeters();

    int rd;

    if (flightStyle > 4)
        flightStyle = 2;

    takeoffPowerDiff = (takeoffPower - hill.optimalTakeoffPower);

    if (takeoffPowerDiff < 0)
        (takeoffPowerDiff *= 0.6456);
    else
        takeoffPowerDiff *= 0.44;

    takeoffPowerDiff = round(takeoffPowerDiff);

    basicDistance();
    land();
    setPoints();
    setToBeat();
}

void Jumper::setTakeoffPower()
{
    if (takeoffPowerS > 120)
        takeoffPowerS = 120;
    if (takeoffPowerS < 1)
        takeoffPowerS = 1;

    takeoffPower = (takeoffPowerS);
    takeoffPower += normalRandom(0, 4);
    takeoffPower = round(takeoffPower);
    if (takeoffPower > 160)
        takeoffPower = 160;
    else if (takeoffPower < 1)
        takeoffPower = 1;
}
void Jumper::setTakeoffTechnique()
{
    if (takeoffTechniqueS > 120)
        takeoffTechniqueS = 120;
    if (takeoffTechniqueS < 1)
        takeoffTechniqueS = 1;

    takeoffTechnique = (takeoffTechniqueS * 0.980) + (form * 1.057);
    takeoffTechnique += normalRandom(0, 6);
    takeoffTechnique = round(takeoffTechnique);
    if (takeoffTechnique > 280)
        takeoffTechnique = 280;
    if (takeoffTechnique < 1)
        takeoffTechnique = 1;
}

void Jumper::setFlightTechnique()
{
    if (flightTechniqueS > 120)
        flightTechniqueS = 120;
    if (flightTechniqueS < 1)
        flightTechniqueS = 1;

    flightTechnique = (flightTechniqueS * 0.875) + (form * 1.162);
    if (flightStyle == 0)
        flightTechnique += randomInt(-17, -9);
    else if (flightStyle == 1)
        flightTechnique += randomInt(-2.5, 2.5);
    else if (flightStyle == 2)
        flightTechnique += randomInt(-3.2, 3.2);
    else if (flightStyle == 3)
        flightTechnique += randomInt(-4, 4);
    else if (flightStyle == 4)
        flightTechnique += randomInt(-4.8, 4.8);

    flightTechnique += normalRandom(0, 6);
    flightTechnique = round(flightTechnique);
    if (flightTechnique > 280)
        flightTechnique = 280;
    if (flightTechnique < 1)
        flightTechnique = 1;
}

void Jumper::setGateAndWindMeters()
{
    if (hill.gateMeters == (-1))
    {
        hill.gateMeters = (hill.gatePoints / hill.metersPoints);
        hill.gateMeters *= 0.97;
    }
    if (hill.windMetersBack == (-1))
    {
        hill.windMetersBack = (hill.windMetersBack / hill.metersPoints);
        hill.windMetersBack *= 1.17;
    }
    if (hill.windMetersFront == (-1))
    {
        hill.windMetersFront = (hill.windMetersFront / hill.metersPoints);
        hill.windMetersFront *= 1.04;
    }
}

void Jumper::setPoints()
{
    if (hill.windComp == 1)
    {
        if (windB < 0)
            compensationWind = -windB * hill.windPointsBack;
        else if (windB > 0)
            compensationWind = -windB * hill.windPointsFront;
    }
    if (hill.gateComp == 1)
        compensationGate = (gateDiff)*hill.gatePoints;

    points = (hill.pointsForK + (hill.metersPoints * (distance - hill.kpoint)));
    if (hill.isJudges == 1)
        points += judgesAll;
    if (hill.gateComp == 1)
        points += compensationGate;
    if (hill.windComp == 1)
        points += compensationWind;

    if (points < 0)
        points = 0;
}

void Jumper::land()
{
    int rd, rd1;

    landRating = landSkill + (form / 12) + (landSkill / 25);
    landRating += normalRandom(0, 3);

    if (landRating > 80)
        landRating = 80;
    else if (landRating < 1)
        landRating = 1;

    judgeRating = 15;
    judgeRating += landSkill / 35;
    judgeRating += landSkill / 25;
    judgeRating += ((distance - hill.kpoint) / hill.judgeDivider);

    judgeRating = (round(judgeRating) * 2) / 2;

    rd = randomInt(0, 100000);
    rd1 = 80000 - (landRating * 350);
    rd1 += ((distance - hill.maxdist) * hill.landDifficulty * 15);

    // cout << "rd1: " << rd1 << endl;
    // getch();
    if (rd < rd1)
    {
        landType = 4;
        judgeRating -= (9 + (randomInt(1, 1) / 2));
    }
    else
    {
        rd = randomInt(1, 100000);
        rd1 = 60000 - (landRating * 350); // - (expernice * 300);
        rd1 += ((distance - hill.maxdist) * hill.landDifficulty * 15);
        // cout << "rd1: " << rd1 << endl;
        // getch();
        if (rd < rd1)
        {
            landType = 3;
            judgeRating -= (7 + (randomInt(1, 1) / 2));
        }
        else
        {
            rd = randomInt(1, 100000);
            rd1 = 100000 - (landRating * 460); // - (expernice * 300);
            rd1 += ((distance - hill.maxdist) * hill.landDifficulty * 17);

            // cout << "rd1: " << rd1 << endl;
            // getch();
            if (rd < rd1)
            {
                landType = 2;
                judgeRating -= randomInt(1, 2);
                rd = randomInt(1, 30);
                if (rd == 1)
                    judgeRating -= 1;
                else
                {
                    landType = 2;
                    judgeRating -= (randomInt(-1, 1) / 2);
                }
            }
            else
                landType = 1;
        }
    }
    if (hill.isJudges == 1)
    {
        for (auto &jdg : judges)
        {
            jdg = judgeRating;
            rd = randomInt(1, 5);
            if (rd == 1)
                jdg += (-0.5);
            if (rd == 2 || rd == 3 || rd == 4)
                jdg += (0);
            if (rd == 5)
                jdg += (0.5);

            rd = (randomInt(1, 20));
            if (rd == 1)
                jdg += (-1);
            if (rd == 2)
                jdg += (1);

            if (jdg > 20)
                jdg = 20;
            else if (jdg < 1)
                jdg = 1;
        }

        minJudge = judges[0];
        maxJudge = judges[0];
        for (auto jg : judges)
        {
            if (jg < minJudge)
                minJudge = jg;
            if (jg > maxJudge)
                maxJudge = jg;
        }
        judgesAll = 0;
        for (auto jg : judges)
        {
            judgesAll += jg;
        }
        judgesAll -= (minJudge + maxJudge);
    }
}

void Jumper::showResult()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << name << " " << surname << " (" << nationality << ")" << endl;
    cout << "Odleglosc: " << distance << "m"
         << " (Belka " << gate << " (";

    int t = -gateDiff;
    if (t > 0)
    {
        colorText(2, "+");
        colorText(2, to_string(t));
    }
    if (t == 0)
    {
        colorText(7, "+0");
    }
    if (t < 0)
    {
        colorText(4, to_string(t));
    }
    SetConsoleTextAttribute(hcon, 15);
    cout << "))" << endl;

    if (hill.isJudges == 1)
    {
        cout << "| ";
        for (auto jdg : judges)
        {
            cout << jdg << " | ";
            Sleep(300);
        }
        cout << endl;
    }

    if (windB < 0)
    {
        colorText(12, "Wiatr: ");
        colorText(12, to_string(windB));
    }

    else if (windB > 0)
    {
        colorText(10, "Wiatr: ");
        colorText(10, to_string(windB));
    }
    else
    {
        colorText(7, "Wiatr: ");
        colorText(7, to_string(windB));
    }
    cout << endl;
    if (compensationGate < 0)
    {
        colorText(12, "Za belke: ");
        colorText(12, to_string(compensationGate));
    }
    else if (compensationGate > 0)
    {
        colorText(10, "Za belke: ");
        colorText(10, to_string(compensationGate));
    }
    else
    {
        colorText(7, "Za belke: ");
        colorText(7, to_string(compensationGate));
    }
    cout << endl;
    if (compensationWind < 0)
    {
        colorText(12, "Za wiatr: ");
        colorText(12, to_string(compensationWind));
    }
    else if (compensationWind > 0)
    {
        colorText(10, "Za wiatr: ");
        colorText(10, to_string(compensationWind));
    }
    else
    {
        colorText(7, "Za wiatr: ");
        colorText(7, to_string(compensationWind));
    }
    cout << endl;
    if ((compensationWind + compensationGate) < 0)
    {
        colorText(12, "Lacznie: ");
        colorText(12, to_string((compensationWind + compensationGate)));
    }
    else if ((compensationWind + compensationGate) > 0)
    {
        colorText(10, "Lacznie: ");
        colorText(10, to_string((compensationWind + compensationGate)));
    }
    else
    {
        colorText(7, "Lacznie: ");
        colorText(7, to_string((compensationWind + compensationGate)));
    }

    SetConsoleTextAttribute(hcon, 15);
    cout << "\nPunkty: " << points << endl;

    cout << "Skok zakonczony ";
    if (landType == 1)
        colorText(11, "telemarkiem");
    else if (landType == 2)
        colorText(3, "ladowaniem na dwie nogi");
    else if (landType == 3)
        colorText(5, "podporka");
    else if (landType == 4)
        colorText(12, "upadkiem");

    SetConsoleTextAttribute(hcon, 15);
}

void Jumper::showHideInfo()
{
    cout << "Moc wybicia: " << takeoffPower << ", Technika wybicia: " << takeoffTechnique << ", Technika lotu: " << flightTechnique << endl;
}

void Jumper::showDistanceAndToBeat()
{
    for (int i = 0; i <= distance; i++)
    {
        cout << "Do objecia prowadzenia: " << toBeat << endl;
        if (i == distance)
        {
            cout << "| " << i << "m |" << endl;
        }
        else
            cout << i << "m" << endl;

        if (distance - i < 5 + (randomInt(-12, 12)))
            Sleep(80.5);
        else if (distance - i < 10 + (randomInt(-12, 12)))
            Sleep(72);
        else if (distance - i < 25 + (randomInt(-12, 12)))
            Sleep(60);
        else if (distance - i < 45 + (randomInt(-12, 12)))
            Sleep(47);
        else if (distance - i < 70 + (randomInt(-12, 12)))
            Sleep(30);
        else if (distance - i < 100 + (randomInt(-12, 12)))
            Sleep(16);
        else if (distance - i < 150 + (randomInt(-12, 12)))
            Sleep(12);
        else
            Sleep(8);

        cls;
    }
    cls;
}

void Jumper::setHill(Hill &h)
{
    hill = h;
}
void Jumper::basicDistance()
{
    distance = hill.startDist;
    distance += (gate * hill.gateMeters);

    if (windB > 0)
        distance += (windB * hill.windMetersFront);
    else if (windB < 0)
        distance += (windB * hill.windMetersBack);

    distance -= (abs(hill.optimalTakeoffPower - takeoffPower) * hill.takeoffPowerImportance);
    distance += takeoffTechnique * hill.takeoffTechniqueMeters;
    distance += flightTechnique * hill.flightTechniqueMeters;

    for (int i = 0; i < 5; i++)
    {
        if (flightStyle == i)
        {
            distance += hill.flightStyleMeters[i];
        }
    }

    if (distance > hill.maxdist)
        distance = hill.maxdist + normalRandom(0, hill.maxdistRandom);
    distance = round(distance * 2) / 2;
}

void Jumper::setToBeat()
{
    toBeat = hill.leaderPoints - hill.pointsForK;
    if (hill.isJudges == 1)
        toBeat -= 54;

    if (hill.gateComp == 1)
        toBeat -= compensationGate;

    if (hill.windComp == 1)
        toBeat -= compensationWind;

    toBeat /= hill.metersPoints;
    toBeat += hill.kpoint;
    toBeat = ceil(toBeat * 2) / 2;
}

void Jumper::saveToTxt(string filename)
{
    fstream rsf;
    rsf.open(filename, ios::out | ios::app);
    rsf << name << " " << surname << " (" << nationality << ")  |  " << distance << "m  Belka: " << gate << "  Wiatr: " << windB;
    if (hill.windComp == 1 || hill.gateComp == 1)
    {
        rsf << "  Rekompensata: " << compensationGate + compensationWind;
    }
    if (hill.isJudges == true)
    {
        rsf << "  |";
        for (int i = 0; i < 5; i++)
        {
            rsf << judges[i] << "|";
        }
    }
    rsf << "  " << points << "pkt";
    rsf << endl;
    rsf.close();
}

void Jumper::saveToCsv(string filename)
{
    fstream rsf;
    char c = ';';
    rsf.open(filename, ios::out | ios::app);
    rsf << name << c << surname << c << nationality << c << distance << c << gate << c << windB << c;
    if (hill.windComp == 1 || hill.gateComp == 1)
        rsf << compensationGate + compensationWind << c;

    if (hill.isJudges == 1)
    {
        rsf << "|";
        for (auto jg : judges)
        {
            rsf << jg << "|";
        }
        rsf << c;
    }
    rsf << points << endl;
    rsf.close();
}

void Jumper::setDsq()
{
    int rd = randomInt(1, 130);
    if (rd == 1)
        dsq = true;
    else
        dsq = false;

    if (dsq)
    {
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