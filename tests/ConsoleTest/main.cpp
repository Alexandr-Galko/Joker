#include <QCoreApplication>
#include <QTest>
#include <QSettings>
#include <QTime>

#include "PhTools/PhTimeCode.h"
#include "PhTools/PhDebug.h"

#include "PhTools/tests/PhTimeCodeTest.h"


int main(int argc, char *argv[])
{

	// Initialize the Debug module.
//	PhDebug::init(false, true, true, true, true, true, 1, argv[0]);


	PHDEBUG << "should always display.";
	PhDebug::setLogMask(0b11);
	PHDBG(1) << "1 should display";
	PHDBG(2) << "2 should not display";

	QSettings settings("Phonations", "ConsoleTest");

	settings.setValue("test", true);

	int total = 10000;
	QTime t;
	PHDEBUG << "starting";
	t.start();
	int n = 0;
	for(int i = 0; i < total; i++)
	{
		if(settings.value("test", false).toBool())
			n++;
	}

	PHDEBUG << "settings " << t.elapsed();

	t.restart();

	bool b = true;
	for(int i = 0; i < total; i++)
	{
		if(b)
			n++;
	}

	PHDEBUG << "bool " << t.elapsed();

	return 0;
}
