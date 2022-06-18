#include "Competition.h"

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

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
    for (auto &fin : finalResults)
    {
    }

    sortResultsVector(finalResults);
}

void Competition::startCompetition()
{
    system("cls");
    for (int actualRound = 0; actualRound < competitionConfig.getRoundsCount(); actualRound++)
    {
        int i = 0;
        for (auto &jumper : jumpers)
        {
            JumpData jumpData = JumpData();
            jumpData.setParameters(jumper, *hill, *this);
            jumpData.jump();

            if (isShowResults)
            {
                jumpData.showResults();
            }
            actualResults.push_back(jumpData);
            actualSortedResults = actualResults;
            sortResultsVector(actualSortedResults);

            configFinalResults(&jumper, &jumpData);

            getch();
            system("cls");
        }
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
    cout << position << ". " << jumper->getName() << " " << jumper->getSurname() << " --> " << totalPoints << "pkt\n";
}
void Competition::FinalResults::setTotalPoints()
{
    totalPoints = 0;
    for (const auto &res : jumperResults)
    {
        totalPoints += res.getPoints();
    }
}