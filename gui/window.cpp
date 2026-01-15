//
// Created by stek on 5.11.2025.
//

#include <QMenuBar>

#include "../algs/audio_lsb.h"
#include "../algs/graphics_lsb.h"
#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
	m_main_menu = new QMenuBar(this);
	m_about_widget = new AboutWidget(this);
	m_interface_widget = new InterfaceWidget(this);

	m_graphics_menu = new QMenu("Graphics", m_main_menu);
	const QAction *graphics_LSB_action = m_graphics_menu->addAction("LSB");
	m_main_menu->addMenu(m_graphics_menu);

	connect(graphics_LSB_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		m_interface_widget->setEncodeFunction(&gr::lsb_encode);
		m_interface_widget->setDecodeFunction(&gr::lsb_decode);
		m_interface_widget->m_is_audio = false;
		setCentralWidget(m_interface_widget);
	});

	m_audio_menu = new QMenu("Audio", m_main_menu);
	const QAction *audio_LSB_action = m_audio_menu->addAction("LSB");
	m_main_menu->addMenu(m_audio_menu);

	connect(audio_LSB_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		m_interface_widget->m_is_audio = true;
		m_interface_widget->setEncodeFunction(ad::lsb_encode);
		m_interface_widget->setDecodeFunction(ad::lsb_decode);
		setCentralWidget(m_interface_widget);
	});

	const QAction *about_action = m_main_menu->addAction("About");
	connect(about_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_about_widget);
	});

	setCentralWidget(m_interface_widget);
	m_interface_widget->setEncodeFunction(&gr::lsb_encode);
	m_interface_widget->setDecodeFunction(&gr::lsb_decode);
	m_interface_widget->m_is_audio = false;
	centralWidget()->setParent(nullptr);
	setCentralWidget(m_about_widget);

	setMenuBar(m_main_menu);

	show();
}