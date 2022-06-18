#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"
#include "CompetitionConfig.h"

#include <vector>
#include <string>

class App
{
private:
    void loadJumpersFromFile();
    void loadHillsFromFile();
    void loadCompetitionConfigFromFile();

    // wybory w menu
    void singleCompetitionChoice();

    // mini-funkcje dla wybor¢w w menu
    void selectHill(Competition * comp);
    void selectCompetitionConfig(Competition * comp);

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