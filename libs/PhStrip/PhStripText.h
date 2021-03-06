/**
 * @file
 * @copyright (C) 2012-2014 Phonations
 * @license http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#ifndef PHSTRIPTEXT_H
#define PHSTRIPTEXT_H

#include "PhPeople.h"
#include "PhStrip/PhStripPeopleObject.h"

/**
 * @brief Sentence or part of a sentence of a PhPeople with synchronization information.
 *
 * Its property is content.
 */
class PhStripText : public PhStripPeopleObject {

public:

	/**
	 * @brief PhStripText constructor
	 * @param timeIn the beggining of the text
	 * @param people the text's speaker
	 * @param timeOut the end of the text
	 * @param track the track of the text
	 * @param content the content of the text
	 */
	PhStripText( PhTime timeIn, PhPeople * people, PhTime timeOut, int track,  QString content);
	/**
	 * @brief Get the text content
	 * @return _content
	 */
	QString getContent();
	/**
	 * @brief Set the text content
	 * @param content the desired content
	 */
	void setContent(QString content);

private:

/**
 * Text string of Sentence or part of a sentence.
 */
	QString _content;


};

#endif // PHSTRIPTEXT_H
