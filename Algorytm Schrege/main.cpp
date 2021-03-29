#include <iostream>
#include <vector>
#include "RandomNumberGenerator.h"
#include <algorithm>


//Adam Kubiak 249480
//Piotr Gorzelnik 248947

std::ostream& operator << (std::ostream& StrmWy, std::vector<int> wek)
{
    int LiczbaZadan = wek.size();
    StrmWy << "[";

    for (int j = 0; j < LiczbaZadan; j++)
    {
        if (j == LiczbaZadan - 1)
        {
            StrmWy << wek[j];
        }
        else
        {
            StrmWy << wek[j] << ", ";
        }

    }

    StrmWy << "]" << std::endl;

    return StrmWy;
}

std::ostream& operator << (std::ostream& StrmWy, std::vector<std::pair<int, int>> wek)
{
    int LiczbaZadan = wek.size();
    StrmWy << "r: [";

    for (int j = 0; j < LiczbaZadan; j++)
    {
        if (j == LiczbaZadan - 1)
        {
            StrmWy << wek[j].first;
        }
        else
        {
            StrmWy << wek[j].first << ", ";
        }

    }

    StrmWy << "]" << std::endl;
    StrmWy << "p: [";
    for (int j = 0; j < LiczbaZadan; j++)
    {
        if (j == LiczbaZadan - 1)
        {
            StrmWy << wek[j].second;
        }
        else
        {
            StrmWy << wek[j].second << ", ";
        }
    }
    StrmWy << "]" << std::endl;

    return StrmWy;
}

void addCQ(std::vector<std::vector<int>> RPQ, std::vector<int> c, std::vector<int>* wynik)
{
    int size = RPQ[2].size();

    for (int i = 0; i < size; i++)
    {
        wynik->push_back(RPQ[2][i] + c[i + 1]);
    }
}

void FillPi(std::vector<int>& pi, int LiczbaZadan, int tryb)
{
    RandomNumberGenerator Obiekt(1);
    pi.clear();

    if (tryb == 1)
    {
        for (int i = 0; i < LiczbaZadan; i++)
        {
            pi.push_back(i + 1);
        }
    }
    if (tryb == 2)
    {
        for (int i = 0; i < LiczbaZadan; i++)
        {
            pi.push_back(i + 1);
        }
        std::random_shuffle(pi.begin(), pi.end());

    }
}


void genereteRpqVector(int LiczbaZadan, std::vector<std::vector<int>>& RPQ, std::vector<int> pi)
{
    
    int seed = 1;
   
    auto randomNumber = RandomNumberGenerator(seed);
    int A = 0;
    std::vector<int> r;
    for (int i = 0; i < 3; i++)
    {
        RPQ.push_back(r);
        
    }

    for (int i = 0; i < LiczbaZadan; i++) {
        RPQ[1].push_back(randomNumber.nextInt(1, 29));
        A += RPQ[1][i];
    }

    for (int i = 0; i < LiczbaZadan; i++) {
        RPQ[0].push_back(randomNumber.nextInt(1, A));
    }

    for (int i = 0; i < LiczbaZadan; i++) {
        RPQ[2].push_back(randomNumber.nextInt(1, A));
    }

    RPQ.push_back(pi);

}



