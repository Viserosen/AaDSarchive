#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

void dfs(int node, int n, int **graf, int *visited)
{
    visited[node] = 1;
    for (int i = 0; i < n; i++)
    {
        if (graf[node][i] == 1 && visited[i] == 0)
        {
            dfs(i, n, graf, visited);
        }
    }
}

void graph_manual(int **graf, unordered_map<int, int> &degree, int l)
{
    cout << "wprowadz krawędzie:" << endl;
    for (int i = 0; i < l; i++)
    {
        int a, b;
        cin >> a >> b;
        graf[a][b] = 1;
        graf[b][a] = 1;
        degree[a]++;
        degree[b]++;
    }
}

void graph_file(int **graf, unordered_map<int, int> &degree, int &l, int &n)
{
    ifstream file("dane.txt");
    int a, b;
    file >> n >> l;
    for (int i = 0; i < l; i++)
    {
        file >> a >> b;
        graf[a][b] = 1;
        graf[b][a] = 1;
        degree[a]++;
        degree[b]++;
    }
    file.close();
}

void free_memory(int **graf, int *visited, bool *checked, int *hamilton, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] graf[i];
    }
    delete[] graf;
    delete[] visited;
    delete[] checked;
    delete[] hamilton;
}

void graph_print(int **graf, int n)
{
    cout << "graf:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << graf[i][j] << " ";
        }
        cout << endl;
    }
}

bool graph_connect_check(int **graf, int *visited, unordered_map<int, int> degree, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && degree[i] > 0)
        {
            dfs(i, n, graf, visited);
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && degree[i] > 0)
        {
            return false;
        }
    }
    return true;
}

void fleury_search(int n, int **graf, int node, vector<int> &euler)
{
    for (int i = 0; i < n; i++)
    {
        if (graf[node][i] == 1)
        {
            graf[node][i] = 0;
            graf[i][node] = 0;
            fleury_search(n, graf, i, euler);
        }
    }
    euler.push_back(node);
}

bool robert_flores_search(int start, int **graf, bool *checked, int node, int &hamilton_visited, int &pos, int n, int *hamilton)
{
    checked[node] = true;
    hamilton_visited++;
    for (int i = 0; i < n; i++)
    {
        if (graf[node][i] == 1)
        {
            if (i == start && hamilton_visited == n)
            {
                hamilton[pos] = node;
                pos++;
                return true;
            }
            if (!checked[i])
            {
                if (robert_flores_search(start, graf, checked, i, hamilton_visited, pos, n, hamilton))
                {

                    hamilton[pos] = node;
                    pos++;
                    return true;
                }
            }
        }
    }
    checked[node] = false;
    hamilton_visited--;
    return false;
}

int main()
{
    int choice_graph = 0;
    int n = 1000, l;

    int **graf = new int *[n];
    int *visited = new int[n];
    bool *checked = new bool[n];
    int *hamilton = new int[n];
    int hamilton_visited = 0;

    unordered_map<int, int> degree;

    for (int i = 0; i < n; i++)
    {
        graf[i] = new int[n];
        visited[i] = 0;
        for (int j = 0; j < n; j++)
        {
            graf[i][j] = 0;
        }
    }

    cout << "0-man, 1-file" << endl;
    cin >> choice_graph;
    if (choice_graph == 0)
    {
        cout << "wierzcholki: ";
        cin >> n;
        cout << "krawedzie: ";
        cin >> l;
        graph_manual(graf, degree, l);
    }
    else if (choice_graph == 1)
    {
        graph_file(graf, degree, l, n);
    }

    graph_print(graf, n);

    if (!graph_connect_check(graf, visited, degree, n))
    {
        cout << endl
             << "niespójny" << endl;
        free_memory(graf, visited, checked, hamilton, n);
        return 1;
    }

    bool eulerc = true;
    bool hamiltonbrumbrum;

    for (int i = 0; i < n; i++)
    {
        checked[i] = false;
    }

    hamilton[0] = 0;
    int pos = 1;
    hamiltonbrumbrum = robert_flores_search(0, graf, checked, 0, hamilton_visited, pos, n, hamilton);
    if (hamiltonbrumbrum)
    {
        cout << "hamilton: " << endl;
        for (int i = 0; i < n + 1; i++)
        {
            cout << hamilton[i] << " ";
        }
    }
    else
    {
        cout << "brak cyklu hamiltona";
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        if (!(degree[i] % 2 == 0))
        {
            eulerc = false;
            break;
        }
    }

    int node = 0;
    for (int i = 0; i < n; i++)
    {
        if (degree[i] > 0)
        {
            node = i;
            break;
        }
    }

    if (eulerc)
    {
        vector<int> euler;
        fleury_search(n, graf, node, euler);
        cout << "euler: " << endl;
        for (int i = 0; i < euler.size(); i++)
        {
            cout << euler[i] << " ";
        }
    }
    else
    {
        cout << "brak cyklu eulera" << endl;
    }
    cout << endl;

    free_memory(graf, visited, checked, hamilton, n);
    return 0;
}
