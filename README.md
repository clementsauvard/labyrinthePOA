# labyrinthePOA

On se propose de réaliser le jeu de type Kill'emAll en beaucoup plus simple, avec un affichage 3D lui aussi simplifié.

La machine anime des personnages de type gardien dont le but est de protéger un trésor caché dans une pièce du labyrinthe, que vous, le chasseur, essayez de prendre. Le but restant le même dans le jeu en réseau (vous pouvez vous allier ou pas avec l'autre humain).

Chaque personnage possède un capital initial de survie qui est décrémenté à chaque fois qu'il subit une attaque de l'un de ses adversaires. Ce capital est incrémenté quand le personnage reste un certain temps sans subir de blessure (ou tout autre critère comme par exemple trouver des réserves de santé sous forme de caisses de survie). Le capital initial de chaque type de personnage (gardiens, chasseur) et le temps de récupération devront être des paramètres du programme.

Les gardiens peuvent attaquer le chasseur à distance en tirant dessus avec une arme qui tire en ligne droite, et dont le projectile est arreté par un obstacle quelconque (mur, objet, etc.), la cible du gardien doit donc être visible pour que le tir ait une chance d'être efficace. Pour laisser une chance au chasseur, chaque gardien a un probabilité de manquer sa cible; cette probabilité dépend de l'état de santé du gardien : moins il a de points de vie, plus il tire mal. Le coefficient qui relie l'état de santé d'un gardien à sa capacité à tirer précisément est aussi un paramètre du programme.

Réciproquement, le chasseur peut attaquer les gardiens, il partage avec les gardiens la caractéristique d'avoir une précision de tir variable avec sont état de santé. Le coefficient n'est pas le même que pour un gardien car le tir du chasseur est dirigé par un humain (et est donc bien moins précis que ce que peut faire la machine qui est parfaite!).

Le chasseur se déplace dans le labyrinthe dans une direction qui est indiquée par la souris et/ou le clavier, c'est le joueur humain qui contrôle complètement le chasseur. Par contre, les gardiens sont des incarnations de la machine : ils sont animés par une sorte d'instinct artificiel qui les poussent d'une part à protéger le trésor, et d'autre part à attaquer le chasseur. C'est l'opposition entre ces deux potentiels plus une dose d'aléatoire qui décide de leur comportement à chaque instant. Chaque gardien sait exactement où se trouvent ses congénères et où est le trésor. Un gardien calcule son potentiel de protection en fonction de la distance qui le sépare du trésor, et du potentiel de protection des autres gardiens.

Un gardien va décider d'aller à la recherche du chasseur dès que son potentiel de protection va être en dessous d'un certain seuil. Pour éviter que les gardiens se figent à une distance qui équilibrent leurs potentiels, on va mettre deux seuils : si le potentiel de protection dépasse le seuil haut, le gardien passe à l'attaque, si le potentiel de protection devient inférieur au seuil bas, il reste en défense. Ces seuils sont des paramètres du programme. Enfin, pour rendre réaliste le comportement des gardiens, on tirera un nombre aléatoire qui s'ajoutera (ou se retranchera s'il est négatif) au potentiel calculé; cela devrait éviter aux gardiens d'avoir un comportement trop prédictible!

# How to play

Pour lancer le fichier : make -f Makefile-proto cstrike64

Puis : ./cstrike64 -l labyrinthe.txt
