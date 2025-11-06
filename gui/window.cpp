//
// Created by stek on 5.11.2025.
//

#include <QMenuBar>

#include "window.h"

#include "about_widget.h"

Window::Window() {
	m_about_widget = new AboutWidget(this);

	m_menu = new QMenuBar(this);
	m_menu->addMenu("Graphics");
	m_menu->addMenu("Audio");
	m_menu->addMenu("About");

	setMenuBar(m_menu);
	setCentralWidget(m_about_widget);
	show();
}
