#ifndef DATETIMEMODULE_H
#define DATETIMEMODULE_H

#include "moduleinterface.h"
#include "datetime.h"
#include "datetimework.h"
#include "datetimemodel.h"

class DatetimeModule : public QObject, public ModuleInterface
{
    Q_OBJECT

public:
    explicit DatetimeModule(FrameProxyInterface* frame, QObject* parent = 0);

    void initialize();
    void moduleActive();
    void moduleDeactive();
    void reset();
    ModuleWidget *moduleWidget();

    const QString name() const;

    void contentPopped(ContentWidget * const w);

public slots:
    void slotEditDatetime();
    void onAddTimezoneClick();
    void onChangeClick();
    void onSetTimezone(const Timezone& tz);

private:
    ~DatetimeModule();

private:
    DatetimeWork* m_work;
    DatetimeModel* m_model;
    Datetime* m_datetimeWidget;
    DateSettings* m_dateSettings;
    ChoseDialog* m_choseDlg;
};

#endif // DATETIMEMODULE_H