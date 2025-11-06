//
// Created by stek on 5.11.2025.
//

#ifndef HIDDENBYTES_WINDOW_H
#define HIDDENBYTES_WINDOW_H

#include <QMainWindow>

#include "about_widget.h"

class Window final : public QMainWindow {
	Q_OBJECT
public:
	explicit Window();

private:
	QMenuBar *m_menu;
	AboutWidget *m_about_widget;
};

#endif //HIDDENBYTES_WINDOW_H
