//
// Created by stek on 16.11.2025.
//

#include "interface_widget.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>


InterfaceWidget::InterfaceWidget(QWidget *parent) :
	QWidget(parent), m_encode_text(""), m_decoded_text(""), m_output_directory("") {
	QGridLayout *layout = new QGridLayout(this);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);

	createEncodeGroupBox();
	createDecodeGroupBox();

	layout->addWidget(m_encode_group_box, 0, 0);
	layout->addWidget(m_decode_group_box, 0, 1);
}


void InterfaceWidget::createEncodeGroupBox() {
	m_encode_group_box = new QGroupBox("Encode", this);
	QVBoxLayout *encode_layout = new QVBoxLayout(m_encode_group_box);

	QLabel *encode_file_label = new QLabel(m_encode_group_box);
	encode_file_label->setText(m_encode_file);
	encode_file_label->setAlignment(Qt::AlignLeft);

	QPushButton *encode_file_button = new QPushButton("Choose a file to encode text in", m_encode_group_box);
	encode_file_label->setBuddy(encode_file_button);
	connect(encode_file_button, &QPushButton::clicked, this, [this, encode_file_label]() -> void {
		chooseFile(true);
		encode_file_label->setText(m_encode_file);
	});
	encode_layout->addWidget(encode_file_button);
	encode_layout->addWidget(encode_file_label);

	QLabel *output_dir_label = new QLabel(m_encode_group_box);
	output_dir_label->setText(m_output_directory);
	output_dir_label->setAlignment(Qt::AlignLeft);

	QPushButton *output_dir_button = new QPushButton("Choose the output directory", m_encode_group_box);
	output_dir_label->setBuddy(output_dir_button);
	connect(output_dir_button, &QPushButton::clicked, this, [this, output_dir_label]() -> void {
		chooseOutputDirectory();
		output_dir_label->setText(m_output_directory);
	});
	encode_layout->addWidget(output_dir_button);
	encode_layout->addWidget(output_dir_label);

	QLineEdit *text_input = new QLineEdit(m_encode_group_box);
	text_input->setPlaceholderText("Enter message to encode");
	connect(text_input, &QLineEdit::editingFinished, this,
			[this, text_input, encode_file_label]() -> void { m_encode_text = text_input->text(); });
	encode_layout->addWidget(text_input);

	QPushButton *encode_button = new QPushButton("Encode", m_encode_group_box);
	encode_layout->addWidget(encode_button);
	connect(encode_button, &QPushButton::clicked, this, [this]() -> void {
		m_encoded_image = m_encode_function(m_encode_file, m_encode_text);
		if (!m_encoded_image.save(m_output_directory + "/res.png")) {
			throw std::runtime_error("Failed to save image");
		}
	});

	encode_layout->addStretch();
}


void InterfaceWidget::createDecodeGroupBox() {
	m_decode_group_box = new QGroupBox("Decode", this);
	QVBoxLayout *decode_layout = new QVBoxLayout(m_decode_group_box);

	QLabel *decode_file_label = new QLabel(m_encode_group_box);
	decode_file_label->setText(m_decode_file);
	decode_file_label->setAlignment(Qt::AlignLeft);

	QPushButton *decode_file_button = new QPushButton("Choose a file to decode", m_encode_group_box);
	decode_file_label->setBuddy(decode_file_button);
	connect(decode_file_button, &QPushButton::clicked, this, [this, decode_file_label]() -> void {
		chooseFile(false);
		decode_file_label->setText(m_decode_file);
	});
	decode_layout->addWidget(decode_file_button);
	decode_layout->addWidget(decode_file_label);

	QTextEdit *text_output = new QTextEdit(m_decode_group_box);
	text_output->setReadOnly(true);
	text_output->setPlaceholderText("Decoded text");

	QPushButton *decode_button = new QPushButton("Decode", m_decode_group_box);
	connect(decode_button, &QPushButton::clicked, this,
			[text_output]() -> void { text_output->setText("Functionality under construction"); });
	decode_layout->addWidget(decode_button);
	decode_layout->addWidget(text_output);

	decode_layout->addStretch();
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
