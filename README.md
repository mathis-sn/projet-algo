# 🚀 ECE-Type — Shoot’em Up 2D (Allegro 5)

**ECE-Type** est un shoot’em up 2D inspiré du classique *R-Type (1987)*, développé en langage **C** avec la bibliothèque **Allegro 5** dans le cadre d’un projet informatique de semestre.  

Le jeu applique la méthode **DTI (Données / Traitements / Interface)** à travers une architecture modulaire propre et extensible.

---

## 🎯 Objectif du projet

Créer un jeu vidéo arcade à scrolling horizontal en 2D intégrant :

- gestion d’un joueur et de ses tirs  
- ennemis mobiles et fixes  
- détection de collisions  
- ressources graphiques et sonores  
- boucle de jeu événementielle  
- architecture modulaire en C  

---

## 🕹️ Gameplay

- Le joueur contrôle un vaisseau dans une zone de **800×600 px**
- Le décor défile de **droite à gauche** à vitesse constante  
- Des ennemis apparaissent dynamiquement (mobiles ou statiques)  
- Le joueur peut tirer avec **Espace**

### 💥 Collisions

- tirs du joueur ↔ ennemis  
- vaisseau ↔ ennemis  

### ⚙️ Systèmes intégrés

- système de vies  
- fin de partie  
- chargement des images et sons depuis `assets/`  

---

## 🎮 Contrôles

| Touche | Action |
|--------|--------|
| ↑ / ↓ / ← / → | Déplacer le vaisseau |
| Espace | Tirer |
| Échap | Quitter le jeu |
| P *(à venir)* | Pause |

---

## 🧩 Architecture du projet

Le projet suit une architecture modulaire claire :

| Module | Rôle |
|--------|------|
| `main.c` | Point d’entrée du jeu |
| `jeu.c / jeu.h` | Boucle principale, logique du moteur |
| `joueur.*` | Gestion du vaisseau joueur |
| `ennemi.*` | Gestion des ennemis |
| `tir.*` | Gestion et affichage des tirs |
| `collision.*` | Détection et traitement des collisions |
| `ressources.*` | Chargement et libération des images/sons |
| `assets/` | Images, sprites, sons |

---

## 🛠️ Compilation & Exécution

### 💻 Sous MSYS2 / MinGW-w64 (64-bit)

```bash
cd /c/Users/mathi/OneDrive/Documents/workspace/workspace/ECE-Type
make
./ShootEmUp.exe
```

## 🧠 Fonctionnalités réalisées

- [x] Déplacement fluide du joueur  
- [x] Scrolling horizontal du décor  
- [x] Tirs multiples du joueur  
- [x] Apparition d’ennemis mobiles  
- [x] Détection de collisions *(tirs ↔ ennemis, joueur ↔ ennemis)*  
- [x] Gestion des vies et fin de partie  
- [x] Chargement d’images Allegro + libération mémoire  
- [x] Architecture modulaire propre  
- [x] Gestion clavier événementielle  
- [x] Aucune fuite mémoire détectée  
- [x] Ressources < 50 Mo  

---

## ✨ Extensions prévues

- [ ] 🔥 Bonus Force Pod  
- [ ] 📊 Système de score + HUD  
- [ ] 💥 Animations d’explosions avancées (`explosion.png`)  
- [ ] 👾 Boss de fin de niveau (`boss.png`)  
- [ ] 🔊 Effets sonores synchronisés *(via `ressources.c`)*  
