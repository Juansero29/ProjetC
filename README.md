De Vries Gerben, Rodriguez Juan 
Groupe 7

Projet Structures de donn�es � P2
Gestion d�une Ludoth�que

Liste des fonctionnalit�s propos�es�: 

- Un menu principal � partir duquel l�utilisateur choisit les actions qu�il veut effectuer. A partir de ce dernier, il va choisir s�il veut faire l�affichage d�une liste, ajouter un �l�ment � une liste ou encore supprimer un �l�ment en saisissant le nombre correspondant au choix voulu, ce qui va permettre d�acc�der au sous-menu.

- Dans le 1er sous-menu, on peut choisir d�ajouter�: un nouvel adh�rent, un jeu, l�emprunt d�un jeu, une apr�s-midi th�matique, une inscription d�un adh�rent � cette derni�re, ou encore de renouveler une adh�sion.

- Dans le 2eme sous-menu, on peut choisir d�afficher�: la liste des jeux tri�s par ordre alphab�tique, la liste des adh�rents, la liste des emprunts en cours, la liste d�inscrits � une apr�s-midi th�matique, ainsi que les emprunteurs qui ont un retard.

- Enfin, dans le 3eme sous-menu, on peut choisir de supprimer�: un adh�rent, un jeu�; de rendre un emprunt, ou de d�sinscrire un adh�rant d�une apr�s-midi th�matique.


Description des fonctionnalit�s�: 

