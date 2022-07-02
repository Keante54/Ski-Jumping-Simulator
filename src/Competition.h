#pragma once
#include "JumpData.h"
#include "Jumper.h"
#include "Hill.h"
#include "CompetitionConfig.h"
#include "Classification.h"
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
    int ID;
    static int objectsCount;
    void setID() { ID = objectsCount - 1; }

    int startGate;
    double startWind;
    double windChange;
    double windFaulty;

    bool isGateComp, isWindComp;
    bool isJudges;
    bool isShowResults;

    int actualRound;

    vector<Jumper> jumpers;
    vector<Jumper *> actualJumpers;
    vector<JumpData> actualResults;
    vector<FinalResults> finalResults;
    vector<FinalResults> tempFinalResults;

    std::vector<Classification *> targetClassifications;
    std::vector<int> targetClassificationsIDs;
    void setTargetClassificationsIDs();

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
    void configFinalResults(Jumper *jumper, JumpData *jumpData);

    Hill *hill;
    CompetitionConfig competitionConfig;

    int hillID;
    void setHillID();

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &ID;
        ar &startGate;
        ar &startWind;
        ar &windChange;
        ar &windFaulty;
        ar &isGateComp;
        ar &isWindComp;
        ar &isJudges;
        ar &isShowResults;
        ar &jumpers;
        ar &finalResults;
    }

public:
    Competition(int startGate_, double startWind_, double windChange_, double windFaulty_, bool isGateComp_, bool isWindComp_, bool isJudges_, bool isShowResults_);
    Competition();
    Competition(const Competition &comp);
    Competition &operator=(const Competition &competition);
    ~Competition();

    void startCompetition();

    int getID() const { return ID; }
    int getStartGate() const { return startGate; }
    double getStartWind() const { return startWind; }
    double getWindChange() const { return windChange; }
    double getWindFaulty() const { return windFaulty; }
    bool getIsGateComp() const { return isGateComp; }
    bool getIsWindComp() const { return isWindComp; }
    bool getIsJudges() const { return isJudges; }
    CompetitionConfig getCompetitionConfig() { return competitionConfig; }
    Hill *getHill() const { return hill; }
    const std::vector<Classification *> &getTargetClassifications() const { return targetClassifications; }

    void setJumpers(const vector<Jumper> &jumpers) { this->jumpers = jumpers; }
    void setHill(Hill *const hill) { this->hill = hill; }
    void setCompetitionConfig(const CompetitionConfig &config) { competitionConfig = config; }
    void setIsShowResults(bool arg) { isShowResults = arg; }

    void loadParametersFromFile();
    void askForStartGate();
    void showParameters();

    void addTargetClassification(Classification *clas);
    void deleteTargetClassification(int index) { targetClassifications.erase(targetClassifications.begin() + index); }

    enum class SaveMode
    {
        Text,
        Csv
    };
    void saveResultsToFile(SaveMode mode);
};