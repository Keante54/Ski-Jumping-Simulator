#include "App.h"
#include "JumpData.h"
#include "Jumper.h"
#include "Competition.h"
#include "CompetitionConfig.h"
#include "Hill.h"

#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <filesystem>

#define sclear system("cls")
#define getchText cout << "Kliknij dowolny przycisk... "

App::App()
{
    isShowResults = true;
    isShowStartingNumbers = false;
    isSaveStartingNumbers = false;
    loadSettings();
}

App::~App()
{
}

void App::start()
{
    using namespace std;
    loadJumpersFromFile();
    loadHillsFromFile();
    loadCompetitionConfigFromFile();

    while (true)
    {
        system("cls");
        cout << "Witaj w symulatorze skok¢w narciarskich! Co chcesz zrobi†?\n";
        cout << "1. Symuluj pojedynczy konkurs\n2. Symyluj pojedyncze skoki (niedost©pne)\n3. Ustawienia";

        switch (numberChoice("\n", 1))
        {
        case 1:
            singleCompetitionChoice();
            break;
        case 2:
            break;
        case 3:
            settingsChoice();
            break;
        default:
            break;
        }
    }

    getch();
}

void App::loadJumpersFromFile()
{
    using namespace std;
    string name, surname, nationality, tps, tts, fts, fs, ls, f;

    ifstream ifs;
    ifs.open("resources/jumpers.csv");
    if (ifs.good() == false)
    {
        cout << "Nie udaˆo si© otworzy† pliku jumpers.csv!\n";
        Sleep(1500);
        abort();
    }

    jumpersList.erase(jumpersList.begin(), jumpersList.end());

    while (getline(ifs, name, ','))
    {
        getline(ifs, surname, ',');
        getline(ifs, nationality, ',');
        getline(ifs, tps, ',');
        getline(ifs, tts, ',');
        getline(ifs, fts, ',');
        getline(ifs, fs, ',');
        getline(ifs, ls, ',');
        getline(ifs, f);
        jumpersList.push_back(Jumper(name, surname, nationality, stoi(tps), stoi(tts), stoi(fts), stoi(fs), stoi(ls), stoi(f)));
    }
    ifs.close();
}

void App::loadHillsFromFile()
{
    using namespace std;
    string name, country, k, hs, gp, fwp, md, sd, otp, tpi, ttm, ftm;
    ifstream ifs;
    ifs.open("resources/hills.csv");
    if (ifs.good() == false)
    {
        cout << "Nie udaˆo si© otworzy† pliku hills.csv!\n";
        Sleep(1500);
        abort();
    }

    hillsList.erase(hillsList.begin(), hillsList.end());

    while (getline(ifs, name, ','))
    {
        getline(ifs, country, ',');
        getline(ifs, k, ',');
        getline(ifs, hs, ',');
        getline(ifs, gp, ',');
        getline(ifs, fwp, ',');
        getline(ifs, md, ',');
        getline(ifs, sd, ',');
        getline(ifs, otp, ',');
        getline(ifs, tpi, ',');
        getline(ifs, ttm, ',');
        getline(ifs, ftm);
        hillsList.push_back(Hill(name, country, stoi(k), stoi(hs), stod(md), stod(gp), stod(fwp), stod(sd), stod(ttm), stod(ftm), stod(otp), stod(tpi)));
    }
    ifs.close();
}

void App::loadCompetitionConfigFromFile()
{
    using namespace std;

    ifstream ifs;
    ifs.open("resources/competitionConfig.csv");
    if (ifs.good() == false)
    {
        cout << "Nie udaˆo si© otworzy† pliku competitionConfig.csv!\n";
        Sleep(1500);
        abort();
    }

    competitionConfigList.erase(competitionConfigList.begin(), competitionConfigList.end());

    string line;
    vector<string> lines;
    vector<string> result;

    while (getline(ifs, line))
    {
        if (line.size() > 0)
            lines.push_back(line);
    }
    for (const auto &l : lines)
    {
        CompetitionConfig config;
        boost::split(result, l, boost::is_any_of(","));
        config.setName(result[0]);
        result.erase(result.begin(), result.begin() + 1);
        for (const auto &num : result)
        {
            config.addRoundsData(stoi(num));
        }
        competitionConfigList.push_back(config);
    }

    ifs.close();
}

void App::singleCompetitionChoice()
{

    askForCompetitionParameters(&singleCompetition);
    std::cout << "Rozpocz©to konkurs...\n";
    Sleep(600);

    singleCompetition.startCompetition();

    getch();
}

void App::settingsChoice()
{
    using std::cout;
    while (true)
    {
        saveSettings();
        system("cls");
        cout << "Ustawienia: (1 - tak, 0 - nie)\n";
        cout << "1. Pokazywanie wynik¢w skok¢w w konkursie (" << isShowResults << ")\n"
             << "2. Pokazywanie numer¢w startowych w wynikach (" << isShowStartingNumbers << ")\n"
             << "3. Zapisywanie numer¢w startowych do pliku z wynikami (" << isSaveStartingNumbers << ")\n"
             << "4. Wr¢†\n\n";

        switch (numberChoice("\n", 1))
        {
        case 1:
            isShowResultsChoice();
            continue;
        case 2:
            isShowStartingNumbersChoice();
            continue;
        case 3:
            isSaveStartingNumbersChoice();
            continue;
        case 4:
            return;
            break;
        }
    }
}

