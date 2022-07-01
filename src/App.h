#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"
#include "CompetitionConfig.h"

#include <vector>
#include <string>
#include <map>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
    void isShowResultsChoice();
    // konkursy
    void selectHill(Competition *comp);
    void selectCompetitionConfig(Competition *comp);
    void askForCompetitionParameters(Competition *comp);
    // ustawienia
    std::vector<Jumper> jumpersList;
    std::vector<Hill> hillsList;
    std::vector<CompetitionConfig> competitionConfigList;
    void showJumpers();
    void showHills();
    void showCompetitionConfigs();

    Competition singleCompetition;

    int numberChoice(std::string text, bool enter);
    bool isShowResults;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &isShowResults;
    }

    void saveSettings();
    void loadSettings();
    bool isConfigFileEmpty();

public:
    App();
    ~App();
    void start();
};