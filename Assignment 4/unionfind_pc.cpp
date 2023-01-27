#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

class UF
{
private:
    int *id;  // access to component id
    int size; // Number of nodes
    int counter; // number of components
    int *sz; // size of component for roots
    int get_height(int p);

public:
    UF(int n);
    int count() {return counter;}
    bool connected(int p, int q) {return find(p) == find(q);}
    int find(int p);
    void unions(int p, int q);
    void print(int longest_path);
    int max_height();
    ~UF() {delete [] id;}
};

UF::UF(int n)
{
    counter = n;
    size = n;
    id = new int[n];
    for (int i=0; i<n; i++)
        id[i] = i;
    sz = new int[n];
    for (int i=0; i<n; i++)
        sz[i] = 1;
}

int UF::find(int p)
{
    // follow links to find root
    if (p != id[p])
    {
        id[p] = find(id[p]);
        return id[p];
    }
    else
        return p;
}

void UF::unions(int p, int q)
{
    // put p and q in the same component
    int i = find(p);
    int j = find(q);

    // check if p and q are already in the same component
    if (i == j)
        return;

    // make smaller root point to larger one
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }

    counter--;
}

void UF::print(int longest_path)
{
    for (int h=longest_path; h>0; h--)
    {
        cout << "Height: " << h << endl;
        for (int i=0; i<size; i++)
            if (get_height(i) == h)
                cout << "[" << i << "->" << id[i] << "] ";
        cout << endl;
    }
}

int UF::get_height(int p)
{
    int h = 0;
    for (int q = p; id[q] != q; q = id[q])
        h++;
    return h;
}

int UF::max_height()
{
    int h = 0;
    int p_height;
    for (int p=0; p<size; p++)
    {
        p_height = get_height(p);
        if (p_height > h)
            h = p_height;
    }
    return h;
}

int main()
{
    ifstream in;
    in.open("uf.txt");

    int N;
    //cout << "How many elements are there? ";
    in >> N;
    UF uf(N);

    cout << "I read ";
    while (!in.eof())
    {
        int p,q;
        in >> p;
        in >> q;
        if (uf.connected(p,q))
            continue;
        uf.unions(p,q);
        cout << "(" << p << "," << q << ") ";
    }
    cout << endl;
    cout << "There are " << uf.count() << " components" << endl;
    int longest_path = uf.max_height();
    cout << "The maximum height is " << longest_path << endl << endl;
    uf.print(longest_path);

return 0;
}
