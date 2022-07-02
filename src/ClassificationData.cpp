#include "ClassificationData.h"

void ClassificationData::setJumpsData()
{
    jumpsData.clear();
    for (const auto &fin : finalResults)
        for (const auto &res : fin.jumperResults)
            jumpsData.push_back(res);
}