#include <iostream>

#include "Dataset.h"
#include "CFTree.h"
#include "GlobalClustering.h"
#include "Phase2.h"
#include "Phase3.h"
#include "Output.h"
using namespace std;


int main()
{

    Dataset dataset;


    if(!dataset.loadCSV(
        "two_emitter_pdw_dataset.csv"))
    {
        return 1;
    }



    dataset.normalize();



    vector<vector<double>> data =
        dataset.getData();



    cout<<"Rows: "
        <<data.size()
        <<endl;


    cout<<"Features: "
        <<data[0].size()
        <<endl;



    double threshold = 0.5;

    int branchingFactor = 5;



    CFTree tree(
        threshold,
        branchingFactor
    );



    // ============================
    // PHASE 1
    // CF TREE CONSTRUCTION
    // ============================


    for(auto point:data)
    {
        tree.insert(point);
    }



    tree.printTree();

    tree.printClusters();



    vector<CF> leafCFs =
        tree.getLeafCFs();



    GlobalClustering::printCFs(leafCFs);




    // ============================
    // PHASE 2
    // CONDENSE CF TREE
    // ============================


    cout<<"\n===== PHASE 2 =====\n";



    Phase2 phase2(5);



    vector<CF> cleanCFs =
        phase2.condense(
            tree.getRoot()
        );



    cout<<"CFs after condensation: "
        <<cleanCFs.size()
        <<endl;




    // ============================
    // PHASE 3
    // GLOBAL CLUSTERING
    // ============================


    cout<<"\n===== PHASE 3 =====\n";



    Phase3 phase3(2);



    vector<int> labels =
        phase3.cluster(
            cleanCFs
        );



    for(int i=0;i<labels.size();i++)
    {

        cout<<"Micro Cluster "
            <<i
            <<" belongs to Cluster "
            <<labels[i]
            <<endl;

    }
// =====================================
// FINAL DATA POINT CLUSTER ASSIGNMENT
// =====================================


cout<<"\n===== FINAL DATA LABELING =====\n";



vector<int> finalLabels =
    Output::assignClusters(
        data,
        cleanCFs,
        labels
    );



for(int i=0;i<finalLabels.size();i++)
{

    cout<<"Point "
        <<i
        <<" -> Cluster "
        <<finalLabels[i]
        <<endl;

}



// =====================================
// SAVE OUTPUT CSV
// =====================================


Output::saveCSV(

    "birch_results.csv",

    data,

    finalLabels

);


cout<<"\nResult saved to birch_results.csv\n";


    return 0;

}