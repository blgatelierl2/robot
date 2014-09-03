Documentation du robot
=

Châssis Baron-4WD
-

[Wiki du châssis](http://www.dfrobot.com/wiki/index.php?title=NEW_A4WD_Mobile_Robot_with_encoder_%28SKU:ROB0025%29)

[Guide de montage PDF](http://www.dfrobot.com/image/data/ROB0025/ROB0025-Instruction%20Mannual%20V2.0.pdf)

**Attention**  Les 4 moteurs fournis ne sont pas pré-cablés, il faut préparer
  (couper, dénuder les extrémités) les fils fournis et les souder aux
  moteurs avant de les monter au châssis.

Le montage des roues codeuses (ou encodeurs, i.e. roue dentée
solidaire de la rotation du moteur et détecteur optique pour mesurer la
vitesse de rotation des roues du robot) est **à la fin** du guide de montage,
utiliser **directement** cette partie (car le montage est différent,
il faut en particulier utiliser des vis plus longues pour fixer les moteurs et
le détecteur) pour le montage des deux roues avant
ou arrière au choix.

Carte microcontrôleur Romeo V2
-

[Wiki de la carte Romeo V2](http://www.dfrobot.com/wiki/index.php/Romeo_V2-All_in_one_Controller_%28R3%29_%28SKU:DFR0225%29)

La carte se programme directement avec l'[interface pour Arduino](http://arduino.cc/en/Main/Software). Il
faut choisir le type de carte **Arduino Leonardo** dans l'interface pour transférer les
programmes vers la carte Romeo.

Capteurs infrarouge
-

[Wiki des capteurs infrarouge](http://www.dfrobot.com/wiki/index.php?title=Adjustable_Infrared_Sensor_Switch_%28SKU:SEN0019%29)

Les capteurs infrarouge ont une sortie binaire selon qu'un objet est dans le champ ou
non. Le capteur ne mesure pas la distance le séparant de l'objet. Une led est présente à l'arrière du capteur et s'allume
lorsqu'un obstacle est détecté. Le réglage de la distance de détection
(de 3 à 80 cm) se fait manuellement via la vis du potentiomètre au dos
du capteur. Ce réglage "en dur" est fixé avant utilisation, il ne peut être
modifié dynamiquement par le programme.

Capteur ultrason
-

[Wiki du capteur ultrason](http://www.dfrobot.com/wiki/index.php?title=URM37_V3.2_Ultrasonic_Sensor_%28SKU:SEN0001%29)

[Documentation de la librairie du capteur ultrason](http://milesburton.com/URM37_Ultrasonic_Distance_Measurement_Library)

Buzzer
-

[Wiki du buzzer](http://www.dfrobot.com/wiki/index.php?title=Digital_Buzzer_Module_%28SKU:_DFR0032%29)

Pour un exemple d'utilisation, brancher le buzzer sur la pin 8 de la
carte Romeo et transférer le code Arduino
Examples/02.Digital/toneMelody.

Module Bluetooth
-

[Wiki du module Bluetooth](http://www.dfrobot.com/wiki/index.php?title=DF-BluetoothV3_Bluetooth_module_%28SKU:TEL0026%29)

Il s'agit d'un module de communication série par Bluetooth standard et
très facile à utiliser. Il se
branche directement sur les ports Bluetooth de la carte Romeo.

Anneau de LED
-

[Wiki de l'anneau](http://www.dfrobot.com/wiki/index.php/Light_Disc_%28SKU:DFR0106%29)
