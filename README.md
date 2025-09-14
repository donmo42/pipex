🌀 Pipex
🔎 Description

pipex est un programme qui reproduit le comportement suivant de ton shell :
< infile cmd1 | cmd2 > outfile


Il prend 4 arguments :

argv[1] = infile → fichier d’entrée
argv[2] = cmd1 → première commande à exécuter
argv[3] = cmd2 → deuxième commande à exécuter
argv[4] = outfile → fichier de sortie

⚙️ Fonctionnement interne

Ton pipex crée un pipe et utilise fork() pour créer deux processus :
processus enfant → exécute cmd1
processus parent → exécute cmd2
Les deux communiquent via le pipe.

🧒 Processus enfant (cmd1)

dup2(data->infile, 0);    // stdin ← infile
dup2(data->fd[1], 1);     // stdout → pipe(write)
close(data->fd[0]);       // inutile ici
execve(data->cmd_path, data->cmd, envp);
➡️ Concrètement :

cmd1 lit depuis infile (comme si on faisait < infile)

cmd1 écrit dans le pipe (côté écriture)

👉 Résultat :
cmd1 < infile |


👨‍🦳 Processus parent (cmd2)

dup2(data->outfile, 1);   // stdout → outfile
dup2(data->fd[0], 0);     // stdin ← pipe(read)
close(data->fd[1]);       // inutile ici
execve(data->cmd_path2, data->cmd2, envp);

➡️ Concrètement :

cmd2 lit depuis le pipe (ce que cmd1 a écrit)

cmd2 écrit dans outfile (comme si on faisait > outfile)

👉 Résultat :
| cmd2 > outfile

🖼️ Vision d’ensemble

         infile
           │
           ▼
   [ Processus enfant : cmd1 ]
      stdin ← infile
      stdout → pipe(write)
           │
           ▼
   [ Processus parent : cmd2 ]
      stdin ← pipe(read)
      stdout → outfile
           │
           ▼
         outfile
🚀 Conclusion

Grâce à dup2, tu rediriges correctement les entrées/sorties avant execve.
Ensuite execve remplace le code du processus par la commande à exécuter.

👉 Résultat final identique à :
< infile cmd1 | cmd2 > outfile
