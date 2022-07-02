#include "Season.h"

#include <iostream>
#include <Windows.h>

Season::Season()
{
    saveName = "name";
}

void Season::showCompetitions()
{
    int i = 1;
    for (const auto &comp : competitions)
    {
        std::cout << i << ". " << *comp.getHill();
        if (comp.getTargetClassifications().size() != 0)
        {
            std::cout << " (";
            for (const auto &target : comp.getTargetClassifications())
                std::cout << target->getName() << ",";
            std::cout << ")";
        }
        std::cout << "\n";
        i++;
    }
}

void Season::addCompetition(const Competition &comp, int index = -1)
{
    if (index == (-1))
        competitions.push_back(comp);
    else
        competitions.insert(competitions.begin() + index, comp);

    std::cout << "Dodano zawody na skoczni " << *comp.getHill() << "\n";
    Sleep(800);
}

void Season::deleteCompetition(int index = -1)
{
    if (index == (-1))
        index = competitions.size() - 1;

    std::cout << "Usuni©to zawody na skoczni " << *competitions[index].getHill() << "\n";
    competitions.erase(competitions.begin() + index);
    Sleep(800);
}

void Season::addCompetitionTarget(int classificationIndex = -1, int competitionIndex = -1)
{
    if (classificationIndex == -1)
        classificationIndex = classifications.size() - 1;
    if (competitionIndex == -1)
        competitionIndex = competitions.size() - 1;

    competitions[competitionIndex].addTargetClassification(&classifications[classificationIndex]);
    std::cout << "Dodano klasyfikacj© " << classifications[classificationIndex].getName() << " do konkursu na skoczni " << *competitions[competitionIndex].getHill() << "\n";
    Sleep(800);
}

void Season::deleteCompetitionTarget(int classificationIndex = -1, int competitionIndex = -1)
{
    if (classificationIndex == -1)
        classificationIndex = classifications.size() - 1;
    if (competitionIndex == -1)
        competitionIndex = competitions.size() - 1;

    std::cout << "Usuni©to klasyfikacj© " << classifications[classificationIndex].getName() << " z konkursu na skoczni " << *competitions[competitionIndex].getHill() << "\n";
    competitions[competitionIndex].deleteTargetClassification(competitionIndex);
    Sleep(800);
}

void Season::showClassifications()
{
    int i = 1;
    for (const auto &clas : classifications)
    {
        std::cout << i << ". " << clas.getName();
        if (clas.getType() == Classification::Places)
            std::cout << " (Miejsca)\n";
        else
            std::cout << " (Punkty)\n";
        i++;
    }
}

void Season::addClassification(const Classification &clas)
{
    classifications.push_back(clas);
    std::cout << "Dodano klasyfikacje " << clas.getName() << "\n";
    Sleep(800);
}

void Season::deleteClassification(int index = -1)
{
    if (index == (-1))
        index = classifications.size() - 1;

    std::cout << "Usuni©to klasyfikacje " << classifications[index].getName() << "\n";
    classifications.erase(classifications.begin() + index);
    Sleep(800);
}