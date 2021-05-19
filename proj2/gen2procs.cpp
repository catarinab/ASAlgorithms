/*************************************************************
 * Small generator of Two-processor distributed model
 *  - of size N processes
 *  - max execution cost C of any process
 *
 * Pedro T. Monteiro - Pedro.Tiago.Monteiro@tecnico.ulisboa.pt
 *************************************************************/

#include <cmath>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Adj list c_ij
int _N, _C;
list<pair<int,int>> *_g;
int _nedges = 0;
vector<int> _X, _Y;

//-------------------------------------------------------------------

void printUsage() {
  cout << "Usage: gen2procs #N #C seed" << endl;
  cout << "\t#N: number of processes (N >= 2)" << endl;
  cout << "\t#C: max cost of any process execution (C>0)" << endl;
  cout << "\tseed: random seed number (optional)" << endl;
  exit(0);
}

void parseArgs(int argc, char **argv) {
  int seed = 0;

  if (argc < 3) printUsage();

  sscanf(argv[1], "%d", &_N);
  if (_N < 2) {
    cout << "ERROR: # N must be >= 2" << endl;
    printUsage();
  }

	sscanf(argv[2], "%d", &_C);
  if (_C <= 0) {
    cout << "ERROR: # C must be > 0" << endl;
    printUsage();
  }

  if (argc > 3) {
    // Init rand seed
    sscanf(argv[3], "%d", &seed);
    srand(seed);
  } else {
    srand((unsigned int)time(NULL));
  }
}

int randomValue(int max) {
  return 1 + rand() % max; // [1, max]
}

void addPotentialCost(int u, int v, int w) {
	if (w <= 0) return;
	_g[u].push_back(make_pair(v, w));
	_nedges++;
}

int main(int argc, char *argv[]) {
	// parse arguments
  parseArgs(argc, argv);

	_X.resize(_N, 0);
	_Y.resize(_N, 0);
	for (int i = 0; i < _N; i++) { // 1st and 2nd processor
		_X[i] = randomValue(_C);
		_Y[i] = randomValue(_C);
	}

	// init graph
	_g = new list<pair<int,int>>[_N];
	// add c_ij's as a bidirectional graph
	for (int i = 0; i < _N; i++) { // upper triangular matrix - O(N^2)
		for (int j = i+1; j < _N; j++) {
			if ((_X[i] < _Y[i] && _X[j] > _Y[j]) ||
					(_X[i] > _Y[i] && _X[j] < _Y[j])) {
				addPotentialCost(i, j, (int)min(_X[i],_X[j])/2);
			}
		}
	}

	// print header
	printf("%d %d\n", _N, _nedges);
	
	// print execution costs
	for (int i = 0; i < _N; i++) // 1st and 2nd processor
		printf("%d %d\n", _X[i], _Y[i]);

	// print communication costs
	for (int u = 0; u < _N; u++) { // O(N + nedges)
		for (list<pair<int,int>>::iterator iter = _g[u].begin(); iter != _g[u].end(); iter++) {
			int v = iter->first, w = iter->second;
			printf("%d %d %d\n", u+1, v+1, w);
		}
	}
	return 0;
}
