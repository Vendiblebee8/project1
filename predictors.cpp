#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <getopt.h>
#include <stdlib.h>
#include "parser.h"
#include <math.h>
#include <vector>
using namespace std;

ofstream myfile;
int size[] = {16, 32, 128, 256, 512, 1024, 2048};
int ts=0;
class answer
{
public:
    answer();
    void setT(string i);
    void setN(int i);
    string getT();
    int getN();

private:
    string type;
    int num;
};

answer::answer()
{
    type = "";
    num = 0;
}

void answer::setT(string i)
{
    type = i;
}

void answer::setN(int i)
{
    num = i;
}

string answer::getT()
{
    return type;
}

int answer::getN()
{
    return num;
}

class Data
{
public:
    Data();
    int getA();
    int getB();
    int getT();
    void setA(int i);
    void setB(int i);
    void setT(int i);

private:
    int address;
    int bValue;
    int target;
};

Data::Data()
{
    address = -1;
    bValue = -1;
    target = -1;
}

int Data::getA()
{
    return address;
}

int Data::getB()
{
    return bValue;
}

void Data::setA(int i)
{
    address = i;
}

void Data::setB(int i)
{
    bValue = i;
}

void Data::setT(int i){
    target =i;
}

int Data::getT(){
    return target;
}

vector<Data> data;
vector<answer> results;

void alwaysTaken()
{
    int taken = 0;
    answer a;
    a.setT("taken");
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).getB() == 1)
        {
            taken++;
        }
    }
    a.setN(taken);
    results.push_back(a);
}

void alwaysNonTaken()
{
    int nonTaken = 0;
    answer a;
    a.setT("non-taken");
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).getB() == 0)
        {
            nonTaken++;
        }
    }
    a.setN(nonTaken);
    results.push_back(a);
}

void singleBitbimodal(int tSize)
{
    vector<int> counter(tSize, 1);
    int correct = 0;
    int curI;
    answer a;
    a.setT("singleBitbimodal");
    for (int i = 0; i < data.size(); i++)
    {
        curI = (data.at(i).getA()) % tSize;
        if (counter.at(curI) == data.at(i).getB())
        {
            correct++;
        }
        else
        {
            counter.at(curI) = data.at(i).getB();
        }
    }
    a.setN(correct);
    results.push_back(a);
}

void twoBitbimodal(int tSize)
{
    vector<int> counter(tSize, 3);
    int correct = 0;
    int curI;
    int curS;
    answer a;
    a.setT("twoBitbimodal");
    for (int i = 0; i < data.size(); i++)
    {
        curI = (data.at(i).getA()) % tSize;
        curS = counter.at(curI);
        if ((data.at(i).getB() << 1) == (curS & 2))
        {
            correct++;
        }
        if (data.at(i).getB() == 1)
        {
            if (curS != 3)
            {
                curS++;
            }
        }
        else
        {
            if (curS != 0)
            {
                curS--;
            }
        }
        counter.at(curI) = curS;
    }
    a.setN(correct);
    results.push_back(a);
}

void gshare(int bits, int sizeC)
{
    vector<int> counter(sizeC, 3);
    int correct = 0;
    int sizeG = pow(2, bits) - 1;
    int g = 0;
    int curI;
    int curS;
    answer a;
    a.setT("gshare");
    for (int i = 0; i < data.size(); i++)
    {
        curI = (data.at(i).getA() ^ (g & sizeG)) % sizeC;
        curS = counter.at(curI);
        if ((data.at(i).getB() << 1) == (curS & 2))
        {
            correct++;
        }
        if (data.at(i).getB() == 1)
        {
            if (curS != 3)
            {
                curS++;
            }
        }
        else
        {
            if (curS != 0)
            {
                curS--;
            }
        }
        g = g << 1;
        g = g | data.at(i).getB();
        counter.at(curI) = curS;
    }
    a.setN(correct);
    results.push_back(a);
}

