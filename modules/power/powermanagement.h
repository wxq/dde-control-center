#ifndef POWERMANAGEMENT
#define POWERMANAGEMENT

#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include <libdui/dtextbutton.h>
#include <libdui/dseparatorhorizontal.h>

#include "moduleheader.h"
DUI_USE_NAMESPACE

class PowerManagement:public QFrame {
    Q_OBJECT
public:
    PowerManagement(QWidget *parent=0);
    ~PowerManagement();

    bool m_batteryIsPresent;
    bool m_onBattery;
    double m_batteryPercentage;
public slots:
    void reset();
    void reset(bool clicked);
    void batteryReservedControl(bool batteryIsPresent);
    void setElectricQuantity(double electricQuantity);
    void initConnection();
signals:
    void Reset();
private:
    int m_contentHeight;
    int m_bgContentHeight;
    QString headTitle;
    // top header
    QVBoxLayout* topHeaderLayout;
    ModuleHeader* m_topHeaderLine;
    QLabel* m_powerManagerViewLabel;
    QLabel* m_powerManagerLabel;
    QLabel* m_shortSeparatorLine;
    QLabel* m_powerPercentageLabel;
    QHBoxLayout* m_powerManagerLayout;
    DTextButton* m_powerResetButton;
    DSeparatorHorizontal * m_firstHSeparator;
};
#endif // powermanager
