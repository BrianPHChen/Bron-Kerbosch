#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int V = 4;
vector< vector<bool> > adj(V, vector<bool>(V, false));

void printSet(set<int> set_a) {
    cout << "{ ";
    for(auto& e: set_a) {
        cout << e << " ";
    }
    cout << "}" << endl;
}

set<int> neighbor(int v) {
    set<int> result;
    for(int i = 0; i < V; i++) {
        if (adj[v][i]) {
            result.insert(i);
        }
    }
    return result;
}

set<int> intersection(set<int> set_a, set<int> set_b) {
    set<int> result;
    set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), inserter(result, result.begin()));
    return result;
}

void BronKerbosch(set<int> R, set<int> P, set<int> X) {
    cout << "R: ";
    printSet(R);
    cout << "P: ";
    printSet(P);
    cout << "X: ";
    printSet(X);
    cout << "==========================\n";
    if (P.size() == 0 && X.size() == 0) {
        cout << "maximal size: " << R.size() << endl;
        cout << "set: { ";
        for(auto& e : R) {
            cout << e << " ";
        }
        cout << "}" << endl;
        return;
    }

    int pivot = 0;
    for(pivot = 0; pivot < V; pivot++) {
        if(P.count(pivot) || X.count(pivot)) {
            cout << "pivot: " << pivot << endl;
            break;
        }
    }

    for(int i = 0; i < V; i++) {
        if(P.count(i) && !adj[pivot][i]) {
            R.insert(i);
            BronKerbosch(R, intersection(P, neighbor(i)), intersection(X, neighbor(i)));
            R.erase(i);
            P.erase(i);
            X.insert(i);
        }
    }
}

int main(int argc, char *argv[]) {
    set<int> R, P, X;
    for(int i = 0; i < 4; i++) { 
        P.insert(i);
    }
    adj = {
        {false, true, true, false},
        {true, false, true, true},
        {true, true, false, false},
        {false, true, false, false}
    };
    BronKerbosch(R, P, X);
    return 0;
}