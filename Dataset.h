#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include <string>
using namespace std;
class Dataset
{

private:

    vector<vector<double>> data;
public:

    bool loadCSV(string filename);
    void normalize();
    vector<vector<double>> getData();
};
#endif