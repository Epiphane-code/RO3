`README.md` Mini Shell :

```markdown
🐚 Mini Shell - Projet C

📌 Description

Ce projet implémente un mini shell en langage C. Il lit les commandes saisies par l'utilisateur, les exécute dans un processus fils, et gère certaines erreurs.

---

🧩 Fonctionnalités

- Invite de commande personnalisée : `MiniShell >`
- Exécution de commandes systèmes (`ls`, `pwd`, `echo`, etc.)
- Gestion des erreurs de commande
- Possibilité de quitter avec `exit`

---

📁 Fichiers

- `minishell.c` : script principal du shell
- `README.md` : description du projet

---

🔧 Compilation

Compile avec `gcc` :

```bash
gcc minishell.c -o minishell
```

---

▶️ Exécution

Lance le shell :

```bash
./minishell
```

Tape une commande comme :

```bash
ls
pwd
echo Hello World
exit
```

---

⚙️ Commandes utilisées dans le script

- `fgets()` : lire l'entrée utilisateur
- `strtok()` : séparer commande et arguments
- `fork()` : créer un processus fils
- `execvp()` : exécuter la commande
- `wait()` : attendre la fin du processus fils
- `strcmp()` : comparer les chaînes (ex: pour `exit`)

---
Ce travail est le fruit des apports indidividuels des membres du Rush-11 dans le cadre du programme *Piscine-Codeloccol, Projet R03 : Mini Shell*.

👤 Auteurs                                             

Omar_EN
LAOULI_MH
Sultan_B
Hassan_I
Abdou_Kalassi_M
NB: Chaque membres a apporté ses contributions afin de pouvoir se decider sur ce fichier.
```
