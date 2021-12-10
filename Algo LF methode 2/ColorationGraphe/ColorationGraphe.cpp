#include <iostream>

//---------------- structure sommets simplifié 
struct Sommet
{
    int indice;
    int deg;
    int couleur;
};
void initMadj(int** Madj, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int nbr_arretes;
            if (i == j)
                Madj[i][j] = 0;
            else if(Madj[i][j] == -1)
            {
                std::cout << "Donnez nombre arretes entre Sommet : " << i << " et " << j << std::endl;
                std::cin >> nbr_arretes;
                Madj[i][j] = nbr_arretes;
                Madj[j][i] = nbr_arretes;
            }
        }
    }
}
int** createMadj(int n)
{
    int** Madj = new int* [n];
    for (int i = 0; i < n; i++)
        Madj[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Madj[i][j] = -1;

    initMadj(Madj, n);

    return Madj;
}
void deleteMadj(int**Madj,int n)
{
    for (int i = 0; i < n; i++)
        delete[]Madj[i];

    delete[]Madj;
}

int getDeg(int** Madj, int n, int indice)
{
    int degres=0;
    for (int j = 0; j < n; j++)
        degres += Madj[indice][j];
    return degres;
}
void quickSort(Sommet* sommet, int gauche, int droite)
{
    if (gauche < droite)
    {
        int pivot = droite;
        for (int i = droite - 1; i >= gauche; i--)
        {
            if (sommet[i].deg < sommet[pivot].deg)
            {
                Sommet tmp = sommet[pivot];
                sommet[pivot] = sommet[i];
                sommet[i] = sommet[pivot - 1];
                sommet[pivot - 1] = tmp;

                pivot--;

            }
        }
        quickSort(sommet, gauche, pivot - 1);
        quickSort(sommet, pivot + 1, droite);
    }
}
Sommet* createSommet(int** Madj, int n)
{
    Sommet*sommet = new Sommet[n];
    for (int i = 0; i < n; i++){
        sommet[i].indice = i;
        sommet[i].deg = getDeg(Madj, n, i);
        sommet[i].couleur = 0;
    }
    quickSort(sommet, 0, n - 1);
    return sommet;
}
int firstWithOutColor(Sommet* sommet, int n)
{
    for (int i = 0; i < n; i++)
        if (sommet[i].couleur == 0)
            return i;
    return -1;
}
bool noVoisin(int**Madj,Sommet *sommet,int indice,int indice_2,int n)
{
    bool check = (Madj[indice][indice_2] == 0);
    bool check2 = false;
    
    if (check)
    {
        for (int j = indice; j <+indice_2; j++)
        {
            if (Madj[indice][sommet[j].indice] == 0) 
                if (sommet[j].couleur != 0)
                    check2 = (Madj[sommet[j].indice][indice_2] == 0);
        }
        return check2;
    }
    else
        return false;
}


int colorGraphe(Sommet*sommet,int*colors,int**Madj,int n)
{
    int k = 0, indice = 0;
    while (indice != -1)
    {
        sommet[indice].couleur = colors[k];
        for (int i = indice; i < n; i++)
        {
            if (noVoisin(Madj,sommet,sommet[indice].indice, sommet[i].indice,n))
                sommet[i].couleur = colors[k];
        }
        k++;
        indice = firstWithOutColor(sommet, n);
    }
    return k;
}
int* createPalette(int n)
{
    int* couleur = new int[n];
    for (int i = 0; i < n; i++)
        couleur[i] = i + 1;
    return couleur;
}

void showGraphe(Sommet* sommet, int n)
{
    std::cout << "\n Coloration du Graphe " << std::endl;
    std::cout << "---------------------" << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << "Sommet : " << sommet[i].indice << " Couleur : " << sommet[i].couleur << " Degres : " << sommet[i].deg << std::endl;
    
}
int main()
{
    int n;
    std::cout << "Donnez nombre de sommet : " << std::endl;
    std::cin >> n;
    int** Madj = createMadj(n);
    int* colors = createPalette(n);
    Sommet* sommet = createSommet(Madj, n);
    int nbr_chromatique = colorGraphe(sommet, colors, Madj, n);
    std::cout << "Le nombre Chromatique est : "<<nbr_chromatique << std::endl;
    showGraphe(sommet, n);
    delete[]colors;
    delete[]sommet;
    deleteMadj(Madj, n);
    return 0;
}
