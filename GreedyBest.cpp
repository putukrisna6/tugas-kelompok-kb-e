#include <bits/stdc++.h>

#define N 3

using namespace std;

struct Statespace {
    int puzzle[N][N];
    int spare[2];
    int evaluate;

    bool operator< (Statespace s) const {
        return (evaluate < s.evaluate);
    }
    int operator- (Statespace s) const {
        int count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (puzzle[i][j] != s.puzzle[i][j] \
                    && puzzle[i][j] != 0)
                    count++;
            }
        }
        return count;
    }
    bool operator== (Statespace s) const {
        if ((*this) - s == 0)
            return true;
        else
            return false;
    }
    void operator= (Statespace s) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                puzzle[i][j] = s.puzzle[i][j];
            }
        }

        spare[0] = s.spare[0];
        spare[1] = s.spare[1];
        evaluate = s.evaluate;
    }
};

istream& operator>> (istream& input, Statespace& s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input >> s.puzzle[i][j];

            if (s.puzzle[i][j] == 0) {
                s.spare[0] = i;
                s.spare[1] = j;
            }
        }
    }

    return input;
}
ostream& operator<< (ostream& output, Statespace& s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            output << s.puzzle[i][j] << " ";
        }
        output << endl;
    }

    return output;
}

class Equal {
    bool greater;

public:
    Equal(const bool& lesser = 1) {
        greater = lesser ? false : true;
    }

    bool operator() (const Statespace& src, const Statespace& dest) const {
        if (greater)
            return (src < dest ? false : true);
        else 
            return (src < dest);
    }
};

ofstream ofs("output.txt");
// stores the start and the goal puzzle states
Statespace start, goal;
// tracks the current state
Statespace current;

// keep track of the "open list"
set<Statespace, Equal> openList;
// tracks which puzzle states have been explored already
vector<Statespace> explored;

int t = 0;

inline int move(char pos) {
    int p, q, \
        r, c, \
        heuristic;
    
    int s1 = current.spare[0], \
        s2 = current.spare[1];

    switch (pos) {
    case 'R':
        p = 0;
        q = 1;
        break;
    case 'L':
        p = 0;
        q = -1;
        break;
    case 'U':
        p = 1;
        q = 0;
        break;
    case 'D':
        p = -1;
        q = 0;
        break;
    }

    r = s1 + p;
    c = s2 + q;
    
    swap(current.puzzle[s1][s2], current.puzzle[r][c]);

    if (find(explored.begin(), explored.end(), current) != explored.end()) {
        current = start;
        return 0;
    }

    current.spare[0] = r;
    current.spare[1] = c;

    heuristic = goal - current;
    current.evaluate = heuristic;

    openList.insert(current);
    current = start;

    return 0;
}

int greedyBest() {
    set<Statespace, Equal>::iterator l = openList.begin();
    current = *l;

    if (current == goal)
        return t;
    
    ofs << current << endl;
    cout << current << endl;

    explored.push_back(current);
    openList.erase(l);

    start = current;

    if (current.spare[1] < 2)
        move('R');
    if (current.spare[1] > 0)
        move('L');
    if (current.spare[0] < 2)
        move('U');
    if (current.spare[0] > 0)
        move('D');

    t++;
    greedyBest();

    return 0;
}

void initiate() {
    start.evaluate = start - goal;
    openList.insert(start);
    greedyBest();
}

int main() {
    ifstream inf("input.txt");
    inf >> start >> goal;

    initiate();

    ofs << current << endl;
    cout << current << endl;

    return 0;
}