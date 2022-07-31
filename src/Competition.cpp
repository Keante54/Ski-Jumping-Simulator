#include "Competition.h"
#include "Random.h"

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include <array>
#include <math.h>

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

void Competition::setToBeatDistance(FinalResults *fin, JumpData *jum)
{
    double actualJumperTotalPoints = fin->totalPoints;
    double actualJumperLastJump = fin->jumperResults[fin->jumperResults.size() - 1].getPoints();

    sortResultsVector(finalResults);
    double leaderPoints = finalResults[0].totalPoints;

    if (actualRound == 0)
        toBeatDistance = leaderPoints;
    else
        toBeatDistance = leaderPoints - actualJumperTotalPoints + actualJumperLastJump;

    toBeatDistance -= hill->getPointsForKPoint();

    if (isJudges)
        toBeatDistance -= 54;

    if (isWindComp)
        toBeatDistance -= jum->getWindCompensation();

    if (isGateComp)
        toBeatDistance -= jum->getGateCompensation();

    toBeatDistance /= hill->getPointsForMeters();
    toBeatDistance += hill->getKPoint();
    toBeatDistance = round(toBeatDistance * 2) / 2;
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
    int howManyJumpersDroppedOut;
    system("cls");
    std::cout << "Zakoäczono rund© " << actualRound + 1 << "!\n";
    if (competitionConfig.getRoundsData()[actualRound + 1] > actualJumpers.size())
        howManyJumpersDroppedOut = 0;
    else
        howManyJumpersDroppedOut = actualJumpers.size() - competitionConfig.getRoundsData()[actualRound + 1];

    std::cout << "Odpadˆo " << howManyJumpersDroppedOut << " zawodnik¢w.\n"
              << "Wyniki po rundzie " << actualRound + 1 << ":\n";
    showActualResults(false);
    std::cout << "Wci˜nij dowolny przycisk aby przej˜† do nast©pnej serii.\n";
    getch();
    system("cls");
}

void Competition::competitionSummary()
{
    std::cout << "Koniec konkursu! Najlepszy okazaˆ si© " << *finalResults[0].jumper;
    std::cout << "\nPeˆne wyniki:\n";
    showFullResults();
    std::cout << "Aby przej˜† do menu, wci˜nij dowolny przycisk.\n";
    getch();
    system("cls");
    saveResultsToFile(SaveMode::Csv);
}

void Competition::sortActualJumpers()
{
    actualJumpers.clear();
    for (int i = 0; i < competitionConfig.getRoundsData()[actualRound]; i++)
        for (auto &jum : jumpers)
            if (&jum == finalResults[i].jumper)
                actualJumpers.insert(actualJumpers.begin(), &jum);
}

void Competition::showStartList(int actualIndex)
{
    int i = 1;
    std::cout << "\n\nLista startowa:\n";
    for (const auto &jumper : actualJumpers)
    {
        colorText(6, i);
        std::cout << ". " << *jumper;
        if (actualIndex >= i - 1)
            colorText(8, " (Skakaˆ)");
        std::cout << "\n";
        i++;
    }
}

void Competition::showActualResults(bool isFinal)
{
    int round = actualRound + 1;

    sortResultsVector(finalResults);
    std::cout << "\n";

    for (const auto &fin : finalResults)
    {
        if (fin.jumperResults.size() == round && fin.position <= competitionConfig.getRoundsData()[round])
            fin.show(!isFinal, 2, isShowStartingNumbers);

        else if (fin.jumperResults.size() == round && fin.position > competitionConfig.getRoundsData()[round])
            fin.show(false, 6, isShowStartingNumbers);

        else if (fin.jumperResults.size() == round - 1)
            fin.show(false, 4, isShowStartingNumbers);
    }
}

void Competition::showFullResults()
{
    sortResultsVector(finalResults);
    std::cout << "\n";

    for (const auto &fin : finalResults)
    {
        if (fin.position <= 3)
            fin.show(false, 2, isShowStartingNumbers);
        else
            fin.show(false, 6, isShowStartingNumbers);
    }
}

