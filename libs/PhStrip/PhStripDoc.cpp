/**
* Copyright (C) 2012-2013 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <QtXml>

#include <QFile>
#include "PhStripDoc.h"
#include <math.h>
#include <limits>


PhStripDoc::PhStripDoc(QObject *parent) :
	QObject(parent)
{
    reset();
}


bool PhStripDoc::openDetX(QString fileName)
{
	PHDEBUG << fileName;
    if (!QFile(fileName).exists())
	{
		PHDEBUG << "The file doesn't exists" << fileName;
        return false;
	}

	_filePath = fileName;

	// Opening the XML file
    QFile xmlFile(fileName);
    if(!xmlFile.open(QIODevice::ReadOnly))
    {
		PHDEBUG << "Unable to open" << fileName;
        return false;
    }

	// Loading the DOM (document object model)
	QDomDocument *domDoc = new QDomDocument();
	if (!domDoc->setContent(&xmlFile))
    {
        xmlFile.close();
		PHDEBUG << "The XML document seems to be bad formed " << fileName;
        return false;
    }

	PHDEBUG << ("Start parsing " + fileName);

    reset();

	QDomElement detX = domDoc->documentElement();

	if(detX.tagName() != "detx")
	{
		xmlFile.close();
		PHDEBUG << "Bad root element :" << detX.tagName();
		return false;
	}

	//With DetX files, fps is always 25 no drop
    _tcType = PhTimeCodeType25;
    _timeScale = 25.00;

	// Reading the header
	if(detX.elementsByTagName("header").count())
	{
		QDomElement header = detX.elementsByTagName("header").at(0).toElement();

		// Reading Cappella version : TODO

		// Reading the title
		if(header.elementsByTagName("title").count())
			_title = detX.elementsByTagName("title").at(0).toElement().text();

		// Reading the video path
		if(header.elementsByTagName("videofile").count())
		{
			QDomElement videoFile = header.elementsByTagName("videofile").at(0).toElement();
			_videoPath = videoFile.text();
			// Reading the video framestamp
			_videoFrameStamp = PhTimeCode::frameFromString(videoFile.attribute("timestamp"), _tcType);
		}

		// Reading the last position
		if(header.elementsByTagName("last_position").count())
		{
			QDomElement lastPosition = header.elementsByTagName("last_position").at(0).toElement();
			_lastFrame = PhTimeCode::frameFromString(lastPosition.attribute("timecode"), _tcType);

			// Reading the last track : TODO
		}

		// Reading the author name
		if(header.elementsByTagName("author").count())
		{
			QDomElement author = header.elementsByTagName("author").at(0).toElement();
			_authorName = author.attribute("firstname") + " " + author.attribute("name");
		}
	}

    // Reading the "role" lists
	if(detX.elementsByTagName("roles").count())
	{
		QDomElement roles = detX.elementsByTagName("roles").at(0).toElement();
		QDomNodeList roleList = roles.elementsByTagName("role");
		for (int i = 0; i < roleList.length(); i++)
		{
			QDomElement role = roleList.at(i).toElement();
			PhPeople *people = new PhPeople(role.attribute("name"), role.attribute("color"));

			//Currently using id as key instead of name
			_peoples[role.attribute("id")] = people;
		}
    }

#warning TODO try reading first loop number if possible
	int loopNumber = 1;

	// Reading the strip body
	if(detX.elementsByTagName("body").count())
	{
		QDomElement body = detX.elementsByTagName("body").at(0).toElement();
		for(int i = 0; i < body.childNodes().length(); i++)
		{
			if(body.childNodes().at(i).isElement())
			{
				QDomElement elem = body.childNodes().at(i).toElement();

				// Reading loops
				if(elem.tagName() == "loop")
					_loops.append(new PhStripLoop(loopNumber++,
								PhTimeCode::frameFromString(elem.attribute("timecode"), _tcType)));
				// Reading cuts
				else if(elem.tagName() == "shot")
					_cuts.append(new PhStripCut(PhStripCut::Simple,
								PhTimeCode::frameFromString(elem.attribute("timecode"), _tcType)));
				else if(elem.tagName() == "line")
				{
					PhFrame frameIn = -1;
					PhFrame lastFrame = -1;
					PhPeople *people = _peoples[elem.attribute("role")];
					int track = elem.attribute("track").toInt();
					QString currentText = "";
					for(int j = 0; j < elem.childNodes().length(); j++)
					{
						if(elem.childNodes().at(j).isElement())
						{
							QDomElement lineElem = elem.childNodes().at(j).toElement();
							if(lineElem.tagName() == "lipsync")
							{
								if(lineElem.attribute("link") != "off")
								{
									PhFrame frame = PhTimeCode::frameFromString(lineElem.attribute("timecode"), _tcType);
									if(frameIn < 0)
										frameIn = frame;
									if(currentText.length())
									{
										_texts.append(new PhStripText(lastFrame, people, frame, track, currentText));
										currentText = "";
									}
									lastFrame = frame;
								}
							}
							else if(lineElem.tagName() == "text")
								currentText += lineElem.text();
						}
					}
					// Handling line with no lipsync out
					if(currentText.length())
					{
						PhFrame frame = lastFrame + currentText.length();
						_texts.append(new PhStripText(lastFrame, people, frame, track, currentText));
						lastFrame = frame;
					}
					if(elem.attribute("voice") == "off")
						_offs.append(new PhStripOff(frameIn, people, lastFrame, track));
				}
			}
		}
	}

	emit this->changed();

	return true;
}

bool PhStripDoc::createDoc(QString text, int nbPeople, int nbLoop, int nbText, int nbTrack, PhTime videoTimeCode)
{
	this->reset();
	_title = "Fake file";
	_tcType = PhTimeCodeType25;
	_timeScale = 25.00;
	_videoFrameStamp = videoTimeCode;
	_lastFrame = _videoFrameStamp;

	if (nbTrack > 4 || nbTrack < 1)
		nbTrack = 3;

	QStringList names;
	names.append("Actor");
	names.append("Actress");
	names.append("Jack");
	names.append("Jane");

	int nbNames = names.length();
	QStringList idList;
	// Creation of the Peoples
	for (int i = 1; i <= nbPeople; i++)
	{
		PhPeople *people = new PhPeople(names.at(i % nbNames) + " " + QString::number(i), "black");
		_peoples[people->getName()] = people;
		idList.append(people->getName());
	}

	int position = _videoFrameStamp;
	// Creation of the text
	for (int i=0; i < nbText; i++)
	{
		//Make people "talk" alternaly
		QString id = _peoples[idList.at(i % nbPeople)]->getName();

		int start = position;
		int end = start + text.length() * 1.20588 + 1;

		splitText(_peoples[id], start, end,
				  text, i % nbTrack, 0);

		// So the texts are all one after the other
		position += end - start;
	}

	emit changed();
	return true;
}

void PhStripDoc::reset()
{
	_peoples.clear();
	_cuts.clear();
	_tcType = PhTimeCodeType25;
	_lastFrame = 0;
	_loops.clear();
	_nbTexts = 0;
	_texts.clear();
	_timeScale = 25; //TODO fix me
	_title = QString();
	_videoPath = QString();
	_videoFrameStamp = 0;
	_authorName = "";

	emit this->changed();
}

void PhStripDoc::splitText(PhPeople * actor, PhTime start, PhTime end, QString sentence, int track, int i)
{

	if(sentence != " " && sentence != "" ){
		// if the sentence is short enough
		if( end - start < 150)
		{
			_texts.push_back(new PhStripText(start, actor,
											  end,
											 track, sentence));
			_nbTexts ++;
		}
		else // we split in half
		{
			int length = sentence.length();
			splitText(actor, start, start + (end - start)/2, sentence.left(length/2), track, i);
			i++;
			if (length % 2 == 0){
				splitText(actor, start + (end - start)/2, end, sentence.right(length/2), track, i);
			}
			else{
				splitText(actor, start + (end - start)/2, end, sentence.right(length/2 + 1), track, i);
			}
		}
	}
}

int PhStripDoc::getNbTexts()
{
	return _nbTexts;
}

PhFrame PhStripDoc::getPreviousTextFrame(PhFrame frame)
{
	PhFrame previousTextFrame = 0;

	foreach(PhStripText* text, _texts)
	{
		if((text->getTimeIn() < frame) && (text->getTimeIn() > previousTextFrame) )
			previousTextFrame = text->getTimeIn();
	}

	return previousTextFrame;
}

PhFrame PhStripDoc::getPreviousLoopFrame(PhFrame frame)
{
	PhFrame previousLoopFrame = 0;

	foreach(PhStripLoop* loop, _loops)
	{
		if((loop->getTimeIn() < frame) && (loop->getTimeIn() > previousLoopFrame) )
			previousLoopFrame = loop->getTimeIn();
	}

	return previousLoopFrame;
}

PhFrame PhStripDoc::getPreviousCutFrame(PhFrame frame)
{
	PhFrame previousCutFrame = 0;

	foreach(PhStripCut* cut, _cuts)
	{
		if((cut->getTimeIn() < frame) && (cut->getTimeIn() > previousCutFrame) )
			previousCutFrame = cut->getTimeIn();
	}

	return previousCutFrame;
}

PhFrame PhStripDoc::getPreviousElementFrame(PhFrame frame)
{
	PhFrame previousElementFrame = getPreviousCutFrame(frame);

	if(getPreviousLoopFrame(frame) > previousElementFrame)
			previousElementFrame = getPreviousLoopFrame(frame);

	if(getPreviousTextFrame(frame) > previousElementFrame)
			previousElementFrame = getPreviousTextFrame(frame);

	return previousElementFrame;
}

PhFrame PhStripDoc::getNextTextFrame(PhFrame frame)
{
	PhFrame nextTextFrame = pow(2,32);

	foreach(PhStripText* text, _texts)
	{
		if((text->getTimeIn() > frame) && (text->getTimeIn() < nextTextFrame) )
			nextTextFrame = text->getTimeIn();
	}

	return nextTextFrame;
}

PhFrame PhStripDoc::getNextLoopFrame(PhFrame frame)
{
	PhFrame nextLoopFrame = pow(2,32);

	foreach(PhStripLoop* loop, _loops)
	{
		if((loop->getTimeIn() > frame) && (loop->getTimeIn() < nextLoopFrame) )
			nextLoopFrame = loop->getTimeIn();
	}

	return nextLoopFrame;
}

PhFrame PhStripDoc::getNextCutFrame(PhFrame frame)
{
	PhFrame nextCutFrame = pow(2,32);

	foreach(PhStripCut* cut, _cuts)
	{
		if((cut->getTimeIn() > frame) && (cut->getTimeIn() < nextCutFrame) )
			nextCutFrame = cut->getTimeIn();
	}

	return nextCutFrame;
}

PhFrame PhStripDoc::getNextElementFrame(PhFrame frame)
{
	PhFrame nextElementFrame = getNextCutFrame(frame);

	if(getNextLoopFrame(frame) < nextElementFrame)
			nextElementFrame = getNextLoopFrame(frame);

	if(getNextTextFrame(frame) < nextElementFrame)
			nextElementFrame = getNextTextFrame(frame);

	return nextElementFrame;
}

PhFrame PhStripDoc::getFrameIn()
{
	return getNextElementFrame(0);
}

PhFrame PhStripDoc::getFrameOut()
{
	return getPreviousElementFrame(std::numeric_limits<PhFrame>::max());
}

QString PhStripDoc::getFilePath()
{
	return _filePath;
}

QString PhStripDoc::getVideoPath()
{
    return _videoPath;
}

PhTimeCodeType PhStripDoc::getTCType()
{
	return _tcType;
}

QString PhStripDoc::getTitle()
{
    return _title;
}

PhTime PhStripDoc::getVideoTimestamp()
{
    return _videoFrameStamp;
}

PhFrame PhStripDoc::getLastFrame()
{
    return _lastFrame;
}

QMap<QString, PhPeople *> PhStripDoc::getPeoples()
{
    return _peoples;
}

QList<PhStripText *> PhStripDoc::getTexts()
{
	return _texts;
}

QList<PhStripLoop *> PhStripDoc::getLoops()
{
	return _loops;
}

QList<PhStripOff *> PhStripDoc::getOffs()
{
	return _offs;
}

QList<PhStripCut *> PhStripDoc::getCuts()
{
	return _cuts;
}

