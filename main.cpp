#include <iostream>
using namespace std;
#include "other.cpp"
#include "Hill.cpp"
#include "Jumper.cpp"

void loadHills();
void loadJumpers();
void loadConfig(Hill &h);
void selectHill(Hill &h);
void selectTrainingJumper(Jumper &jp);
void showHillInfo(Hill hl);
void showJumpers();
void defaultClearFile(string file);
Hill hill;
Jumper trainingJumper;
fstream hillsfile, jumpersfile, configfile, resultsfile;
vector<Hill> hills;
vector<Jumper> jumpers;
#define tj trainingJumper

int main()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    // defaultClearFile("../results/training/tresults.csv");
    // defaultClearFile("../results/training/tresults.txt");
    // loadHills();
    // loadJumpers(true);
    char choice;
    string choice1;
    Jumper jp;

    cout << "Symulator skokow narciarskich " << APP_VERSION << "\n1. Seria skokow\n2. Pojedynczy skok";
    choice = getch();
    switch (choice)
    {
    case '1':
    {
        vector<Jumper> saveJumpers;
        cls;
        loadJumpers();
        loadHills();
        selectHill(hill);
        cls;
        // showJumpers();
        loadConfig(hill);
        hill.startWind = randomDouble(hill.typicalWind[0], hill.typicalWind[1]);

        for (auto &jp : jumpers)
        {
            jp.points = 0;
        }

        rsf.open("results/results.txt", ios::out);
        rsf.clear();
        rsf.close();
        rsf.open("results/results.csv", ios::out);
        rsf.clear();
        rsf.close();

        int i = 0;
        hill.leaderPoints = 0;
        for (auto &jp : jumpers)
        {
            jp.setDsq();
            jp.hill = hill;
            jp.wind = hill.startWind;

            if (hill.IsshowResults == 1)
            {
                jp.setup();
            }
            if (i == 0)
            {
                cout << "Belka startowa: ";
                cin >> hill.startGate;
            }

            jp.hill.startGate = hill.startGate;

            if (i == 0)
                jumpers[0].gate = hill.startGate;
            else if (hill.IsshowResults == 1)
            {
                cout << "Belka: ";
                cin >> jp.gate;
            }
            cls;

            hill.startGate = jumpers[0].gate;

            if (hill.IsshowResults == 0)
            {
                jp.gate = hill.startGate;
            }
            jp.gateDiff = hill.startGate - jp.gate;
            for (auto jp : jumpers)
            {
                if (jp.points > hill.leaderPoints)
                    hill.leaderPoints = jp.points;
            }
            if (jp.dsq == false)
            {
                jp.jump();
                if (hill.IsshowResults == 1)
                {
                    jp.showDistanceAndToBeat();
                    jp.showResult();
                }
            }
            if (jp.dsq == true)
            {
                cout << "Dyskwalifikacja!!!" << endl;
                cout<< "Powod: "<<jp.dsqReason<<endl;
            }

            if (hill.IsshowResults == 1)
            {
                if (hill.sleepAfterJump <= 0)
                    getch();
                else
                    Sleep(hill.sleepAfterJump);
                cls;
            }

            if (i == 0)
            {
                hill.leaderPoints = jp.points;
            }

            cls;
            saveJumpers.push_back(jp);
            i++;
            jp.saveToCsv("results/results.csv");
            jp.saveToTxt("results/results.txt");
        }

        break;
    }

    case '2':
    {
        break;
        cls;
        loadJumpers();
        loadHills();
        selectHill(hill);
        cls;
        loadConfig(hill);
        tj.hill = hill;
        selectTrainingJumper(tj);
        cls;

        cout << "Belka: ";
        cin >> tj.gate;
        hill.startGate = tj.gate;
        tj.setup();
        tj.jump();
        tj.showDistanceAndToBeat();
        tj.showResult();

        getch();

        break;
    }
    }

    getch();
}
void showJumpers()
{
    int n = 1;
    cout << "Lista startowa:\n";
    for (auto jp : jumpers)
    {
        cout << n << ". " << jp.name << " " << jp.surname << " (" << jp.nationality << ")";
        n++;
    }
}

