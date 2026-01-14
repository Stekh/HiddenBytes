//
// Created by stek on 5.11.2025.
//

#include <QLabel>
#include <QVBoxLayout>

#include "about_widget.h"

AboutWidget::AboutWidget(QWidget *parent) :
	QWidget(parent) {
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setDirection(QBoxLayout::TopToBottom);
	layout->setSpacing(50);
	setLayout(layout);

	QLabel *title = new QLabel(this);
	title->setText(
			"<h1>About HiddenBytes</h1>\n<small><a href='https://github.com/Stekh/HiddenBytes'>GitHub repository</small>");
	title->setAlignment(Qt::AlignCenter);
	title->setOpenExternalLinks(true);
	title->setMinimumWidth(width() - width() / 10);
	layout->addWidget(title, 0, Qt::AlignCenter | Qt::AlignTop);

	QLabel *desc = new QLabel(this);
	desc->setText(
			"<p>HiddenBytes is a simple GUI application made to showcase a few select steganography algorithms. It is capable of both encoding and decoding hidden messages in both graphics and audio files. Further encryption of such messages is not supported hovewver - it's not strictly a part of steganography and was as such deemed out of scope for the project. You are however welcome to use any outside tools of your liking for such purposes.");
	desc->setAlignment(Qt::AlignCenter);
	desc->setWordWrap(true);
	desc->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(desc, 0, Qt::AlignCenter | Qt::AlignTop);

	QLabel *authors = new QLabel(this);
	authors->setText("<h2>Authors:</h2>\n - <a href='https://github.com/Stekh'>Stekh</a><br> - <a href='https://github.com/inzwl'>inzwl</a>");
	authors->setAlignment(Qt::AlignCenter);
	authors->setOpenExternalLinks(true);
	layout->addWidget(authors, 0, Qt::AlignCenter | Qt::AlignTop);

	QLabel *libs = new QLabel(this);
	libs->setText(
			"<h2>Built using:</h2>\n<big><a href='https://www.qt.io/'>Qt6<a/></big> - licensed under the <a href='https://www.gnu.org/licenses/lgpl-3.0.html'>LGPL version 3</a> license");
	libs->setAlignment(Qt::AlignCenter);
	libs->setOpenExternalLinks(true);
	layout->addWidget(libs, 0, Qt::AlignCenter | Qt::AlignTop);

	layout->addStretch();

	show();
}