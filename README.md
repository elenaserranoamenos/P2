PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Añada la etiqueta `origin` a su copia del repositorio. Esto es útil para facilitar los *push* y
		*pull* al repositorio original:
		```.sh
		git remote add origin dirección-del-fork-de-la-práctica
		```
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de
		seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

<img width="1440" alt="Captura de Pantalla 2021-11-12 a les 15 15 10" src="https://user-images.githubusercontent.com/92745258/141492839-3e7ba158-c12f-4fa8-8e2f-4c6cd925147d.png">

Hemos etiquetado manualmente los segmentos de voz (V) y silencio (S) en la transcripción .lab. Seguidamente se puede ver la tasa de cruces por cero, el contorno de potencia y por último la señal con el eje temporal.

El audio contiene el siguiente mensaje: "Maria Piñol, Elena Serrano. Estamos en el lab de PAV".

- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.
	  
	  Si observamos la gráfica del contorno de potencia vemos que hay un incremento de hasta 70 dB respecto al silencio inicial.

	* Duración mínima razonable de los segmentos de voz y silencio.

	  Duración mínima segmentos de voz: 1.5 s
	
	  Duración mínima segmentos de silencio: 0.8 s

	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?

	  1) Detectar consonantes sordas -> tasa alta.
  	  2) Detectar un tramo de voz -> tasa baja.
  	  3) Tramo de silencio (con ruido de fondo) -> tasa media.


### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal tan
  exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.
  
  Se puede ver el código definitivo en la carpeta src.

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 
  
  <img width="1440" alt="comparació vad - lab" src="https://user-images.githubusercontent.com/92745258/141493246-1efa321c-e973-4388-b695-392209193e73.png">

   Primero observamos el etiquetado manual (.lab) y seguidamente el etiquetado de la detección automática (.vad).

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

![image](https://user-images.githubusercontent.com/92745258/141536683-c7923607-18ee-4bef-be93-1974c60be755.png)

  El programa tiene mucha precisión, ya que los segmentos de voz y silencio de la detección automática son prácticamente iguales a los segmentos del etiquetado manual. Por ejemplo, los sonidos sordos como la letra "s" ("Serrano" "eStamoS") el programa la detecta correctamente ya que el tramo lo reconoce como voz (V). Esto se debe a los niveles de umbrales k0, k1 y k2 que hemos considerado para realizar el detector de voz.
  
  En la captura anterior se puede ver que en nuestro caso, con nuestro fichero de audio, la tasa de recall que obtenemos es de 98.87% para la voz (V) y de 99.50% para el silencio (S), que la tasa de presión que obtenemos es de 99.64% para la voz (V) y de 98.48% para el silencio (S) y que el F_score es 99.03% para la voz (V) y de 98.82% para el silencio (S), es decir, en nuestro caso las diferencias son imperceptibles.
  

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).
  
  ![image](https://user-images.githubusercontent.com/92745258/141536465-169a38e9-7d27-402e-a7d4-8f9218fdbd47.png)
  
	En caso de todos los audios, la tasa de recall que obtenemos es de 87.69% para la voz (V) y de 91.75% para el silencio (S), que la tasa de precisión que obtenemos es de 93.74% para la voz (V) y de 85.53% para el silencio (S) y que el F_score es 88.84% para la voz (V) y de 85.53% para el silencio (S). Si observamos un poco por encima todos los archivos de audio que hemos intentado detectar se observa que un gran número de archivos se encuentran entre el 85% y el 99%, el problema es que hay algunos que se encuentran más bajos y es por eso que la media baja. Creemos que los valores obtenidos son sufucientes para determinar que tenemos un sistema bastante correcto, aunque siempre se podría mejorar.
 

### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).
  
  Para crear la señal de audio sin ruido hemos modificado el código y hemos utilizado el siguiente comando:
  
  ![image](https://user-images.githubusercontent.com/92745258/141565754-7d278616-78d8-4dee-a870-71ceb0c66d5a.png)

  Así pues, en la siguiente captura podemos ver una primera señal sin ruido seguida del audio original.
  
  ![image](https://user-images.githubusercontent.com/92745258/141564601-46db8db6-5833-4aeb-ace7-b1c21bdf4b6a.png)

  Como podemos ver, en la primera señal, el poco ruido que hay al principio se pone a cero. El resto de segmentos de silencio no se aprecia ruido, por lo tanto, no vemos ninguna diferencia. 
  
  Como nuestra señal tiene muy poco ruido, hemos cogido un audio de la base de datos para que se vea mejor la cancelación de ruido.
  En la siguiente captura se puede apreciar como la primera gráfica es la señal con ruido y debajo, la señal con el ruido cancelado. Los cambios son muy notables, por lo tanto, podemos decir que nuestro programa funciona correctamente.
  
  ![image](https://user-images.githubusercontent.com/92745258/141615101-53e7887f-11d2-407b-aa53-fb13548227fe.png)

  
#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.

![image](https://user-images.githubusercontent.com/92745258/141539922-354b8db0-5809-4180-adb9-3ab73bb76aad.png)


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.


### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.
