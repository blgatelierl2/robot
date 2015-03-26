Documentation utilisateur du robot
=

La documentation **technique** a migré vers le **[wiki](https://github.com/blgatelierl2/robot/wiki)**.

# Réseau

Un routeur wifi est configuré pour gérer un réseau local de SSID `robot` et d'adresse `192.168.42.0/24` avec DHCP. Les robots sont identifiés par adresse MAC et récupèrent des IP fixes `192.168.42.10x` (`x` entre 0 et 9). Leurs hostnames sont `robotX` (`X` entre 0 et 9).

Pour le bon fonctionnement avec Erlang, il est indispensable d'ajouter avant tout chose les hôtes suivants à `/etc/hosts` :
```
192.168.42.100  robot0
192.168.42.101  robot1
192.168.42.102  robot2
192.168.42.103  robot3
192.168.42.104  robot4
192.168.42.105  robot5
192.168.42.106  robot6
192.168.42.107  robot7
192.168.42.108  robot8
192.168.42.109  robot9
```

# Librairie Erlang

La librairie Erlang est dans le fichier `erlib/robocom.erl`. Les fonctions utiles sont commentées.

Il y a plusieurs façons d'utiliser la librairie, la manière la plus simple est illustrée en premier.

## Contrôle distant du robot

Allumer le robot (ici on prendra `robot0` comme exemple) et s'y connecter via `ssh` :
```
$ ssh ubuntu@robot0
```
Le mot de passe est `ubuntu`.

Lancer le script `erlig/start_robot` sur le robot. Un serveur se lance. Sauf problème technique nécessitant de relancer le serveur, toutes les manipulations se font à partir de maintenant directement sur votre machine.

Sur votre machine, lancer Erlang avec `erlib/start_control` ou en utilisant la syntaxe suivante :
```
erl -sname control -setcookie ROBOT`
```
Le nom `control` n'a aucune importance, le changer n'aura pas d'incidence. En revanche, le cookie doit être `ROBOT` !

Vérifier la communication avec le serveur :
```
> robocom:ping_robot(0).
pong
```
Si la réponse est `pang`, il y a un problème (vérifier le cookie).

Récupérer le PID du serveur du robot :
```
> R = robocom:get_robot(0).
```

Contrôler le robot (cf fonctions de contrôle de la lib) :
```
> robocom:led(R,1).
> robocom:servo(R,45).
...
```

On terminera tout programme de contrôle d'un robot par un appel à `reset_robot` :
```
> robocom:reset_robot(0).
```


### Communication

Si plusieurs robots sont contrôlés par une même machine (au sein d'un même noeud Erlang), la communication entre robots peut être simulée par la communication locale entre leurs contrôleurs.

Si en revanche, chaque robot est contrôlé par des machines distinctes, des mécanismes de la lib permettent de les identifier simplement afin de communiquer.

Chaque contrôleur s'enregistre auprès de son robot : 
```
> robocom:enregistrement(0).
```

Pour obtenir le PID du contrôleur (distant, supposé enregistré auprès de son robot sinon la réponse sera `none`) d'un autre robot (ici `robot1`) :
```
> Control1 = robocom:get_controleur(1).
```

Vous pouvez maintenant écrire à `Control1` sans difficulté (`Control1 ! coucou`).
