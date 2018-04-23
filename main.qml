import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    width: 300
    height: 300
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}

