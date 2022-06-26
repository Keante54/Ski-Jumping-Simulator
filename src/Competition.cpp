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
    int howManyJumpersDroppedOut;
    system("cls");
    std::cout << "Zako�czono rund� " << actualRound + 1 << "!\n";
    if (competitionConfig.getRoundsData()[actualRound + 1] > actualJumpers.size())
        howManyJumpersDroppedOut = 0;
    else
        howManyJumpersDroppedOut = actualJumpers.size() - competitionConfig.getRoundsData()[actualRound + 1];

    std::cout << "Odpad�o " << howManyJumpersDroppedOut << " zawodnik�w.\n"
              << "Wyniki po rundzie " << actualRound + 1 << ":\n";
    showActualResults(true, true);
    std::cout << "Wci�nij dowolny przycisk aby przej�� do nast�pnej serii.\n";
    getch();
    system("cls");
}

void Competition::competitionSummary()
{
    std::cout << "Koniec konkursu! Najlepszy okaza� si� " << *finalResults[0].jumper;
    std::cout << "\nPe�ne wyniki:\n";
    showActualResults(true, true);
    std::cout << "Aby przej�� do menu, wci�nij dowolny przycisk.\n";
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

void Competition::showStartList()
{
    int i = 1;
    std::cout << "\n\nLista startowa:\n";
    for (const auto &jum : actualJumpers)
    {
        std::cout << i << ". " << *jum << "\n";
        i++;
    }
}

void Competition::showActualResults(bool isFinal, bool nextRound)
{
    sortResultsVector(finalResults);
    std::cout << "\n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool isShowDownResults = true;
    ;

    int i = 0;
    for (const auto &fin : finalResults)
    {
        if (actualRound + 1 != competitionConfig.getRoundsCount() && fin.position <= competitionConfig.getRoundsData()[actualRound + 1] && nextRound && isFinal)
            fin.show(true);
        else if (actualRound + 1 != competitionConfig.getRoundsCount() && fin.position <= competitionConfig.getRoundsData()[actualRound + 1])
        {
            if (isFinal)
                fin.show(false);
            else
                fin.show(true);
        }
        else if (actualRound + 1 == competitionConfig.getRoundsCount())
        {
            fin.show(false);
            isShowDownResults = false;
        }
    }

    if (isShowDownResults)
    {
        std::cout << "---\n";
        for (const auto &fin : finalResults)
            if (actualRound + 1 != competitionConfig.getRoundsCount() && fin.position > competitionConfig.getRoundsData()[actualRound + 1])
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
    bool isShowStartList;
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
            configFinalResults(jumper, &jumpData);

            if (ii + 1 != actualJumpers.size())
                std::cout << "\nNast�pny zawodnik: " << *actualJumpers[ii + 1];

            showActualResults(false, false);

            if (isShowResults)
                jumpData.showResults();

            if (isShowStartList)
                showStartList();

            std::cout << "\nWci�nij dowolny przycisk, aby przej�� do nast�pnego skoku (wci�nij 's' aby pokaza� list� startow�)\n";

            if (getch() == 's')
            {
                if (isShowStartList)
                    isShowStartList = false;
                else
                {
                    isShowStartList = true;
                    showStartList();
                }
                getch();
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
        std::cout << "Nie uda�o si� otworzy� pliku config.csv!\n";

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

void Competition::askForStartGate()
{
    std::cout << "Belka startowa: ";
    std::cin >> startGate;
}

void Competition::showParameters()
{
    using std::cout;
    cout << "Belka startowa: " << startGate << "\n"
         << "Wiatr: " << startWind << "\n"
         << "Zmienno�� wiatru: " << windChange << "\n"
         << "Fa�szywo�c pomiaru wiatru: " << windFaulty << "\n"
         << "Rekompensata za belk�: " << isGateComp << "\n"
         << "Rekompensata za wiatr: " << isWindComp << "\n"
         << "Noty za styl: " << isJudges << "\n"
         << "Pokazywa� wyniki? " << isShowResults << "\n";
}

void Competition::saveResultsToFile(SaveMode mode)
{
    using namespace std::filesystem;
    using std::to_string;
    std::string fileName;
    fileName = hill->getName() + "K" + to_string(hill->getKPoint()) + "HS" + to_string(hill->getHsPoint());
    if (mode == SaveMode::Csv)
    {
        if (!is_directory("results/csv") || !exists("results/csv"))
            create_directories("results/csv");

        fileName += ".csv";

        std::ofstream ofs;
        ofs.clear();
        ofs.open("results/csv/" + fileName);
        for (const auto &fin : finalResults)
        {
            ofs << fin.jumper->getName() << ", " << fin.jumper->getSurname() << "," << fin.jumper->getNationality() << ",";
            for (const auto &res : fin.jumperResults)
            {
                ofs << res.getGate() << "," << res.getWind() << "," << res.getDistance() << "," << res.getPoints() << ",";
                if (isJudges)
                {
                    ofs << "|";
                    for (int i = 0; i < 5; i++)
                        ofs << res.getJudges(i) << "|";
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
        if (!is_directory("results/text") || !exists("results/text"))
            create_directories("results/text");

        fileName += ".txt";

        std::ofstream ofs;
        ofs.clear();
        ofs.open("results/text/" + fileName);
        for (const auto &fin : finalResults)
        {
            ofs << fin.jumper->getName() << " " << fin.jumper->getSurname() << " (" << fin.jumper->getNationality() << "), ";
            for (const auto &res : fin.jumperResults)
            {
                ofs << "Belka: " << res.getGate() << ", Wiatr: " << res.getWind() << ", " << res.getDistance() << "m, " << res.getPoints() << "pts, ";
                if (isJudges)
                {
                    ofs << "|";
                    for (int i = 0; i < 5; i++)
                        ofs << res.getJudges(i) << "|";
                    ofs << ", ";
                }
                if (isWindComp || isGateComp)
                    ofs << "Rekompensata: " << res.getTotalCompensation() << ", ";
            }
            ofs << "��cznie: " << fin.totalPoints << "pts\n";
        }
        ofs.close();
    }
}

void Competition::FinalResults::show(bool isQualified) const
{
    using std::cout;
    using std::fixed;
    using std::setprecision;

    colorText(2, position);
    colorText(7, ". " + jumper->getName() + " " + jumper->getSurname() + " (" + jumper->getNationality() + ")");
    colorText(15, " --> ");

    for (const auto &res : jumperResults)
    {
        colorText(3, res.getDistance());
        colorText(3, "m");
        cout << " (";
        cout << fixed << setprecision(1);
        colorText(6, res.getPoints());
        colorText(6, "pts");
        cout << "), ";
        cout << fixed;
    }
    colorText(15, "--> ");
    colorText(14, totalPoints);
    colorText(14, "pts");
    if (isQualified)
        colorText(15, " (Q)\n");
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