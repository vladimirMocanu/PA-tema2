/*
Mocanu-Prejma Vladimir-Georgian
325CB
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

class Task
{

public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

private:
    int n, m, k;
    int contor = 0;
    std::vector<std::vector<int> > matrice;
    std::vector<std::vector<int> > vizitat1;

    void read_input()
    {
        //dechidem fisierul si citim din el
        //introducem valorile in matrice
        ifstream fin("p2.in");

        fin >> n >> m >> k;

        matrice.resize(n);
        vizitat1.resize(n);

        //parcurgem si introducem in matrice
        for (int i = 0; i < n ; ++i)
        {
            matrice[i].resize(m);
            vizitat1[i].resize(m);

            for (int j = 0, e; j < m; j++)
            {
                fin >> e;
                matrice[i][j] = e;
            }
        }

        fin.close();
    }

    //vedem daca un element are vecini corespunzatori
    //vecinii de sus,jos,stanga,dreapta
    //prima data verificam sa nu depasim limitele matricei
    //si vecinul trebuie sa fie intre element si element+k
    //crestem contor si apelam din nou functia pentru vecinul gasit
    void vecini(int element, int i, int j)
    {
        //vecinul de jos
        if((i + 1 < n) && (matrice[i + 1][j] <= element + k) && (matrice[i + 1][j] >= element) )
        {
            if(vizitat1[i + 1][j] == 0)
            {
                vizitat1[i + 1][j] = 1;
                contor++;

                vecini(element, i + 1, j);
            }
        }

        //vecinul de sus
        if( i > 0 && (matrice[i - 1][j] <= element + k) && (matrice[i - 1][j] >= element) )
        {
            if(vizitat1[i - 1][j] == 0)
            {
                vizitat1[i - 1][j] = 1;
                contor++;
                vecini(element, i - 1, j);
            }
        }

        //vecinul din dreapta
        if( j + 1 < m && (matrice[i][j + 1] <= element + k) && (matrice[i][j + 1] >= element) )
        {
            if(vizitat1[i][j + 1] == 0)
            {
                vizitat1[i][j + 1] = 1;
                contor++;
                vecini(element, i, j + 1);
            }
        }

        //vecinul din stanga
        if( j > 0 && (matrice[i ][j - 1] <= element + k) && (matrice[i][j - 1] >= element) )
        {
            if(vizitat1[i][j - 1] == 0)
            {
                vizitat1[i][j - 1] = 1;
                contor++;
                vecini(element, i, j - 1);
            }
        }
    }

    int get_result()
    {
        //vizitat este pentru a stii daca am fost intr-un nod
        //contorMax este aria maxima
        int contorMax = 1;
        int vizitat[n][m];

        //parcurgem matricea si apelam vecini() pentru fiecare element din matrice
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {   
                //daca nu a fost vizitat, in parcurgem
                if(vizitat[i][j] == 0)
                {
                    //contorul mereu o sa inceapa de la 0
                    contor = 0;
                    vecini(matrice[i][j], i, j);

                    //reinitializam matricea cu 0
                    for (int z = 0; z < n; ++z)
                    {
                        for (int y = 0; y < m; ++y)
                        {
                            vizitat1[z][y] = 0;
                        }
                    }

                    vizitat[i][j] = 1;

                    //daca am gasit un contor mai mare
                    //il retinem
                    if(contor > contorMax)
                    {
                        contorMax = contor;
                    }
                }
            }
        }

        return contorMax;
    }

    void print_output(int result)
    {
        //scriem in fisier
        ofstream fout("p2.out");
        fout << result;
        fout.close();
    }
};

int main()
{
    std::ios::sync_with_stdio(false);

    Task task;
    task.solve();
    return 0;
}
