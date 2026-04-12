🚀 Projet ECE‑Type (Shoot'em Up – Allegro 5)
Jeu d’arcade développé en langage C avec la bibliothèque Allegro 5, inspiré du classique R‑Type (1987).

🎯 Objectif du projet
Projet du semestre d’informatique visant à appliquer la méthode DTI (Données / Traitements / Interface) à travers la création d’un shoot’em up à scrolling horizontal en 2D.

🕹️ Gameplay
Le joueur contrôle un vaisseau se déplaçant librement dans une aire de jeu de 800×600 px.
Le décor défile de droite à gauche à vitesse constante.
Des ennemis mobiles et fixes apparaissent.
Le joueur peut tirer avec la touche Espace.
Les collisions sont détectées entre :
tirs du joueur et ennemis,
vaisseau et ennemis.
Le jeu dispose d’un système de vies et de fins de partie.
Les images et sons sont chargés depuis le répertoire assets/.
Contrôles
Touche	Action
↑ / ↓ / ← / →	Déplacer le vaisseau
Espace	Tirer
Échap	Quitter le jeu
P (à venir)	Pause
🧩 Architecture
Projet structuré selon une architecture modulaire :

Module	Rôle
main.c	Point d’entrée du jeu
jeu.c / jeu.h	Boucle principale et logique du moteur
joueur.*	Gestion du vaisseau joueur
ennemi.*	Gestion des ennemis
tir.*	Gestion et affichage des tirs
collision.*	Détection et traitement des collisions
ressources.*	Chargement et libération des sons/images
assets/	Contient les images du jeu
🛠️ Compilation
Sous MSYS2 / MinGW 64‑bit
bash


cd /c/Users/mathi/OneDrive/Documents/workspace/workspace/ECE-Type
make
./ShootEmUp.exe
Bibliothèques nécessaires
Installe Allegro 5 via :

bash


pacman -S mingw-w64-x86_64-allegro
🧠 Fonctionnalités respectées du cahier des charges
✅ Déplacement fluide du joueur
✅ Scrolling du décor
✅ Tirs multiples du joueur
✅ Ennemis mobiles et détection de collisions
✅ Explosions (code prévu)
✅ Architecture modulaire et codage C propre
✅ Chargement d’images Allegro et libération mémoire
✅ Gestion clavier événementielle en temps réel
✅ Absence de fuites mémoire observée
✅ Ressources conformes (< 50 Mo)

✨ Extensions prévues
Bonus de type Force Pod
Système de score et vies affiché à l’écran
Animations d’explosions enrichies (explosion.png)
Boss de fin de niveau (boss.png)
Effets sonores synchronisés avec ressources.c
