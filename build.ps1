windres resource.rc -O coff -o resource.o
g++ XiaoaiAgentInjector.cpp resource.o -o XiaoaiAgentInjector.exe -static -static-libgcc -static-libstdc++ -luser32 -mwindows