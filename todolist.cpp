#include "todolist.h"
#include <QDebug>

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    qDebug()<<__FILE__<<__FUNCTION__;
    mItems.append({true,QStringLiteral("Wash the car")});
    mItems.append({true,QStringLiteral("Fix the sink")});
}

QVector<ToDoItem> ToDoList::items() const
{
    qDebug()<<__FILE__<<__FUNCTION__;
    return mItems;
}

bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    //Update C++ list model with a changes done on HMI side called from setData of model
    qDebug()<<__FILE__<<__FUNCTION__;

    if(index < 0 || index >= mItems.size())
        return false;

    const ToDoItem &oldItem = mItems.at(index);
    //Below condiotion is to verify whether data is really changed? by comparing it with older data
    if(item.done == oldItem.done && item.description == oldItem.description)
        return false;
    mItems[index] = item; //Replace data at existing index, as per data changes done on HMI and gets model updated
    return true;
}

void ToDoList::appendItem()
{
    //This method is called on clicked on ADDNEWITEM button
    qDebug()<<__FILE__<<__FUNCTION__;
    emit preItemAppended();

    // Adding new item with initial value
    ToDoItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void ToDoList::removeCompletedItems()
{
    //This method is called on clicked on REMOVE COMPLETED button, Checked item are removed
    qDebug()<<__FILE__<<__FUNCTION__;
    for(int i =0; i <mItems.size();){
        if(mItems.at(i).done){
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        }else{
            ++i;
        }
    }
}