1er sous-menu�:
Le fonctionnement des fonctions qui ajoutent des �l�ments dans les tableaux est tr�s similaire. On passe en param�tres les tableaux permettant de faire les v�rifications des contraintes souhait�es ainsi que les tableaux directement concern�s par l�ajout des nouvelles valeurs. Nous commenterons une fonction de chaque type afin d�en expliquer le fonctionnement g�n�ral.
On prend pour exemple la fonction ChargerTAprem(), qui permet d�ajouter des Apr�s-midis dans le tableau tAprem[]
ApremTh *ChargerTAprem(ApremTh tAprem[], int *nbAprems, int *taillePhysique, int nbAjouts) {


if(*nbAprems == 0) {
// si le nombre d��l�ments du tableau est �gal � 0, on n�a pas encore fait de malloc pour le tableau. On le fait donc maintenant.
    *taillePhysique += 3;
    tAprem = (ApremTh *) malloc(*taillePhysique * sizeof(ApremTh));
    if (tAprem == NULL) {
        printf("Probleme d'allocation de memoire (malloc tAdherants)");
        exit(1);
    }
}

ApremTh aprem, *tApremBuffer;
int apremDeb = *nbAprems;    
if (*nbAprems == *taillePhysique) {//Si � ce moment-l� la taille logique est �gale � la taille physique, on augmente la capacit� de stockage du tableau.
        *taillePhysique += 3; //on augmente la capacit� de stockage du tableau de 3.
        tApremBuffer = (ApremTh *) realloc(tAprem, *taillePhysique * sizeof(ApremTh));
// on effectue une r�allocation de la m�moire pour correspondre � la nouvelle taille physique du tableau
        if (tApremBuffer == NULL) {
            printf("Probleme d'allocation de memoire. (realloc tAdherants)");
            exit(1);
        }
        tAprem = tApremBuffer;
    }
    aprem = SaisirApremTh(tAprem, *nbAprems);
// on appelle la fonction saisirApremTh
    tAprem[*nbAprems] = aprem;

return tAprem;
// on renvoie tAprem avec son nouveau contenu

Les fonctions de chargement poss�dent une fonction de saisie. Elles renvoient un type qui sera ins�r� dans le tableau correspondant dans la fonction de chargement. La fonction de saisie demande � l�utilisateur de renseigner les informations n�cessaires qui seront stock�es dans un type renvoy� par la fonction. 
On tient compte des contraintes lors de la saisie. Par exemple, lors de la saisie d�une date on v�rifie que celle-ci est correcte, lorsqu�on demande d�emprunter un jeu on v�rifie qu�il y ait des exemplaires de disponibles, etc�

Explication de la fonction SaisirApremTh()�:

ApremTh SaisirApremTh(ApremTh tAprems[], int nbAprems) {

    ApremTh apremTh;
    printf("\n\n|SAISIE APRES-MIDI THEMATIQUE|\n\n");
    apremTh.date = SaisirDate();
// fonction qui permet de saisir une date et qui l�enregistre dans un type Date.
    printf("Quel est le nombre correspondant a l'heure de debut de l'evenement ? (format 24h) :\n");
// on demande � l�utilisateur de saisir l�heure de d�but de l�apr�s-midi th�matique.
    scanf("%d", &apremTh.heureDebut);
// on v�rifie que les saisies soient correctes.
    while (apremTh.heureDebut < 1 || apremTh.heureDebut > 23) {
        printf("Saisie incorrecte (format 24h, entrez 2 chiffres). Reessayez :\n");
        scanf("%d", &apremTh.heureDebut);
    }
// L�utilisateur saisit le nombre de places de l��v�nement.
    printf("Quel sera le nombre de places ?\n");
    scanf("%d", &apremTh.nbPlaces);

    apremTh.nbAdhInscrits = 0;
// on initialise le nombre d�adh�rents inscrits � 0.
    strcpy(apremTh.codeAprem, CreerIdentifiant(2));
// on cr�e un identifiant unique pour l�apr�s-midi, en v�rifiant qu�il ne soit pas d�j� utilis�.
    int index = RechercherAprem(tAprems, nbAprems, apremTh.codeAprem);
    while (index != -1) {
        strcpy(apremTh.codeAprem, CreerIdentifiant(2));
        index = RechercherAprem(tAprems, nbAprems, apremTh.codeAprem);
    }
// permet de sauter des lignes dans la console
    system("cls");
    printf("\n-- Apres-midi thematique cree avec succes! --\n");
    return apremTh;
}

2i�me sous-menu�:
Les fonctions d�affichage, elles aussi, sont tr�s similaires. Chaque fonction d�affichage d�un tableau affiche les �l�ments de ce dernier.
Nous allons prendre pour exemple la fonction AfficherJeux()�:
void AfficherJeux(Jeu tJeux[], int nbJeux) {

	// si le tableau de jeu ne contient aucun �l�ment, on affiche un    message sp�cifique.
     if(nbJeux == 0){
        printf("\nAucun jeu n'a ete trouve.\n");
        return;
    }

    int i; // on initialise un compteur
    // on r�p�te l�affichage autant de fois qu�il y�a d��l�ments.
    for (i = 0; i < nbJeux; i++) { 
        printf("\n\nNom : %s (%s) - # Exemplaires: %d \n", tJeux[i].nom, tJeux[i].nomCategorie, tJeux[i].nbExemplaires);
    } 
}

3i�me sous-menu�:
Les fonctions de suppression permettent � l�utilisateur de supprimer un �l�ment d�un tableau. Afin d�expliquer le fonctionnement de ces fonctions, on va s�appuyer sur l�exemple de la fonction SupprimerInscription()�:
void SupprimerInscription(Inscription tInscriptions[], int *nbInscriptions, ApremTh tAprems[], int nbAprems, Adherant tAdherants[], int nbAdherants){
    // le tableau dont on veut supprimer des �l�ments est pass� en param�tres, ainsi que d�autres tableaux qui permettent de v�rifier les contraintes voulues.
    if(*nbInscriptions <= 0){
        printf("Aucune inscription n'a ete trouvee. Impossible de supprimer. \n");
        return;
    }
    int numAdherant, index;
    char *codeAprem;

// codeAprem est l�identifiant de l�apres-midi th�matique
    codeAprem = malloc(sizeof(char) * (3));
    printf("\n|ANNULER L'INSCRIPTION A UNE APRES-MIDI|\n");
    printf("Saisissez le numero de l'adherant qui veut annuler son inscription : ");
    scanf("%d", &numAdherant);
// on recherche si l�adh�rant existe bien
    index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    while (index == -1) {
// L�utilisateur est forc� de rentrer le num�ro d�un adh�rant existant.
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n\t Reessayez. Saissisez le numero de l'Adherant a inscrire : \n");
        scanf("%d", &numAdherant);
        index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    }
    printf("Cet adherant est inscrit aux apres-midis suivantes: \n");
// on affiche les apr�ms auxquels l�adh�rant est inscrit, afin de faciliter  le travail de l�utilisateur.
    int i, j=0;
    for(i=0; i < *nbInscriptions; i++){
        if(tInscriptions[i].numAdherant == numAdherant){
            Afficher1Aprem(tAprems, nbAprems, tInscriptions[i].codeAprem);
            j++;
        }
    }
    if (j == 0){
// on traite le cas o� l�adh�rant n�est inscrit � aucune apr�s midi
        system("cls");
        printf("\nCet adherant n'est inscrit a aucune apres-midi. Impossible d'annuler une inscription.\n");
        return;
    }
// sinon, on demande de quelle apr�m il veut se d�sinscrire.
    printf("\n\nEntrez le numero d'apres-midi de laquelle il veut se desinscrire.\n");
    scanf("%s", codeAprem);
    index = RechercherAprem(tAprems, nbAprems, codeAprem);
    while (index == -1) {
        printf("\nL'adherant n'est pas inscrit a cette apres-midi. Voici celles auxquelles il l'est :\n");
        for(i=0; i < nbAprems; i++){
            if(tInscriptions[i].numAdherant == numAdherant){
                Afficher1Aprem(tAprems, nbAprems, tInscriptions[i].codeAprem);
            }
        }
        printf("\n\nEntrez le numero de l'apres-midi: \n");
        scanf("%s", codeAprem);
        index = RechercherAprem(tAprems, nbAprems, codeAprem);
    }
// si l�utilisateur a bien saisi un num�ro d�apr�s-midi auquel l�adh�rant �tait inscrit, celui-ci est maintenant supprim�, et le type ApremTh contient un adh�rant d�inscrit en moins.
    tAprems[index].nbAdhInscrits--;

    index = RechercherInscription(tInscriptions, *nbInscriptions, codeAprem, numAdherant);
    for (i = index; i < *nbInscriptions - 1; i++){
        tInscriptions[i] = tInscriptions[i +1];
    }
    *nbInscriptions = *nbInscriptions - 1;
    printf("�L�adherant a bien annule son inscription! --\n");
}


Explication des fonctions de recherche�:
Nous avons utilis� des fonctions de recherche r�cursives. Lorsque l��l�ment recherch� est trouv�, on envoie son rang dans le tableau et sinon, on renvoie -1.
int RechercherEmprunt(Emprunt tEmprunts[], int nbEmprunts, int numAdherant, char nomJeu[]){
    if (strcmp(tEmprunts[nbEmprunts].nomJeu, nomJeu) == 0 && tEmprunts[nbEmprunts].numAdherant == numAdherant) {
        return nbEmprunts;
    }
    if (nbEmprunts == -1){
        return -1;
    }
    return RechercherEmprunt(tEmprunts, nbEmprunts - 1, numAdherant, nomJeu);
}

Explication fonction de tri (utilis�e pour trier la liste des jeux par ordre alphab�tique) :
D'abord, cette fonction partitionne le tableau des jeux en deux parties. Puis, elle fait un tri ind�pendant des deux sous-tableaux obtenus. 
Le point de d�part pour effectuer ce partitionnement est indiqu� par l'index 'pivot'. Le pivot sera plac� toujours � sa place d�finitive (tri�).
Puis, on proc�de � la permutation des �l�ments de telle sorte � ce que ceux qui se situent � la partie gauche soient inferieurs au pivot 
Finalement, on d�finit un pivot pour chacun des sous-tableaux et on r�p�te le partitionnement. Ce processus est r�p�t� de mani�re r�cursive jusqu'� ce que tous les �l�ments soient tri�s.

Explication des contr�les dans les fonctions de saisie�: 

SaisirDate()�:
while(date.jour < 1 || date.jour > 31 || date.mois < 1 || date.mois > 12 || date.annee < 1900 || date.annee > 2150){
    printf("\nSaisie incorrecte. Reessayez (au format JJ/MM/AAAA) :\n");
    scanf("%d/%d/%d", &date.jour, &date.mois, &date.annee);
}
On demande � l�utilisateur de faire une saisie de la date tant qu�elle est incorrecte.

SaisirAdherant()�:
- On g�n�re un identifiant unique pour l�adh�rent.
- On demande � l�utilisateur de saisir son nom, pr�nom (de 14 caract�res maximum, tronqu� au-del�) et sa date d�adh�sion (saisie gr�ce � l�appel de la fonction SaisirDate()).

SaisirEmprunt()�:
- on demande la saisie d�un adh�rent, on v�rifie que ce dernier soit existant.
- on v�rifie si l�adh�sion de l�adh�rent est expir�e, dans quel cas on ne peut pas saisir d�emprunt.
- on v�rifie si l�adh�rent emprunte actuellement 3 jeux, cas dans lequel il ne peut pas en emprunter plus.
- on demande la saisie d�un jeu.
- on v�rifie que le jeu existe, le cas �ch�ant, on montre la liste des jeux que l�adh�rent peut emprunter.
- on v�rifie que tous les exemplaires de ce jeu ne soient pas emprunt�s actuellement.
- si la saisie du jeu et de l�adh�rent sont valides, on augmente de 1 le nombre d�emprunts en cours de l�utilisateur, ainsi que le nombre d�exemplaires de ce jeu actuellement emprunt�s.

SaisirApremTh()�:
- on demande la saisie de la date de l�apr�m par l�interm�diaire de la fonction SaisirDate().
- on demande la saisie de l�heure de d�but de l��v�nement en v�rifiant que celle-ci se situe entre 0 et 24 exclus, le nombre de places.
- on cr�e un identifiant unique pour l�apr�s-midi.

SaisirJeu()
- on demande la saisie d�un nom du jeu, et on v�rifie qu�il n�existe pas d�j�. Si ce jeu existe d�j�, on demande si l�utilisateur veut ajouter un exemplaire � ce jeu, sinon, on lui demande de saisir un autre nom de jeu.
- on affiche les cat�gories de jeu, et on demande de saisir le nombre correspondant � la cat�gorie
SaisirInscription()
- on demande la saisie de l�identifiant d�une apr�s-midi, si l�utilisateur rentre un identifiant incorrect on affiche liste des apr�s-midi qui ont encore des places de disponible.
- on demande l�identifiant de l�utilisateur qui souhaite s�inscrire
- on v�rifie s�il n�est pas d�j� inscrit
Explication des fonctions de sauvegarde�:
Apr�s chaque modification d�un �l�ment d�un tableau, on sauvegarde le tableau dans le fichier correspondant. Cette fonctionnalit� permet de sauvegarder r�guli�rement, au lieu de tout sauvegarder en m�me temps en quittant le programme, ce qui pourrait provoquer une perte des donn�es modifi�es si l�utilisateur ferme directement la console, ou encore lors d�un incident tel qu�une coupure d��lectricit�. Nous avons choisi d�utiliser les fichiers binaires pour la facilit� de sauvegarde.

Nous prenons comme exemple la fonction SauverAdherant()
void SauverAdherants(Adherant tAdherants[], int nbAdherants) {

    FILE *fb;
// d�claration du pointeur fb
    fb = fopen("adherants.bin", "wb");
// fb pointe sur le fichier qui est ouvert en mode �criture binaire
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
// si fb est �gal � NULL cela signifie que nous avons des probl�mes de droits dans le r�pertoire courant, on quitte alors le programme
    }
    fwrite(&nbAdherants, sizeof(int), 1, fb);
// on sauvegarde le nombre d��l�ments du tableau
    fwrite(tAdherants, sizeof(Adherant), (size_t) nbAdherants, fb);
// on sauvegarde le tableau
    fclose(fb);
// et on n�oublie pas de fermer le fichier.
}

