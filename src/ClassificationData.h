#pragma once

#include "Jumper.h"
#include "FinalResults.h"
#include "JumpData.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>


class FinalResults;
class JumpData;

class ClassificationData
{
private:
    int jumperID;
    Jumper *jumper;
    std::vector<FinalResults> finalResults;
    std::vector<JumpData> jumpsData;

    void setJumperID(){jumperID = jumper->getID();}
    void setJumpsData();

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &jumperID;
        ar & finalResults;
        ar & jumpsData;
    }

public:
};