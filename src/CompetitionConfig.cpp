#include "CompetitionConfig.h"

CompetitionConfig::CompetitionConfig(std::string name_, bool isQualifications_, const vector<int> &roundsData_)
{
    name = name_;
    roundsData = roundsData_;
}

CompetitionConfig::~CompetitionConfig()
{
}