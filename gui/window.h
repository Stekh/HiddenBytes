//
// Created by stek on 5.11.2025.
//

#ifndef HIDDENBYTES_WINDOW_H
#define HIDDENBYTES_WINDOW_H

#include <QMainWindow>
#include <QMenu>

#include "about_widget.h"
#include "interface_widget.h"

class Window final : public QMainWindow {
	Q_OBJECT
public:
	explicit Window(QWidget *parent = nullptr);

private:
	QMenuBar *m_main_menu;
	QMenu *m_graphics_menu;
	QMenu *m_audio_menu;
	AboutWidget *m_about_widget;
	InterfaceWidget *m_interface_widget;
};

#endif //HIDDENBYTES_WINDOW_H
