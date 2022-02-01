#include "mainwindow.h"
#include "CommandClass.h"

#include <QTextEdit>
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QString>
#include <QLineEdit>
#include <QVector>

/*
 * Dylan Nasution
 * CS3307A
 * 251109643
 */

// vector for storing CommandClass objects
QVector<CommandClass> cmdVector;

CommandGUI::CommandGUI()
{	
	// connect button to handler function
	button = new QPushButton(tr("Execute"));
	connect(button, &QPushButton::released, this, &CommandGUI::handleButton);

	// connect history list to handler function
	historyList = new QListWidget;
	connect(historyList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(historyItemClicked(QListWidgetItem*)));
	
	// calls functions to create the sections in the GUI
	createCommandHorizontalBox();
	createOutputGridBox();
	createHistoryGridBox();

	// sets the layout and adds the sections as widgets
	
	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(commandHorizontalBox);
	mainLayout->addWidget(outputGridBox);
	mainLayout->addWidget(historyGridBox);

	setLayout(mainLayout);

	setWindowTitle(tr("CommandGUI"));
}

void CommandGUI::createCommandHorizontalBox()
{
	// this is for the user input/command section of the GUI
	
	commandHorizontalBox = new QGroupBox();
	QHBoxLayout *layout = new QHBoxLayout;
	
	// command label set
	commandLabel = new QLabel(tr("Command: "));
	layout->addWidget(commandLabel);

	// this is where the user types their command
	commandEditor = new QLineEdit;
	layout->addWidget(commandEditor);	

	// put the button in the layout
	layout->addWidget(button);

    	commandHorizontalBox->setLayout(layout);
}

void CommandGUI::createOutputGridBox()
{
	// this is for the ouput section of the GUI

	outputGridBox = new QGroupBox(tr("Output"));
	gridLayout = new QGridLayout;
	
	// read only text box for output
        outputText = new QTextEdit;
        outputText->setReadOnly(true);
        gridLayout->addWidget(outputText);

	// exit status label
        statusLabel = new QLabel(tr("Exit Status: "));
        gridLayout->addWidget(statusLabel);

	outputGridBox->setLayout(gridLayout);	
}

void CommandGUI::createHistoryGridBox()
{
	// this is for the history section of the GUI
	
	historyGridBox = new QGroupBox(tr("History"));
        historyLayout = new QGridLayout;
	
	historyLayout->addWidget(historyList);
	
	historyGridBox->setLayout(historyLayout);
}


void CommandGUI::handleButton()
{
	// check if command input box empty
	if (commandEditor->text().isEmpty()) {
		outputText->setPlainText("Nothing was entered");
		return;
	}

	// invode CommandClass::execute() 
	std::string command = commandEditor->text().toStdString();
	CommandClass cmd(command);
	cmd.execute();

	// add to vector
	cmdVector.append(cmd);
	
	// convert from std::string to QString then display result
	QString qstrResult = QString::fromStdString(cmd.get_result());
	outputText->setPlainText(qstrResult);

	// display return code
	statusLabel->setText(tr("Exit Status: %1").arg(cmd.get_return_code()));
	
	// add command with return code to history
	std::string commandLog = cmd.get_command_text() + " (" + std::to_string(cmd.get_return_code()) + ")"; 
	QString qstrHistory = QString::fromStdString(commandLog);
	historyList->addItem(new QListWidgetItem(tr("%1").arg(qstrHistory), historyList));
}

void CommandGUI::historyItemClicked(QListWidgetItem *item)
{
	// get row the item user selected in historyList
	int row = historyList->row(item);

	// convert from std::string to QString then display result
        QString qstrResult = QString::fromStdString(cmdVector.at(row).get_result());
        outputText->setPlainText(qstrResult);
	
	// display return code
        statusLabel->setText(tr("Exit Status: %1").arg(cmdVector.at(row).get_return_code()));
}
