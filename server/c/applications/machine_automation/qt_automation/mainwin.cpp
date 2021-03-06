#include "mainwin.h"

#include <sequanto/macros.h>
#include <iostream>
#include <QtGui>
#include <QNetworkInterface>

MainWin::MainWin ( QWidget * _parent )
   : QMainWindow ( _parent )
{
   ui.setupUi ( this );
   for ( int row = 0; row < ui.m_tableWidget->rowCount(); row++ )
   {
      for ( int column = 0; column < ui.m_tableWidget->columnCount(); column++ )
      {
         QTableWidgetItem * item = ui.m_tableWidget->item(row,column);
         if ( item == NULL )
         {
            ui.m_tableWidget->setItem(row, column, new QTableWidgetItem(QString("%1,%2").arg(row).arg(column)) );
         }
         else
         {
            item->setText(QString("%1,%2").arg(row).arg(column) );
         }
      }
      ui.m_tableWidget->setColumnHidden ( 1, true );
   }
   QString text("Listening on:\n");
   QHostAddress address;
   foreach(address, QNetworkInterface::allAddresses())
   {
       text += address.toString();
       text += "\n";
   }
   ui.m_listeningOn->setText(text);
}

void MainWin::on_exitButton_clicked()
{
   this->close();
}

void MainWin::on_m_loadFileButton_clicked()
{
   QMessageBox * messageBox = new QMessageBox( QMessageBox::Information, "About to open file", "I am not going to ask you which file to open", QMessageBox::Ok );
   messageBox->setModal ( true );
   messageBox->show();
   messageBox->deleteLater();

   QString filename = QFileDialog::getOpenFileName( this, "Open a file..." );
}

void MainWin::on_actionExit_activated()
{
   this->close();
}

void MainWin::on_actionAdd_some_items_activated()
{
   int count = 0;
   for ( int i = 0; i < 5; i++ )
   {
      ui.listView->addItem ( QString("Item %1").arg(count + i) );
   }
}

void MainWin::on_listView_currentItemChanged( QListWidgetItem * _current, QListWidgetItem * _previous )
{
   SQ_UNUSED_PARAMETER(_previous);
   
   QString text ( _current->text() );
      qDebug() << text;

   //std::cout << _current->text().toStdString() << std::endl;
}

void MainWin::on_m_updateButton_clicked()
{
  QPoint windowTopLeft ( this->geometry().topLeft() );
  ui.m_windowGlobalPosition->setText ( QString("Global window pos: %1, %2").arg(windowTopLeft.x()).arg(windowTopLeft.y()) );
  
  QPoint pos = ui.m_updateButton->mapTo ( this, ui.m_updateButton->pos() );
  ui.m_buttonPositionMappedToWindow->setText ( QString("Button pos mapped to window: %1, %2").arg(pos.x()).arg(pos.y()) );

  pos = ui.m_updateButton->mapToGlobal(QPoint(0,0));
  ui.m_buttonPositionMappedToGlobal->setText ( QString("Button pos mapped to global: %1, %2").arg(pos.x()).arg(pos.y()) );
  
  pos -= windowTopLeft;
  ui.m_buttonPositionTranslated->setText ( QString("Button pos (translated): %1, %2").arg(pos.x()).arg(pos.y()) );
}

void MainWin::on_m_addLabel_clicked()
{
   QString label = QString("Button %1").arg(ui.m_labelList->rowCount());
   QPushButton * button = new QPushButton(label);
   button->setObjectName ( QString("m_button%1").arg(ui.m_labelList->rowCount()) );
   ui.m_labelList->addRow ( QString("%1").arg(ui.m_labelList->rowCount()), button );
}

void MainWin::on_m_changeColor_clicked()
{
   QPalette palette ( this->palette() );
   QColor current = palette.color ( QPalette::Background );
   if ( current == QColor("blue") )
   {
      QLinearGradient gradient ( (qreal) width() / 2, 0, (qreal) width() / 2, height() );
      gradient.setColorAt(0, QColor("red") );
      gradient.setColorAt(1, QColor("yellow") );

      palette.setBrush ( QPalette::Background, QBrush(gradient) );
   }
   else
   {
      palette.setColor ( QPalette::Background, QColor("blue") );
   }
   this->setPalette ( palette );
}

extern "C" void close_connection();
extern "C" void open_connection();

class CloseConnectionTask : public QRunnable
{
  void run()
  {
    close_connection();
  }
};

void MainWin::on_m_closeConnection_clicked()
{
  qDebug() << "Close";

  QThreadPool::globalInstance()->start ( new CloseConnectionTask() );
    
  ui.m_closeConnection->setEnabled(false);
  ui.m_openConnection->setEnabled(true);
}

void MainWin::on_m_openConnection_clicked()
{
  qDebug() << "Open";

  open_connection();
  
  ui.m_openConnection->setEnabled(false);
  ui.m_closeConnection->setEnabled(true);
}
