//
// Created by stek on 5.11.2025.
//

#ifndef HIDDENBYTES_ABOUT_WIDGET_H
#define HIDDENBYTES_ABOUT_WIDGET_H

#include <QWidget>

class AboutWidget final {
public:
	explicit AboutWidget(QWidget *parent);

	QWidget *getWidget() const { return m_widget; }

private:
	QWidget* m_widget;
};

#endif //HIDDENBYTES_ABOUT_WIDGET_H