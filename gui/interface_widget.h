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

private slots:
	void chooseFile(bool encode);
	void chooseOutputDirectory();

private:
	QGroupBox *m_encode_group_box;
	QString m_encode_file;
	QString m_output_directory;

	QGroupBox *m_decode_group_box;
	QString m_decode_file;
};

#endif //HIDDENBYTES_INTERFACE_WIDGET_H
