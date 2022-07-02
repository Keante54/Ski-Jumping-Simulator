#include "Jumper.h"
#include <iostream>

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
}

Jumper::Jumper()
{
    name = surname = nationality = "";
    takeoffPowerSkill = takeoffTechniqueSkill = flightTechniqueSkill = landingSkill = form = 0;
    flightStyle = 1;
}

Jumper::~Jumper()
{
}

std::ostream &operator<<(std::ostream &os, const Jumper &jumper)
{
    os << jumper.getName() << " " << jumper.getSurname() << " (" << jumper.getNationality() << ")";
    return os;
}