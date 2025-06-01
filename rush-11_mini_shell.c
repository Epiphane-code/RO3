#include <stdio.h>             // printf(), getline(), perror(), fflush()
#include <stdlib.h>            // exit(), free() 
#include <string.h>            // strcmp(), strtok()
#include <unistd.h>            // chdir(), getcwd(), execvp(), fork(), waitpid()
#include <sys/types.h>         // pid_t
#include <errno.h>             // errno
#include <signal.h>            // signal handling
#include <fcntl.h>             // open(), O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
#include <sys/types.h>         // pid_t
#include <sys/wait.h>          // waitpid(), WIFEXITED()
#include <limits.h>            // PATH_MAX


int main()
{
    printf("||||||||||||||||||||| MINI_SHELL RUSH-11 ||||||||||||||||||||||||\n");
    char * line = NULL;                                // Pointeur pour stocker la ligne lue depuis l'entrée standard
    size_t len = 0;                                    // Taille initiale de la ligne, size_t : type non utilisé pour recuperer la taille memoire par exemple
    ssize_t read;                                      // Nombre de caractères lus depuis l'entrée standard
    char *args[100];                                   // Tableau pour stocker les arguments de la commande
    pid_t pid;                                         // Identifiant du processus
    int status;                                        // Statut de retour du processus enfant
    char rep[PATH_MAX];                                // Tableau pour stocker le répertoire de travail actuel
    while (1) {
        getcwd(rep, sizeof(rep)),                      // Récupérer le répertoire de travail actuel
        printf("mini_shell>%s> ", rep);                // Afficher le prompt avec le répertoire actuel
        fflush(stdout);                                // pour vider le tampon de sortie standard

        read = getline(&line, &len, stdin);            // lire une ligne depuis l'entrée standard
        if (read == -1) {
            perror("getline");                        // Afficher une erreur si getline échoue
            free(line);                               // Libérer la mémoire allouée pour la ligne
            exit(EXIT_FAILURE);                       // Quitter le programme en cas d'erreur
        }


        if (line[read - 1] == '\n') {                 // Vérifier si le dernier caractère est un saut de ligne
            line[read - 1] = '\0';                    // Remplacer le saut de ligne par un caractère nul
        }

        // stockage des arguments de la commande
        int i = 0;   
        args[i] = strtok(line, " ");                 // Diviser la ligne en tokens (arguments) en utilisant l'espace comme délimiteur
        while (args[i] != NULL) {                    // Tant qu'il y a des arguments à traiter
            i++;                                     // Incrémenter l'index pour le prochain argument
            args[i] = strtok(NULL, " ");             // Continuer à diviser la ligne en tokens
        }

        // Si la ligne est vide, continuer à la prochaine itération
        if (i == 0) {                                // Si aucun argument n'est trouvé, ignorer la ligne vide
            continue;                                // Passer à l'itération suivante de la boucle
        }

        if (strcmp(args[0], "exit") == 0) {          // Vérifier si la commande est "exit"
            free(line);                              // Libérer la mémoire allouée pour la ligne
            exit(EXIT_SUCCESS);                      // Quitter le programme avec succès
         break;                                      // Sortir de la boucle principale si la commande est "exit"
        }

        if (strcmp(args[0], "cd") == 0){             // Vérifier si la commande est "cd"
            chdir(args[1]);                          // Changer le répertoire de travail actuel
            continue;                                // Passer à l'itération suivante de la boucle
        }

        // Fork a child process
        pid = fork();                               // Créer un nouveau processus enfant
        if (pid < 0) {                              // Vérifier si le fork a échoué
            perror("fork");                         // Afficher une erreur si le fork échoue
            free(line);                             // Libérer la mémoire allouée pour la ligne
            exit(EXIT_FAILURE);                     // Quitter le programme en cas d'erreur
        } else if (pid == 0) {                      // si nous sommes dans le processus enfant
            // Redirection de l'entrée/sortie si nécessaire
            execvp(args[0], args);                  // Exécuter la commande avec les arguments fournis
            perror("execvp");                       // Afficher une erreur si execvp échoue
            exit(EXIT_FAILURE);                     // Quitter le processus enfant en cas d'erreur
        } else {
            // Si nous sommes dans le processus parent, attendre que l'enfant se termine
            do {
                waitpid(pid, &status, 0);           // Attendre que le processus enfant se termine
            } while (!WIFEXITED(status));           // Vérifier si le processus enfant s'est terminé normalement
        }
    }

    free(line);                                    // Libérer la mémoire allouée pour la ligne
    return 0;                                      // Retourner 0 pour indiquer que le programme s'est terminé avec succès

}
