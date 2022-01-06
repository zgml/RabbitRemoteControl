// Author: Kang Lin <kl222@126.com>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTabWidget>
#include <QActionGroup>
#include <QToolButton>
#include <QSpinBox>
#include <QDockWidget>
#include <QSystemTrayIcon>

#include "ViewTable.h"
#include "ManageConnecter.h"
#include "RabbitRecentMenu.h"
#include "ParameterApp.h"
#include "FavoriteView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CFrmFullScreenToolBar;

class MainWindow : public QMainWindow, CManageConnecter::Handle
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

Q_SIGNALS:
    void sigFullScreen();
    void sigShowNormal();
    
private Q_SLOTS:
    void on_actionExit_E_triggered();
    void on_actionAbout_A_triggered();
    void on_actionUpdate_U_triggered();
    
    void on_actionOpenStyle_O_triggered();
    void on_actionDefaultStyle_D_triggered();

    void on_actionSend_ctl_alt_del_triggered();

    ///////// Connect ///////// 
    void slotUpdateParameters(CConnecter* pConnecter);
    void on_actionClone_triggered();
    void on_actionOpen_O_triggered();
    void slotOpenFile(const QString& szFile, bool bOpenSettings = false);
    void slotConnect();
    void slotConnected();
private:
    int Connect(CConnecter* p, bool set, QString szFile = QString());
    int LoadConnectLasterClose();
    int SaveConnectLasterClose();
public:
    virtual int onProcess(const QString &id, CPluginViewer *pFactory) override;
private:
    CManageConnecter m_ManageConnecter;
    QMap<CConnecter*, QString> m_ConfigureFiles;
    QVector<CConnecter*> m_Connecters;
    
    ///////// Disconnect /////////
private Q_SLOTS:
    void on_actionDisconnect_D_triggered();
    void slotCloseView(const QWidget* pView);    
    void slotDisconnected();
    void slotError(const int nError, const QString &szInfo);
    
    /*!
     * \brief Show information
     * \param szInfo
     * \see CConnecter::sigInformation()
     */
    void slotInformation(const QString& szInfo);
    void slotUpdateName(const QString& szName);
    
    void on_actionShow_TabBar_B_triggered();
    void slotShowTabBar(bool bShow);

    void on_actionScreenshot_triggered();
    void on_actionSettings_triggered();
    void on_actionCurrent_connect_parameters_triggered();
    void slotShortCut();

protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

    ///////// UI ///////// 
private:
    Ui::MainWindow *ui;
    CView* m_pView;
    QActionGroup* m_pGBView;
    
    ///////// Full screen ///////// 
private:
    CFrmFullScreenToolBar* m_pFullScreenToolBar;
    friend CFrmFullScreenToolBar;
private Q_SLOTS:
    void on_actionFull_screen_F_triggered();
    void on_actionToolBar_T_triggered(bool checked);
    
    ///////// Zoom ///////// 
private:
    QToolButton* m_ptbZoom;
    QSpinBox* m_psbZoomFactor;
private Q_SLOTS:
    void on_actionZoom_window_to_remote_desktop_triggered();
    void on_actionOriginal_O_changed();
    void on_actionOriginal_O_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void slotZoomFactor(int v);
    void on_actionZoomToWindow_Z_triggered();
    void on_actionKeep_aspect_ration_to_windows_K_toggled(bool arg1);
    void slotAdaptWindows(const CFrmViewer::ADAPT_WINDOWS aw);
    
    ///////// Recent open ///////// 
private:
    RabbitCommon::CRecentMenu* m_pRecentMenu;
    
    ///////// Favorite //////////
private:
    QDockWidget* m_pFavoriteDockWidget;
    CFavoriteView* m_pFavoriteView;
private Q_SLOTS:
    void on_actionAdd_to_favorite_triggered();
    void slotDockWidgetFavoriteVisibilityChanged(bool visible);
    void on_actionFavorites_triggered();
    
public:
    CParameterApp m_Parameter;

    ///////// Drop //////////
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
private:
    QPoint m_DragStartPosition;

private Q_SLOTS:
    void slotSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void slotSystemTrayIconTypeChanged();
private:
    QSharedPointer<QSystemTrayIcon> m_TrayIcon;
};

#endif // MAINWINDOW_H
