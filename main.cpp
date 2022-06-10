#include		"Application.h"

int main(void) {
	Sample::Framework* fw = new Sample::Application();
	fw->Create(1024, 768, "OpenGL_ImGui");
	fw->Run();
	delete fw;
	return 0;
}