Explication des fonctions de lecture�:
Au d�but du programme, on lit le nombre d��l�ments des tableaux, on alloue la m�moire n�cessaire en fonction du nombre d��l�ments que poss�de chacun d�entre eux, puis on les remplit gr�ce aux donn�es stock�es dans les fichiers binaires.
Exemple�: la fonction LireEmprunts ()
Emprunt *LireEmprunts(int *nbEmprunts){
    FILE *fb;
    fb = fopen("emprunts.bin", "rb");
    if (fb == NULL){
        printf("Probleme d'ouverture de ficiher. \n");
        *nbEmprunts = -1;
        return NULL;
    }
    fread(nbEmprunts, sizeof(int), 1, fb);
    Emprunt *tEmprunt;
    tEmprunt = (Emprunt*) malloc (*nbEmprunts * sizeof(Emprunt));
// allocation de la m�moire en fonction du nombre d��l�ments
    if (tEmprunt == NULL){
        printf("Probleme d'allocation de memoire (lecture tEmprunts)");
        exit(1);
    }

    fread(tEmprunt, sizeof(Emprunt), (size_t)*nbEmprunts, fb);
    return tEmprunt;
}

Explication des structures�:
Dans notre programme, nous avons utilis�s 6 structures. Chacune d�entre elles r�pond � un besoin essentiel de l�application. Les structures impl�ment�es sont les suivantes�: 
Structure �Date��:
typedef struct {
    int jour, mois, annee;
    time_t time;
}Date;

