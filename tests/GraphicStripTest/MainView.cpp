/**
* Copyright (C) 2012-2013 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/


//#include <QAction>
//#include <QFileDialog>
//#include <QMenuBar>

//#include <QInputDialog>

#include "MainView.h"

//#if LEAP
//using namespace Leap;
//#endif

MainView::MainView()
{
//#if LEAP
//    _leapController.addListener(leapListener);
//#endif
 //   _MController = new PhGraphicStripController();
//-    if(_MController->openDoc(file))
//        _MController->setLastFile(file);
    resize(1280,360);
    setWindowTitle(tr("GraphicStripTest"));
    _strip = new PhGraphicStripView(this);
	_strip->resize(1000, 300);
	//createMenus();
	//_strip->setController(_MController);
	//_strip->setNaturalScroll(_MController->getNaturalScrollPref());
	//_strip->connectSlots();
	//_strip->show();

//#if LEAP
//    qDebug() << leapListener.objectName();
//    connect(&leapListener, SIGNAL(setPosition(int move)), _MController, SLOT(onPositionChanged2(int move)));
//    connect(&leapListener, SIGNAL(setRate(float rate)), _MController, SLOT(onRateChanged2(float rate)));
//#endif
}

/*void MainView::createMenus()
{
	// The tr("&string") at the begining of a string is for translation tools

	// Add a menu
	fileMenu = menuBar()->addMenu(tr("&File"));

	// Create a new Open action
	openAct = new QAction(tr("&Open"), this);
	// Set a shortcut to execute this action
	openAct->setShortcut(QKeySequence::Open);
	// Add the action to the file menu
	fileMenu->addAction(openAct);
	// Connect the action to a function
	connect(openAct, SIGNAL(triggered()), _strip, SLOT(stopScroll()));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

	// Add a menu
	toolMenu = menuBar()->addMenu(tr("&Tools"));

	changeFontAct = new QAction(tr("&Change font..."), this) ;
	toolMenu->addAction(changeFontAct);
	connect(changeFontAct, SIGNAL(triggered()), this, SLOT(changeFont()));

	//Separate 2 parts in the same menu list
	toolMenu->addSeparator();

	exportRythmoAct = new QAction(tr("&Export next minute"), this) ;
	toolMenu->addAction(exportRythmoAct);
	exportRythmoAct->setShortcut(QKeySequence::Print);
	connect(exportRythmoAct, SIGNAL(triggered()), this, SLOT(exportRythomAsPNG()));

	//Separate 2 parts in the same menu list
	toolMenu->addSeparator();

	switchScroll = new QAction(tr("&Toggle scroll"), this) ;
	toolMenu->addAction(switchScroll);
	connect(switchScroll, SIGNAL(triggered()), this, SLOT(switchScrolling()));

}

void MainView::openFile(QString fileName)
{
  //  PhString fileName = QFileDialog::getOpenFileName(this, tr("Open a script"),QDir::homePath(), "Script File (*.detx)");
	if(!fileName.isNull())
	   { _MController->openDoc(fileName);
	//	qDebug() << "filename : " << fileName;
	//	_strip->openFile("");
	}
}

//void MainView::switchScrolling()
//{
//	_strip->toggleScroll();
//}

void MainView::changeFont()
{

	// This is a routine witch load Apple system TTF fonts

	// Set the location

#if defined(Q_OS_MAC)
	QString sourceFolder = "/Library/Fonts/";
#elif defined(Q_OS_UNIX)
	QString sourceFolder = "/usr/share/fonts/truetype/freefont/";
#endif

	QDir sourceDir(sourceFolder);
	// List all files
	QStringList files = sourceDir.entryList(QDir::Files);
	QStringList fonts;
	// browse files and select only TTF ones
	for(int i = 0; i< files.count(); i++)
	{
		if(files[i].split(".").at(1) == "ttf")
		{
			fonts.push_back(files[i].split(".").at(0));
		}
	}

	// i & j are used to display the current font in the QInputDialog
	int i = 0;
	int j = 0;
	QString oldFont = _strip->getCurrentFont()->getFontName();
	foreach (QString it, fonts ){
		if (it.contains(oldFont))
			j = i;
		i++;
	}
	bool ok;
	QString item = QInputDialog::getItem(this, tr("Font Selection"),tr("fonts loaded"), fonts, j, false, &ok);
	if (true){
		QString file = sourceFolder + item + ".ttf";
		_strip->setCurrentFont(file);
	}

}*/

//void MainView::exportRythomAsPNG()
//{
//	_strip->getContext()->exportToPng();
//	QMessageBox::about(this, "Info",
//					   tr("Export ended well! \n") + tr("file(s) saved here : ") + QDir::homePath() + "") ;
//}

//void MainView::resizeEvent(QResizeEvent *)
//{
//	// Call the resize of the OpenGL context

//	_strip->resizeGL(this->width(), this->height());

//}

//void MainView::keyPressEvent( QKeyEvent *keyEvent )
//{

//	switch(keyEvent->key())
//	{
//	case Qt::Key_Space:
//		_strip->changeScroll();
//		break;
//	case Qt::Key_Escape:
//		close();
//		break;
//	case Qt::Key_F10:
//		toggleFullWindow();
//		break;
//	case Qt::Key_Right:
//		_strip->setScroll(false);
//		_strip->setXmove(this->width());
//		break;
//	case Qt::Key_Left:
//		_strip->setScroll(false);
//		_strip->setXmove(-this->width());
//		break;
//	default:
//		_strip->keyPressEvent(keyEvent);
//	}
//}

//void MainView::wheelEvent(QWheelEvent *wheel)
//{
//	QPoint numPixels = wheel->pixelDelta();
//	_strip->setXmove(numPixels.x());
//	_strip->setXmove(-numPixels.y());
//}



//void MainView::toggleFullWindow()
//{
//	if(this->isFullScreen())
//		showNormal();
//	else
//		showFullScreen();
//}

