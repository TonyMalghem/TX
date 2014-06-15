TX - Réalisation de démonstrateurs pédagogiques pour les algorithmes RC4 et RSA
===============================================================================

La documentation utilisateur est disponible dans le document "manuel_utilisateur.pdf".

La documentation programmeur est disponible dans l'archive "doxygen_tx_demonstrateurs_pedagogiques.zip".
Cette documentation a été réalisée via Doxygen, sous forme de fichier HTML.
Afin de l'ouvrir, il suffit de lancer un navigateur et ouvrir le fichier index.html.

L'application est fournie pour être portable sur Linux, Windows et MacOS X. Les différents portages sont disponibles dans 3 archives séparées, nommées respectivement "TX_portage_linux.tar.gz", "TX_portage_windows.tar.gz" et "TX_portage_macOS.tar.gz".
Ces archives contiennent l'executable, les différentes librairies nécessaires au bon fonctionnement de l'application, ainsi qu'une image nommée "rc4_keystream.jpg" permettant de réaliser la démonstration étape par étape du chiffrement RC4. Il est impératif que cette image et les différentes libraires (fichiers .dll pour le portage windows) soient placées dans le même répertoire que l'exécutable pour le bon fonctionnement de l'application.

Compilation:
La méthode la plus directe et la plus simple pour recompiler le projet est d'utiliser l'IDE QtCreator (http://qt-project.org/wiki/category:tools::qtcreator). Pour ce faire, choisir l'option Fichier -> Ouvrir un fichier ou un projet... puis sélectionner le fichier TX.pro se trouvant dans l'archive des codes fournie. Il est nécessaire que les fichiers sources et en-tête (fichiers .cpp et .h) se trouvent dans le même dossier que le fichier TX.pro.
Une autre manière de réaliser la compilation est de générer un Makefile en console avec qmake, en utilisant la commande : 
$ qmake-qt4 -makefile -o Makefile TX.pro
Une fois le Makefile généré, il est possible de compiler le projet en utilisant la commande make.
qmake est téléchargeable à l'adresse suivante : http://qt-project.org/downloads, dans la section Qt Library (en bas du site, dans la section Qt 4.8)