Cette structure est compos�e de trois entiers�: ��jour��, ��mois�� et ��annee�� qui permettent de stocker les informations n�cessaires au moment de saisir une date. Puis, en utilisant ces entiers enregistr�s, on cr�e une variable ��time�� de type ��time_t�� qui garde une valeur de temps du syst�me. 
Structure �Jeu��:

typedef struct {
    char nom[25];
    char nomCategorie[20];
    int nbExemplaires;
    int nbEmprunts;
}Jeu;

Cette structure est compos�e deux cha�nes de caract�res et deux entiers. Le nom sert comme identifiant pour cette structure car on n�accepte pas deux jeux avec le m�me nom. Si au moment de saisir un jeu il se trouve que le nom est d�j� parmi les jeux existants, on augmente la variable ��nbExemplaires�� de un. Finalement, la variable ��nbEmprunts�� garde le nombre de emprunts courants pour ce jeu. Un jeu qui a 2 exemplaires et 2 emprunts ne pourra donc pas �tre emprunt� � ce moment-l�.

Structure �Emprunt��:

typedef struct {
    Date dateEmprunt;
    char nomJeu[25];
    int numAdherant;
}Emprunt;

Cette structure est compos�e d�une variable de type ��Date�� qui indique quand l�emprunt a �t� effectu�. Elle contient aussi le nom du jeu emprunt� sous forme de chaine de caract�res et finalement l�adh�rent qui a effectu� cet emprunt.

