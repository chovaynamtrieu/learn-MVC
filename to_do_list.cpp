#include "to_do_list.h"
#include <QModelIndex>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>

ToDoItem::ToDoItem(const QString &content, const bool &isDone)
{
    m_content = content;
    m_isDone = isDone;
}

QString ToDoItem::content() const
{
    return m_content;
}

bool ToDoItem::isDone() const
{
    return m_isDone;
}

bool ToDoItem::setContent(const QString &content)
{
    m_content = content;
    return true;
}

bool ToDoItem::setIsDone(const bool &isDone)
{
    m_isDone = isDone;
    return true;
}

ToDoList::ToDoList(QObject *parent):
    QAbstractListModel(parent)
{
    m_ToDoList.append(ToDoItem("abs", false));
    m_ToDoList.append(ToDoItem("xyz", true));
}

int ToDoList::rowCount(const QModelIndex &parent) const
{
    return m_ToDoList.length();
}

QVariant ToDoList::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    const ToDoItem &item = m_ToDoList[index.row()];
    switch (role) {
    case ContentRole:
        return item.content();
    case IsDoneRole:
        return item.isDone();
    default:
        return QVariant();
    }
}

bool ToDoList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()){
        return false;
    }

    ToDoItem &item = m_ToDoList[index.row()];
    switch (role) {
    case ContentRole:
        return item.setContent(value.toString());
    case IsDoneRole:
        return item.setIsDone(value.toBool());
    default:
        return false;
    }
}

void ToDoList::addItem()
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    m_ToDoList.append(ToDoItem("", true));
    //qDebug() << rowCount(QModelIndex());
    endInsertRows();
}

void ToDoList::removeItem(const int &index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_ToDoList.remove(index, 1);
    endRemoveRows();
}

QHash<int, QByteArray> ToDoList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ContentRole] = "noidung";
    roles[IsDoneRole] = "trangthai";
    return roles;
}

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().canConvert<int>()) {
        int value = qvariant_cast<int>(index.data());

        if (option.state & QStyle::State_Selected){
            qDebug() << "void MyDelegate::paint : State_Selected";
            painter->fillRect(option.rect, option.palette.highlight());
        }
        QString text = QString::number(value);
        painter->drawText(option.rect, Qt::AlignCenter, text);

//        StarRating starRating = qvariant_cast<StarRating>(index.data());

//        if (option.state & QStyle::State_Selected){
//            qDebug() << "void MyDelegate::paint : State_Selected";
//            painter->fillRect(option.rect, option.palette.highlight());
//        }

//        starRating.paint(painter, option.rect, option.palette,
//                         StarRating::EditMode::ReadOnly);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
        qDebug() << "void MyDelegate::paint : Default";
    }
}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //    QSpinBox *editor = new QSpinBox(parent);
    //    editor->setMinimum(0);
    //    editor->setMaximum(100);

    QSlider *editor = new QSlider(Qt::Horizontal, parent);
    editor->setMinimum(0);
    editor->setMaximum(200);
    return editor;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //    int value = index.model()->data(index, Qt::EditRole).toInt();

    //    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    //    spinbox->setValue(value);

    int value = index.model()->data(index, Qt::EditRole).toInt();

    QSlider *slider = static_cast<QSlider*>(editor);
    slider->setValue(value);
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
//    spinbox->interpretText();
//    int value = spinbox->value();
//    model->setData(index, value, Qt::EditRole);

    QSlider *slider = static_cast<QSlider*>(editor);
    //slider->inter();
    int value = slider->value();
    model->setData(index, value, Qt::EditRole);
}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;
    int sliderWidth = rect.width() / 2;
    int sliderHeight = rect.height();
    int sliderX = rect.x() + rect.width() / 2;
    int sliderY = rect.y();
    editor->setGeometry(sliderX, sliderY, sliderWidth, sliderHeight);
    //editor->setGeometry(option.rect);
}


