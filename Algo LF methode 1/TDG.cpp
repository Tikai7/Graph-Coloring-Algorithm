#include <iostream>
#include <string>
   

//---------------------------------- Structure qui represente un sommet 
struct Element
{
    int degres; //--- son degres
    int couleur; //-------- couleur 
    char nom;       //----- son Nom
    char *voisin;   //---- tableau de voisin 
};


//--------------------------------------------- Triage décroissant des degres   
void trier(Element tab[],int taille)
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = i; j < taille; j++)
        {
            if (tab[i].degres < tab[j].degres)  
            { 
                Element tmp = tab[i]; //------------ permutation des sommets
                tab[i] = tab[j];
                tab[j] = tmp;

            }
        }
    }
}

//-------------------------------------------------------- Affiche le resultat 
void afficher(Element tab[],int n)   
{
  
    for (int i = 0; i < n; i++)
    {
        std::cout << std::endl;
        std::cout << "Deg(" << tab[i].nom << ")" << ": " << tab[i].degres << " / Couleur : " << tab[i].couleur << std::endl;
        std::cout << "Sommets Voisin :" << std::endl;
        for (int j = 0; j < tab[i].degres; j++)
            std::cout << tab[i].voisin[j] <<" ";  
    }
    std::cout << std::endl;
}

//---------------------------------------------- initialise les couleurs à " None " 
void init(Element tab[], int n)
{
    for (int i = 0; i < n; i++)
        tab[i].couleur = 0;
}

//---------------------------------------------------------------- Fonction qui cherche si un sommet est un voisin d'un sommet donné
bool find(Element tab[],int indice, int taille, char name,int couleur) 
{
    for (int j = 0; j <= indice; j++)
    {
        for (int i = 0; i < taille; i++)
        {
            if ((name == tab[j].voisin[i]) && (couleur == tab[j].couleur)) //---- on verifie si le sommet a un voisin , et si la couleur utilisé pour le voisin est la meme que l'actuel
                return true;    
           
        }   
    }
    
    return false;
}

//----------------------------------- cherches les elements pas encore colorié
int noColor(Element tab[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (tab[i].couleur == 0)
            return i;
    }
    return 100;
}
//--------------------------------------------------------------- Coloration des sommets
void coloration(Element tab[], int n,int couleur[],int &chromatique)
{
  
    int k = 0;
    int indice = 0;

    while(indice != 100) //--- tant que tout les elements sont pas encore colorié on continue 
    {
        tab[indice].couleur = couleur[k]; //------ premier sommet prend la premiere couleur     
        for (int i = indice; i < n; i++)
        {
            if (!find(tab, i , n, tab[i].nom,couleur[k])) //------ cherche si ce sommet est un voisin des sommets precedent
                tab[i].couleur = couleur[k];

        }
        k++;    
        indice = noColor(tab, n); //---- on prend l'indice de l'element pas colorié 
    }
    chromatique = k;
}   

//------------------------------------------- Libération Mémoire utiliser pour le tableau des sommets voisins
void clear(Element tab[],int taille)
{
    for (int i = 0; i < taille; i++)
        delete[] tab[i].voisin; 
}

//------------------------------------------- Represente le graphe obtenue(sans lien) 
void dessiner(Element tab[], int taille)
{
    std::cout << "\n\n";
    for (int i = 0; i < taille; i++)
    {
        std::cout <<"\t"<<tab[i].nom <<" ("<<tab[i].couleur<<") \t\t";          

        if (i % 2 != 0)
            std::cout << "\n\n\n";
    }

    std::cout << "\n";
}

//------------------------------------------- initialise le tableau des couleurs de 1 a n
void init_color(int* couleur,int n)
{
    for (int i = 0; i < n; i++)
        couleur[i] = i+1;

}

//--------------------- FONCTION PRINCIPALE
int main()
{
    int n;      
    std::cout << "Donnez nombre sommets" << std::endl;
    std::cin >> n;

    Element* tab = new Element[n];     //---- allocation dynamique d'un tableau de n sommets  
    int* couleur = new int[n];         //---- allocation dynamique d'un tableau de n couleurs  
     
    init_color(couleur,n);  //---- initialise le tableau de couleur
    
    for (int i = 0; i < n; i++)
    {
        std::cout << "Donnez nom du sommet (lettre Majuscule) " << std::endl; //------- demande le nom du sommet 
        std::cin >> tab[i].nom;
        do
        {
            std::cout << "Donnez degres sommet " << i + 1 << ": ";  //------- demande le degres du sommet qui doit être inferieur ou egale au nombre de sommets
            std::cin >> tab[i].degres;

        } while (tab[i].degres >= n);       
       
        if (tab[i].degres > 0) //---------------------- si degres > 0
        {
            tab[i].voisin = new char[tab[i].degres]; //---- allocation dynamique d'un tableau qui va contenir les voisins de ce dernier

            for (int j = 0; j < tab[i].degres; j++)
            {
                std::cout << "Donnez nom des sommets voisin (lettre Majuscule) " << std::endl;
                std::cin >> tab[i].voisin[j];
            }
        }
        else
        {
            tab[i].voisin = new char[1]; //--------------- si le degres !=0 on crée un tableau a une case ou on mettre un " / " 
            tab[i].voisin[0] = '/';
        }   
        
    }
    int nbr_chromatique;

    init(tab, n); //----------- initialisation des couleurs des sommets ( couleur à 0 ) 
    trier(tab, n); //------------- triage 
    coloration(tab, n, couleur, nbr_chromatique); //-------- coloration et recuperation nombre chromatique
    afficher(tab, n); //-------- affichage
    dessiner(tab, n);
    clear(tab,n); //------- liberation de la mémoire alloué pour le tableau de voisin

    std::cout << "Le Nombre Chromatique est : " << nbr_chromatique << std::endl; //------ nombre chromatique obtenue

    //--------- liberation memoire alloué
    delete[] tab; 
    delete[] couleur;

    return 0;
}

