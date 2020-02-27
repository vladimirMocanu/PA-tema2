/*
Mocanu-Prejma Vladimir-Georgian
325CB
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

const int kMod = 1e9 + 7;

class Task
{

public:
    void solve()
    {
        read_input();
        get_result();
    }

private:
    int n;
    vector<int> distante;
    vector<int> distante1;

    void read_input()
    {
        ifstream fin("p1.in");

        fin >> n;
        //citim din fisier si introducem in cel doi vectori
        for (int i = 0, e; i < n; i++)
        {
            fin >> e;

            distante.push_back(e);
            distante1.push_back(e);
        }

        fin.close();
    }

    void get_result()
    {
        ofstream fout("p1.out");

        //definim si initializam variabilele pe care o sa le folosim
        int nodParinte = 1;
        int numarDistante = n;
        int numarMuchii = 0;
        int nodTemporar = 0;
        int nod1, nod2;

        //coada o folosim pentru afisare
        queue <int> afisare;

        //pentru cazul cand nu exista graf
        sort(distante.begin(), distante.end());

        //parcurgem vectorul de distante
        for (int i = 1; i < n ; ++i)
        {
            //daca mai sunt elemnte in vectorul distante
            if(numarDistante > 1)
            {   
                for (int j = 1; j < n; ++j)
                {
                    //daca gasim 2 distante consecutive
                    //si diferenta lor este mai mare de 1
                    //nu se poate forma graful
                    if(distante[j] - distante[j - 1] > 1)
                    {
                        fout << "-1";
                        fout.close();
                        return;
                    }

                    //daca gasim distante egale cu 0(in afara de primul)
                    //nu se poate forma graful
                    if(distante[j] == 0)
                    {
                        fout << "-1";
                        fout.close();
                        return;
                    }

                    //luam pe rand toate distantele, crescator
                    // Ex. prima data distantele 1, dupa 2 etc
                    if(distante1[j] == i)
                    {   
                        //bagam nodul parinte in coada
                        //crestem numarulMuchii si scadeam distanta
                        afisare.push(nodParinte);
                        afisare.push(j + 1);
                        numarMuchii++;
                        nodTemporar = j + 1;

                        numarDistante--;
                    }
                }

                //am trecut la alt nivel in graf
                //o sa avem un nou parinte
                nodParinte = nodTemporar;
            }
            else
                break;
        }

        //afisam numarul de muchiii
        fout << numarMuchii << "\n";

        //cat timp avem in coada elemente
        //scoatem 2 cate 2 si le afisam
        while(afisare.size() > 0)
        {
            nod1 = afisare.front();
            afisare.pop();
            nod2 = afisare.front();
            afisare.pop();

            fout << nod1 << " " << nod2 << "\n";
        }

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
