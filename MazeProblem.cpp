// #include<iostream>
// #include <chrono>
// #include<vector>
// #include<queue>
// #include<map>
// #include<algorithm>
// #include<random>
// #include<stack>
// #include <thread>
#include <bits/stdc++.h>
using namespace std;

struct Cell
{
    int x, y;
    bool walls[4]; // 0=Up,1=Right,2=Down,3=Left
    bool visited;
};

// Maze size
const int N = 20, M = 20;
Cell maze[N][M];

// Movement arrays: Up, Right, Down, Left
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// Check if inside grid
bool valid(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < M;
}

// Direction vectors: 0=top,1=right,2=bottom,3=left
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool valid(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < M);
}

void generateMaze(int sx, int sy)
{
    stack<Cell *> st;
    maze[sx][sy].visited = true;
    st.push(&maze[sx][sy]);

    std::mt19937 rng(std::random_device{}()); // random engine

    while (!st.empty())
    {
        Cell *curr = st.top();
        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end(), rng);

        bool moved = false;
        for (int d : dirs)
        {
            int nx = curr->x + dx[d];
            int ny = curr->y + dy[d];

            if (valid(nx, ny) && !maze[nx][ny].visited)
            {
                // remove walls between curr and next
                curr->walls[d] = false;
                maze[nx][ny].walls[(d + 2) % 4] = false;
                maze[nx][ny].visited = true;

                st.push(&maze[nx][ny]);
                moved = true;
                break;
            }
        }
        if (!moved)
            st.pop();
    }
}

int main()
{
    // initialize maze
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            maze[i][j] = {i, j, {true, true, true, true}, false};
        }
    }

    generateMaze(0, 0);
    cout << "Maze generated successfully!\n";
}

// Print maze with optional path/visited
void printMaze(vector<vector<char>> display)
{
    // system("cls"); // use "cls" on Windows
    // #ifdef _WIN32
    // // system("cls");
    // #else
    // system("clear");
    // #endif

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << display[i][j] << ' ';
        }
        cout << "\n";
    }
    this_thread::sleep_for(chrono::milliseconds(50));
}

// BFS solve with animation
void solveMaze(pair<int, int> start, pair<int, int> goal)
{
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    map<pair<int, int>, pair<int, int>> parent;

    vector<vector<char>> disp(N, vector<char>(M, ' '));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            disp[i][j] = ' ';
        }
    }

    q.push(start);
    visited[start.first][start.second] = true;
    disp[start.first][start.second] = 'S';
    disp[goal.first][goal.second] = 'E';

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (make_pair(x, y) == goal)
            break;

        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) && !maze[x][y].walls[d] && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                parent[{nx, ny}] = {x, y};
                q.push({nx, ny});
                if (disp[nx][ny] == ' ')
                    disp[nx][ny] = '.';
            }
        }
        printMaze(disp);
    }

    // reconstruct path
    pair<int, int> cur = goal;
    while (cur != start)
    {
        disp[cur.first][cur.second] = '*';
        cur = parent[cur];
    }
    disp[start.first][start.second] = 'S';
    disp[goal.first][goal.second] = 'E';
    printMaze(disp);
}

int main()
{
    // srand(time(0));
    maze.assign(N, vector<Cell>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            maze[i][j] = Cell(i, j);

    generateMaze(0, 0);

    solveMaze({0, 0}, {N - 1, M - 1});

    return 0;
}

// #include <iostream>
// #include <chrono>
// #include <vector>
// #include <queue>
// #include <map>
// #include <algorithm>
// #include <random>
// #include <stack>
// #include <thread>
// using namespace std;

// struct Cell
// {
//     int x, y;
//     bool walls[4]; // top,right,bottom,left
//     bool visited;
//     Cell(int _x = 0, int _y = 0) : x(_x), y(_y), visited(false)
//     {
//         for (int i = 0; i < 4; i++)
//             walls[i] = true;
//     }
// };

// int N, M; // maze size (global)
// vector<vector<Cell>> maze;
// int dx[4] = {-1, 0, 1, 0};
// int dy[4] = {0, 1, 0, -1};

// bool valid(int x, int y)
// {
//     return x >= 0 && y >= 0 && x < N && y < M;
// }

// // Generate maze using Recursive Backtracking
// void generateMaze(int sx, int sy)
// {
//     stack<Cell *> st;
//     maze[sx][sy].visited = true;
//     st.push(&maze[sx][sy]);

//     while (!st.empty())
//     {
//         Cell *curr = st.top();
//         vector<int> dirs = {0, 1, 2, 3};
//         shuffle(dirs.begin(), dirs.end(), std::mt19937(std::random_device()()));

//         bool moved = false;
//         for (int d : dirs)
//         {
//             int nx = curr->x + dx[d], ny = curr->y + dy[d];
//             if (valid(nx, ny) && !maze[nx][ny].visited)
//             {
//                 // remove walls between curr and next
//                 curr->walls[d] = false;
//                 maze[nx][ny].walls[(d + 2) % 4] = false;
//                 maze[nx][ny].visited = true;
//                 st.push(&maze[nx][ny]);
//                 moved = true;
//                 break;
//             }
//         }
//         if (!moved)
//             st.pop();
//     }
// }

// // Print maze with optional path/visited
// void printMaze(vector<vector<char>> display)
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < M; j++)
//         {
//             cout << display[i][j] << ' ';
//         }
//         cout << "\n";
//     }
//     this_thread::sleep_for(chrono::milliseconds(50));
// }

// // BFS solve with animation
// void solveMaze(pair<int, int> start, pair<int, int> goal)
// {
//     queue<pair<int, int>> q;
//     vector<vector<bool>> visited(N, vector<bool>(M, false));
//     map<pair<int, int>, pair<int, int>> parent;

//     vector<vector<char>> disp(N, vector<char>(M, ' '));

//     q.push(start);
//     visited[start.first][start.second] = true;
//     disp[start.first][start.second] = 'S';
//     disp[goal.first][goal.second] = 'E';

//     while (!q.empty())
//     {
//         auto [x, y] = q.front();
//         q.pop();

//         if (make_pair(x, y) == goal)
//             break;

//         for (int d = 0; d < 4; d++)
//         {
//             int nx = x + dx[d], ny = y + dy[d];
//             if (valid(nx, ny) && !maze[x][y].walls[d] && !visited[nx][ny])
//             {
//                 visited[nx][ny] = true;
//                 parent[{nx, ny}] = {x, y};
//                 q.push({nx, ny});
//                 if (disp[nx][ny] == ' ')
//                     disp[nx][ny] = '.';
//             }
//         }
//         printMaze(disp);
//     }

//     // reconstruct path
//     pair<int, int> cur = goal;
//     while (cur != start)
//     {
//         disp[cur.first][cur.second] = '*';
//         cur = parent[cur];
//     }
//     disp[start.first][start.second] = 'S';
//     disp[goal.first][goal.second] = 'E';
//     printMaze(disp);
// }

// int main()
// {

//     maze.resize(N);
//     for (int i = 0; i < N; i++)
//     {
//         maze[i].resize(M);
//         for (int j = 0; j < M; j++)
//         {
//             maze[i][j] = Cell(i, j);
//         }
//     }

//     generateMaze(0, 0);
//     solveMaze({0, 0}, {N - 1, M - 1});

//     return 0;
// }
