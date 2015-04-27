-module(robocom).
-export([start/0,spawn_serveur/0,start_serveur/0,robot_node/1,ping_robot/1,get_robot/1,reset_robot/1,enregistrement/1,get_controleur/1,moteurs/3,vitesse/3,led/2,servo/2,ultrason/1,odometres/1,infrarouge/1,reset/1]).

-define(DEVICE,"/dev/ttyACM0").
-define(SERIALSPEED,9600).
-define(TIMEOUT,5000).
-define(RECODELAY,1000).


%%% FONCTIONS DU SERVEUR ROBOT
%%% INUTILES AUX ETUDIANTS
start() ->
    register(accueil,self()),
    Serv = spawn_serveur(),
    io:format("Serveur en place.~n"),
    accueil(Serv).

accueil(Serv) -> accueil(Serv,none).
accueil(Serv,Cont) ->
    receive
	{get_serveur,Client} ->
	    Client ! {serveur,node(),Serv},
	    accueil(Serv,Cont);
	{register_control,Client} ->
	    Client ! {registered,node()},
	    accueil(Serv,Client);
	{ask_control,Client} ->
	    Client ! {controleur,node(),Cont},
	    accueil(Serv,Cont);
	{reset,_} ->
	    reset(Serv),
	    accueil(Serv,Cont);
	{disconnected,Serv} when Cont==none -> accueil(Serv,Cont);
	{disconnected,Serv} ->
	    Cont ! {notif_deconnexion,node()},
	    accueil(Serv,Cont)
    end.

spawn_serveur() -> spawn(?MODULE,start_serveur,[]).

start_serveur() ->
    process_flag(trap_exit,true),
    SerialPort = serial:start([{speed,?SERIALSPEED},{open,?DEVICE}]),
    serveur(SerialPort).

serveur(SerialPort) ->
    receive
	{mot,PL,PR} ->
	    SerialPort ! {send, <<"m",PL:16/integer-signed-little,PR:16/integer-signed-little>>},
	    serveur(SerialPort);
	{vit,VL,VR} ->
	    SerialPort ! {send, <<"v",VL:16/integer-signed-little,VR:16/integer-signed-little>>},
	    serveur(SerialPort);
	{led,B} ->
	    SerialPort ! {send, <<"l",B:8,0:24>>},
	    serveur(SerialPort);
	{srv,A} ->
	    SerialPort ! {send, <<"s",A:8/integer-signed-little,0:24>>},
	    serveur(SerialPort);
	{ult,Pid} ->
	    SerialPort ! {send, <<"u",0:32>>},
	    receive
		{data, Bytes} ->
		    <<D:16/integer-signed-little>> = Bytes,
		    Pid ! {ult_res,self(),D},
		    serveur(SerialPort)
	    after ?TIMEOUT -> serveur(SerialPort)
	    end;
	{odo,Pid} ->
	    SerialPort ! {send, <<"o",0:32>>},
	    receive
		{data, Bytes} ->
		    <<OL:32/integer-signed-little,OR:32/integer-signed-little>> = Bytes,
		    Pid ! {odo_res,self(),OL,OR},
		    serveur(SerialPort)
	    after ?TIMEOUT -> serveur(SerialPort)
	    end;
	{ird,Pid} ->
	    SerialPort ! {send, <<"i",0:32>>},
	    receive
		{data, Bytes} ->
		    <<_:5,IR:1,IC:1,IL:1>> = Bytes,
		    Pid ! {ird_res,self(),IL,IC,IR},
		    serveur(SerialPort)
	    after ?TIMEOUT -> serveur(SerialPort)
	    end;
	{'EXIT',SerialPort,_} ->
	    io:format("ERREUR : Deconnexion serial !~n--> Tentative de reconnexion (dans ~wms).~n",[?RECODELAY]),
	    accueil ! {disconnected,self()},
	    timer:sleep(?RECODELAY),
	    start_serveur()
    end.


%%% FONCTIONS D'INTERFACE
%%% UTILES AUX ETUDIANTS !

robot_node(N) -> list_to_atom(lists:concat(["robonode@robot",N])).


%% VERIFICATIONS

% Ping un robot : repond "pong" si up, "pang" si down
ping_robot(N) -> net_adm:ping(robot_node(N)).


%% DIALOGUE AVEC L'ACCUEIL DU ROBOT
% Obtenir le PID du serveur d'un robot
get_robot(N) ->
    Node = robot_node(N),
    {accueil,Node} ! {get_serveur,self()},
    receive
	{serveur,Node,Serveur} -> Serveur
    after ?TIMEOUT -> timeout
    end.

% S'enregistrer comme controleur aupres d'un robot
enregistrement(N) ->
    Node = robot_node(N),
    {accueil,Node} ! {register_control,self()},
    receive
	{registered,Node} -> ok
    after ?TIMEOUT -> timeout
    end.

% Recuperer le PID du controleur d'un robot (pour pouvoir communiquer avec lui)
get_controleur(N) ->
    Node = robot_node(N),
    {accueil,Node} ! {ask_control,self()},
    receive
	{controleur,Node,Cont} -> Cont
    after ?TIMEOUT -> timeout
    end.

reset_robot(N) ->
    {accueil,robot_node(N)} ! {reset,self()},
    ok.


%% CONTROLE DU ROBOT
%% L'argument Serv est le PID du serveur du robot

% Controler les moteurs (Pl/Pr entre -255 et 255)
moteurs(Serv,Pl,Pr) ->
    Serv ! {mot,Pl,Pr},
    ok.

vitesse(Serv,Vl,Vr) ->
    Serv ! {vit,Vl,Vr},
    ok.

% Allumer/eteindre la LED du robot (B = 0 ou 1)
led(Serv,B) ->
    Serv ! {led,B},
    ok.

% Controle du servomoteur (A l'angle entre 0 et 180)
servo(Serv,A) -> 
    Serv ! {srv,A},
    ok.

% Distance mesuree par le capteur ultrason (en cm)
ultrason(Serv) ->
    Serv ! {ult,self()},
    receive
	{ult_res,Serv,D} -> D
    after ?TIMEOUT -> timeout
    end.

% Valeurs des roues codeuses (1 unite = 1/10 de tour de roue)
odometres(Serv) ->
    Serv ! {odo,self()},
    receive
	{odo_res,Serv,OL,OR} -> {OL,OR}
    after ?TIMEOUT -> timeout
    end.

% Etat des capteurs infrarouge (1 = obstacle, 0 sinon)
infrarouge(Serv) ->
    Serv ! {ird,self()},
    receive
	{ird_res,Serv,IL,IC,IR} -> {IL,IC,IR}
    after ?TIMEOUT -> timeout
    end.

reset(Serv) ->
    vitesse(Serv,0,0),
    servo(Serv,90),
    led(Serv,0),
    ok.
