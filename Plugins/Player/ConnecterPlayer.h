// Author: Kang Lin <kl222@126.com>

#ifndef CONNETERPLAYER_H
#define CONNETERPLAYER_H

#include "ConnecterThread.h"
#include "ParameterPlayer.h"

class CConneterPlayer : public CConnecterThread
{
    Q_OBJECT

public:
    explicit CConneterPlayer(CPluginClient *plugin);
    virtual ~CConneterPlayer();

    // CConnecter interface
public:
    virtual qint16 Version() override;
    // CConnecterConnect interface
    virtual CConnect *InstanceConnect() override;

private:
    virtual QDialog *OnOpenDialogSettings(QWidget *parent) override;

private:
    CParameterPlayer m_Parameters;
};

#endif // CONNETERPLAYER_H