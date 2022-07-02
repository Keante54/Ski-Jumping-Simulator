#pragma once
#include "Jumper.h"
#include "Hill.h"
#include "Competition.h"
#include "CompetitionConfig.h"
#include "Season.h"

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
    void seasonsChoice();
    void singleCompetitionChoice();
    void settingsChoice();

    // ustawienia
    void isShowResultsChoice();

    // sezony
    void createSeasonChoice();
    // tworzenie kalendarza
    void addCompetitionChoice();
    void deleteCompetitionChoice();
    void classificationsChoice();
    void addClassificationChoice();
    void deleteClassificationChoice();
    void addTargetClassificationChoice();
    void deleteTargetClassificationChoice();

    // konkursy
    void selectHill(Competition *comp);
    void selectCompetitionConfig(Competition *comp);
    void askForCompetitionParameters(Competition *comp);
    std::vector<Jumper> jumpersList;
    std::vector<Hill> hillsList;
    std::vector<CompetitionConfig> competitionConfigList;
    void showJumpers();
    void showHills();
    void showCompetitionConfigs();
    Competition singleCompetition;

    std::vector<Season> seasons;
    std::unique_ptr<Season> season;
    void setSeason(Season *s) { season.reset(s); }

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

    void saveSeason(const Season & season);

public:
    App();
    ~App();
    void start();
};