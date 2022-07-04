#include "FinalResults.h"
#include "Random.h"


FinalResults::FinalResults()
{
}


FinalResults::~FinalResults()
{
}


void FinalResults::show(bool isQualified, short positionColor = 7) const
{
    using std::cout;
    using std::fixed;
    using std::setprecision;

    colorText(positionColor, position);
    colorText(7, ". " + jumper->getName() + " " + jumper->getSurname() + " (" + jumper->getNationality() + ")");
    colorText(15, " --> ");

    for (const auto &res : jumperResults)
    {
        colorText(3, res.getDistance());
        colorText(3, "m");
        cout << " (";
        cout << fixed << setprecision(1);
        colorText(6, res.getPoints());
        colorText(6, "pts");
        cout << "), ";
        cout << fixed;
    }
    colorText(15, "--> ");
    colorText(14, totalPoints);
    colorText(14, "pts");
    if (isQualified)
        colorText(15, " (Q)\n");
    else
        cout << "\n";
}
void FinalResults::setTotalPoints()
{
    totalPoints = 0;
    for (const auto &res : jumperResults)
    {
        totalPoints += res.getPoints();
    }
}