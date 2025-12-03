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
	void setDecodeFunction(QString (*f)(QString)) { m_decode_function = f; };

	bool m_is_audio;

private slots:
	void chooseFile(bool encode, bool audio);
	void chooseOutputDirectory();

private:
	void createEncodeGroupBox();
	void createDecodeGroupBox();

	QImage (*m_encode_function)(QString, QString);
	QGroupBox *m_encode_group_box;
	QString m_encode_file;
	QString m_output_directory;
	QString m_encode_text;
	QImage m_encoded_image;

	QString (*m_decode_function)(QString);
	QGroupBox *m_decode_group_box;
	QString m_decode_file;
	QString m_decoded_text;
};

#endif // HIDDENBYTES_INTERFACE_WIDGET_H
