
EXENAME=cbcp

macos:
		clang++ -framework Foundation -framework AppKit -o $(EXENAME) main.cpp macos_platform.mm

# doesn't work yet
win:
		clang++ -o $(EXENAME) main.cpp win_platform.cpp

linux:
		clang++ -o $(EXENAME) main.cpp linux_platform.cpp

