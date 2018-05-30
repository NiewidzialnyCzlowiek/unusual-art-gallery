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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GL/glew.h"
#include <cstdio>

class ShaderProgram {
private:
	bool initialized;
	GLuint shaderProgram; //Uchwyt reprezentuj�cy program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentuj�cy vertex shader
	GLuint geometryShader; //Uchwyt reprezentuj�cy geometry shader
	GLuint fragmentShader; //Uchwyt reprezentuj�cy fragment shader
	char* readFile(const char* fileName); //metoda wczytuj�ca plik tekstowy do tablicy znak�w
	GLuint loadShader(GLenum shaderType,const char* fileName); //Metoda wczytuje i kompiluje shader, a nast�pnie zwraca jego uchwyt
public:
	ShaderProgram();
	void load(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);
	~ShaderProgram();
	bool isInitialized();
	void use(); //W��cza wykorzystywanie programu cieniuj�cego
	GLuint getUniformLocation(const char* variableName); //Pobiera numer slotu zwi�zanego z dan� zmienn� jednorodn�
	GLuint getAttribLocation(const char* variableName); //Pobiera numer slotu zwi�zanego z danym atrybutem
};



#endif
