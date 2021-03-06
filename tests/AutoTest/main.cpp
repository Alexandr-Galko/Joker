#include <stdio.h>

#include <PhTools/tests/PhTimeCodeTest.h>
#include <PhTools/tests/PhSettingsTest.h>
#include <PhStrip/tests/PhStripDocTest.h>
#include <PhSync/tests/PhSonyControllerTest.h>

int main(int argc, char *argv[])
{
	bool testAll = (argc < 2); // if no argument, test all
	bool testTC = testAll;
	bool testSettings = testAll;
	bool testDoc = testAll;
	bool testSony = testAll;
	bool quiet = false;

	bool success = true;

	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "tc") == 0)
			testTC = true;
		else if(strcmp(argv[i], "settings") == 0)
			testSettings = true;
		else if(strcmp(argv[i], "doc") == 0)
			testDoc = true;
		else if(strcmp(argv[i], "sony") == 0)
			testSony = true;
		else if(strcmp(argv[i], "quiet") == 0)
			quiet = true;
	}

	if(testTC) {
		// Testing PhTimeCode
		PhTimeCodeTest tcTest;
		success &= !QTest::qExec(&tcTest);
	}

	if(testSettings) {
		// Testing PhSettings
		PhSettingsTest settingsTest;
		success &= !QTest::qExec(&settingsTest);
	}

	if(testDoc) {
		// Testing PhStripDoc
		PhStripDocTest docTest;
		success &= !QTest::qExec(&docTest);
	}

	if(testSony) {
		// Testing PhSonyController
		PhSonyControllerTest sonyTest;
		success &= !QTest::qExec(&sonyTest);
	}

	QThread::msleep(500);

	if(quiet)
		return !success;

	if(success) {

		PHDEBUG << "                            ************";
		PHDEBUG << "                         *****************";
		PHDEBUG << "                       ********************";
		PHDEBUG << "                        ********************";
		PHDEBUG << "                         ********";
		PHDEBUG << "                          ********                 *********";
		PHDEBUG << "                           ***********              *********";
		PHDEBUG << "              *********      ****       *            *********";
		PHDEBUG << "            *            ***               *          *********";
		PHDEBUG << "          *                       **         *          ********";
		PHDEBUG << "         *                         **         *       ***********";
		PHDEBUG << "        *        *****              **      *********************";
		PHDEBUG << "       *        *******                     *********************";
		PHDEBUG << "       *         *****                         *****************";
		PHDEBUG << "       *                                        *";
		PHDEBUG << "        *     *               *                 *";
		PHDEBUG << "         *     *             *                  *";
		PHDEBUG << "           *    *           *                  *";
		PHDEBUG << "             *    *       *                   *";
		PHDEBUG << "                *   *****                   *";
		PHDEBUG << "       ***               *     ************";
		PHDEBUG << "      *   *            *      *";
		PHDEBUG << "      *   *          *********          ***";
		PHDEBUG << "  ****    **********        *          *   *";
		PHDEBUG << " *               *         *           *   *";
		PHDEBUG << "*              *           *************    ****";
		PHDEBUG << "*      *******                                  *";
		PHDEBUG << "*      *    *                                    *";
		PHDEBUG << "  *****    *              *****************      *";
		PHDEBUG << "          *               *               *      *";
		PHDEBUG << "         *      ****      *                *****";
		PHDEBUG << "         *    *      **   *";
		PHDEBUG << "         *   *         ** *";
		PHDEBUG << "      *** *  *            *";
		PHDEBUG << "     *    *   *            *    *";
		PHDEBUG << "      *    *   *           *   * *";
		PHDEBUG << "       *     *  *          *  *  *";
		PHDEBUG << "         *     * *         *  *  *";
		PHDEBUG << "          *       *        *  *  *";
		PHDEBUG << "            *       *    *****   *";
		PHDEBUG << "               *      * * *****  *";
		return 0;
	}
	else {
		PHDEBUG << "                                     _";
		PHDEBUG << "                                     gs        ,8+";
		PHDEBUG << "                                    d88        888.";
		PHDEBUG << "                                    888        888b";
		PHDEBUG << "                                   8888        8888";
		PHDEBUG << "                                   8888        8888";
		PHDEBUG << "                                   8888        8888.";
		PHDEBUG << "                                  ,8888        8888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88889";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  88888        88888";
		PHDEBUG << "                                  ~8888        8888~";
		PHDEBUG << "                                   8888Y+y.'fsY8888";
		PHDEBUG << "                                   Y8888+lif'f+8888";
		PHDEBUG << "                                   '8886~~~~~~~7888";
		PHDEBUG << "                                   88`          V88";
		PHDEBUG << "                                 ,88       _    d88";
		PHDEBUG << "                                 88   __+  ]]   ~ Yi";
		PHDEBUG << "                               d88`   !8!  ]]]    !8.";
		PHDEBUG << "                   _cooooooooood888i   889  ]]]]    88";
		PHDEBUG << "                i88~~~~` ~Y8~~~Y~808   808   ]]]    88";
		PHDEBUG << "              g88f`       '~`    808   808   ]]]    888";
		PHDEBUG << "             d88                 !8!   !8!    ]]    88!";
		PHDEBUG << "            88!                                     d8";
		PHDEBUG << "           ,88                                     ,8!";
		PHDEBUG << "           888     ,d88888.                       ,d8";
		PHDEBUG << "           888   ,888888888]                     g88";
		PHDEBUG << "           '88.  !888888888]                  ,g88f`";
		PHDEBUG << "            !88.                             ,888";
		PHDEBUG << "             '88nsnnnnnnnnnnnnnn___________nnn88~";
		PHDEBUG << "              '~~~~~~~~~~~~~~~~~88888i  g8~`";
		PHDEBUG << "                                88  88` T8`";
		PHDEBUG << "                                88     i8f";
		PHDEBUG << "                                88    ,88";
		PHDEBUG << "                                88    888";
		PHDEBUG << "                                888b____d88";
		PHDEBUG << "                                88888888888";
		PHDEBUG << "                               ~88~~~~~~Y8~";
		PHDEBUG << "                              ,88`      88";
		PHDEBUG << "                              d8        88";
		PHDEBUG << "                              88        '88";
		PHDEBUG << "                             88          88";
		PHDEBUG << "                             88          !8b";
		PHDEBUG << "                             Y8       /\\  ~88";
		PHDEBUG << "                             !8.      88   ~88s.      o";
		PHDEBUG << "                              8b      88   88!88b.    #o_";
		PHDEBUG << "                              88.     88   '888888b    88o";
		PHDEBUG << "                              8V8     88    88~~V88b   d88s";
		PHDEBUG << "                   ,____d8____8.8!    88    88   !88   d888";
		PHDEBUG << "                _o88f~~~  o8888888888g88    88!   8b.  88088";
		PHDEBUG << "               g88~,_i  ,8888f~~~~~~~V88    8b__gg888888~ 889";
		PHDEBUG << "              ,88  88   88  ,d!   ,.        8888_.!88d88_8889      ,";
		PHDEBUG << "_/\\===+/\\~~T/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\";
		PHDEBUG << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

		return -1;
	}
}
