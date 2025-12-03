//
// Created by stek on 5.11.2025.
//

#include <QMenuBar>

#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
	m_main_menu = new QMenuBar(this);
	m_about_widget = new AboutWidget(this);
	m_interface_widget = new InterfaceWidget(this);

	m_graphics_menu = new QMenu("Graphics", m_main_menu);
	const QAction *graphics_LSB_action = m_graphics_menu->addAction("LSB");
	const QAction *graphics_alg2_action = m_graphics_menu->addAction("Alg 2");
	const QAction *graphics_alg3_action = m_graphics_menu->addAction("Alg 3");
	m_main_menu->addMenu(m_graphics_menu);

	connect(graphics_LSB_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});
	connect(graphics_alg2_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});
	connect(graphics_alg3_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});

	m_audio_menu = new QMenu("Audio", m_main_menu);
	const QAction *audio_alg1_action = m_audio_menu->addAction("Alg 1");
	const QAction *audio_alg2_action = m_audio_menu->addAction("Alg 2");
	const QAction *audio_alg3_action = m_audio_menu->addAction("Alg 3");
	m_main_menu->addMenu(m_audio_menu);

	connect(audio_alg1_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});
	connect(audio_alg2_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});
	connect(audio_alg3_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_interface_widget);
	});

	const QAction *about_action = m_main_menu->addAction("About");
	connect(about_action, &QAction::triggered, this, [this]() -> void {
		centralWidget()->setParent(nullptr);
		setCentralWidget(m_about_widget);
	});

	setCentralWidget(m_about_widget);
	centralWidget()->setParent(nullptr);
	setCentralWidget(m_interface_widget);
	setMenuBar(m_main_menu);

	show();
}
