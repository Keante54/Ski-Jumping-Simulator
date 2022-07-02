#include "Classification.h"

int Classification::objectsCount = 0;

void Classification::setCompetitionsID()
{
    competitionsID.clear();
    for (const auto &comp : competitions)
    {
        competitionsID.push_back(comp->getID());
    }
}

void Classification::setCompetitionsFromIDs()
{

}