# Running the Project

## Requirements

Before running the project, make sure the following tools are installed:

- C++ compiler (G++ recommended)
- Git
- Terminal / Command Prompt

The project was developed and tested using:


C++17
G++ Compiler
Windows/Linux Environment


---

# Step 1: Clone the Repository

Clone the GitHub repository:

```bash
git clone <repository_url>

Move into the project directory:

cd BIRCH_Project

The project directory should contain:

BIRCH_Project
│
├── main.cpp
├── CF.cpp
├── CF.h
├── CFNode.cpp
├── CFNode.h
├── CFTree.cpp
├── CFTree.h
├── Dataset.cpp
├── Dataset.h
├── Phase2.cpp
├── Phase2.h
├── Phase3.cpp
├── Phase3.h
├── GlobalClustering.cpp
├── GlobalClustering.h
├── Output.cpp
├── Output.h
│
└── two_emitter_pdw_dataset.csv
Step 2: Dataset Placement

Place the input dataset file inside the project folder:

two_emitter_pdw_dataset.csv

The program reads this file during execution.

The dataset contains five input features:

TOA_ns
Freq_MHz
PW_ns
Az_deg
El_deg
Step 3: Compile the Program

Compile all C++ source files together:

g++ main.cpp CF.cpp CFNode.cpp CFTree.cpp Dataset.cpp Phase2.cpp Phase3.cpp GlobalClustering.cpp Output.cpp -o birch

If compilation is successful, an executable file will be generated:

Windows:

birch.exe

Linux:

birch
Step 4: Run the Program
Windows

Run:

birch.exe
Linux / macOS

Run:

./birch
Step 5: Execution Flow

When the program starts, the following operations are performed automatically:

Input CSV Dataset
        |
        |
        v
Dataset Loading
        |
        |
        v
Feature Normalization
        |
        |
        v
Phase 1:
CF Tree Construction
        |
        |
        v
Incremental Point Insertion
        |
        |
        v
CF Merge / New CF Creation
        |
        |
        v
Node Overflow Detection
        |
        |
        v
CF Tree Splitting
        |
        |
        v
Phase 2:
CF Tree Condensation
        |
        |
        v
Removal of Small Micro Clusters
        |
        |
        v
Phase 3:
Global Clustering
        |
        |
        v
Final Cluster Assignment
        |
        |
        v
Result CSV Generation
Step 6: Configuration Parameters

The main BIRCH parameters can be modified in:

main.cpp

Current configuration:

double threshold = 0.5;

int branchingFactor = 5;
Threshold

Controls the maximum distance allowed for merging a new point into an existing CF.

Example:

Distance <= Threshold

Point is merged

Otherwise:

New CF is created
Branching Factor

Controls the maximum number of CF entries stored in one node.

Example:

Branching Factor = 5

When the node contains more than 5 CF entries:

Node Overflow detected

and the node is split.

Step 7: Program Output

During execution, the terminal displays:

Phase 1 Output

Example:

Distance = 0.0417

Merged into existing CF

or:

Distance = 0.5339

Created new CF

When the node exceeds capacity:

Node Overflow detected

Splitting root node...
Phase 2 Output

Small micro clusters are removed.

Example:

Removing small CF N=1

Phase 2 Remaining CFs = 2
Phase 3 Output

Final cluster assignment:

Example:

Micro Cluster 0 belongs to Cluster 0

Micro Cluster 1 belongs to Cluster 1
Step 8: Generated Output File

After successful execution, the clustering results are stored in:

birch_results.csv

The output contains:

Point ID
Cluster Label

Example:

Point,Cluster

0,0
1,1
2,0
3,1
...
Troubleshooting
Compilation Error

Make sure all .cpp files are included during compilation:

g++ main.cpp CF.cpp CFNode.cpp CFTree.cpp Dataset.cpp Phase2.cpp Phase3.cpp GlobalClustering.cpp Output.cpp -o birch
Dataset Not Found

If the program displays a file loading error, check that:

two_emitter_pdw_dataset.csv

is located in the same folder as the executable.

Permission Error (Linux)

Give execution permission:

chmod +x birch

Then run:

./birch
Complete BIRCH Execution Summary

The implementation performs:

1. Load PDW dataset

2. Normalize features

3. Construct CF Tree

4. Incrementally insert points

5. Merge points into existing CFs

6. Create new CFs when threshold is exceeded

7. Split overflowing CF Nodes

8. Condense CF Tree

9. Remove insignificant micro clusters

10. Perform global clustering

11. Generate final cluster labels

12. Save results to CSV

The complete BIRCH clustering pipeline can therefore be executed using a single compilation and run command.
