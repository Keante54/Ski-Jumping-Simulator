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
        std::cout << fin.jumper->getSurname() << "\n";
        fin.position = i;
        i++;
    }
}

void Competition::updateActualJumpers(int round)
{
    for (const auto &fin : finalResults)
        if (fin.position > competitionConfig.getRoundsData()[round])
        {
            int i = 0;
            int howManyDeleted = 0;
            for (const auto &jum : actualJumpers)
            {
                if (&jum == fin.jumper)
                {
                    std::cout << "Usuni©to skoczka " << actualJumpers[i].getName() << " " << actualJumpers[i].getSurname() << "(pozycja " << fin.position << ")\n";
                    actualJumpers.erase(actualJumpers.begin() + i);
                }
                else
                    // std::cout << "Nie usuni©to skoczka. (Aktualnie: " << actualJumpers[i].getName() << " " << actualJumpers[i].getSurname() << ")\n";
                    i++;
            }
        }
}

void Competition::showActualResults()
{
    int i = 1;
    sortResultsVector(finalResults);
    std::cout << "\n";
    for (const auto &fin : finalResults)
    {
        fin.show();
    }
}

void Competition::configFinalResults(Jumper *jumper, JumpData *jumpData)
{
    bool isExists;
    for (const auto &fin : finalResults)
    {
        if (fin.jumper == jumper)
            isExists = true;
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
    actualJumpers = jumpers;
    for (int actualRound = 0; actualRound < competitionConfig.getRoundsCount(); actualRound++)
    {
        int i = 0;
        int ii = 0;
        for (auto &jumper : actualJumpers)
        {
            JumpData jumpData = JumpData();
            jumpData.setParameters(jumper, *hill, *this);
            jumpData.jump();

            if (isShowResults)
                jumpData.showResults();

            actualResults.push_back(jumpData);
            sortResultsVector(actualResults);
            configFinalResults(&jumper, &jumpData);

            if (ii + 1 != actualJumpers.size())
                std::cout << "\nNast©pny zawodnik: " << actualJumpers[ii + 1].getName() << " " << actualJumpers[ii + 1].getSurname() << " (" << actualJumpers[ii + 1].getNationality() << ")";

            showActualResults();

            getch();
            system("cls");
            ii++;
        }
        updateActualJumpers(actualRound);
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

void Competition::FinalResults::show() const
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
    cout << "--> " << totalPoints << "pts\n";
}
void Competition::FinalResults::setTotalPoints()
{
    totalPoints = 0;
    for (const auto &res : jumperResults)
    {
        totalPoints += res.getPoints();
    }
}