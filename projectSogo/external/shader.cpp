#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <QOpenGLFunctions_3_3_Core>

#include "shader.hpp"
#include "Logger.h"

GLuint LoadShaders( const char * vertex_file_path,const char * fragment_file_path){
 Logger::GetLoggerIntance()->LogInfo("loadshader start");

    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());
	// Create the shaders
    GLuint VertexShaderID = f->glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = f->glCreateShader(GL_FRAGMENT_SHADER);

    Logger::GetLoggerIntance()->LogInfo("created shaders");

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
        Logger::GetLoggerIntance()->LogError("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n");
		getchar();
		return 0;
	}

    Logger::GetLoggerIntance()->LogInfo("read in  vertexshaders");

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

    Logger::GetLoggerIntance()->LogInfo("read in  fragmentshader");

	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
    f->glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    f->glCompileShader(VertexShaderID);

	// Check Vertex Shader
    f->glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    f->glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        f->glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    f->glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    f->glCompileShader(FragmentShaderID);

	// Check Fragment Shader
    f->glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    f->glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        f->glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

Logger::GetLoggerIntance()->LogInfo("compiled shaders");

	// Link the program
	printf("Linking program\n");
    GLuint ProgramID = f->glCreateProgram();
    f->glAttachShader(ProgramID, VertexShaderID);
    f->glAttachShader(ProgramID, FragmentShaderID);
    f->glLinkProgram(ProgramID);

	// Check the program
    f->glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    f->glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        f->glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

    Logger::GetLoggerIntance()->LogInfo("linking done");

    f->glDeleteShader(VertexShaderID);
    f->glDeleteShader(FragmentShaderID);

    Logger::GetLoggerIntance()->LogInfo("loadshader ende");
	return ProgramID;
}


