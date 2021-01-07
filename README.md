# vplayer

A simple music player written in C++ and SQL. The project is divided in three modules: the core player module, the database module, and the user interface module. 
- The core module is responsible of the low level audio IO logic, from reading the PCM audio data from an input object, to sending that PCM data to the output sound card driver.
- The database module is responsible for setting a system of persistent storage of the audio library, it is currently written using an SQLite database.
- The ui module presents the system in a suitable manner for the user to interact with the system, currently being written using the GTK+ library for C++, gtkmm4.
(Work still in progress.)
