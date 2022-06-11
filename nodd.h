#ifndef NODD_H_INCLUDED
#define NODD_H_INCLUDED
typedef struct structnoeud {
    struct structnoeud * pere ;
    struct structnoeud * fd ;
    struct structnoeud * fg ;
    struct structnoeud* suivant ;
    char ch ;
    int freq ;
    int par ;
}structNoeud,*NOEUD ;
typedef struct noeud {
    struct noeud * suiv ;
    int val ;
} noeud ;
typedef noeud * pile;
typedef struct
{
    NOEUD tete;
    int lg;
}laStruct,*LISTE;


LISTE remplissage(char sh[]);
 NOEUD construction (NOEUD l);
void code (char sh[],char ch[],LISTE L);
void decodage(char sh[],char ch[],LISTE L);

#endif // NODD_H_INCLUDED
