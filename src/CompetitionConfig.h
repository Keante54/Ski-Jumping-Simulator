#pragma once
#include <vector>
#include <string>
using std::vector;

class CompetitionConfig
{
private:
    std::string name;
    vector<int> roundsData;

public:
    CompetitionConfig(std::string name_ = "", bool isQualifications_ = 0, const vector<int> &roundsData_ = vector<int>());
    ~CompetitionConfig();

    std::string getName() const { return name; }
    int getRoundsCount() const { return roundsData.size(); }
    vector<int> getRoundsData() const { return roundsData; }

    void setName(const std::string &arg) { name = arg; }
    void addRoundsData(int arg) { roundsData.push_back(arg); }
    void setRoundsData(const vector<int> arg) { roundsData = arg; }
};