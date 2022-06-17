#include "App.h"
#include "JumpData.h"
#include "Jumper.h"
#include "Competition.h"
#include "CompetitionConfig.h"
#include "Hill.h"

#include <conio.h>
#include <vector>
#include <fstream>
#include <iostream>

App::App()
{
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

    for (const auto &cf : competitionConfigList)
    {
        cout << cf.getName() << " Ilo˜† rund: " << cf.getRoundsCount() << " S¥ kwalifikacje? " << cf.getIsQualifications() << "\n";
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
        cout << "Nie udaˆo si© otworzy† pliku jumpers.csv\n";
        getch();
    }
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
    ifs.open("resoucres/competitionConfig.csv");

    vector<int> vec;
    string name, isQual, round;
    while (getline(ifs, name, ','))
    {
        getline(ifs, isQual, ',');
        while (getline(ifs, round, ','))
            vec.push_back(stoi(round));
        competitionConfigList.push_back(CompetitionConfig(name, stoi(isQual), vec));
    }

    ifs.close();
}