#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QPainter>

class ToDoItem
{
public:
    explicit ToDoItem(const QString &content, const bool &isDone);
    QString content() const;
    bool isDone() const;
    bool setContent(const QString &content);
    bool setIsDone(const bool &isDone);

private:
    QString m_content;
    bool m_isDone;
};

class ToDoList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ToDoList(QObject *parent = nullptr);

    enum ToDoItemRoles{
        ContentRole = Qt::UserRole + 1,
        IsDoneRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Q_INVOKABLE void addItem();
    Q_INVOKABLE void removeItem(const int &index);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ToDoItem> m_ToDoList;
};

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // TODOLIST_H
