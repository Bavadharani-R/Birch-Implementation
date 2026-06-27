#include "Metrics.h"
#include <iostream>
#include <algorithm>
using namespace std;
void Metrics::evaluateOutlierDetection(vector<string> groundTruth, vector<int> noiseIndices, int totalPoints)
{
    int TP = 0, FP = 0, FN = 0, TN = 0;
    vector<bool> predictedNoise(totalPoints, false);
    for(int idx : noiseIndices)
    {
        predictedNoise[idx] = true;
    }
    for(int i = 0; i < totalPoints; i++)
    {
        bool actualNoise = (groundTruth[i] == "Noise");
        bool predNoise = predictedNoise[i];
        if(actualNoise && predNoise) TP++;
        else if(!actualNoise && predNoise) FP++;
        else if(actualNoise && !predNoise) FN++;
        else TN++;
    }
    double precision = (TP + FP > 0) ? (double)TP / (TP + FP) : 0;
    double recall = (TP + FN > 0) ? (double)TP / (TP + FN) : 0;
    double f1 = (precision + recall > 0) ? 2 * precision * recall / (precision + recall) : 0;
    cout<<"\n===== OUTLIER DETECTION METRICS (LOF) =====\n";
    cout<<"TP="<<TP<<" FP="<<FP<<" FN="<<FN<<" TN="<<TN<<endl;
    cout<<"Precision = "<<precision<<endl;
    cout<<"Recall = "<<recall<<endl;
    cout<<"F1-Score = "<<f1<<endl;
}
void Metrics::evaluateClustering(vector<string> groundTruth, vector<string> predictedLabels)
{
    int correct = 0;
    int total = 0;
    for(int i = 0; i < groundTruth.size(); i++)
    {
        if(groundTruth[i] == "Noise") continue;
        total++;
        if(groundTruth[i] == predictedLabels[i]) correct++;
    }
    double accuracy = (total > 0) ? (double)correct / total : 0;
    cout<<"\n===== CLUSTERING METRICS (BIRCH only, Emitter_1 vs Emitter_2) =====\n";
    cout<<"Correctly clustered = "<<correct<<" / "<<total<<endl;
    cout<<"Clustering Accuracy = "<<accuracy<<endl;
}
void Metrics::evaluateCombined(vector<string> groundTruth, vector<string> predictedLabels)
{
    int correct = 0;
    int total = groundTruth.size();
    for(int i = 0; i < total; i++)
    {
        if(groundTruth[i] == predictedLabels[i]) correct++;
    }
    double accuracy = (total > 0) ? (double)correct / total : 0;
    cout<<"\n===== COMBINED PIPELINE METRICS (Outlier + Clustering) =====\n";
    cout<<"Correctly labeled = "<<correct<<" / "<<total<<endl;
    cout<<"Overall Accuracy = "<<accuracy<<endl;
}