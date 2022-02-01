#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CommandClass.h"

#include <QDialog>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <vector>
/*
 * Dylan Nasution
 * CS3307A
 */
class CommandGUI: public QDialog
{
	Q_OBJECT
	
	public: 
		CommandGUI();

	private slots:
        void handleButton();
		void historyItemClicked(QListWidgetItem* item);

	private:
		void createCommandHorizontalBox();
		void createOutputGridBox();
		void createHistoryGridBox();

		QGroupBox *commandHorizontalBox;
		QGroupBox *outputGridBox;
		QGroupBox *historyGridBox;

		QTextEdit *outputText;
		QPushButton *button;
		QLabel *commandLabel;
		QLabel *statusLabel;
		QLineEdit *commandEditor;
		QListWidget *historyList;

		QGridLayout *gridLayout;
		QGridLayout *historyLayout;
};

#endif // MAINWINDOW_H
