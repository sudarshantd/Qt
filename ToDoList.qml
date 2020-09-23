import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import ToDo 1.0

ColumnLayout{
    Frame {
        Layout.fillWidth: true
        ListView {
            implicitWidth: 250
            implicitHeight: 250
            clip: true
            anchors.fill:parent
            //        model: 100

            //        model: ListModel{
            //            ListElement{
            //                done: true
            //                description: "wash the car"
            //            }

            //            ListElement{
            //                done: false
            //                description: "fix the sink"
            //            }
            //        }

            model: ToDoModel {
                list: toDoList
            }

            delegate: RowLayout{
                width: parent.width
                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description
                    onEditingFinished: model.description = text
                    Layout.fillWidth: true
                }
            }
        }
    }

    RowLayout{
        Button{
            text: qsTr("Add new item")
            onClicked: toDoList.appendItem();
            Layout.fillWidth: true
        }

        Button{
            text: qsTr("Remove Completed")
            onClicked: toDoList.removeCompletedItems();
            Layout.fillWidth: true
        }
    }
}
