#include <bits/stdc++.h>
using namespace std;

// define Node
class Node {
public:
    int puzzle[3][3];
    int x, y;
    int cost;
    int depth;
};

// define comparator for priority queue
class Compare {
public:
    bool operator()(const Node &a, const Node &b) {
        return (a.cost + a.depth) > (b.cost + b.depth);
    }
};

// uniform search
int uniformSearch(int puzzle[3][3], int goal[3][3]) {
    return 0;
}

// tiles misplaced heuristic
int tilesMisplaced(int puzzle[3][3], int goal[3][3]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// euclidean distance heuristic
int euclideanDistance(int puzzle[3][3], int goal[3][3]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] != 0) {
                int x, y;
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (goal[k][l] == puzzle[i][j]) {
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

// print puzzle
void printPuzzle(int puzzle[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// is puzzle solvable?
bool isSolvable(int puzzle[3][3]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (puzzle[i / 3][i % 3] && puzzle[j / 3][j % 3] &&
                puzzle[i / 3][i % 3] > puzzle[j / 3][j % 3]) {
                count++;
            }
        }
    }
    return count % 2 == 0;
}

// solve using uniform cost search
int solve(int puzzle[3][3], int goal[3][3], int choice) {
    // condition if puzzle is not solvable
    if (!isSolvable(puzzle)) {
    cout << "the puzzle is unsolvable" << endl;
    return -1;
    }

    priority_queue<Node, vector<Node>, Compare> queue;
    set<string> visited;
    int max_queue = 0;
    int nodes_expanded = 0;

    // create initial node and push to queue
    Node initial;
    memcpy(initial.puzzle, puzzle, sizeof(initial.puzzle));
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
    if(choice == 1) {
        initial.cost = uniformSearch(initial.puzzle, goal);
    } else if(choice == 2){
        initial.cost = tilesMisplaced(initial.puzzle, goal);
    } else {
        initial.cost = euclideanDistance(initial.puzzle, goal);
    }
    queue.push(initial);
    //int num_moves;

    while (!queue.empty()) {
    // get current node and pop
        Node current = queue.top();
        queue.pop();
        //num_moves++;
        nodes_expanded++;

    // is puzzle solved?
        if (memcmp(current.puzzle, goal, sizeof(current.puzzle)) == 0) {
            cout << "Solution:" << endl;
            printPuzzle(current.puzzle);
            cout << "Expanded Nodes: " << nodes_expanded << endl;
            cout << "Max Queue Size: " << max_queue << endl;
            cout << "Depth Cost: " << current.depth << endl;
            //cout << num_moves << endl;
            return 0;
        }

    // possible moves
        int x = current.x;
        int y = current.y;
        if (x > 0) {
            Node next = current;
            next.x--;
            swap(next.puzzle[x][y], next.puzzle[x - 1][y]);
            string key = to_string(next.puzzle[0][0]) + to_string(next.puzzle[0][1]) + to_string(next.puzzle[0][2]) +
                         to_string(next.puzzle[1][0]) + to_string(next.puzzle[1][1]) + to_string(next.puzzle[1][2]) +
                         to_string(next.puzzle[2][0]) + to_string(next.puzzle[2][1]) + to_string(next.puzzle[2][2]);
            if (visited.find(key) == visited.end()) {
                next.depth = current.depth + 1;
                if(choice == 1) {
                    next.cost = uniformSearch(next.puzzle, goal);
                } else if(choice == 2){
                    next.cost = tilesMisplaced(next.puzzle, goal);
                } else {
                    next.cost = euclideanDistance(next.puzzle, goal);
                }
                visited.insert(key);
                queue.push(next);
            }
        }
        if (x < 2) {
            Node next = current;
            next.x++;
            swap(next.puzzle[x][y], next.puzzle[x + 1][y]);
            string key = to_string(next.puzzle[0][0]) + to_string(next.puzzle[0][1]) + to_string(next.puzzle[0][2]) +
                         to_string(next.puzzle[1][0]) + to_string(next.puzzle[1][1]) + to_string(next.puzzle[1][2]) +
                         to_string(next.puzzle[2][0]) + to_string(next.puzzle[2][1]) + to_string(next.puzzle[2][2]);
            if (visited.find(key) == visited.end()) {
                next.depth = current.depth + 1;
                if(choice == 1) {
                    next.cost = uniformSearch(next.puzzle, goal);
                } else if(choice == 2){
                next.cost = tilesMisplaced(next.puzzle, goal);
                } else {
                    next.cost = euclideanDistance(next.puzzle, goal);
                }
                visited.insert(key);
                queue.push(next);
            }
        }
        if (y > 0) {
            Node next = current;
            next.y--;
            swap(next.puzzle[x][y], next.puzzle[x][y - 1]);
            string key = to_string(next.puzzle[0][0]) + to_string(next.puzzle[0][1]) + to_string(next.puzzle[0][2]) +
                         to_string(next.puzzle[1][0]) + to_string(next.puzzle[1][1]) + to_string(next.puzzle[1][2]) +
                         to_string(next.puzzle[2][0]) + to_string(next.puzzle[2][1]) + to_string(next.puzzle[2][2]);
            if (visited.find(key) == visited.end()) {
                next.depth = current.depth + 1;
                if(choice == 1) {
                    next.cost = uniformSearch(next.puzzle, goal);
                } else if(choice == 2){
                    next.cost = tilesMisplaced(next.puzzle, goal);
                } else {
                    next.cost = euclideanDistance(next.puzzle, goal);
                }
                visited.insert(key);
                queue.push(next);
            }
        }
        if (y < 2) {
            Node next = current;
            next.y++;
            swap(next.puzzle[x][y], next.puzzle[x][y + 1]);
            string key = to_string(next.puzzle[0][0]) + to_string(next.puzzle[0][1]) + to_string(next.puzzle[0][2]) +
                         to_string(next.puzzle[1][0]) + to_string(next.puzzle[1][1]) + to_string(next.puzzle[1][2]) +
                         to_string(next.puzzle[2][0]) + to_string(next.puzzle[2][1]) + to_string(next.puzzle[2][2]);
            if (visited.find(key) == visited.end()) {
                next.depth = current.depth + 1;
                if(choice == 1) {
                    next.cost = uniformSearch(next.puzzle, goal);
                } else if(choice == 2){
                    next.cost = tilesMisplaced(next.puzzle, goal);
                } else {
                    next.cost = euclideanDistance(next.puzzle, goal);
                }
                visited.insert(key);
                queue.push(next);
            }
        }
// update max_queue
    max_queue = max(max_queue, (int)queue.size());
    
    }
    return 0;
}

int main() {
    int choice = 0, puzzle[3][3];
    int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    cout << "1: use default puzzle or 2: enter a custom puzzle: ";
    cin >> choice;
    if (choice == 2) {
        cout << "enter the puzzle(add space in between each number) : ex) 1 2 3 4 5 6 7 8 0" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> puzzle[i][j];
            }
        }
    } else {
        int defaultPuzzle[3][3] = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                puzzle[i][j] = defaultPuzzle[i][j];
            }
        }
    }

    int search;
    cout << "1: use uniform cost search, 2: use A* with tiles misplaced heuristic or 2: use A* with euclidean distance heuristic: ";
    cin >> search;

    int result = solve(puzzle,goal, search);

    return 0;
}