void Competition::configFinalResults(Jumper *jumper, JumpData *jumpData, int index)
{
    bool isExists;

    for (const auto &fin : finalResults)
        if (fin.jumper == jumper)
            isExists = true;
    if (!isExists)
    {
        FinalResults finres(jumper);
        finres.startingNumber = index;
        finalResults.push_back(finres);
    }
    sortResultsVector(finalResults);
    for (auto &fin : finalResults)
        if (fin.jumper == jumper)
        {
            sortResultsVector(finalResults);
            fin.jumperResults.push_back(*jumpData);
            fin.setTotalPoints();
            setToBeatDistance(&fin, jumpData);
        }
    setFinalResultsPosition();
}

void Competition::startCompetition()
{
    system("cls");
    for (auto &jum : jumpers)
        actualJumpers.push_back(&jum);
    bool isShowStartList = false;
    actualGate = startGate;
    while (actualRound < competitionConfig.getRoundsCount())
    {
        int i = 0;
        int ii = 0;
        for (auto &jumper : actualJumpers)
        {
            JumpData jumpData = JumpData();
            jumpData.setParameters(*jumper, *hill, *this);
            jumpData.jump();

            actualResults.push_back(jumpData);
            sortResultsVector(actualResults);
            configFinalResults(jumper, &jumpData, ii + 1);
            if (i > 0 || ii > 0 && isShowResults)
            {
                std::cout << "\nDo obj©cia prowadzenia: ";
                colorText(10, toBeatDistance);
            }

            if (isShowResults)
            {
                if (ii + 1 != actualJumpers.size())
                    std::cout << "\nNast©pny zawodnik: " << *actualJumpers[ii + 1];
                showActualResults(false);
                jumpData.showResults();
            }

            if (isShowStartList)
                showStartList(ii);

            if (isShowResults)
            {
                char fromGetch;
                colorText(8, "\nWci˜nij dowolny przycisk, aby przej˜† do nast©pnego skoku (wci˜nij 's' aby pokaza†/ukry† list© startow¥) ('b' aby ustawi† belk©)\n");
                fromGetch = getch();
                if (fromGetch == 's')
                    do
                    {
                        if (isShowStartList)
                        {
                            isShowStartList = false;

                            system("cls");
                            showActualResults(false);
                            jumpData.showResults();
                        }
                        else
                        {
                            isShowStartList = true;
                            system("cls");

                            showActualResults(false);
                            jumpData.showResults();

                            showStartList(ii);
                            colorText(8, "\nWci˜nij dowolny przycisk, aby przej˜† do nast©pnego skoku (wci˜nij 's' aby pokaza†/ukry† list© startow¥) ('b' aby ustawi† belk©)\n");
                        }
                    } while (getch() == 's');
                else if (fromGetch == 'b')
                    do
                    {
                        int newGate;
                        std::cout << "\nBelka: ";
                        std::cin >> newGate;
                        if (newGate > actualGate)
                            std::cout << "Podwy¾szono belk© o " << (newGate - actualGate) << " stopni.\n";
                        else if (newGate < actualGate)
                            std::cout << "Obni¾ono belk© o " << (actualGate - newGate) << " stopni.\n";
                        else
                            std::cout << "Belka nie zmieniˆa si©.\n";
                        Sleep(1200);

                        actualGate = newGate;

                        system("cls");

                        showActualResults(false);
                        jumpData.showResults();

                        if (isShowStartList)
                            showStartList(ii);
                        colorText(8, "\nWci˜nij dowolny przycisk, aby przej˜† do nast©pnego skoku (wci˜nij 's' aby pokaza†/ukry† list© startow¥) ('b' aby ustawi† belk©)\n");
                    } while (getch() == 'b');
            }

            system("cls");
            ii++;
            saveResultsToFile(SaveMode::Text);
            saveResultsToFile(SaveMode::Csv);
        }
        if (actualRound + 1 == competitionConfig.getRoundsCount())
            competitionSummary();
        else
            roundSummary();
        if (actualRound + 1 != competitionConfig.getRoundsCount())
            updateActualJumpers();
        actualRound++;
        sortActualJumpers();
        startWind += normalRandom(0, windChange / 2);
        system("cls");
    }
}

