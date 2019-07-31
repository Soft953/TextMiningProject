# TextMiningProject

1.	Décrivez les choix de design de votre programme
 
 Nous avons tout d'abord implémenté un Trie afin de parser le fichier de mot.
 Ce Trie est composé de map pour chaque noeud, et chaque map contient les liens vers les fils.
 Exemple : map['c'] = Node()

 Nous sauvegardons également la fréquence si c'est la fin d'un mot, sinon la valeur par défaut est zéro.

 On utilise ensuite ce Trie pour construire un Patricia Trie.

 Ce Patricia Trie utilise un vecteur de charactère pour stocker les lettres, et un index dans chaque noeuds afin d'y accéder.


2.	Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)

 Test end to end


3.	Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?
    
 Oui dans le cas des acronymes ou des abréviations il peut s'avérer que la correction par distance ne fonctionne pas.


4.	Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?

 Nous avons implémenté un Trie et un Patricia Trie. Le Trie est pour nous une étape indispensable pour fabriquer le Patricia Trie,
 qui est certainement une des structures de données les mieux adaptés à ce projet (pratique et rapide (parcours, espace)).

5.	Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats

 Pour un mot inférieur à 5 lettres nous pourrions prendre les mots à une distance de 1, puis une distance de 2 pour les mots plus grands.


6.	Comment comptez vous améliorer les performances de votre programme

 Dans un premier temps il faudrait optimiser la construction du Trie puis du Patricia Trie. Ensuite une implémentation optimale des jugy array permettrai  une recherche plus rapide et moins couteuse.


7.	Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?

    Il manque la prise en compte de la phonétique des mots et la prise en compte du contexte pour qu'il soit à l'état de l'art.
