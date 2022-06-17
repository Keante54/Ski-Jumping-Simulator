#include "Competition.h"
#include <Windows.h>
#include <conio.h>

Competition::Competition(int startGate_, double startWind_, double windChange_, double windFaulty_, bool isGateComp_, bool isWindComp_, bool isJudges_, bool isShowResults_)
{
    startGate = startGate_;
    startWind = startWind_;
    windChange = windChange_;
    windFaulty = windFaulty_;
    isGateComp = isGateComp_;
    isWindComp = isWindComp_;
    isJudges = isJudges_;
    isShowResults = isShowResults_;
}

Competition::Competition()
{
    startGate = startWind = windChange = windFaulty = isGateComp = isWindComp = isJudges = isShowResults = 0;
}
Competition::~Competition()
{
}

void Competition::startCompetition()
{
    Hill hill("Zakopane", "Polska", 125, 140, 151, 7, 10.8, 0, 0.3, 0.3, 88, 0.1);

    for (int actualRound = 0; actualRound < competitionConfig.getRoundsCount(); actualRound++)
    {
        for (auto &jumper : jumpers)
        {
            JumpData jumpData(&jumper, &hill, this);
            jumpData.jump();

            if (isShowResults)
            {
                jumpData.showResults();
            }
            getch();
            system("cls");
            actualResults.push_back(jumpData);
        }
    }
}