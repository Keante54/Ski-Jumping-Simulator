#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"
#include "CompetitionConfig.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

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
    void singleJumpChoice();
    void settingsChoice();

    // ustawienia
    void isShowResultsChoice();
    void isShowStartingNumbersChoice();
    void isSaveStartingNumbersChoice();

    //pojedynczy skok
    void startSingleJumps(int jumpsCount, int gate);
    std::vector<JumpData> singleJumps;
    void showSingleJumpsStats();

    // konkursy
    void selectHill(Competition *comp);
    void selectCompetitionConfig(Competition *comp);
    void askForCompetitionParameters();
    std::vector<Jumper> jumpersList;
    std::vector<Hill> hillsList;
    std::vector<CompetitionConfig> competitionConfigList;
    void showJumpers();
    void showHills();
    void showCompetitionConfigs();
    Competition singleCompetition;

    int numberChoice(std::string text, bool enter);

    bool isShowResults;
    bool isShowStartingNumbers;
    bool isSaveStartingNumbers;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &isShowResults;
        ar &isShowStartingNumbers;
        ar &isSaveStartingNumbers;
    }

    void saveSettings();
    void loadSettings();
    bool isConfigFileEmpty();

    Hill * singleJumpHill;
    Jumper * singleJumpJumper;

public:
    App();
    ~App();
    void start();
};