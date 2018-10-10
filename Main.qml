import QtQuick 2.7
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    width: 500
    height: 500
    visible: true

    ColumnLayout {
        anchors.centerIn: parent
        RowLayout {
            Layout.fillWidth: true
            Label { text: "User name"; }
            Label { text: user.name }
        }

        RowLayout {
            Layout.fillWidth: true
            Label { text: "Edit user name" }
            TextField { onEditingFinished: user.name = text }
        }

        RowLayout {
            Layout.fillWidth: true
            Label { text: "Signal value" }
            TextField {
                id: signalValueTextField
                readOnly: true
            }
        }

        Connections {
            target: user
            onNameChanged: signalValueTextField.text = name
        }
    }

}
