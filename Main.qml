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
        Label {
            id: displayLabel
            text: user.name
        }

        TextField {
            onEditingFinished: user.name = text
        }
    }

}
