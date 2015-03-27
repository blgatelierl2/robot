-module(demo).
-export([start/1]).

start(N) ->
    R = robocom:get_robot(N),
    tourne(R,robocom:infrarouge(R)).

init_avance(R) ->
    robocom:moteurs(R,100,100),
    avance(R).

avance(R) -> avance(R,{0,0,0}).
avance(R,{0,0,0}) ->
    timer:sleep(250),
    avance(R,robocom:infrarouge(R));
avance(R,X) -> init_tourne(R,X).

init_tourne(R,{0,_,1}) ->
    robocom:moteurs(R,-200,200),
    tourne(R);
init_tourne(R,_) ->
    robocom:moteurs(R,200,-200),
    tourne(R).

tourne(R) -> tourne(R,{0,1,0}).
tourne(R,{0,0,0}) -> init_avance(R);
tourne(R,_) ->
    timer:sleep(250),
    tourne(R,robocom:infrarouge(R)).
