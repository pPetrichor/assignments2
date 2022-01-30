woman(mia).
woman(jody).
woman(yolanda).
/*play***/
playsAirGuitar(jody).
happy(yolanda).
listens2music(mia,jody,yolanda).
listens2music(mia,x,y).
listens2music(yolanda):- happy(yolanda).
playsAirGuitar(mia):- listens2music(mia,x,a).
playsAirGuitar(yolanda):- listens2music(yolanda,y,b).