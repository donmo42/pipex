# 🌀 Pipex

## 🔎 Description
Mon programme `pipex` reproduit le comportement suivant du shell :  

< infile cmd1 | cmd2 > outfile

Il prend 4 arguments :  
- argv[1] = infile → fichier d’entrée  
- argv[2] = cmd1 → première commande à exécuter  
- argv[3] = cmd2 → deuxième commande à exécuter  
- argv[4] = outfile → fichier de sortie  

## ⚙️ Fonctionnement
Pipex fonctionne en créant un **pipe** et en utilisant **fork()** pour gérer deux processus qui communiquent entre eux. L’idée est simple : lire depuis un fichier d’entrée, passer le résultat d’une commande à une autre, puis écrire dans un fichier de sortie.

Voici le déroulement :

1. Le flux d’entrée standard est redirigé vers `infile`, et la sortie standard vers le côté écriture du pipe.  
2. La première commande (`cmd1`) s’exécute avec `execve`. Elle lit dans `infile` et écrit dans le pipe.  
3. Le flux de sortie du pipe devient l’entrée standard pour la deuxième commande (`cmd2`), dont la sortie standard est redirigée vers `outfile`.  
4. Ensuite, `cmd2` s’exécute avec `execve` et écrit le résultat final dans `outfile`.

En code, tout cela se traduit par :

```c
dup2(data->infile, 0);    // stdin ← infile
dup2(data->fd[1], 1);     // stdout → pipe(write)
close(data->fd[0]);       // côté lecture du pipe inutile
execve(data->cmd_path, data->cmd, envp);

dup2(data->outfile, 1);   // stdout → outfile
dup2(data->fd[0], 0);     // stdin ← pipe(read)
close(data->fd[1]);       // côté écriture du pipe inutile
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
