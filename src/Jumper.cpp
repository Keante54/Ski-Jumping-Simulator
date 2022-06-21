#include "Jumper.h"

int Jumper::objectsCount = 0;

Jumper::Jumper(std::string name_ = "", std::string surname_ = "", std::string nationality_ = "", int takeoffPowerSkill_ = 0, int takeoffTechniqueSkill_ = 0, int flightTechniqueSkill_ = 0, int flightStyle_ = 0, int landingSkill_ = 0, int form_ = 0)
{
    name = name_;
    surname = surname_;
    nationality = nationality_;
    takeoffPowerSkill = takeoffPowerSkill_;
    takeoffTechniqueSkill = takeoffTechniqueSkill_;
    flightTechniqueSkill = flightTechniqueSkill_;
    flightStyle = flightStyle_;
    landingSkill = landingSkill_;
    form = form_;
    objectsCount++;
    setID();
}

Jumper::Jumper(const Jumper &jumper)
{
    name = jumper.name;
    surname = jumper.surname;
    nationality = jumper.nationality;
    takeoffPowerSkill = jumper.takeoffPowerSkill;
    takeoffTechniqueSkill = jumper.takeoffTechniqueSkill;
    flightTechniqueSkill = jumper.flightTechniqueSkill;
    flightStyle = jumper.flightStyle;
    landingSkill = jumper.landingSkill;
    form = jumper.form;
    objectsCount++;
    setID();
}

Jumper &Jumper::operator=(const Jumper &jumper)
{
    if (this == &jumper)
        return *this;

    name = jumper.name;
    surname = jumper.surname;
    nationality = jumper.nationality;
    takeoffPowerSkill = jumper.takeoffPowerSkill;
    takeoffTechniqueSkill = jumper.takeoffTechniqueSkill;
    flightTechniqueSkill = jumper.flightTechniqueSkill;
    flightStyle = jumper.flightStyle;
    landingSkill = jumper.landingSkill;
    form = jumper.form;
    objectsCount++;
    setID();

    return *this;
}

Jumper::Jumper()
{
    name = surname = nationality = "";
    takeoffPowerSkill = takeoffTechniqueSkill = flightTechniqueSkill = landingSkill = form = 0;
    flightStyle = 1;
    setID();

    objectsCount++;
}

Jumper::~Jumper()
{
    --objectsCount;
}