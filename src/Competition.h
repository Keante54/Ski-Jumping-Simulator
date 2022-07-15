#pragma once
#include "JumpData.h"
#include "Jumper.h"
#include "Hill.h"
#include "CompetitionConfig.h"
#include "FinalResults.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

using std::vector;

class Jumper;
class JumpData;
class FinalResults;
class Classification;

class Competition
{
private:
    int startGate;
    double startWind;
    double windChange;
    double windFaulty;

    int actualGate;

    bool isGateComp, isWindComp;
    bool isJudges;
    bool isShowResults;
    bool isShowStartingNumbers;
    bool isSaveStartingNumbers;

    int actualRound;

    int type;

    vector<Jumper> jumpers;
    vector<Jumper *> actualJumpers;
    vector<JumpData> actualResults;
    vector<FinalResults> finalResults;
    vector<FinalResults> tempFinalResults;

    double toBeatDistance;
    void setToBeatDistance(const FinalResults & fin, const JumpData & jum);

    template <typename T>
    void sortResultsVector(vector<T> &vec);
    void setFinalResultsPosition();
    void updateActualJumpers();
    void roundSummary();
    void competitionSummary();
    void sortActualJumpers();
    void showStartList(int actualIndex);

    void showActualResults(bool isFinal);
    void showFullResults();
    void configFinalResults(Jumper *jumper, JumpData *jumpData, int index);

    Hill *hill;
    CompetitionConfig competitionConfig;

public:
    Competition(int startGate_, double startWind_, double windChange_, double windFaulty_, bool isGateComp_, bool isWindComp_, bool isJudges_, bool isShowResults_);
    Competition();
    ~Competition();

    void startCompetition();

    int getStartGate() const { return startGate; }
    int getActualGate() const { return actualGate; }
    double getStartWind() const { return startWind; }
    double getWindChange() const { return windChange; }
    double getWindFaulty() const { return windFaulty; }
    bool getIsGateComp() const { return isGateComp; }
    bool getIsWindComp() const { return isWindComp; }
    bool getIsJudges() const { return isJudges; }
    CompetitionConfig getCompetitionConfig() { return competitionConfig; }
    Hill *getHill() const { return hill; }
    int getType() const { return type; }

    void setJumpers(vector<Jumper> jum) { jumpers = jum; }
    void setHill(Hill *const hl) { hill = hl; }
    void setCompetitionConfig(const CompetitionConfig &config) { competitionConfig = config; }
    void setIsShowResults(bool arg) { isShowResults = arg; }
    void setIsShowStartingNumbers(bool arg) { isShowStartingNumbers = arg; }
    void setIsSaveStartingNumbers(bool arg) { isSaveStartingNumbers = arg; }
    void setStartGate(int arg) { startGate = arg; }
    void setActualGate(int arg) { actualGate = arg; }
    void setType(int arg) { type = arg; }

    void loadParametersFromFile();
    void askForStartGate();
    void showParameters();

    enum Type
    {
        MultipleJumps,
        SingleJump
    };

    enum class SaveMode
    {
        Text,
        Csv
    };
    void saveResultsToFile(SaveMode mode);
};