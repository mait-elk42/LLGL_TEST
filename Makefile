all:
	c++ TestWindow.cpp -L lib -lLLGL -lLLGL_Null -lLLGL_OpenGL -lLLGL_Metal -Xlinker -framework -Xlinker OpenGL -Xlinker -framework -Xlinker Cocoa -framework CoreVideo -Xlinker -framework -Xlinker metal -Xlinker -framework -Xlinker metalkit -I include -std=c++17 -o Test_Window.app/Contents/MacOS/Test_Window