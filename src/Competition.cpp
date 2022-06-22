#include "Competition.h"

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

Competition::Competition(int startGate_, double startWind_, double windChange_, double windFaulty_, bool isGateComp_, bool isWindComp_, bool isJudges_, bool isShowResults_)
{
    startGate = startGate_;
    startWind = startWind_;
    windChange = windChange_;
    windFaulty = windFaulty_;
    isGateComp = isGateComp_;
    isWindComp = isWindComp_;
    isJudges = isJudges_;
    isShowResults = isShowResults_;
}

Competition::Competition()
{
    startGate = startWind = windChange = windFaulty = isGateComp = isWindComp = isJudges = isShowResults = 0;
}
Competition::~Competition()
{
}

template <typename T>
void Competition::sortResultsVector(vector<T> &vec)
{
    std::sort(vec.begin(), vec.end(), std::greater<T>());
}

template <>
void Competition::sortResultsVector(vector<FinalResults> &vec)
{
    std::sort(vec.begin(), vec.end(), std::greater<FinalResults>());
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].position = i + 1;
    }
}

void Competition::setFinalResultsPosition()
{
    sortResultsVector(finalResults);
    int i = 1;
    for (auto &fin : finalResults)
    {
        fin.position = i;
        i++;
    }
}

void Competition::updateActualJumpers()
{
    int difference = actualJumpers.size() - competitionConfig.getRoundsData()[actualRound];
    sortResultsVector(finalResults);
    for (const auto &fin : finalResults)
    {
        if (fin.position > competitionConfig.getRoundsData()[actualRound])
        {
            int i = 0;
            for (const auto &jum : actualJumpers)
            {
                if (jum == fin.jumper)
                {
                    actualJumpers.erase(actualJumpers.begin() + i);
                    break;
                }
                i++;
            }
        }
    }
}

void Competition::roundSummary()
{
    system("cls");
    std::cout << "Zakoäczono rund© " << actualRound + 1 << "!\n"
              << "Odpadˆo " << (actualJumpers.size() - competitionConfig.getRoundsData()[actualRound]) << " zawodnik¢w.\n"
              << "Wyniki po rundzie " << actualRound + 1 << ":\n";
    showActualResults();
    std::cout << "Wci˜nij dowolny przycisk aby przej˜† do nast©pnej serii.\n";
    getch();
    system("cls");
}

void Competition::competitionSummary()
{
    std::cout << "Koniec konkursu! Najlepszy okazaˆ si© " << *finalResults[0].jumper;
    std::cout << "\nPeˆne wyniki:\n";
    showActualResults();
    std::cout << "Aby przej˜† do menu, wci˜nij dowolny przycisk.\n";
    getch();
    system("cls");
}

void Competition::sortActualJumpers()
{
    vector<Jumper *> temp;
    for (auto &jum : jumpers)
        temp.push_back(&jum);

    for (const auto jum : actualJumpers)
    {
        for (const auto fin : finalResults)
        {
            if (fin.jumper == jum)
                temp.push_back(jum);
        }
    }
    actualJumpers.erase(actualJumpers.begin(), actualJumpers.end());
    for (const auto &t : temp)
        actualJumpers.push_back(t);
}

void Competition::showActualResults()
{
    int i = 1;
    sortResultsVector(finalResults);
    std::cout << "\n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    for (const auto &fin : finalResults)
    {
        if (!(fin.position > competitionConfig.getRoundsData()[actualRound]))
            fin.show(true);
        else
            fin.show(false);
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void Competition::configFinalResults(Jumper *jumper, JumpData *jumpData)
{
    bool isExists;
    for (const auto &fin : finalResults)
    {
        if (fin.jumper == jumper)
        {
            isExists = true;
        }
    }
    if (!isExists)
    {
        FinalResults finres(jumper);
        finalResults.push_back(finres);
    }
    for (auto &fin : finalResults)
    {
        if (fin.jumper == jumper)
        {
            fin.jumperResults.push_back(*jumpData);
            fin.setTotalPoints();
        }
    }
    setFinalResultsPosition();
}

void Competition::startCompetition()
{
    system("cls");
    for (auto &jum : jumpers)
    {
        actualJumpers.push_back(&jum);
    }
    while (actualRound < competitionConfig.getRoundsCount())
    {
        int i = 0;
        int ii = 0;
        for (auto &jumper : actualJumpers)
        {
            JumpData jumpData = JumpData();
            jumpData.setParameters(*jumper, *hill, *this);
            jumpData.jump();

            if (isShowResults)
                jumpData.showResults();

            actualResults.push_back(jumpData);
            sortResultsVector(actualResults);
            configFinalResults(jumper, &jumpData);

            if (ii + 1 != actualJumpers.size())
                std::cout << "\nNast©pny zawodnik: " << actualJumpers[ii + 1]->getName() << " " << actualJumpers[ii + 1]->getSurname() << " (" << actualJumpers[ii + 1]->getNationality() << ")";

            showActualResults();

            getch();
            system("cls");
            ii++;
        }
        if (actualRound + 1 == competitionConfig.getRoundsCount())
            competitionSummary();
        else
            roundSummary();
        if (actualRound + 1 != competitionConfig.getRoundsCount())
            updateActualJumpers();
        actualRound++;
        //sortActualJumpers();
        system("cls");
    }
}

void Competition::loadParametersFromFile()
{
    using std::getline;

    std::string tmp;
    std::ifstream ifs;
    ifs.open("resources/config.csv");
    if (ifs.good() == false)
        std::cout << "Nie udaˆo si© otworzy† pliku config.csv!\n";

    getline(ifs, tmp, ',');
    startGate = stoi(tmp);
    getline(ifs, tmp, ',');
    startWind = stod(tmp);
    getline(ifs, tmp, ',');
    windChange = stod(tmp);
    getline(ifs, tmp, ',');
    windFaulty = stod(tmp);
    getline(ifs, tmp, ',');
    isGateComp = stoi(tmp);
    getline(ifs, tmp, ',');
    isWindComp = stoi(tmp);
    getline(ifs, tmp, ',');
    isJudges = stoi(tmp);
    getline(ifs, tmp, ',');
    isShowResults = stoi(tmp);

    ifs.close();
}

void Competition::showParameters()
{
    using std::cout;
    cout << "Belka startowa: " << startGate << "\n"
         << "Wiatr: " << startWind << "\n"
         << "Zmienno˜† wiatru: " << windChange << "\n"
         << "Faˆszywo˜c pomiaru wiatru: " << windFaulty << "\n"
         << "Rekompensata za belk©: " << isGateComp << "\n"
         << "Rekompensata za wiatr: " << isWindComp << "\n"
         << "Noty za styl: " << isJudges << "\n"
         << "Pokazywa† wyniki? " << isShowResults << "\n";
}

void Competition::FinalResults::show(bool isQualified) const
{
    using std::cout;
    using std::fixed;
    using std::setprecision;

    cout << position << ". " << jumper->getName() << " " << jumper->getSurname() << " (" << jumper->getNationality() << ")"
         << " --> ";

    for (const auto &res : jumperResults)
    {
        cout << res.getDistance() << "m (";
        cout << fixed << setprecision(1);
        cout << res.getPoints() << "pts), ";
        cout << fixed;
    }
    cout << "--> " << totalPoints << "pts";
    if (isQualified)
        cout << " (Q)\n";
    else
        cout << "\n";
}
void Competition::FinalResults::setTotalPoints()
{
    totalPoints = 0;
    for (const auto &res : jumperResults)
    {
        totalPoints += res.getPoints();
    }
}