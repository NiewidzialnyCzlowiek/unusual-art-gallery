/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include "ShaderProgram.h"

char* ShaderProgram::readFile(const char* fileName) {
	int filesize;
	FILE *plik;
	char* result;

	plik=fopen(fileName,"rb");
	fseek(plik,0,SEEK_END);
	filesize=ftell(plik);
	fseek(plik,0,SEEK_SET);
	result=new char[filesize+1];
	fread(result,1,filesize,plik);
	result[filesize]=0;
	fclose(plik);

	return result;
}

GLuint ShaderProgram::loadShader(GLenum shaderType, const char* fileName) {
	GLuint shader=glCreateShader(shaderType);
	const GLchar* shaderSource=readFile(fileName);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	delete []shaderSource;

	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&infologLength);
	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		delete []infoLog;
	}
	return shader;
}

ShaderProgram::ShaderProgram() {
	initialized = false;
}

void ShaderProgram::load(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile) {
	if(vertexShaderFile != nullptr && fragmentShaderFile != nullptr) {
		printf("Loading vertex shader...\n");
		vertexShader=loadShader(GL_VERTEX_SHADER,vertexShaderFile);

		if (geometryShaderFile != nullptr) {
			printf("Loading geometry shader...\n");
			geometryShader=loadShader(GL_GEOMETRY_SHADER,geometryShaderFile);
		} else {
			geometryShader=0;
		}

		printf("Loading fragment shader...\n");
		fragmentShader=loadShader(GL_FRAGMENT_SHADER,fragmentShaderFile);

		shaderProgram=glCreateProgram();

		glAttachShader(shaderProgram,vertexShader);
		glAttachShader(shaderProgram,fragmentShader);
		if (geometryShaderFile != nullptr) glAttachShader(shaderProgram,geometryShader);
		glLinkProgram(shaderProgram);
		
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH,&infologLength);
		if (infologLength > 1)
		{
			infoLog = new char[infologLength];
			glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			delete []infoLog;
		}
		printf("Shader program created \n");
		initialized = true;
	}
}

ShaderProgram::~ShaderProgram() {
	if(initialized) {
		glDetachShader(shaderProgram, vertexShader);
		if (geometryShader!=0) glDetachShader(shaderProgram, geometryShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		if (geometryShader!=0) glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
}


void ShaderProgram::use() {
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::getUniformLocation(const char* variableName) {
	return glGetUniformLocation(shaderProgram,variableName);
}

GLuint ShaderProgram::getAttribLocation(const char* variableName) {
	return glGetAttribLocation(shaderProgram,variableName);
}

bool ShaderProgram::isInitialized() {
	return initialized;
}
