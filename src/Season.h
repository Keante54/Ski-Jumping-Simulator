#pragma once

#include <vector>
#include <string>

#include "Competition.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Season
{
private:
    std::string saveName;
    std::vector<Competition> competitions;
    std::vector<Classification> classifications;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &saveName;
        ar &competitions;
        ar &classifications;
    }

public:
    Season();
    Season(const std::string &name) : saveName(name) {}

    std::string getSaveName() const { return saveName; }
    std::vector<Competition> getCompetitions() const { return competitions; }
    std::vector<Classification> getClassifications() const { return classifications; }

    void setName(const std::string &name) { saveName = name; }

    // konkursy
    void showCompetitions();
    void addCompetition(const Competition &comp, int index);
    void deleteCompetition(int index);

    void addCompetitionTarget(int classificationIndex, int competitionIndex);
    void deleteCompetitionTarget(int classificationIndex, int competitionIndex);
    // klasyfikacje
    void showClassifications();
    void addClassification(const Classification &clas);
    void deleteClassification(int index);
};