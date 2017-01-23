De Vries Gerben - Rodriguez Juan | Groupe 7

**Projet Structures de données – P2
Gestion d’une Ludothèque**

Liste des fonctionnalités proposées : 

- Un menu principal à partir duquel l’utilisateur choisit les actions qu’il veut effectuer. A partir de ce dernier, il va choisir s’il veut faire l’affichage d’une liste, ajouter un élément à une liste ou encore supprimer un élément en saisissant le nombre correspondant au choix voulu, ce qui va permettre d’accéder au sous-menu.

- Dans le 1er sous-menu, on peut choisir d’ajouter : un nouvel adhérent, un jeu, l’emprunt d’un jeu, une après-midi thématique, une inscription d’un adhérent à cette dernière, ou encore de renouveler une adhésion.

- Dans le 2eme sous-menu, on peut choisir d’afficher : la liste des jeux triés par ordre alphabétique, la liste des adhérents, la liste des emprunts en cours, la liste d’inscrits à une après-midi thématique, ainsi que les emprunteurs qui ont un retard.

- Enfin, dans le 3eme sous-menu, on peut choisir de supprimer : un adhérent, un jeu ; de rendre un emprunt, ou de désinscrire un adhérant d’une après-midi thématique.


Description des fonctionnalités : 

1er sous-menu :
Le fonctionnement des fonctions qui ajoutent des éléments dans les tableaux est très similaire. On passe en paramètres les tableaux permettant de faire les vérifications des contraintes souhaitées ainsi que les tableaux directement concernés par l’ajout des nouvelles valeurs. Nous commenterons une fonction de chaque type afin d’en expliquer le fonctionnement général.
On prend pour exemple la fonction ChargerTAprem(), qui permet d’ajouter des Après-midis dans le tableau tAprem[]


	ApremTh *ChargerTAprem(ApremTh tAprem[], int *nbAprems, int *taillePhysique, int nbAjouts) {
	if(*nbAprems == 0) {
	// si le nombre d’éléments du tableau est égal à 0, on n’a pas encore fait de malloc pour le tableau. On le fait donc maintenant.
	    *taillePhysique += 3;
	    tAprem = (ApremTh *) malloc(*taillePhysique * sizeof(ApremTh));
	    if (tAprem == NULL) {
		printf("Probleme d'allocation de memoire (malloc tAdherants)");
		exit(1);
	    }
	}
	ApremTh aprem, *tApremBuffer;
	int apremDeb = *nbAprems;    
	if (*nbAprems == *taillePhysique) {//Si à ce moment-là la taille logique est égale à la taille physique, on augmente la capacité de stockage du tableau.
		*taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
		tApremBuffer = (ApremTh *) realloc(tAprem, *taillePhysique * sizeof(ApremTh));
	// on effectue une réallocation de la mémoire pour correspondre à la nouvelle taille physique du tableau
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



Les fonctions de chargement possèdent une fonction de saisie. Elles renvoient un type qui sera inséré dans le tableau correspondant dans la fonction de chargement. La fonction de saisie demande à l’utilisateur de renseigner les informations nécessaires qui seront stockées dans un type renvoyé par la fonction. 
On tient compte des contraintes lors de la saisie. Par exemple, lors de la saisie d’une date on vérifie que celle-ci est correcte, lorsqu’on demande d’emprunter un jeu on vérifie qu’il y ait des exemplaires de disponibles, etc…

Explication de la fonction SaisirApremTh() :


	ApremTh SaisirApremTh(ApremTh tAprems[], int nbAprems) {
    ApremTh apremTh;
    printf("\n\n|SAISIE APRES-MIDI THEMATIQUE|\n\n");
    apremTh.date = SaisirDate();
	// fonction qui permet de saisir une date et qui l’enregistre dans un type Date.
	    printf("Quel est le nombre correspondant a l'heure de debut de l'evenement ? (format 24h) :\n");
	// on demande à l’utilisateur de saisir l’heure de début de l’après-midi thématique.
	    scanf("%d", &apremTh.heureDebut);
	// on vérifie que les saisies soient correctes.
	    while (apremTh.heureDebut < 1 || apremTh.heureDebut > 23) {
		printf("Saisie incorrecte (format 24h, entrez 2 chiffres). Reessayez :\n");
		scanf("%d", &apremTh.heureDebut);
	    }
	// L’utilisateur saisit le nombre de places de l’évènement.
	    printf("Quel sera le nombre de places ?\n");
	    scanf("%d", &apremTh.nbPlaces);

	    apremTh.nbAdhInscrits = 0;
	// on initialise le nombre d’adhérents inscrits à 0.
	    strcpy(apremTh.codeAprem, CreerIdentifiant(2));
	// on crée un identifiant unique pour l’après-midi, en vérifiant qu’il ne soit pas déjà utilisé.
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

2ième sous-menu :
Les fonctions d’affichage, elles aussi, sont très similaires. Chaque fonction d’affichage d’un tableau affiche les éléments de ce dernier.
Nous allons prendre pour exemple la fonction AfficherJeux() :

	void AfficherJeux(Jeu tJeux[], int nbJeux) {
	// si le tableau de jeu ne contient aucun élément, on affiche un    message spécifique.
     if(nbJeux == 0){
        printf("\nAucun jeu n'a ete trouve.\n");
        return;
    }

    int i; // on initialise un compteur
    // on répète l’affichage autant de fois qu’il y’a d’éléments.
    for (i = 0; i < nbJeux; i++) { 
        printf("\n\nNom : %s (%s) - # Exemplaires: %d \n", tJeux[i].nom, tJeux[i].nomCategorie, tJeux[i].nbExemplaires);
    } 
	}

3ième sous-menu :
Les fonctions de suppression permettent à l’utilisateur de supprimer un élément d’un tableau. Afin d’expliquer le fonctionnement de ces fonctions, on va s’appuyer sur l’exemple de la fonction SupprimerInscription() :

	void SupprimerInscription(Inscription tInscriptions[], int *nbInscriptions, ApremTh tAprems[], int nbAprems, Adherant tAdherants[], int nbAdherants){
	    // le tableau dont on veut supprimer des éléments est passé en paramètres, ainsi que d’autres tableaux qui permettent de vérifier les contraintes voulues.
	    if(*nbInscriptions <= 0){
		printf("Aucune inscription n'a ete trouvee. Impossible de supprimer. \n");
		return;
	    }
	    int numAdherant, index;
	    char *codeAprem;

	// codeAprem est l’identifiant de l’apres-midi thématique
	    codeAprem = malloc(sizeof(char) * (3));
	    printf("\n|ANNULER L'INSCRIPTION A UNE APRES-MIDI|\n");
	    printf("Saisissez le numero de l'adherant qui veut annuler son inscription : ");
	    scanf("%d", &numAdherant);
	// on recherche si l’adhérant existe bien
	    index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
	    while (index == -1) {
	// L’utilisateur est forcé de rentrer le numéro d’un adhérant existant.
		printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
		AfficherAdherants(tAdherants, nbAdherants);
		printf("\n\t Reessayez. Saissisez le numero de l'Adherant a inscrire : \n");
		scanf("%d", &numAdherant);
		index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
	    }
	    printf("Cet adherant est inscrit aux apres-midis suivantes: \n");
	// on affiche les aprèms auxquels l’adhérant est inscrit, afin de faciliter  le travail de l’utilisateur.
	    int i, j=0;
	    for(i=0; i < *nbInscriptions; i++){
		if(tInscriptions[i].numAdherant == numAdherant){
		    Afficher1Aprem(tAprems, nbAprems, tInscriptions[i].codeAprem);
		    j++;
		}
	    }
	    if (j == 0){
	// on traite le cas où l’adhérant n’est inscrit à aucune après midi
		system("cls");
		printf("\nCet adherant n'est inscrit a aucune apres-midi. Impossible d'annuler une inscription.\n");
		return;
	    }
	// sinon, on demande de quelle aprèm il veut se désinscrire.
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
	// si l’utilisateur a bien saisi un numéro d’après-midi auquel l’adhérant était inscrit, celui-ci est maintenant supprimé, et le type ApremTh contient un adhérant d’inscrit en moins.
	    tAprems[index].nbAdhInscrits--;

	    index = RechercherInscription(tInscriptions, *nbInscriptions, codeAprem, numAdherant);
	    for (i = index; i < *nbInscriptions - 1; i++){
		tInscriptions[i] = tInscriptions[i +1];
	    }
	    *nbInscriptions = *nbInscriptions - 1;
	    printf("—L’adherant a bien annule son inscription! --\n");
	}


Explication des fonctions de recherche :
Nous avons utilisé des fonctions de recherche récursives. Lorsque l’élément recherché est trouvé, on envoie son rang dans le tableau et sinon, on renvoie -1.

	int RechercherEmprunt(Emprunt tEmprunts[], int nbEmprunts, int numAdherant, char nomJeu[]){
	    if (strcmp(tEmprunts[nbEmprunts].nomJeu, nomJeu) == 0 && tEmprunts[nbEmprunts].numAdherant == numAdherant) {
		return nbEmprunts;
	    }
	    if (nbEmprunts == -1){
		return -1;
	    }
	    return RechercherEmprunt(tEmprunts, nbEmprunts - 1, numAdherant, nomJeu);
	}


Explication fonction de tri (utilisée pour trier la liste des jeux par ordre alphabétique) :
D'abord, cette fonction partitionne le tableau des jeux en deux parties. Puis, elle fait un tri indépendant des deux sous-tableaux obtenus. 
Le point de départ pour effectuer ce partitionnement est indiqué par l'index 'pivot'. Le pivot sera placé toujours à sa place définitive (trié).
Puis, on procède à la permutation des éléments de telle sorte à ce que ceux qui se situent à la partie gauche soient inferieurs au pivot 
Finalement, on définit un pivot pour chacun des sous-tableaux et on répète le partitionnement. Ce processus est répété de manière récursive jusqu'à ce que tous les éléments soient triés.

Explication des contrôles dans les fonctions de saisie : 

	SaisirDate() :
	while(date.jour < 1 || date.jour > 31 || date.mois < 1 || date.mois > 12 || date.annee < 1900 || date.annee > 2150){
	    printf("\nSaisie incorrecte. Reessayez (au format JJ/MM/AAAA) :\n");
	    scanf("%d/%d/%d", &date.jour, &date.mois, &date.annee);
	}
On demande à l’utilisateur de faire une saisie de la date tant qu’elle est incorrecte.

SaisirAdherant() :
- On génère un identifiant unique pour l’adhérent.
- On demande à l’utilisateur de saisir son nom, prénom (de 14 caractères maximum, tronqué au-delà) et sa date d’adhésion (saisie grâce à l’appel de la fonction SaisirDate()).

SaisirEmprunt() :
- on demande la saisie d’un adhérent, on vérifie que ce dernier soit existant.
- on vérifie si l’adhésion de l’adhérent est expirée, dans quel cas on ne peut pas saisir d’emprunt.
- on vérifie si l’adhérent emprunte actuellement 3 jeux, cas dans lequel il ne peut pas en emprunter plus.
- on demande la saisie d’un jeu.
- on vérifie que le jeu existe, le cas échéant, on montre la liste des jeux que l’adhérent peut emprunter.
- on vérifie que tous les exemplaires de ce jeu ne soient pas empruntés actuellement.
- si la saisie du jeu et de l’adhérent sont valides, on augmente de 1 le nombre d’emprunts en cours de l’utilisateur, ainsi que le nombre d’exemplaires de ce jeu actuellement empruntés.

SaisirApremTh() :
- on demande la saisie de la date de l’aprèm par l’intermédiaire de la fonction SaisirDate().
- on demande la saisie de l’heure de début de l’évènement en vérifiant que celle-ci se situe entre 0 et 24 exclus, le nombre de places.
- on crée un identifiant unique pour l’après-midi.

SaisirJeu()
- on demande la saisie d’un nom du jeu, et on vérifie qu’il n’existe pas déjà. Si ce jeu existe déjà, on demande si l’utilisateur veut ajouter un exemplaire à ce jeu, sinon, on lui demande de saisir un autre nom de jeu.
- on affiche les catégories de jeu, et on demande de saisir le nombre correspondant à la catégorie
SaisirInscription()
- on demande la saisie de l’identifiant d’une après-midi, si l’utilisateur rentre un identifiant incorrect on affiche liste des après-midi qui ont encore des places de disponible.
- on demande l’identifiant de l’utilisateur qui souhaite s’inscrire
- on vérifie s’il n’est pas déjà inscrit
Explication des fonctions de sauvegarde :
Après chaque modification d’un élément d’un tableau, on sauvegarde le tableau dans le fichier correspondant. Cette fonctionnalité permet de sauvegarder régulièrement, au lieu de tout sauvegarder en même temps en quittant le programme, ce qui pourrait provoquer une perte des données modifiées si l’utilisateur ferme directement la console, ou encore lors d’un incident tel qu’une coupure d’électricité. Nous avons choisi d’utiliser les fichiers binaires pour la facilité de sauvegarde.

Nous prenons comme exemple la fonction SauverAdherant()

	void SauverAdherants(Adherant tAdherants[], int nbAdherants) {
		    FILE *fb;
		// déclaration du pointeur fb
		    fb = fopen("adherants.bin", "wb");
		// fb pointe sur le fichier qui est ouvert en mode écriture binaire
		    if (fb == NULL) {
			printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
			exit(1);
		// si fb est égal à NULL cela signifie que nous avons des problèmes de droits dans le répertoire courant, on quitte alors le programme
		    }
		    fwrite(&nbAdherants, sizeof(int), 1, fb);
		// on sauvegarde le nombre d’éléments du tableau
		    fwrite(tAdherants, sizeof(Adherant), (size_t) nbAdherants, fb);
		// on sauvegarde le tableau
		    fclose(fb);
		// et on n’oublie pas de fermer le fichier.
		}

Explication des fonctions de lecture :
Au début du programme, on lit le nombre d’éléments des tableaux, on alloue la mémoire nécessaire en fonction du nombre d’éléments que possède chacun d’entre eux, puis on les remplit grâce aux données stockées dans les fichiers binaires.
Exemple : la fonction LireEmprunts ()

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
	// allocation de la mémoire en fonction du nombre d’éléments
	    if (tEmprunt == NULL){
		printf("Probleme d'allocation de memoire (lecture tEmprunts)");
		exit(1);
	    }

	    fread(tEmprunt, sizeof(Emprunt), (size_t)*nbEmprunts, fb);
	    return tEmprunt;
	}

Explication des structures :
Dans notre programme, nous avons utilisés 6 structures. Chacune d’entre elles répond à un besoin essentiel de l’application. Les structures implémentées sont les suivantes : 
Structure ‘Date’ :

	typedef struct {
	    int jour, mois, annee;
	    time_t time;
	}Date;

Cette structure est composée de trois entiers : « jour », « mois » et « annee » qui permettent de stocker les informations nécessaires au moment de saisir une date. Puis, en utilisant ces entiers enregistrés, on crée une variable « time » de type « time_t » qui garde une valeur de temps du système. 
Structure ‘Jeu’ :

	typedef struct {
	    char nom[25];
	    char nomCategorie[20];
	    int nbExemplaires;
	    int nbEmprunts;
	}Jeu;

Cette structure est composée deux chaînes de caractères et deux entiers. Le nom sert comme identifiant pour cette structure car on n’accepte pas deux jeux avec le même nom. Si au moment de saisir un jeu il se trouve que le nom est déjà parmi les jeux existants, on augmente la variable « nbExemplaires » de un. Finalement, la variable « nbEmprunts » garde le nombre de emprunts courants pour ce jeu. Un jeu qui a 2 exemplaires et 2 emprunts ne pourra donc pas être emprunté à ce moment-là.

Structure ‘Emprunt’ :

	typedef struct {
	    Date dateEmprunt;
	    char nomJeu[25];
	    int numAdherant;
	}Emprunt;

Cette structure est composée d’une variable de type « Date » qui indique quand l’emprunt a été effectué. Elle contient aussi le nom du jeu emprunté sous forme de chaine de caractères et finalement l’adhèrent qui a effectué cet emprunt.

Structure ‘Adherant’ :
	typedef struct {
	    int numAdherant;
	    char nomAdherant[15];
	    char prenomAdherant[15];
	    int nbEmpCourants;
	    Date dateAdhesion;
	}Adherant;

Cette structure est composée d’abord d’un entier qui sert comme identifiant unique pour un adhérent. Cet entier est créé à partir de la fonction CreerIdentifiant () . En plus, la structure contient le nom et le prénom du adhérant, suivi d’un entier qui garde le nombre d’emprunts courants pour cet adhérent et une variable de type « Date » qui garde sa date d’adhésion à la Ludothèque.

Structure ‘ApremTh’ :

	typedef struct {
	    char codeAprem[6];
	    Date date;
	    int heureDebut;
	    int nbPlaces;
	    int nbAdhInscrits;
	}ApremTh;

Cette structure est composée d’un code unique « codeAprem » qui est initialisée à partir de la fonction CreerIdentifiant (). La structure contient aussi une variable de type « Date » qui garde la date de l’évènement. Finalement, elle garde aussi le nombre de places pour cet évènement dans la variable « nbPlaces » et le nombre d’inscrits dans la variable « nbAdhInscrits ». Un adhérent ne pourra pas s’inscrire à une après-midi qui contient des valeurs égales pour « nbPlaces » et « nbAdhInscrits ».
Structure ‘Inscription’ :

	typedef struct {
	    char codeAprem[6];
	    int numAdherant;
	}Inscription;

Cette structure permet d’effectuer l’inscription d’un membre à une après-midi thématique. Elle contient les identifiants des deux structures concernées. « codeAprem » sert à identifier l’après-midi à laquelle l’adhèrent est inscrit et « numAdherant » sert à identifier l’adhèrent qui est inscrit.

