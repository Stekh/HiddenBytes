//
// Created by stek on 5.11.2025.
//

#include <QMenuBar>

#include "window.h"
#include "about_widget.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
	m_main_menu = new QMenuBar(this);

	m_graphics_menu = new QMenu("Graphics", m_main_menu);
	m_graphics_menu->addAction("Alg 1");
	m_graphics_menu->addAction("Alg 2");
	m_graphics_menu->addAction("Alg 3");
	m_main_menu->addMenu(m_graphics_menu);

	m_audio_menu = new QMenu("Audio", m_main_menu);
	m_audio_menu->addAction("Alg 1");
	m_audio_menu->addAction("Alg 2");
	m_audio_menu->addAction("Alg 3");
	m_main_menu->addMenu(m_audio_menu);

	m_audio_menu = new QMenu("About", m_main_menu);
	m_main_menu->addMenu("About");

	setMenuBar(m_main_menu);

	m_about_widget = new AboutWidget(this);
	setCentralWidget(m_about_widget);
	show();
}
