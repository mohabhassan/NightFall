gcc -c -rdynamic -fpic -o ./bin/misc.o ./src/misc.c 
gcc -c -rdynamic -fpic -o ./bin/gamex86.o ./src/gamex86.c 
gcc -shared -rdynamic -o ./release/fgameded.so ./bin/misc.o ./bin/gamex86.o
chmod -x ./release/fgameded.so
cp ./release/fgameded.so /home/mohaa/wmss/wmss_server1/



