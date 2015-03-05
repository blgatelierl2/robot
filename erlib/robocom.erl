-module(robocom).
-export([init/0,start/0,moteurs/3,led/2,servo/2,ultrason/1,odometres/1]).

-define(DEVICE,"/dev/ttyACM0").

init() -> spawn(?MODULE,start,[]).

start() -> start(9600).
start(Speed) ->
    SerialPort = serial:start([{speed,Speed},{open,?DEVICE}]),
    serveur(SerialPort).

serveur(SerialPort) ->
    receive
	{mot,PL,PR} ->
	    SerialPort ! {send, <<"m",PL:16/integer-signed-little,PR:16/integer-signed-little>>},
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
		    Pid ! {ult_res,D},
		    serveur(SerialPort)
	    end;
	{odo,Pid} ->
	    SerialPort ! {send, <<"o",0:32>>},
	    receive
		{data, Bytes} ->
		    <<OL:32/integer-signed-little,OR:32/integer-signed-little>> = Bytes,
		    Pid ! {odo_res,OL,OR},
		    serveur(SerialPort)
	    end
    end.

moteurs(Serv,Pl,Pr) ->
    Serv ! {mot,Pl,Pr},
    ok.

led(Serv,B) ->
    Serv ! {led,B},
    ok.

servo(Serv,A) -> 
    Serv ! {srv,A},
    ok.

ultrason(Serv) ->
    Serv ! {ult,self()},
    receive
	{ult_res,D} -> D
    end.

odometres(Serv) ->
    Serv ! {odo,self()},
    receive
	{odo_res,OL,OR} -> {OL,OR}
    end.