void tournament(int sizeB, int sizeG, int sizeT, int gBit)
{
    answer a;
    a.setT("tournament");
    int correct = 0;
    vector<int> counterB(sizeB, 3);
    vector<int> counterG(sizeG, 3);
    vector<int> counterT(sizeT, 3);
    int gSize = pow(2, gBit) - 1;
    int g = 0;
    int curIB;
    int curIG;
    int curIT;
    int curSB;
    int curSG;
    int curST;
    for (int i = 0; i < data.size(); i++)
    {
        curIB = data.at(i).getA() % sizeB;
        curSB = counterB.at(curIB);
        curIG = (data.at(i).getA() ^ (g & gSize)) % sizeG;
        curSG = counterG.at(curIG);
        curIT = data.at(i).getA() % sizeT;
        curST = counterT.at(curIT);
        int predictB = curSB & 2;
        int predictG = curSG & 2;
        if (data.at(i).getB() == 1)
        {
            if (curSB != 3)
            {
                curSB++;
            }
            if (curSG != 3)
            {
                curSG++;
            }
        }
        else
        {
            if (curSB != 0)
            {
                curSB--;
            }
            if (curSG != 0)
            {
                curSG--;
            }
        }
        g = g << 1;
        g = g | data.at(i).getB();
        counterB.at(curIB) = curSB;
        counterG.at(curIG) = curSG;
        if (predictB == predictG)
        {
            if ((data.at(i).getB() << 1) == predictG)
            {
                correct++;
            }
        }
        else
        {
            if ((curST & 2) == 2)
            {
                if ((data.at(i).getB() << 1) == predictG)
                {
                    correct++;
                    if (curST != 3)
                    {
                        curST++;
                    }
                }
                else
                {
                    if (curST != 0)
                    {
                        curST--;
                    }
                }
            }
            else
            {
                if ((data.at(i).getB() << 1) == predictB)
                {
                    correct++;
                    if (curST != 0)
                    {
                        curST--;
                    }
                }
                else
                {
                    if (curST != 3)
                    {
                        curST++;
                    }
                }
            }
        }
        counterT.at(curIT) = curST;
    }
    a.setN(correct);
    results.push_back(a);
}

void singleBitbimodalT(int tSize)
{
    vector<int> counter(tSize, 1);
    int correct = 0;
    int curI;
    answer a;
    a.setT("singleBitbimodal");
    for (int i = 0; i < data.size(); i++)
    {
        curI = (data.at(i).getT()) % tSize;
        if (counter.at(curI) == data.at(i).getB() && ((data.at(i).getA()%2)==0 || (data.at(i).getT()%2==0)))
        {
            correct++;
        }
        else
        {
            counter.at(curI) = data.at(i).getB();
        }
    }
    a.setN(correct);
    results.push_back(a);
}

void readFile(string file)
{
    unsigned long long addr;
    string behavior;
    unsigned long long target;
    ifstream infile(file.c_str());
    int branches = 0;
    while (infile >> std::hex >> addr >> behavior >> std::hex >> target)
    {
        stringstream ss;
        Data b;
        branches++;
        if (behavior == "T"){
            b.setB(1);
            ts++;
        }
        else
        {
            b.setB(0);
        }
        b.setA(addr);
        b.setT(target);
        data.push_back(b);
    }
    infile.close();
}

int main(int argc, char *argv[])
{
    int runs = 0;
    ifstream fin;
    char commands;
    string input = "default";
    string output = "default";

    input = argv[1];  // gets input file name
    output = argv[2]; // gets output file name
    readFile(input);
    myfile.open(output);
    alwaysTaken();
    myfile << results.at(runs).getN() << "," << data.size() << ";" << endl;
    runs++;
    alwaysNonTaken();
    myfile << results.at(runs).getN() << "," << data.size() << ";" << endl;
    runs++;
    for (int i = 0; i < 7; i++)
    {
        singleBitbimodal(size[i]);
        myfile << results.at(runs).getN() << "," << data.size() << "; ";
        runs++;
    }
    myfile << endl;
    for (int i = 0; i < 7; i++)
    {
        twoBitbimodal(size[i]);
        myfile << results.at(runs).getN() << "," << data.size() << "; ";
        runs++;
    }
    myfile << endl;
    for (int i = 3; i < 12; i++)
    {
        gshare(i, 2048);
        myfile << results.at(runs).getN() << "," << data.size() << "; ";
        runs++;
    }
    myfile << endl;
    tournament(2048, 2048, 2048, 11);
    myfile << results.at(runs).getN() << "," << data.size() << ";" << endl;
    runs++;
    singleBitbimodalT(512);
    myfile << results.at(runs).getN() << ",";
    runs++;
    singleBitbimodalT(512);
    myfile << results.at(runs).getN() << ";" << endl;
    runs++;
}