#pragma once

#include <vector>
#include <string>

#include "Competition.h"
#include "ClassificationData.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Competition;
class ClassificationData;

class Classification
{
private:
    int ID;
    static int objectsCount;
    void setID() { ID = objectsCount - 1; };

    std::string name;
    std::vector<Competition *> competitions;
    std::vector<ClassificationData> results;
    int type;

    std::vector<int> competitionsID;
    void setCompetitionsID();
    void setCompetitionsFromIDs();

public:
    enum Type
    {
        Places,
        Points
    };

    Classification(const std::string &name_, Type t) : name(name_), type(t) {}
    Classification() {}

    int getID() const { return ID; }
    std::string getName() const { return name; };
    int getType() const { return type; }
    void setName(const std::string &arg) { name = arg; }

    void showCompetitions();

private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &name;
        ar &results;
        ar &competitionsID;
        ar &type;
    }
};