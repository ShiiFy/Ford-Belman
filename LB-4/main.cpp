#include <iostream>
#include <vector>

using namespace std;

class Graph{
    private:
        int vertices;
        vector<vector<int>> adjacencyMatrix;
        vector<int> Path;
        void findPaths(int current, int finish, vector<int>& currentPath, vector<vector<int>>& allPaths);
    public:
        void inputGraph();
        void displayGraph();
        void MinPath(int start, int finish);
        void MaxPath(int start, int finish);

};
void Graph::inputGraph(){
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    adjacencyMatrix.clear();
    adjacencyMatrix.assign(vertices, vector<int>(vertices, 0));

    cout << "Enter the weight of the graph:" << endl;

    for(int i = 0; i < vertices; ++i){
        for(int j = 0; j < vertices; ++j){
            do{
                cout << "Enter value for adjacencyMatrix[" << i + 1 << "][" << j + 1 << "]: ";
                cin >> adjacencyMatrix[i][j];
            }while (adjacencyMatrix[i][j] < 0);
        }
    }
}
void Graph::displayGraph(){
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
void Graph::MinPath(int start, int finish) {
    Path.resize(vertices, INT_MAX);
    Path[start - 1] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < vertices; ++j) {
            for (int k = 0; k < vertices; ++k) {
                if (adjacencyMatrix[j][k] != 0 && Path[j] != INT_MAX && Path[j] + adjacencyMatrix[j][k] < Path[k]) {
                    Path[k] = Path[j] + adjacencyMatrix[j][k];
                }
            }
        }
    }

    for(int i = 0; i < vertices; i++){
        cout << Path[i] << " ";
    }
    cout << "\n";

    vector<vector<int>> allPaths;
    vector<int> currentPath;
    findPaths(start - 1, finish - 1, currentPath, allPaths);

    for (const auto& Path : allPaths) {
        for (int i = 0; i < Path.size(); ++i) {
            int currentVertex = Path[i] + 1;
            if (i != 0) {
                int previousVertex = Path[i - 1];
                cout << " <-(" << adjacencyMatrix[previousVertex][currentVertex - 1] << ")- ";
            }
            cout << currentVertex;
        }
        cout << endl;
    }
}

void Graph::findPaths(int current, int finish, vector<int>& currentPath, vector<vector<int>>& allPaths) {
    currentPath.push_back(current);
    if (current == finish) {
        allPaths.push_back(currentPath);
    } else {
        for (int i = 0; i < vertices; ++i) {
            if (adjacencyMatrix[current][i] != 0 && Path[current] + adjacencyMatrix[current][i] == Path[i]) {
                findPaths(i, finish, currentPath, allPaths);
            }
        }
    }
    currentPath.pop_back();
}

void Graph::MaxPath(int start, int finish){
    Path.resize(vertices, INT_MIN);
    Path[start - 1] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
            for (int j = 0; j < vertices; ++j) {
                for (int k = 0; k < vertices; ++k) {
                    if (adjacencyMatrix[j][k] != 0 && Path[j] != INT_MIN && Path[j] + adjacencyMatrix[j][k] > Path[k]) {
                        Path[k] = Path[j] + adjacencyMatrix[j][k];
                    }
                }
            }
        }

    for(int i = 0; i < vertices; i++){
        cout << Path[i] << " ";
    }
    cout << "\n";

    vector<vector<int>> allPaths;
    vector<int> currentPath;
    findPaths(start - 1, finish - 1, currentPath, allPaths);

    for (const auto& Path : allPaths) {
        for (int i = 0; i < Path.size(); ++i) {
            int currentVertex = Path[i] + 1;
            if (i != 0) {
                int previousVertex = Path[i - 1];
                cout << " -(" << adjacencyMatrix[previousVertex][currentVertex - 1] << ")-> ";
            }
            cout << currentVertex;
        }
        cout << endl;
    }
}

int main()
{
    Graph graph;
    graph.inputGraph();
    graph.displayGraph();
    int m, k, choice;
    do{
        cout << "finding: \n1.Minimum path\n2.Maximum path\n3.inputGraph\n4.displayGraph\n0.Exit\n";
        cin >> choice;
        if(choice == 1 || choice == 2){
            cout << "Start vertex: ";
            cin >> m;
            cout << "Finish vertex: ";
            cin >> k;
        }
        switch(choice){
            case 1:
                graph.MinPath(m, k);
                break;
            case 2:
                graph.MaxPath(m, k);
                break;
            case 3:
                graph.inputGraph();
                break;
            case 4:
                graph.displayGraph();
                break;
        }
    }while(choice != 0);
    return 0;
}
