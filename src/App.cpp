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
        cout << "1. Symuluj sezon\n2. Symuluj pojedynczy konkurs\n3. Symyluj pojedyncze skoki (niedost©pne)\n4. Ustawienia";

        switch (numberChoice("\n", 1))
        {
        case 1:
            seasonsChoice();
            break;
        case 2:
            singleCompetitionChoice();
            break;
        case 3:
            break;
        case 4:
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
        getch();
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
        cout << "Nie udaˆo si© otworzy† pliku hills.csv!\n";

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
        cout << "Nie udaˆo si© otworzy† pliku competitionConfig.csv!\n";

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

void App::seasonsChoice()
{
    while (true)
    {
        system("cls");

        std::cout << "Wczytane zapisy sezon¢w:\n";
        int i = 1;

        if (seasons.size() == 0)
            std::cout << "BRAK\n";
        else
            for (const auto &save : seasons)
            {
                std::cout << i << ". " << save.getSaveName() << "\n";
                i++;
            }

        std::cout << "\nCo chcesz zrobi†?\n1. Rozegraj istniej¥cy sezon\n2. Stw¢rz nowy sezon\n3. Usuä sezon\n4. Wr¢† do menu\n";
        switch (numberChoice("\n", true))
        {
        case 1:
            continue;
        case 2:
            createSeasonChoice();
            continue;
        case 3:
            continue;
        case 4:
            break;
        }
    }
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
             << "2. Wr¢†\n\n";

        switch (numberChoice("\n", 1))
        {
        case 1:
            isShowResultsChoice();
            continue;
        case 2:
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

void App::createSeasonChoice()
{
    using std::cout;

    std::string seasonName;
    std::cout << "Podaj nazw© sezonu: ";
    std::cin.clear();
    std::cin.ignore();
    std::cin.sync();
    std::getline(std::cin, seasonName);

    season = std::make_unique<Season>(Season(seasonName));
    seasons.push_back(*season);

    saveSeason(*season);

    while (true)
    {
        saveSeason(*season);
        system("cls");
        season->showCompetitions();
        std::cout << "\n\n\nCo chcesz zrobi†?\n1. Dodaj konkurs\n2. Usuä konkurs\n----\n3. Klasyfikacje\n4. Dodaj klasyfikacj© do konkursu\n5. Usuä klasyfikacj© z konkursu\n6. Wr¢†\n";
        switch (numberChoice("\n", true))
        {
        case 1:
            addCompetitionChoice();
            continue;
        case 2:
            deleteCompetitionChoice();
            continue;
        case 3:
            classificationsChoice();
            continue;
        case 4:
            addTargetClassificationChoice();
            continue;
        case 5:
            deleteTargetClassificationChoice();
            continue;
        case 6:
            std::cout << "Na pewno wyj˜†? Utracisz dotychczasowy post©p. Je˜li tak, wpisz 't'\n";
            if (getch() == 't')
            {
                season.reset();
                return;
                break;
            }
        }
    }
}

void App::addCompetitionChoice()
{
    system("cls");
    Competition comp;
    showHills();

    int hillIndex = numberChoice("\n\nNa jakiej skoczni odb©dzie si© konkurs?\n", true);
    comp.setHill(&hillsList[hillIndex - 1]);

    int addIndex = numberChoice("W kt¢rym miejscu doda† zawody? -1 aby jako ostatnie.\n", true) - 1;
    if (addIndex == -2)
        addIndex = -1;

    season->addCompetition(comp, addIndex);
}

void App::deleteCompetitionChoice()
{
    system("cls");
    season->showCompetitions();

    int compIndex = numberChoice("\n\nKt¢re zawody chcesz usun¥†? -1 ¾eby ostatnie.\n", true) - 1;
    if (compIndex == -2)
        compIndex = -1;

    season->deleteCompetition(compIndex);
}

void App::classificationsChoice()
{
    while (true)
    {
        system("cls");

        season->showClassifications();
        std::cout << "\n\nCo chcesz zrobi†?\n1. Dodaj klasyfikacje\n2. Usuä klasyfikacje\n3. Wr¢†\n";
        switch (numberChoice("\n", true))
        {
        case 1:
            addClassificationChoice();
            continue;
        case 2:
            deleteClassificationChoice();
            continue;
        case 3:
            return;
            break;
        }
    }
}

void App::addClassificationChoice()
{
    system("cls");
    using std::cin;
    std::string clasName;
    Classification::Type clasType;

    std::cout << "Podaj nazw© klasyfikacji: ";
    cin.clear();
    cin.ignore();
    cin.sync();
    std::getline(cin, clasName);

    std::cout << "Jaki b©dzie spos¢b liczenia punkt¢w?\n1. Zajmowane miejsca\n2. Punkty za skoki\n";
    int type = numberChoice("\n", true);
    if (type == 1)
        clasType = Classification::Places;
    else
        clasType = Classification::Points;

    season->addClassification(Classification(clasName, clasType));
}

void App::deleteClassificationChoice()
{
    system("cls");
    season->showClassifications();
    int index = numberChoice("\nKt¢r¥ klasyfikacje usun¥†? -1 ¾eby ostatni¥\n", true) - 1;
    if (index == -2)
        index = -1;

    season->deleteClassification(index);
}

void App::addTargetClassificationChoice()
{
    std::cout << "\n";
    season->showCompetitions();
    int compIndex = numberChoice("\nKt¢ry konkurs?\n", true) - 1;
    std::cout << "\n";
    season->showClassifications();
    int clasIndex = numberChoice("\nKt¢ra klasyfikacja?\n", true) - 1;

    if (compIndex == -2)
        compIndex = -1;
    if (clasIndex == -2)
        clasIndex = -1;

    season->addCompetitionTarget(compIndex, clasIndex);
}

void App::deleteTargetClassificationChoice()
{
    season->showCompetitions();
    int compIndex = numberChoice("\n\nZ kt¢rego konkursu usun¥†?\n", true) - 1;

    int i = 1;
    for (const auto &comp : season->getCompetitions())
        for (const auto &target : comp.getTargetClassifications())
        {
            std::cout << i << ". " << target->getName() << " (";
            if (target->getType() == Classification::Places)
                std::cout << "Miejsca";
            else
                std::cout << "Punkty";
            std::cout << ")\n";
            i++;
        }
    int clasIndex = numberChoice("\n\nKt¢r¥ klasyfikacje z konkursu usun¥†?\n", true) - 1;

    if (compIndex == -2)
        compIndex = -1;
    if (clasIndex == -2)
        clasIndex = -1;

    season->deleteCompetitionTarget(clasIndex, compIndex);
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

void App::saveSeason(const Season &season)
{
    using namespace std::filesystem;

    std::string seasonPath = "saves/" + season.getSaveName();

    if (!is_directory(seasonPath) || !exists(seasonPath))
        create_directories(seasonPath);

    std::ofstream ofs(seasonPath + "/save.sav");
    boost::archive::text_oarchive oa(ofs);
    oa << season;
}