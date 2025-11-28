//
// Created by stek on 16.11.2025.
//

#ifndef HIDDENBYTES_INTERFACE_WIDGET_H
#define HIDDENBYTES_INTERFACE_WIDGET_H

#include <QGroupBox>
#include <QString>
#include <QWidget>

class InterfaceWidget final : public QWidget {
	Q_OBJECT

public:
	explicit InterfaceWidget(QWidget *parent);
	void setEncodeFunction(QImage (*f)(QString, QString)) { m_encode_function = f; };

private slots:
	void chooseFile(bool encode);
	void chooseOutputDirectory();

private:
	void createEncodeGroupBox();
	void createDecodeGroupBox();

	void encode();
	QImage (*m_encode_function)(QString, QString);

	void decode();

	QGroupBox *m_encode_group_box;
	QString m_encode_file;
	QString m_output_directory;
	QString m_encode_text;
	QImage m_encoded_image;

	QGroupBox *m_decode_group_box;
	QString m_decode_file;
	QString m_decoded_text;
};

#endif // HIDDENBYTES_INTERFACE_WIDGET_H
