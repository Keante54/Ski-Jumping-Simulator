#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "CompetitionConfig.h"

#include <vector>

class App
{
private:
    void loadJumpersFromFile();
    void loadHillsFromFile();
    void loadCompetitionConfigFromFile();

    std::vector<Jumper> jumpersList;
    std::vector<Hill> hillsList;
    std::vector<CompetitionConfig> competitionConfigList;

public:
    App();
    ~App();
    void start();
};