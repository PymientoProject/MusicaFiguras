# MusicaFiguras
Repositorio que aloja todo el código del proyecto "MúsicaFiguras" que es parte de la PyConES 2016. El experimento consiste en una mesa de mezclas que se controla por nfc. Cada chip nfc tiene asignado una melodía, cuando la pones encima de algún lector, este la lee y pone la canción que tiene asignada.

El proyecto consta de un arduino nano, 5 módulos nfc, una raspberry pi. Los módulos nfc se comunican con el arduino por medio de SPI, el arduino le pasa los datos a las raspberry pi por serial, y la raspi pone los audios.

##Instalación
Los componentes del proyecto son:
| Componente        | Número           |
| ------------- |:-------------:|
| Raspberry PI  | x1 |
| Módulos nfc      | x5      |
| Arduino nano  | x1     |
| Tags | x"Los que queramos" |
| PCB | x1 |
| Altavoces | x1 |

Por la parte de la electrónica, el arduino se comunica con los módulos por medio de la librería [rfid](https://github.com/miguelbalboa/rfid). La instalación está en ese repositorio. Luego tenemos que conectar los módulos tal y como se indica en la librería. Metemos el código "codiog de arduino" y conectamos los pines del RX, TX, 5v y GND (del arduino) a los pines de TX, RX, 5v y GND de la (raspberry pi).

En la raspberry pi tenemos que instalar las dependencias. Primero tenemos que instalr VLC: `apt-get install vlc`
Luego instalar el binding de VLC en python, que está [aquí](https://github.com/oaubert/python-vlc).
Instalamos la comunicación serial de las raspberry pi `apt-get install python-serial`

##USO 
Para utilizarlo, tienes que conectar todo como pone anteriormente. Para empezar el programa ejecuta `python Main.py`

##Licencia
Este proyecto está licenciado bajo GPL v3



