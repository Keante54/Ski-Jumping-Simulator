#pragma once
#include <vector>
#include <string>
using std::vector;

class CompetitionConfig
{
private:
    std::string name;
    bool isQualifications;
    vector<int> roundsData;

public:
    CompetitionConfig(std::string name_ = "", bool isQualifications_ = 0, const vector<int> &roundsData_ = vector<int>());
    ~CompetitionConfig();

    std::string getName() const { return name; }
    int getRoundsCount() const { return roundsData.size(); }
    bool getIsQualifications() const { return isQualifications; }
    vector<int> getRoundsData() const { return roundsData; }

    void setIsQualifications(bool arg) { isQualifications = arg; }
    void setRoundsData(const vector<int> arg) { roundsData = arg; }
};