void selectHill(Hill &h)
{
    int i = 1, c;
    for (auto hill : hills)
    {
        cout << i << ". " << hill.name << " (" << hill.country << ") "
             << "K" << hill.kpoint << " HS" << hill.hspoint << endl;
        i++;
    }
    cout << "Skocznia: ";
    cin >> c;
    h = hills[c - 1];
}

void selectTrainingJumper(Jumper &jp)
{
    int i = 1, c;
    for (auto jp : jumpers)
    {
        cout << i << ". " << jp.name << " " << jp.surname << " (" << jp.nationality << ")" << endl;
        i++;
    }
    cout << "Zawodnik: ";
    cin >> c;
    jp = jumpers[c - 1];
}

void loadConfig(Hill &h)
{
    string tmp;
    cf.open("resources/config.csv");
    if (cf.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku. Zamykam program...";
        Sleep(2500);
        exit(0);
    }
    getline(cf, tmp, ',');
    h.typicalWind[0] = stod(tmp);
    getline(cf, tmp, ',');
    h.typicalWind[1] = stod(tmp);
    getline(cf, tmp, ',');
    h.windChange = stod(tmp);
    getline(cf, tmp, ',');
    h.windFaulty = stod(tmp);
    getline(cf, tmp, ',');
    h.windComp = stoi(tmp);
    getline(cf, tmp, ',');
    h.gateComp = stoi(tmp);
    getline(cf, tmp, ',');
    h.isJudges = stoi(tmp);
    getline(cf, tmp, ',');
    h.IsshowResults = stoi(tmp);
    getline(cf, tmp, ',');
    h.sleepAfterJump = stoi(tmp);
    // getline(cf, tmp, ',');
    // h.autoWind = stoi(tmp);
}

void loadHills()
{
    Hill vechill;
    string tmp;
    hlf.open("resources/hills.csv", ios::in);
    if (hlf.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku. Zamykam program...";
        Sleep(2500);
        exit(0);
    }
    while (getline(hlf, vechill.name, ','))
    {
        getline(hlf, vechill.country, ',');
        getline(hlf, tmp, ',');
        vechill.kpoint = stoi(tmp);
        getline(hlf, tmp, ',');
        vechill.hspoint = stoi(tmp);
        getline(hlf, tmp, ',');
        vechill.gatePoints = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.gateMeters = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.windPointsFront = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.windMetersFront = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.windPointsBack = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.windMetersBack = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.maxdist = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.startDist = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.optimalTakeoffPower = stoi(tmp);
        getline(hlf, tmp, ',');
        vechill.takeoffPowerImportance = stod(tmp);
        getline(hlf, tmp, ',');
        vechill.takeoffTechniqueMeters = stod(tmp);
        getline(hlf, tmp);
        vechill.flightTechniqueMeters = stod(tmp);
        hills.push_back(vechill);
    }
    hlf.close();
}

void loadJumpers()
{
    Jumper jp;
    string tmp;
    jpf.open("resources/jumpers.csv", ios::in);
    if (jpf.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku. Zamykam program...";
        Sleep(2500);
        exit(0);
    }
    while (getline(jpf, jp.name, ','))
    {
        //cout << jp.name << endl;
        getline(jpf, jp.surname, ',');
        // cout << jp.surname << endl;
        getline(jpf, jp.nationality, ',');
        // cout << jp.nationality << endl;
        getline(jpf, tmp, ',');
        jp.takeoffPowerS = stoi(tmp);
        // cout << jp.takeoffPowerS << endl;
        getline(jpf, tmp, ',');
        jp.takeoffTechniqueS = stoi(tmp);
        // cout << jp.takeoffTechniqueS << endl;
        getline(jpf, tmp, ',');
        jp.flightTechniqueS = stoi(tmp);
        // cout << jp.flightTechniqueS << endl;
        getline(jpf, tmp, ',');
        jp.flightStyle = stoi(tmp);
        // cout << jp.flightStyle << endl;
        getline(jpf, tmp, ',');
        jp.landSkill = stoi(tmp);
        // cout << jp.landSkill << endl;
        getline(jpf, tmp);
        jp.form = stoi(tmp);
        jumpers.push_back(jp);
    }
    jpf.close();
}
