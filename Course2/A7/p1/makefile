all: main.o admin.o album.o api.o artist.o basics.o browser.o editor.o exceptions.o gerdab.o music_container.o music_lib.o music.o player.o playlist.o queue.o rate.o register.o user.o gerdab_player.o
	g++ -l SDL2_mixer main.o admin.o album.o api.o artist.o basics.o browser.o editor.o exceptions.o gerdab.o music_container.o music_lib.o music.o player.o playlist.o queue.o rate.o register.o user.o gerdab_player.o -o run.out && ./run.out
main.o: main.cpp api.h
	g++ -c main.cpp
admin.h:user.h
admin.o:admin.cpp admin.h
	g++ -c admin.cpp
album.h:music.h music_container.h basics.h rate.h exceptions.h
album.o:album.cpp album.h artist.h user.h
	g++ -c album.cpp
api.o:api.cpp api.h
	g++ -c api.cpp
artist.h:user.h basics.h
artist.o:artist.cpp artist.h
	g++ -c artist.cpp
basics.o:basics.cpp basics.h
	g++ -c basics.cpp
browser.h:music_lib.h user.h artist.h basics.h playlist.h
browser.o:browser.cpp browser.h exceptions.h
	g++ -c browser.cpp
editor.h:user.h
editor.o:editor.cpp editor.h
	g++ -c editor.cpp
exceptions.o:exceptions.cpp exceptions.h
	g++ -c exceptions.cpp
gerdab.h:basics.h browser.h register.h player.h
gerdag.o:gerdab.cpp gerdab.h exceptions.h
	g++ -c gerdab.cpp
music.h:rate.h
music.o:music.cpp music.h album.h artist.h user.h exceptions.h
	g++ -c music.cpp
music_container.h:music.h basics.h
music_container.o:music_container.cpp music_container.h
	g++ -c music_container.cpp
music_lib.h:music.h album.h basics.h
music_lib.o:music_lib.cpp music_lib.h artist.h user.h exceptions.h music_lib.h
	g++ -c music_lib.cpp
player.h:queue.h gerdabPlayer.hpp
player.o:player.cpp player.h
	g++ -c player.cpp
playlist.h:music_container.h basics.h
playlist.o:playlist.cpp playlist.h album.h exceptions.h
	g++ -c playlist.cpp
queue.h:music_container.h
queue.o:queue.cpp queue.h
	g++ -c queue.cpp
rate.h:user.h
rate.o:rate.cpp rate.h
	g++ -c rate.cpp
register.h:user.h artist.h editor.h admin.h basics.h
register.o:register.cpp register.h exceptions.h
	g++ -c register.cpp
user.h:basics.h album.h music.h queue.h playlist.h
user.o:user.cpp user.h exceptions.h
	g++ -c user.cpp
gerdabPlayer.hpp: sdlHeaders.hpp exceptions.h
gerdab_player.o: gerdabPlayer.cpp gerdabPlayer.hpp
	g++ -c -l SDL2_mixer gerdabPlayer.cpp -o gerdab_player.o
clean:
	rm *.o


