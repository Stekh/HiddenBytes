//
// Created by stek on 5.11.2025.
//

#include <QLabel>
#include <QVBoxLayout>

#include "about_widget.h"

AboutWidget::AboutWidget(QWidget *parent) {
	m_widget = new QWidget(parent);
	QVBoxLayout *layout = new QVBoxLayout(m_widget);

	QLabel *label = new QLabel(m_widget);
	label->setText("About page under construction");

	layout->addWidget(label, 0, Qt::AlignCenter);
	m_widget->setLayout(layout);
	m_widget->move(parent->width() / 2, parent->height() / 2);

	m_widget->show();
}
