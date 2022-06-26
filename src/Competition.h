#pragma once
#include "JumpData.h"
#include "Jumper.h"
#include "Hill.h"
#include "CompetitionConfig.h"
#include <vector>
#include <string>
#include <iostream>

using std::vector;

class Jumper;
class JumpData;

class Competition
{
private:
    int startGate;
    double startWind;
    double windChange;
    double windFaulty;

    bool isGateComp, isWindComp;
    bool isJudges;
    bool isShowResults;

    int actualRound;

    struct FinalResults
    {
        Jumper *jumper;
        vector<JumpData> jumperResults;
        double totalPoints;
        int position;

        FinalResults(Jumper *jum) : jumper(jum){};
        void show(bool isQualified) const;
        void setTotalPoints();
        bool operator>(const FinalResults &finalResults) const { return totalPoints > finalResults.totalPoints; }
    };

    vector<Jumper> jumpers;
    vector<Jumper *> actualJumpers;
    vector<JumpData> actualResults;
    vector<FinalResults> finalResults;
    vector<FinalResults> tempFinalResults;

    template <typename T>
    void sortResultsVector(vector<T> &vec);
    void setFinalResultsPosition();
    void updateActualJumpers();
    void roundSummary();
    void competitionSummary();
    void sortActualJumpers();
    void showStartList();

    void showActualResults(bool isFinal, bool nextRound);
    void configFinalResults(Jumper *jumper, JumpData *jumpData);

    Hill *hill;
    CompetitionConfig competitionConfig;

public:
    Competition(int startGate_, double startWind_, double windChange_, double windFaulty_, bool isGateComp_, bool isWindComp_, bool isJudges_, bool isShowResults_);
    Competition();
    ~Competition();

    void startCompetition();

    int getStartGate() const { return startGate; }
    double getStartWind() const { return startWind; }
    double getWindChange() const { return windChange; }
    double getWindFaulty() const { return windFaulty; }
    bool getIsGateComp() const { return isGateComp; }
    bool getIsWindComp() const { return isWindComp; }
    bool getIsJudges() const { return isJudges; }
    CompetitionConfig getCompetitionConfig() { return competitionConfig; }
    Hill *getHill() { return hill; }

    void setJumpers(const vector<Jumper> &jumpers) { this->jumpers = jumpers; }
    void setHill(Hill *const hill) { this->hill = hill; }
    void setCompetitionConfig(const CompetitionConfig &config) { competitionConfig = config; }

    void loadParametersFromFile();
    void askForStartGate();
    void showParameters();

    enum class SaveMode
    {
        Text,
        Csv
    };
    void saveResultsToFile(SaveMode mode);
};