std::vector<std::vector<int>> Schrage(std::vector<std::vector<int>> RPQ, int LiczbaZadan, std::vector<int> pi) {
    int k = 0;
    int indeks = 0;
    std::vector<int> PI;
    std::vector<int> r;
    PI.resize(LiczbaZadan);
    auto kopia = RPQ;
    std::vector<std::vector<int>> wynik;

    std::vector<std::vector<int>> G; //zbiór zadañ gotowych do realizacji

    for (int i = 0; i < 4; i++)
    {
        G.push_back(r);
        wynik.push_back(r);
    }

    //G.push_back(pi);
    //wynik.push_back(r);


    int t = *min_element(RPQ[0].begin(), RPQ[0].end());

    while (!G[0].empty() || !RPQ[0].empty())
    {
        while (!RPQ[0].empty() && *min_element(RPQ[0].begin(), RPQ[0].end()) <= t)
        {
            int j = *min_element(RPQ[0].begin(), RPQ[0].end());

            for (int i = 0; i < LiczbaZadan; i++)
            {
                if (RPQ[0][i] == j)
                {
                    G[0].push_back(RPQ[0][i]);
                    G[1].push_back(RPQ[1][i]);
                    G[2].push_back(RPQ[2][i]);
                    G[3].push_back(RPQ[3][i]);

                    RPQ[0].erase(RPQ[0].begin() + i);
                    RPQ[1].erase(RPQ[1].begin() + i);
                    RPQ[2].erase(RPQ[2].begin() + i);
                    RPQ[3].erase(RPQ[3].begin() + i);

                    break;
                }
            }
        }

        if (!G[0].empty())
        {
            int j = *std::max_element(G[2].begin(), G[2].end());

            for (int i = 0; i < G[2].size(); i++)
            {
                if (j == G[2][i])
                {
                    indeks = i;
                }
            }

            PI[k++] = G[3][indeks]; // nasz numer zadania z vectora pi
            t += G[1][indeks];// nasze p
            G[0].erase(G[0].begin() + indeks);
            G[1].erase(G[1].begin() + indeks);
            G[2].erase(G[2].begin() + indeks);
            G[3].erase(G[3].begin() + indeks);
        }
        else
        {
            t = *min_element(RPQ[0].begin(), RPQ[0].end());
        }

    }


    for (int j = 0; j < LiczbaZadan; j++)
    {
        int indeks = PI[j];
        wynik[0].push_back(kopia[0][indeks - 1]);
        wynik[1].push_back(kopia[1][indeks - 1]);
        wynik[2].push_back(kopia[2][indeks - 1]);
        wynik[3].push_back(kopia[3][indeks - 1]);
    }

    return wynik;
}



int main()
{
    int LiczbaZadan, tryb;
    std::vector <std::vector<int>> RPQ, POSORTOWANE;
    std::vector<int> C1, S1, pi, CQ,CQ1;
    std::vector<int> C2, S2;  

    C1.push_back(0);
    

    std::cout << "Wprowadz liczbe zadan: ";
    std::cin >> LiczbaZadan;
    std::cout << "Podaj tryb generowania wektora PI(1,2): ";
    std::cin >> tryb;

    //wygenerowanie vecotra permutacji PI
    FillPi(pi, LiczbaZadan, tryb);
    //wygenerowanie tablicy vectorów RPQ
    genereteRpqVector(LiczbaZadan, RPQ, pi);
    std::cout << "PI:" << pi;

    //wyliczenie elementów vectorów S1, C1
    for (int i = 0; i < LiczbaZadan; i++)
    {
        int a = pi[i] - 1;

        S1.push_back(std::max(RPQ[0][a], C1[i]));
        C1.push_back(S1[i] + RPQ[1][a]);
    }

 

    //wyliczenie elementów vectora CQ
    addCQ(RPQ, C1, &CQ);


    POSORTOWANE = Schrage(RPQ, LiczbaZadan, pi);

    std::cout << "r: " << RPQ[0];
    std::cout << "p: " << RPQ[1];
    std::cout << "q: " << RPQ[2];
   
    std::cout << "S1:" << S1;
    std::cout << "C1:" << C1;
    std::cout << "CQ: " << CQ;
    std::cout << *std::max_element(CQ.begin(), CQ.end()) << '\n';

    CQ.clear();

    C2.push_back(0);
    for (int i = 0; i < LiczbaZadan; i++)
    {
        int a = pi[i] - 1; // pi?

        S2.push_back(std::max(POSORTOWANE[0][a], C2[i]));
        C2.push_back(S2[i] + POSORTOWANE[1][a]);
    }


    addCQ(POSORTOWANE, C2, &CQ);


    std::cout << "\n\n";
    std::cout << "pi: " << POSORTOWANE[3];
    std::cout << "r: " << POSORTOWANE[0];
    std::cout << "p: " << POSORTOWANE[1];
    std::cout << "q: " << POSORTOWANE[2];
    std::cout << "S2:" << S2;
    std::cout << "C2:" << C2;
    std::cout << "CQ: " << CQ;
    std::cout << *std::max_element(CQ.begin(), CQ.end()) << '\n';

}