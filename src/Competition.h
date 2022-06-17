#pragma once
#include "JumpData.h"
#include "Jumper.h"
#include "Hill.h"
#include "CompetitionConfig.h"
#include <vector>

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

    int jumpsAmount;
    int secondRoundJumpersAmount;

    vector<Jumper> jumpers;
    vector<JumpData> actualResults;
    vector<JumpData> actualSortedResults;
    vector<JumpData> actualSumResults;
    vector<JumpData> actualSortedSumResults;
    vector<vector<JumpData>> resultsData;
    struct FinalResults
    {
        Jumper *jumper;
        vector<JumpData> jumperResults;
        double totalPoints;
    };

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
    void setCompetitionConfig(const CompetitionConfig &config) { competitionConfig = config; }
};