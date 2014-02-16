#ifndef TIMECODEEDIT_H
#define TIMECODEEDIT_H

#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QLineEdit>
#include <QKeyEvent>
#include "PhTools/PhTimeCode.h"

class PhTimeCodeEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit PhTimeCodeEdit(QWidget *parent = 0);

    void setFrame(PhFrame frame, PhTimeCodeType tcType);
	bool isTimeCode();
	/**
	 * @brief Current frame value entered in the text field
	 * @return A frame value.
	 */
	PhFrame frame();

signals:

    void frameChanged(PhFrame frame, PhTimeCodeType tcType);

private slots:
    void onTextChanged(QString text);

private:
	PhTimeCodeType _tcType;
	bool eventFilter(QObject *sender, QEvent *event);
	QString _oldFrame;
	QString _addedNumbers;
	void compute(bool add);
};

#endif // TIMECODEEDIT_H
