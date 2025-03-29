#include <iostream>
#include <unordered_map>

using namespace std;

void dfs(int node, int n, int **graf, int *visited)
{
    cout << node << " ";
    visited[node] = 1;
    for (int i = 0; i < n; i++)
    {
        if (graf[node][i] == 1 && visited[i] == 0)
        {
            dfs(i, n, graf, visited);
        }
    }
}

int main()
{
    int n, l;
    cout << "wierzcholki: ";
    cin >> n;
    cout << "krawedzie: ";
    cin >> l;

    int **graf = new int *[n];
    int *visited = new int[n];
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

    cout << "graf:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << graf[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        cout << degree[i] << " ";
    }
    cout << endl
         << "DFS:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && degree[i] > 0)
        {
            dfs(i, n, graf, visited);
            break;
        }
    }
    bool cone = true;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && degree[i] > 0)
        {
            cone = false;
            cout << "niespójny" << endl;
            return 1;
        }
    }
    bool eulerc = true;
    for (int i = 0; i < n; i++)
    {
        if (!(degree[i] % 2 == 0))
        {
            eulerc = false;
        }
    }
    int conter = 0;
    bool eulerp = false;
    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 == 1 && degree[i] != 0)
        {
            conter++;
        }
    }
    if (conter == 2)
    {
        eulerp = true;
    }

    cout << "c: " << eulerc << " p:" << eulerp << endl;

    for (int i = 0; i < n; i++)
    {
        delete[] graf[i];
    }
    delete[] graf;
    delete[] visited;

    return 0;
}
