#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <getopt.h>
#include <stdlib.h>
#include "parser.h"
#include <vector>
using namespace std;

ofstream myfile;

bool fileOpen(string file, ifstream &fileObj)
{
    fileObj.open(file);
    if (fileObj.is_open())
    {
        return true;
    }
    else
    {
        cout << "does not open" << endl;
        return false;
    }
}

void readFile(string file, ifstream &fileObj, string output)
{
    string line;
    while (getline(fileObj, line))
    {

    }
}

int main(int argc, char *argv[])
{
    ifstream fin;
    char commands;
    string input = "default";
    string output = "default";

    input = argv[1]; //gets input file name
    output = argv[2]; //gets output file name
    if (fileOpen(input, fin)) //opens input file
    {
        readFile(input, fin, output); //reads in input file
        fin.close(); //closes input file
    }
}