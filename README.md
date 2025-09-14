# pipex

argv[1] = infile → fichier d’entrée

argv[2] = cmd1 → première commande à exécuter

argv[3] = cmd2 → deuxième commande à exécuter

argv[4] = outfile → fichier de sortie

Ton pipex crée deux processus (grâce à fork) :

le processus enfant → exécute cmd1 (avec execve)

le processus parent → exécute cmd2 (avec execve)

et ils communiquent à travers le pipe.

1. Dans le processus enfant (cmd1)

Code :
dup2(data->infile, 0);    // stdin = infile
dup2(data->fd[1], 1);     // stdout = pipe (côté écriture)
close(data->fd[0]);       // inutile ici
execve(data->cmd_path, data->cmd, envp);


Ce que ça fait :

Quand cmd1 lit sur stdin, il lit en réalité dans infile.

Quand cmd1 écrit sur stdout, il écrit en réalité dans le pipe (côté écriture).

Le côté lecture du pipe est fermé (inutile ici).

Puis execve transforme le processus enfant en programme cmd1.

👉 Concrètement : cmd1 < infile | (il envoie ses résultats dans le pipe).

2. Dans le processus parent (cmd2)

Code :
dup2(data->outfile, 1);   // stdout = outfile
dup2(data->fd[0], 0);     // stdin = pipe (côté lecture)
close(data->fd[1]);       // inutile ici
execve(data->cmd_path2, data->cmd2, envp);
3. Vision d’ensemble

Ce que ça fait :

Quand cmd2 lit sur stdin, il lit en réalité dans le pipe (côté lecture).

Quand cmd2 écrit sur stdout, il écrit en réalité dans outfile.

Le côté écriture du pipe est fermé (inutile ici).

Puis execve transforme le processus parent en programme cmd2.

👉 Concrètement : | cmd2 > outfile.

3. Vision d’ensemble

         infile
          │
          ▼
   [ process enfant : cmd1 ]
      stdin ← infile
      stdout → pipe(write)
          │
          ▼
   [ process parent : cmd2 ]
      stdin ← pipe(read)
      stdout → outfile
          │
          ▼
        outfile
   \
Donc au final, c’est exactement comme si ton shell avait exécuté :
< infile cmd1 | cmd2 > outfile
⚡ La clé : execve ne fait que remplacer le code du processus par la commande.
Mais avant ça, tu as préparé l’environnement avec dup2 → c’est ça qui fait que cmd1 et cmd2 travaillent sur les bons fichiers/pipes.
