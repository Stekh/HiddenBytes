//
// Created by stek on 5.11.2025.
//

#include <QLabel>
#include <QVBoxLayout>

#include "about_widget.h"

AboutWidget::AboutWidget(QWidget *parent) :
	QWidget(parent) {
	QVBoxLayout *layout = new QVBoxLayout(this);

	QLabel *label = new QLabel(this);
	label->setText("About page under construction");

	layout->addWidget(label, 0, Qt::AlignCenter);
	setLayout(layout);

	show();
}
