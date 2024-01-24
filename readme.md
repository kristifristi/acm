de zijkantkennis vertegenwoordigt hoe parallel de acm and de wand rijdt
linker bochten draaien de logica van rechtdoorgaan en voor een rand merken om

de volgorde van include is belangrijk wegens het gebruik van globals (sorry! maar ik heb geen andere designpatronen om info tussen routines te delen)

de code is opgedeeld in twee routines. De een is een webserver en de andere het stuurprogramma

de webserver stuurt data over de sensorlezingen naar clients en reageert op een paar verschillende requests
"/START" zorgt ervoor dat de acm gaat rijden
"/STOP" stopt de acm
"/RESET" zet de bochtenteller weer op 0
"/SET/<getal>" zet de bochtenteller op een specifiek getal

het stuurprogramma houdt bij welke bochten die gemaakt heeft en bepaalt aan de hand daarvan of die links of recths moet bewegen
test.h is een document met functies om de de hardawareverbindingen te controlleren

