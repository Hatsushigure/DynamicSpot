#include "DynamicSpotApp.h"
#include "DynamicSpot.h"

int main(int argc, char *argv[])
{
	DynamicSpot::theApp = new DynamicSpotApp(argc, argv);
	return DynamicSpot::theApp->exec();
}
