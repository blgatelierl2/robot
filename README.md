Documentation utilisateur du robot
=

La documentation **technique** a migré vers le **[wiki](https://github.com/blgatelierl2/robot/wiki)**.

# Réseau

Un routeur wifi est configuré pour gérer un réseau local de SSID `robot` et d'adresse `192.168.42.0/24` avec DHCP. Les robots sont identifiés par adresse MAC et récupèrent des IP fixes `192.168.42.10x` (`x` entre 0 et 9). Leurs nom d'hôtes sont `robotX` (`X` entre 0 et 9).

Pour le bon fonctionnement avec Erlang, il est indispensable d'ajouter, avant toute chose, les hôtes suivants à `/etc/hosts` :
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

## 1. Contrôle distant du robot

Allumer le robot (ici on prendra `robot0` comme exemple) et s'y connecter via `ssh` :
```
$ ssh ubuntu@robot0
```
Le mot de passe est `ubuntu`.

Lancer le script `erlig/start_robot` sur le robot. Un serveur se lance. Sauf problème technique nécessitant de relancer le serveur, toutes les manipulations se font à partir de maintenant directement sur votre machine.

Sur votre machine, lancer Erlang en utilisant la syntaxe suivante :
```
erl -sname control -setcookie ROBOT
```
Le nom `control` n'a aucune importance, le changer n'aura pas d'incidence. En revanche, le cookie doit être `ROBOT` !

Compiler `robocom` et Vérifier la communication avec le serveur :
```
> robocom:ping_robot(0).
pong
```
Si la réponse est `pang`, il y a un problème (vérifier le cookie).

Récupérer le PID du serveur de contrôle du robot :
```
> R = robocom:get_robot(0).
```

Contrôler le robot (cf fonctions de contrôle de la lib) :
```
> robocom:led(R,1).
> robocom:servo(R,45).
...
```

On terminera tout programme de contrôle d'un robot par un appel à `reset_robot/1` :
```
> robocom:reset_robot(0).
```


### Communication

Si plusieurs robots sont contrôlés par une même machine (au sein d'un même nœud Erlang), la communication entre robots peut être simulée par la communication locale entre leurs contrôleurs.

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

## 2. Contrôle local du robot (robot autonome)

Il n'est **pas recommandé** de suivre le contenu de cette section, sauf problème avec votre machine servant de contrôleur distant.

La librairie est conçue pour que le code écrit pour le contrôle distant (cf. section précédente) soit compatible avec tous les modes de contrôle : il fonctionnera aussi bien lorsque plusieurs controleurs sont répartis sur plusieurs machines distantes que lorsqu'ils sont tous hébergés sur la même machine distance ou qu'ils tournent tous directement localement sur le robot.

Cependant ces mécanismes ne sont pas tous utiles pour un contrôle local. Dans ce cas les choses peuvent être simplifiées. Tout ce passe ici directement sur le robot (typiquement via `ssh`).

Pour un contrôle purement local, plus besoin de lancer le script `robocom/start_robot`, on peut lancer directement le serveur de contrôle du robot localement :
```
R = robocom:spawn_robot().
```

On contrôle alors le robot avec les fonctions de contrôle en utilisant le PID `R`. Les fonctions de dialogue avec l'accueil du robot (cf. lib) ne sont pas disponible dans ce cas (le serveur d'accueil, inutile en local, n'est pas lancé).

On termine enfin tout programme par un appel à `reset/1` :
```
robocom:reset(R).
```

### Upload du code sur le robot (pour contrôle local)

Pour un contrôle local, il devient utile de pouvoir uploader son code sur le robot.

Pour ne pas polluer le robot, il est **déconseillé** d'uploader son code via `scp`.

En lieu et place on **recommande** de créer un nœud Erlang (en `ssh`) sur le robot :
```
ubuntu@robot0$ erl -sname robonode -setcookie ROBOT
```

Puis d'utiliser le code Erlang suivant (qui peut bien sûr être empaqueté dans une fonction Erlang) sur une machine distante pour envoyer le code à exécuter sur le robot (ici `robot0`) :
```
$ erl -sname program -setcookie ROBOT
> c(mon_module).
> {Mod, Bin, _} = code:get_object_code(mon_module).
> rpc:call(robocom:robot_node(0), erlang, load_module, [Mod, Bin]).
> spawn(robocom:robot_node(0), mon_module, ma_fonction, [arg1,arg2,...]).
```

Un processus exécutant `mon_module:ma_fonction(arg1,arg2,...)` sera alors créé sur le nœud Erlang du robot.

**NB.** L'appel à `robot_node(X)` fabrique simplement un atome `robonode@robotX`.