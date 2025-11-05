//
// Created by stek on 5.11.2025.
//

#include <QMenuBar>

#include "window.h"

#include "about_widget.h"

Window::Window() {
	m_main_window = new QMainWindow();
	m_about_widget = new AboutWidget(m_main_window);

	m_menu = new QMenuBar(m_main_window);
	m_menu->addMenu("Graphics");
	m_menu->addMenu("Audio");
	m_menu->addMenu("About");

	m_main_window->setMenuBar(m_menu);
	m_main_window->setCentralWidget(m_about_widget->getWidget());
	m_main_window->show();
}
