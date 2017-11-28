g++ -c /var/www/html/led/cpp/text.cpp
g++ -c /var/www/html/led/cpp/bild.cpp
g++ -c /var/www/html/led/cpp/main.cpp
g++ -c /var/www/html/led/cpp/readBMP.cpp
g++ -c /var/www/html/led/cpp/anzeigeWeb.cpp
g++ -o /var/www/html/led/cpp/main /var/www/html/led/cpp/text.o /var/www/html/led/cpp/bild.o /var/www/html/led/cpp/main.o /var/www/html/led/cpp/readBMP.o /var/www/html/led/cpp/anzeigeWeb.o -lwiringPi
