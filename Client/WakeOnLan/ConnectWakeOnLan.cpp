// Author: Kang Lin <kl222@126.com>

#include "ConnectWakeOnLan.h"
#include "ConnecterDesktopThread.h"

CConnectWakeOnLan::CConnectWakeOnLan(
    CConnecter *pConnecter, QObject *parent, bool bDirectConnection)
    : CConnect{pConnecter, parent, bDirectConnection}
    , m_pParameter(nullptr)
    , m_nRepeat(0)
    , m_tmStart(QTime::currentTime())
{
    m_pParameter = qobject_cast<CConnecterDesktopThread*>(pConnecter)->GetParameter();
    Q_ASSERT(m_pParameter);
}

void CConnectWakeOnLan::slotClipBoardChanged()
{
}

int CConnectWakeOnLan::SetConnecter(CConnecter *pConnecter)
{
    return 0;
}

int CConnectWakeOnLan::SetViewer(CFrmViewer *pView, bool bDirectConnection)
{
    return 0;
}

//! [Check parameters is validity]
CConnect::OnInitReturnValue CConnectWakeOnLan::OnInit()
{
    auto &wol = m_pParameter->m_Net.m_WakeOnLan;
    if(!wol.GetEnable() || !wol.CheckValidity())
        return OnInitReturnValue::Fail;

    m_tmStart = QTime::currentTime();
    return OnInitReturnValue::UseOnProcess;
}
//! [Check parameters is validity]

int CConnectWakeOnLan::OnClean()
{
    return 0;
}

/*!
 * \~chinese 插件连接的具体操作处理
 * \return
 *       \li >= 0: 继续。再次调用间隔时间，单位毫秒
 *       \li = -1: 停止
 *       \li < -1: 错误
 *
 * \~english Specific operation processing of plug-in connection
 * \return
 *       \li >= 0: continue, Interval call time (msec)
 *       \li = -1: stop
 *       \li < -1: error
 * \~
 * \see Connect() slotTimeOut()
*/
int CConnectWakeOnLan::OnProcess()
{
    int nRet = -1;
    auto &wol = m_pParameter->m_Net.m_WakeOnLan;

    do {
        if(m_tmStart.secsTo(QTime::currentTime()) >= wol.GetDelay()) break;
        if(wol.GetRepeat() > m_nRepeat++) break;
        m_Wol.SetBroadcastAddress(wol.GetBroadcastAddress());
        if(wol.GetPassword().isEmpty())
            m_Wol.SendMagicPacket(wol.GetMac());
        else
            m_Wol.SendSecureMagicPacket(wol.GetMac(), wol.GetPassword());
        return wol.GetInterval();
    } while(0);
    emit sigDisconnect();
    return nRet;
}
