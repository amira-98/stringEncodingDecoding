#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
} noeud ,*pile;

typedef struct
{
    NOEUD tete;
    int lg;
}laStruct,*LISTE;
NOEUD noeudcreer()
{
NOEUD n;
n =(NOEUD)malloc(sizeof(structNoeud));
if(!n)
printf ("\nPlus d'espace");
else
{
n->ch='\0';
n->suivant = NULL;
n->fd= NULL;
n->fg= NULL;
n->pere= NULL;
n->freq=0;
n->par=2;
}
return n;
}
LISTE listecreer(){
	LISTE L;
	L=(LISTE)malloc(sizeof(laStruct));
	if (! L)
		printf("\nProblème de mémoire");
	else {
		L->lg = 0;
		L->tete = NULL;}
	return(L);}

LISTE remplissage(char sh[])
{
    int i ;
    LISTE L=listecreer();

           NOEUD q= noeudcreer();
           q->freq=1;
           q->ch=sh[0];
           L->tete=q;
           q->suivant = NULL;
           L->lg=1;


    NOEUD p ; int test;
    for(i=1; i<strlen(sh); i++)
        {
            test=0;p=L->tete;

            while(test==0 && p)
            {

                if (p->ch==sh[i])
                    {test=1; p->freq ++ ;}
                else {
                      p=p->suivant ;
                     }
            }
            if(test==0)
             {  NOEUD n=noeudcreer();

               	{ p=L->tete;int j;
	for(j=1;j<(L->lg);j++)
	{
		p=p->suivant;
	}
	p->suivant=n;
	}

	n->suivant=NULL;
	n->ch=sh[i];
        n->freq = 1 ;

	L->lg++;
}
        }

    return L;
}
NOEUD min (NOEUD l1,NOEUD l2)
{
    if (!l1)
        return l2 ;
    if (!l2)
        return l1 ;
    if (l1->freq <l2->freq)
        return l1 ;
    return l2 ;
}
NOEUD min1(NOEUD q )
{

    if (!q)
        return NULL ;
    if (q->par == 2)
        return (min (q,min1(q->suivant)));
    return(min(min1(q->suivant),min1(q->pere)));
}
NOEUD min2(NOEUD q,NOEUD l1)
{
    if (!q)
        return NULL ;
    if (q == l1)
        return min1(q->suivant);
    if (q->par == 2)
        return (min(q,min2(q->suivant,l1)));
    else
        return (min(min2(q->pere,l1),min2(q->suivant,l1)));
}
int taille (NOEUD q)
{
    if (!q)
        return 0 ;
    if (q->par==2)
        return(1+taille(q->suivant));
    if (q->par==0)
        return (taille(q->suivant)+taille(q->pere));
    else return (taille(q->suivant));
}
void pere(NOEUD m1, NOEUD m2)
{
    NOEUD p ;
    p=noeudcreer();
    p->freq= m1->freq + m2->freq ;
    m1->par = 0;
    m1->pere = p;
    m2 ->pere = p ;
    m2->par = 1;
    p->fd = m1 ;
    p->fg = m2 ;

}
NOEUD construction (NOEUD l)
{
    NOEUD m1,m2;
    int i=taille(l)-1 ;
    while (i) {

        m1 = min1(l);
        m2 = min2(l,m1);
        pere(m1,m2);
        i-- ;
    }
    return l ;
}
pile empiler (pile p, int val )
{
    pile p1 ;
    p1=(pile)malloc(sizeof(noeud));
    p1->val = val ;
    p1->suiv = p ;
    return p1 ;
}
pile depiler (pile p1)
{
    pile p2;
    p2 = p1->suiv ;
    free(p1);
    return (p2);
}
void code_unitaire(NOEUD q,char c,char ch[])
{
    pile p=NULL ;
    strcpy(ch,"");
    while (q) {
        if (c==q->ch) {
            while (q->pere) {
                p=empiler(p,q->par);

                q=q->pere;
            }
            while (p) {
                sprintf(ch+strlen(ch),"%d",p->val);
                p=depiler(p);
            }
            break ;
        }
        q=q->suivant ;
    }
}
void code (char sh[], char ch[],LISTE L )
{
    char sh2[20];
    strcpy(sh,"");
    int i ;NOEUD q=L->tete;
    for (i=0; i<strlen(ch); i++) {
        code_unitaire(q,ch[i],sh2);
        strcat(sh,sh2);
    }
}
NOEUD racine (NOEUD l)
{
    while (l->pere ) {
        l=l->pere ;
    }
    return l ;
}
void decodage(char sh[],char ch[],LISTE L)
{int test=1;
    NOEUD rac ;
    strcpy(sh,"");
    int i = 0 ; NOEUD q=L->tete;
    while (i<strlen(ch)&&test==1) {
        rac = racine(q);

        while (rac->fd&&i<=strlen(ch)) {
            if (ch[i]=='1')
                rac=rac->fg ;
            else rac=rac->fd ;
            i++ ;
        }
        if(i>strlen(ch)&& rac->ch!='\0') test=0;
        else
        sprintf(sh+strlen(sh),"%c",rac->ch);
    }
    if(test==1)
    puts(sh);
    else {puts(sh) ; printf("le reste de la chaine ne peut pas etre decodee \n");}
}
int menu_decodage(char ch[],LISTE L ,char ii[])
{int re1,rep;char nh[500];
    do
    {printf("voulez vous decoder une chaine ? si oui cliquez 1 si non cliquez 0 \n");
     scanf("%i",&re1);
     if(re1==1)
    {do
    {printf("decoder un nouveau code: cliquez 1 / decoder l'ancien code : cliquez 0\n");
    scanf("%i",&rep);}while(rep!=0&&rep!=1);
    if(rep==0)
    {printf("\n apres le decodage de la meme chaine \n");
    decodage(ii,ch,L);}
    else
    {printf("donner un code binaire ( se composant que par  0 / 1) \n");
    do
    scanf("%s",nh);
    while(strlen(nh)<2);
    decodage(ii,nh,L);
    }}
    else {printf("*************au revoir******** ") ;exit(0);}
        }while(re1!=0);
        return 0;
}