void Competition::loadParametersFromFile()
{
    using std::getline;

    std::string tmp;
    std::ifstream ifs;
    ifs.open("resources/competitionRules.csv");
    if (ifs.good() == false)
    {
        std::cout << "Nie udaˆo si© otworzy† pliku competitionRules.csv!\n";
        Sleep(1500);
        abort();
    }

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

    ifs.close();
}

void Competition::askForStartGate()
{
    std::cout << "Belka startowa: ";
    std::cin >> startGate;
}

void Competition::showParameters()
{
    using std::cout;
    cout << "\nSkocznia: " << *hill << "\n"
         << "Belka startowa: " << startGate << "\n"
         << "Wiatr: " << startWind << "\n"
         << "Zmienno˜† wiatru: " << windChange << "\n"
         << "Faˆszywo˜c pomiaru wiatru: " << windFaulty << "\n"
         << "Rekompensata za belk©: " << isGateComp << "\n"
         << "Rekompensata za wiatr: " << isWindComp << "\n"
         << "Noty za styl: " << isJudges << "\n"
         << "Pokazywa† wyniki? " << isShowResults << "\n"
         << "Pokazywa† numery startowe? " << isShowStartingNumbers << "\n"
         << "Zapisywa† numery startowe do pliku? " << isSaveStartingNumbers << "\n";
}

void Competition::saveResultsToFile(int mode)
{
    using namespace std::filesystem;
    using std::to_string;
    std::string fileName;
    fileName = hill->getName() + "K" + to_string(hill->getKPoint()) + "HS" + to_string(hill->getHsPoint());
    if (mode == SaveMode::Csv)
    {
        if (!is_directory("results/competitions/csv") || !exists("results/competitions/csv"))
            create_directories("results/competitions/csv");

        fileName += ".csv";

        std::ofstream ofs;
        ofs.open("results/competitions/csv/" + fileName);
        ofs.clear();
        for (const auto &fin : finalResults)
        {
            if (isSaveStartingNumbers)
                ofs << fin.startingNumber << ", ";
            ofs << fin.jumper->getName() << ", " << fin.jumper->getSurname() << "," << fin.jumper->getNationality() << ",";
            for (const auto &res : fin.jumperResults)
            {
                ofs << res.getGate() << "," << res.getWind() << "," << res.getDistance() << "," << res.getPoints() << ",";
                if (isJudges)
                {
                    ofs << "|";
                    for (int i = 0; i < 5; i++)
                        ofs << res.getJudges()[i] << "|";
                    ofs << ",";
                }
                if (isWindComp || isGateComp)
                    ofs << res.getTotalCompensation() << ",";
            }
            ofs << fin.totalPoints << "\n";
        }
        ofs.close();
    }
    else if (mode == SaveMode::Text)
    {
        if (!is_directory("results/competitions/text") || !exists("results/competitions/text"))
            create_directories("results/competitions/text");

        fileName += ".txt";

        std::ofstream ofs;
        ofs.open("results/competitions/text/" + fileName);
        ofs.clear();
        for (const auto &fin : finalResults)
        {
            ofs << fin.jumper->getName() << " " << fin.jumper->getSurname() << " (" << fin.jumper->getNationality() << ")";
            if (isSaveStartingNumbers)
                ofs << " (nr " << fin.startingNumber << ")";
            ofs << ", ";

            for (const auto &res : fin.jumperResults)
            {
                ofs << "Belka: " << res.getGate() << ", Wiatr: " << res.getWind() << ", " << res.getDistance() << "m, " << res.getPoints() << "pts, ";
                if (isJudges)
                {
                    ofs << "|";
                    for (int i = 0; i < 5; i++)
                        ofs << res.getJudges()[i] << "|";
                    ofs << ", ";
                }
                if (isWindComp || isGateComp)
                    ofs << "Rekompensata: " << res.getTotalCompensation() << ", ";
            }
            ofs << "¥cznie: " << fin.totalPoints << "pts\n";
        }
        ofs.close();
    }
}