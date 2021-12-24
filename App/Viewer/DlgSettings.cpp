// Author: Kang Lin <kl222@126.com>

#include "DlgSettings.h"
#include "ui_DlgSettings.h"
#include "mainwindow.h"
#include "ManagePassword.h"

CDlgSettings::CDlgSettings(CParameterApp *pPara, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgSettings),
    m_pParameters(pPara)
{
    ui->setupUi(this);
        
    ui->cbShotRemoteDesktop->setChecked(m_pParameters->GetScreenShot());
    switch (m_pParameters->GetScreenShotEndAction()) {
    case CParameterApp::NoAction:
        ui->rbShotScreenNoAction->setChecked(true);
        break;
    case CParameterApp::OpenFile:
        ui->rbShotScreenOpenFile->setChecked(true);
        break;
    case CParameterApp::OpenFolder:
        ui->rbShotScreenOpenFolder->setChecked(true);
        break;    
    }
    
    ui->cbReciverShortCut->setChecked(m_pParameters->GetReceiveShortCut());
    ui->cbSaveMainWindowStatus->setChecked(m_pParameters->GetSaveMainWindowStatus());
    
    switch (m_pParameters->GetTabPosition()) {
    case QTabWidget::North:
        ui->rbNorth->setChecked(true);
        break;
    case QTabWidget::South:
        ui->rbSouth->setChecked(true);
        break;
    case QTabWidget::West:
        ui->rbWest->setChecked(true);
        break;
    case QTabWidget::East:
        ui->rbEast->setChecked(true);
        break;
    }
    
    ui->sbRecentMenuMaxCount->setValue(m_pParameters->GetRecentMenuMaxCount());
    
    ui->leEncryptKey->setText(CManagePassword::Instance()->GetPassword());
}

CDlgSettings::~CDlgSettings()
{
    delete ui;
}

void CDlgSettings::on_pbOk_clicked()
{
    if(!m_pParameters) return;
    
    m_pParameters->SetScreenShot(ui->cbShotRemoteDesktop->isChecked());
    
    if(ui->rbShotScreenNoAction->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::NoAction);
    if(ui->rbShotScreenOpenFile->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::OpenFile);
    if(ui->rbShotScreenOpenFolder->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::OpenFolder);
    
    m_pParameters->SetReceiveShortCut(ui->cbReciverShortCut->isChecked());
    m_pParameters->SetSaveMainWindowStatus(ui->cbSaveMainWindowStatus->isChecked());
    
    if(ui->rbNorth->isChecked()) m_pParameters->SetTabPosition(QTabWidget::North);
    if(ui->rbSouth->isChecked()) m_pParameters->SetTabPosition(QTabWidget::South);
    if(ui->rbEast->isChecked()) m_pParameters->SetTabPosition(QTabWidget::East);
    if(ui->rbWest->isChecked()) m_pParameters->SetTabPosition(QTabWidget::West);
    
    m_pParameters->SetRecentMenuMaxCount(ui->sbRecentMenuMaxCount->value());
    
    CManagePassword::Instance()->SetPassword(ui->leEncryptKey->text());
    
    accept();
}

void CDlgSettings::on_pbNo_clicked()
{
    reject();
}