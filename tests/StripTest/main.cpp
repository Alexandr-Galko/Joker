#include <QDebug>

#include <QFileInfo>

#include "PhStrip/PhStripDoc.h"
#include "PhStrip/tests/PhStripDocTest.h"

using namespace std;

/**
 * @brief The application main entry point
 * @param argc Command line argument count
 * @param argv Command line argument list
 * @return 0 if the application works well.
 */
int main(int argc, char *argv[])
{
	PhStripDocTest docTest;
	int test = QTest::qExec(&docTest);
	if(test)
		return test;

	// Creating a new doc:
	PhStripDoc doc;

	//Check argument count
	if (argc > 1) {
		// Open the DetX file in argument:
		QString fileName(argv[1]);
		doc.importDetX(fileName);
	}
	else
		doc.createDoc("test", 3, 9, 3, 0);

	// Display the title:
	PHDEBUG << "title : " << doc.getTitle();
	PHDEBUG << "video file : " << doc.getVideoPath();
	PHDEBUG << "video timestamp" << PhTimeCode::stringFromFrame(doc.getVideoTimestamp(), doc.getTCType());

	// Display actors:
	QMap<QString, PhPeople *> list_actors = doc.getPeoples();
	QMap<QString, PhPeople *>::iterator people;
	PHDEBUG <<"--------- actors ---------";
	PHDEBUG << list_actors.count();
	for( people = list_actors.begin(); people != list_actors.end(); people++) {
		PHDEBUG << (*people)->getName();
	}

	// Display text

	PHDEBUG <<"--------- texts ---------";
	QString line;
	PhPeople * lastPeople;

	foreach(PhStripText* text, doc.getTexts())
	{
		line = text->getPeople()->getName() + " : " + text->getContent();
		PHDEBUG << line;

		//             if(((*text)->getPeople().getName()) != ((*(text-1))->getPeople().getName()))
		//             {
		//                 PHDEBUG << qPrintable( line );
		//                 line = (*text)->getPeople().getName();
		//                 line += " : ";
		//                 line += (*text)->getContent();
		//             }
		//             else
		//             {
		//                 line += (*text)->getContent();
		//             }
	}

	foreach (PhStripOff * off, doc.getOffs()) {
		PHDEBUG << off->getPeople()->getName() << " : " << PhTimeCode::stringFromFrame(off->getTimeIn(), doc.getTCType())
		        << " - " << PhTimeCode::stringFromFrame(off->getTimeOut(), doc.getTCType());
	}

	return 0;
}
