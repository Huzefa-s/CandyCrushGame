CANDY CRUSH GAME
#
A simple Candy Crush Game made using Cpp. Made the game implementing OOP knowlegde and using SFML.
#
To play you need to install sfml correctly. This is How my folder looked, to play simply run this command on your terminal
<br/>
<br/> g++ -g main.cpp Game.cpp Board.cpp Candy.cpp  -I sfml-2.5.1/sfml-2.5.1/include -L sfml-2.5.1/sfml-2.5.1/lib -o CandyCrush.exe -lsfml-graphics -lsfml-window -lsfml-system
<br/>
<br/> then wirte this command
<br/> ./CandyCrush.exe
#
<br/> CandyCrush/
<br/>├── main.cpp
<br/>├── Game.cpp
<br/>├── Board.cpp
<br/>├── Candy.cpp
<br/>├── Game.h
<br/>├── Board.h
<br/>├── Candy.h
<br/>├── SFML DLL files
<br/>├── font/
<br/> │   ├── font files
<br/>├── image/
<br/> │   ├── image files
<br/>├── SFML-2.5.1/
<br/> │   ├── SFML-2.5.1/
<br/> │       ├── include/
<br/> │       ├── lib/