Structure �Adherant��:
typedef struct {
    int numAdherant;
    char nomAdherant[15];
    char prenomAdherant[15];
    int nbEmpCourants;
    Date dateAdhesion;
}Adherant;

Cette structure est compos�e d�abord d�un entier qui sert comme identifiant unique pour un adh�rent. Cet entier est cr�� � partir de la fonction CreerIdentifiant ()�. En plus, la structure contient le nom et le pr�nom du adh�rant, suivi d�un entier qui garde le nombre d�emprunts courants pour cet adh�rent et une variable de type ��Date�� qui garde sa date d�adh�sion � la Ludoth�que.
Structure �Adherant��:
typedef struct {
    char codeAprem[6];
    Date date;
    int heureDebut;
    int nbPlaces;
    int nbAdhInscrits;
}ApremTh;
Cette structure est compos�e d�un code unique ��codeAprem�� qui est initialis�e � partir de la fonction CreerIdentifiant (). La structure contient aussi une variable de type ��Date�� qui garde la date de l��v�nement. Finalement, elle garde aussi le nombre de places pour cet �v�nement dans la variable ��nbPlaces�� et le nombre d�inscrits dans la variable ��nbAdhInscrits��. Un adh�rent ne pourra pas s�inscrire � une apr�s-midi qui contient des valeurs �gales pour ��nbPlaces�� et ��nbAdhInscrits��.
Structure �Inscription��:
typedef struct {
    char codeAprem[6];
    int numAdherant;
}Inscription;
Cette structure permet d�effectuer l�inscription d�un membre � une apr�s-midi th�matique. Elle contient les identifiants des deux structures concern�es. ��codeAprem�� sert � identifier l�apr�s-midi � laquelle l�adh�rent est inscrit et ��numAdherant�� sert � identifier l�adh�rent qui est inscrit.

