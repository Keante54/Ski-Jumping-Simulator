#pragma once
#include <string>

class Jumper
{
private:
    unsigned int ID;
    std::string name, surname, nationality;
    enum flightStyles // style lotu
    {
        ClassicStyle,
        VStyle,
        ModernVStyle,
        WideVStyle,
        HStyle
    };

    // umiejetnosci skoczka
    int takeoffPowerSkill, takeoffTechniqueSkill, flightTechniqueSkill;
    int flightStyle;
    int landingSkill;
    int form;
    static int objectsCount;

public:
    Jumper(std::string name_, std::string surname_, std::string nationality_, int takeoffPowerSkill_, int takeoffTechniqueSkill_, int flightTechniqueSkill_, int flightStyle_, int landingSkill_, int form_);
    Jumper(const Jumper &jumper);
    Jumper();
    ~Jumper();

    Jumper &operator=(const Jumper &jumper);

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getNationality() const { return nationality; }
    int getTakeoffPowerSkill() const { return takeoffPowerSkill; }
    int getTakeoffTechniqueSkill() const { return takeoffTechniqueSkill; }
    int getFlightTechniqueSkill() const { return takeoffTechniqueSkill; }
    int getFlightStyle() const { return flightStyle; }
    int getLandingSkill() const { return landingSkill; }
    int getForm() const { return form; }
    int getID() const { return ID; }
    static int getObjectsCount() { return objectsCount; }

    void setTakeoffPowerSkill(int arg) { takeoffPowerSkill = arg; }
    void setTakeoffTechniqueSkill(int arg) { takeoffTechniqueSkill = arg; }
    void setFlightTechniqueSkill(int arg) { flightTechniqueSkill = arg; }
    void setFlightStyle(int arg) { flightStyle = arg; }
    void setLandingSkill(int arg) { landingSkill = arg; }
    void setForm(int arg) { form = arg; }
    void setID() { ID = objectsCount - 1; }
};