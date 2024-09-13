# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 11:18:19 by mait-elk          #+#    #+#              #
#    Updated: 2024/09/13 18:57:38 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER= c++ -std=c++17
FRAMEWORKS_FOR_MACOS= -framework OpenGL -framework Cocoa -framework CoreVideo -framework metal -framework metalkit
LLGL_STATIC_LIBS= -L lib -lLLGL -lLLGL_Null -lLLGL_OpenGL -lLLGL_Metal
SRCS= TestWindow.cpp
INC=-I include

debug:
	$(COMPILER) $(SRCS) $(INC) -o Test_Window $(LLGL_STATIC_LIBS) $(FRAMEWORKS_FOR_MACOS)
	./Test_Window

release:
	$(COMPILER) $(SRCS) $(INC) -o Test_Window.app/Contents/MacOS/Test_Window $(LLGL_STATIC_LIBS) $(FRAMEWORKS_FOR_MACOS)