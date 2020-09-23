#include "todomodel.h"

#include "todolist.h"
#include <QDebug>

ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
    qDebug()<<__FILE__<<__FUNCTION__;
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    qDebug()<<__FILE__<<__FUNCTION__;
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    qDebug()<<__FILE__<<__FUNCTION__<<"rowcount"<<mList->items().size();
    return mList->items().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    // Updates data from C++ todolist model to HMI
    qDebug()<<__FILE__<<__FUNCTION__<<"index"<<index<<"role"<<role;
    if (!index.isValid() || !mList)
        return QVariant();

    const ToDoItem item = mList->items().at(index.row());
    // FIXME: Implement me!
    switch (role) {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);

    }
    return QVariant();
}

bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //Update todolist model after changes done on hmi side
    qDebug()<<__FILE__<<__FUNCTION__;
    if(!mList)
        return false;

    //Created temp variable to store updated HMI value
    ToDoItem item = mList->items().at(index.row());
    switch (role) {
    case DoneRole:
        item.done = value.toBool();
        break;
    case DescriptionRole:
        item.description = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role); //To inform that model model changed
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    qDebug()<<__FILE__<<__FUNCTION__;
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    qDebug()<<__FILE__<<__FUNCTION__;
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

ToDoList *ToDoModel::list() const
{
    qDebug()<<__FILE__<<__FUNCTION__;
    return mList;
}

void ToDoModel::setList(ToDoList *list)
{
    qDebug()<<__FILE__<<__FUNCTION__;
    beginResetModel();
    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList,&ToDoList::preItemAppended, this,[=](){
            qDebug()<<__FILE__<<__FUNCTION__;
            //Row insertion operation
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(mList,&ToDoList::postItemAppended, this,[=](){
            qDebug()<<__FILE__<<__FUNCTION__;
            endInsertRows();
        });
        connect(mList,&ToDoList::preItemRemoved, this,[=](int index){
            qDebug()<<__FILE__<<__FUNCTION__;
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(mList,&ToDoList::postItemRemoved, this,[=](){
            qDebug()<<__FILE__<<__FUNCTION__;
            endRemoveRows();
        });
    }

    endResetModel();
}