void App::isShowResultsChoice()
{
    system("cls");

    if (isShowResults)
    {
        std::cout << "Wyˆ¥czono pokazywanie wynik¢w w konkursie!\n";
        isShowResults = false;
    }
    else if (!isShowResults)
    {
        std::cout << "Wˆ¥czono pokazywanie wynik¢w w konkursie!\n";
        isShowResults = true;
    }
    Sleep(1200);
}

void App::isShowStartingNumbersChoice()
{
    system("cls");

    if (isShowStartingNumbers)
    {
        std::cout << "Wyˆ¥czono pokazywanie numer¢w startowych w wynikach!\n";
        isShowStartingNumbers = false;
    }
    else if (!isShowStartingNumbers)
    {
        std::cout << "Wˆ¥czono pokazywanie numer¢w startowych w wynikach!\n";
        isShowStartingNumbers = true;
    }
    Sleep(1200);
}

void App::isSaveStartingNumbersChoice()
{
    system("cls");

    if (isSaveStartingNumbers)
    {
        std::cout << "Wyˆ¥czono zapisywanie numer¢w startowych do pliku z wynikami!\n";
        isSaveStartingNumbers = false;
    }
    else if (!isSaveStartingNumbers)
    {
        std::cout << "Wˆ¥czono zapisywanie numer¢w startowych do pliku z wynikami!\n";
        isSaveStartingNumbers = true;
    }
    Sleep(1200);
}

void App::selectHill(Competition *comp)
{
    showHills();
    comp->setHill(&hillsList[numberChoice("\n", 1) - 1]);
    std::cout << "Wybrano skoczni© " << comp->getHill()->getName() << " K" << comp->getHill()->getKPoint() << " HS" << comp->getHill()->getHsPoint() << "\n";
    Sleep(1200);
}

void App::selectCompetitionConfig(Competition *comp)
{
    showCompetitionConfigs();
    comp->setCompetitionConfig(competitionConfigList[numberChoice("\n", 1) - 1]);
    std::cout << "Wybrano konfiguracj© " << comp->getCompetitionConfig().getName() << "\n";
    Sleep(1200);
}

void App::askForCompetitionParameters(Competition *comp)
{
    using std::cout;

    sclear;
    cout << "Wybierz skocznie: \n";
    selectHill(&singleCompetition);
    sclear;

    cout << "Wybierz konfiguracj© konkursu: \n";
    selectCompetitionConfig(&singleCompetition);
    sclear;

    singleCompetition.setJumpers(jumpersList);

    cout << "Lista startowa konkursu: \n";
    showJumpers();
    getch();
    getchText;
    sclear;

    singleCompetition.askForStartGate();
    sclear;

    singleCompetition.loadParametersFromFile();
    singleCompetition.setIsShowResults(isShowResults);
    singleCompetition.setIsShowStartingNumbers(isShowStartingNumbers);
    singleCompetition.setIsSaveStartingNumbers(isSaveStartingNumbers);

    cout << "Parametry konkursu: (1 - tak, 0 - nie)\n";
    singleCompetition.showParameters();
    getch();
    sclear;
}

void App::showJumpers()
{
    using std::cout;

    int i = 1;
    for (const auto &jp : jumpersList)
    {
        cout << i << ". " << jp.getName() << " " << jp.getSurname() << " (" << jp.getNationality() << ")\n";
        i++;
    }
}
void App::showHills()
{
    using std::cout;

    int i = 1;
    for (const auto &hl : hillsList)
    {
        cout << i << ". " << hl.getName() << " (" << hl.getCountry() << ") K" << hl.getKPoint() << " HS" << hl.getHsPoint() << "\n";
        i++;
    }
}
void App::showCompetitionConfigs()
{
    using std::cout;

    int i = 1;
    for (const auto &cf : competitionConfigList)
    {
        cout << i << ". " << cf.getName()
             << " (" << cf.getRoundsCount() << " rundy)";
        cout << "(";
        for (const auto &r : cf.getRoundsData())
        {
            cout << r << ",";
        }
        cout << ")\n";
        i++;
    }
}

int App::numberChoice(std::string text, bool enter)
{
    using std::cin;
    using std::cout;

    int choice;

    cout << text;
    cout << "Wyb¢r: ";

    if (enter)
    {
        cin >> choice;
    }
    else
        choice = getch() - '0';

    return choice;
}

void App::saveSettings()
{
    std::ofstream ofs("config.cfg");
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

void App::loadSettings()
{
    if (!isConfigFileEmpty())
    {
        std::ifstream ifs("config.cfg");
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
    }
}

bool App::isConfigFileEmpty()
{
    std::ifstream ifs("config.cfg");
    return ifs.peek() == std::ifstream::traits_type::eof();
}