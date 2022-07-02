#pragma once

#include <vector>

#include "JumpData.h"
#include "Jumper.h"

class Jumper;
class JumpData;

struct FinalResults
{
    Jumper *jumper;
    vector<JumpData*> jumperResults;
    double totalPoints;
    int position;
    FinalResults(Jumper *jum) : jumper(jum) { };
    FinalResults();
    ~FinalResults();

    void show(bool isQualified, short positionColor) const;
    void setTotalPoints();
    bool operator>(const FinalResults &finalResults) const { return totalPoints > finalResults.totalPoints; }

    void setJumper(std::vector<Jumper> &jumpers);
};
