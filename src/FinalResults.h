#pragma once

#include <vector>

#include "JumpData.h"
#include "Jumper.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Jumper;
class JumpData;

struct FinalResults
{
    int jumperID;
    Jumper *jumper;
    vector<JumpData> jumperResults;
    double totalPoints;
    int position;

    FinalResults(Jumper *jum) : jumper(jum){};
    void show(bool isQualified, short positionColor) const;
    void setTotalPoints();
    bool operator>(const FinalResults &finalResults) const { return totalPoints > finalResults.totalPoints; }

    void setJumperID() {jumperID = jumper->getID();}
    void setJumper(std::vector<Jumper> &jumpers);

private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &jumperID;
        ar & jumperResults;
        ar & totalPoints;
        ar & position;
    }
};
