#include <bits/stdc++.h>
#include <queue>
#include <iostream>
using namespace std;

// define Node
class Node {
public:
    int puzzle[3][3];
    int x, y;
    int cost;
    int depth;
   string path;
};


// define comparator for priority queue
class Compare {
public:
    bool operator()(const Node &a, const Node &b) {
        return (a.cost + a.depth) > (b.cost + b.depth);
    }
};

// print puzzle
void printPuzzle(int puzz[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << puzz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// uniform search
int uniformSearch(int puzz[3][3], int goal[3][3]) {
    return 0;
}

// tiles misplaced heuristic
int tilesMisplaced(int puzz[3][3], int goal[3][3]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzz[i][j] != 0 && puzz[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// euclidean distance heuristic
int euclideanDistance(int puzz[3][3], int goal[3][3]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzz[i][j] != 0) {
                int x, y;
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (goal[k][l] == puzz[i][j]) {
                            x = k;
                            y = l;
                            break;
                        }
                    }
                }
                count += abs(i - x) + abs(j - y);
            }
        }
    }
    return count;
}



// is puzzle solvable?
bool isSolvable(int puzz[3][3]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (puzz[i / 3][i % 3] && puzz[j / 3][j % 3] &&
                puzz[i / 3][i % 3] > puzz[j / 3][j % 3]) {
                count++;
            }
        }
    }
    return count % 2 == 0;
}

bool is_goal(int puzz[3][3], int goal[3][3]) {
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3;j++) {
        if (puzz[i][j] != goal[i][j]) {
            return false;
        }
        }
    }
    return true;
}



// solve and find optimal path
int solve(int puzz[3][3], int goal[3][3], int choice) {
    // condition if puzzle is not solvable
    if (!isSolvable(puzz)) {
    cout << "the puzzle is unsolvable" << endl;
    return -1;
    }

    priority_queue<Node, vector<Node>, Compare> queue;
    set<string> visited;
    int max_queue = 0;
    int nodes_expanded = 0;

    // create initial node and push to queue
    Node initial;
    memcpy(initial.puzzle, puzz, sizeof(initial.puzzle));
    initial.x = initial.y = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (initial.puzzle[i][j] == 0) {
                initial.x = i;
                initial.y = j;
                break;
            }
        }
    }
    initial.depth = 0;
    initial.path = "";
    if(choice == 1) {
        initial.cost = uniformSearch(initial.puzzle, goal);
    } else if(choice == 2){
        initial.cost = tilesMisplaced(initial.puzzle, goal);
    } else {
        initial.cost = euclideanDistance(initial.puzzle, goal);
    }
    cout << endl << "------------- Initial state:" <<  "-------------" << endl;
    printPuzzle(initial.puzzle);
    queue.push(initial);

    while (!queue.empty()) {
    // get current node and pop
        Node current = queue.top();
        queue.pop();
        nodes_expanded++;
    
    // if the goal state is reached
if (is_goal(current.puzzle, goal)) {
    string puzzle = current.path;
    for (int i = 0; i < current.depth; i++) {
        cout << "------------- depth: " << i+1 << "-------------" << endl;
        string row1 = puzzle.substr(i * 9, 3);
        string row2 = puzzle.substr(i * 9 + 3, 3);
        string row3 = puzzle.substr(i * 9 + 6, 3);
        cout << row1[0] << " " << row1[1] << " " << row1[2] << endl;
        cout << row2[0] << " " << row2[1] << " " << row2[2] << endl;
        cout << row3[0] << " " << row3[1] << " " << row3[2] << endl;
        cout << endl;
    }
    cout << "number of nodes expanded: " << nodes_expanded << endl;
    cout << "maximum queue size: " << max_queue << endl;
    cout << "depth cost: " << current.depth << endl;
    return current.depth;
}

// generate children (neighbors)
int ox[] = {-1, 0, 1, 0};
int oy[] = {0, 1, 0, -1};

for (int i = 0; i < 4; i++) {
    int x = current.x + ox[i];
    int y = current.y + oy[i];
    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        Node child;
        memcpy(child.puzzle, current.puzzle, sizeof(child.puzzle));
        child.puzzle[current.x][current.y] = child.puzzle[x][y];
        child.puzzle[x][y] = 0;
        child.x = x;
        child.y = y;
        child.depth = current.depth + 1;
        //child.path = current.path + state;
        if (choice == 1) {
            child.cost = uniformSearch(child.puzzle, goal);
        } else if (choice == 2) {
            child.cost = tilesMisplaced(child.puzzle, goal);
        } else {
            child.cost = euclideanDistance(child.puzzle, goal);
        }

        string state = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                state += to_string(child.puzzle[i][j]);
            }
        }
        //cout << 
        
        child.path = current.path + state;

        if (visited.count(state) == 0) {
            visited.insert(state);
            queue.push(child);
        }
    }
  }
  max_queue = max(max_queue, (int)queue.size());
}
return 0;
}

int main() {
    int choice = 0, puzz[3][3];
    cout << "1: use default puzzle or 2: enter a custom puzzle: ";
    cin >> choice;
    int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    if (choice == 2) {
        cout << "enter the puzzle(add a space in between each number) : ex) 1 2 3 4 5 6 7 8 0" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> puzz[i][j];
            }
        }
    } else {
        int defaultpuzz[3][3] = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                puzz[i][j] = defaultpuzz[i][j];
            }
        }
    }

    int search;
    cout << "1: use uniform cost search, 2: use A* with tiles misplaced heuristic or 3: use A* with euclidean distance heuristic: ";
    cin >> search;

    int result = solve(puzz,goal, search);

    return result;
}



