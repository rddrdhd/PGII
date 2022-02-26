#include "pch.h"
#include "tutorials.h"
#include <sstream>
int main()
{
	printf( "PG2 OpenGL, (c)2020-2022 Tomas Fabian\n\n" );

	// Jak cist vlastni YAML (klic:hodnota)
	/*std::ifstream file("new.txt");
	if (file) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string key,value;
		buffer >> key>>value;
		key.pop_back(); // pryc s dvojteckou
		//auto pi = std::stof(value);
		printf("%s: %0.3f\n", key.c_str(), value);
		int i;
	}*/
	//return tutorial_1();
	//nvidia 511 driver?
	//return tutorial_2();
	//return tutorial_3( "../../../data/environments/abandoned_hopper_terminal_04_1k.jpg" );
	//return tutorial_4( "../../../data/environments/abandoned_hopper_terminal_04_1k.exr" );
	//return tutorial_5();
	//return tutorial_6();
	//return tutorial_7( "../../../data/adjacent_triangles.obj" ); //jeden trojuhelnik slozeny ze 4
	//return tutorial_8();
	return my_tut();
}
