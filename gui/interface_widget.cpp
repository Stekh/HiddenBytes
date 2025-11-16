//
// Created by stek on 16.11.2025.
//

#include "interface_widget.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>

InterfaceWidget::InterfaceWidget(QWidget *parent) :
	QWidget(parent) {
	QGridLayout *layout = new QGridLayout(this);
	setLayout(layout);

	m_encode_group_box = new QGroupBox("Encode", this);
	QVBoxLayout *encode_layout = new QVBoxLayout(m_encode_group_box);
	m_encode_group_box->setLayout(encode_layout);
	QPushButton *encode_file_button = new QPushButton("Choose a file to encode in", m_encode_group_box);
	connect(encode_file_button, SIGNAL(clicked()), this, SLOT(&InterfaceWidget::chooseFile(True)));
	encode_layout->addWidget(encode_file_button);
	QPushButton *output_dir_button = new QPushButton("Choose a file to encode in", m_encode_group_box);
	connect(output_dir_button, SIGNAL(clicked()), this, SLOT(&InterfaceWidget::chooseOutputDirectory()));
	encode_layout->addWidget(output_dir_button);

	m_decode_group_box = new QGroupBox("Decode", this);
	QVBoxLayout *decode_layout = new QVBoxLayout(m_encode_group_box);
	m_decode_group_box->setLayout(decode_layout);
	QPushButton *decode_file_button = new QPushButton("Choose a file to encode in", m_encode_group_box);
	connect(decode_file_button, SIGNAL(clicked()), this, SLOT(&InterfaceWidget::chooseFile(False)));
	encode_layout->addWidget(decode_file_button);

	layout->addWidget(m_encode_group_box, 0, 0);
	layout->addWidget(m_decode_group_box, 0, 1);
}


void InterfaceWidget::chooseFile(const bool encode) {
	QFileDialog file_dialog;
	file_dialog.setFileMode(QFileDialog::ExistingFile);
	file_dialog.setWindowTitle(encode ? "Choose a file to encode" : "Choose a file to decode");
	file_dialog.setDirectory(QDir::homePath());
	file_dialog.setNameFilter("Image files (*.jpg *.png)");

	if (file_dialog.exec() == QDialog::Accepted) {
		encode ? m_encode_file = file_dialog.selectedFiles()[0] : m_decode_file = file_dialog.selectedFiles()[0];
	}
}


void InterfaceWidget::chooseOutputDirectory() {
	QFileDialog file_dialog;
	file_dialog.setFileMode(QFileDialog::Directory);
	file_dialog.setWindowTitle("Choose the output directory");
	file_dialog.setDirectory(QDir::homePath());

	if (file_dialog.exec() == QDialog::Accepted) {
		m_output_directory = file_dialog.selectedFiles()[0];
	}
}
