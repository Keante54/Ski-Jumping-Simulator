#include "other.h"

/*void initSave(string filename)
{
    cout << "";
}

void defaultClearFile(string file)
{
    rsf.open(file, ios::out);
    rsf.clear();
    rsf.close();
}*/

int randomInt(int a, int b)
{
    /*int r1, r2[3000], r3;
    random_device dev;
    uniform_int_distribution<int> rd(a, b);
    uniform_int_distribution<int> rd1(0, 2999);
    r1 = rd1(dev);
    for (auto rr : r2)
    {
        rr = rd(dev);
    }
    r3 = r2[r1];
    return r3;*/
    random_device dev;
    uniform_int_distribution<int> rd(a, b);
    return rd(dev);
}

double randomDouble(double min, double max)
{
    srand(time(NULL));
    double rr[50];
    int rrr = randomInt(0, 49);
    for (int i = 0; i <= 49; i++)
    {
        rr[i] = ((double)rand() / RAND_MAX) * (max - min) + min;
    }
    return rr[rrr];
}

void colorText(unsigned short color, string text)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    cout << text;
}

double percent(double prc, double num)
{
    double sum;
    sum = (prc / 100) * num;
    return sum;
}

double normalRandom(double mid, double a)
{
    srand(time(NULL));
    default_random_engine gen;
    normal_distribution<double> ndist(mid, a);
    double result, min, max;
    double rd[1000];
    int nr = randomInt(0, 999);

    for (int i = 0; i < 1000; i++)
    {
        rd[i] = ndist(gen);
        if (i == 0)
        {
            min = rd[i];
            max = rd[i];
        }
        if (rd[i] > max)
            max = rd[i];
        else if (rd[i] < min)
            min = rd[i];
    }

    return rd[nr];
}
void binomalRandom(int up, int chance)
{
    default_random_engine gen;
    binomial_distribution<int> bdist(up, chance);

    for (int i = 0; i <= 100; i++)
    {
        cout << i + 1 << ". " << bdist(gen) << endl;
    }
}