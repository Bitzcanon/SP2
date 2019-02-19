

#include "Application.h"
#include <time.h>
int main( void )
{
	srand((unsigned)time(NULL));
	Application app;
	app.Init();
	app.Run();
	app.Exit();
}