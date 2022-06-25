#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"
#include "CompetitionConfig.h"

#include <vector>
#include <string>
#include <map>

class App
{
private:
    void loadJumpersFromFile();
    void loadHillsFromFile();
    void loadCompetitionConfigFromFile();

    // wybory w menu
    void singleCompetitionChoice();
    void settingsChoice();

    // mini-funkcje dla wybor¢w w menu
    //konkursy
    void selectHill(Competition * comp);
    void selectCompetitionConfig(Competition * comp);
    void askForCompetitionParameters(Competition *comp);
    //ustawienia
    std::vector<Jumper> jumpersList;
    std::vector<Hill> hillsList;
    std::vector<CompetitionConfig> competitionConfigList;
    void showJumpers();
    void showHills();
    void showCompetitionConfigs();

    Competition singleCompetition;

    int numberChoice(std::string text, bool enter);

public:
    App();
    ~App();
    void start();
};