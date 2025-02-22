#include <Chill.h>

class Sandbox: public Chill::Application
{
public:
	Sandbox() 
	{

	}

	~Sandbox()
	{
	
	}

};

Chill::Application* Chill::CreateApplication()
{
	return new Sandbox();
}