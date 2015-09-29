#include "avatargrid.h"

AvatarGrid::AvatarGrid(const QString &userPath, QWidget *parent)
    : QTableWidget(parent)
{
    m_user = new DBusAccountUser(userPath, this);
    connect(m_user, &DBusAccountUser::IconFileChanged, this, &AvatarGrid::onIconFileChanged);

    m_buttonGroup = new QButtonGroup(this);
    connect(m_buttonGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onButtonToggled(QAbstractButton*,bool)));

    init();
}

void AvatarGrid::setAvatars(const QStringList &list)
{
    clearUp();

    int listCount = list.count();
    int rows = listCount / COLUMN_COUNT;
    rows += listCount % COLUMN_COUNT > 0 ? 1 : 0;

    setRowCount(rows);
    setColumnCount(COLUMN_COUNT);

    int listIndex = 0;
    for (int r = 0; r < rows; r ++){

        setRowHeight(r, ICON_SIZE);

        for (int c = 0; c < COLUMN_COUNT; c ++){
            if (listIndex >= listCount)
                break;

            QString iconName = list.at(listIndex ++);
            UserAvatar *icon = new UserAvatar(this, m_user->IsIconDeletable(iconName).value());
            icon->setFixedSize(ICON_SIZE, ICON_SIZE);
            icon->setIcon(iconName);
            connect(icon, &UserAvatar::clicked, this, &AvatarGrid::onIconPress);
            connect(icon, &UserAvatar::requestDelete, this, &AvatarGrid::onRequestDelete);
            setCellWidget(r, c, icon);  //set and delete old one
            m_buttonGroup->addButton(icon);

            QTableWidgetItem* item = new QTableWidgetItem();
            item->setFlags(Qt::NoItemFlags);
            setItem(r, c, item);
        }
    }

    setFixedSize(COLUMN_COUNT * ICON_SIZE, rows * ICON_SIZE);
}

void AvatarGrid::init()
{
    setAttribute(Qt::WA_TranslucentBackground);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setEditTriggers(NoEditTriggers);
    setDragDropMode(NoDragDrop);
    setSelectionMode(NoSelection);
    setAcceptDrops(false);
    setDragEnabled(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setShowGrid(false);
}

void AvatarGrid::clearUp()
{
    QList<QAbstractButton *> buttonList = m_buttonGroup->buttons();
    foreach (QAbstractButton * button, buttonList) {
        m_buttonGroup->removeButton(button);
    }

    int rowCount = this->rowCount();
    int columnCount = this->columnCount();
    for (int r = 0; r < rowCount; r ++){
        for (int c = 0; c < columnCount; c ++){
            setCellWidget(r, c, NULL);
        }
    }
}

void AvatarGrid::onIconPress()
{
    UserAvatar * icon = qobject_cast<UserAvatar *>(sender());
    if (icon){
        emit avatarSelected(icon->iconPath());
    }
}

void AvatarGrid::onRequestDelete()
{
    UserAvatar * icon = qobject_cast<UserAvatar *>(sender());
    if (icon && m_user->isValid()){
        m_user->DeleteIconFile(icon->iconPath());
    }
}

void AvatarGrid::onIconFileChanged()
{
    if (m_user->isValid()) {
        QList<QAbstractButton *> buttonList = m_buttonGroup->buttons();
        foreach (QAbstractButton * button, buttonList) {
            UserAvatar * avatar = qobject_cast<UserAvatar *>(button);
            if (avatar)
                avatar->setDeleteable(m_user->IsIconDeletable(avatar->iconPath()));
        }
    }
}

void AvatarGrid::onButtonToggled(QAbstractButton *button, bool checked)
{
    UserAvatar * icon = qobject_cast<UserAvatar *>(button);
    if (icon)
        icon->setSelected(checked);
}


