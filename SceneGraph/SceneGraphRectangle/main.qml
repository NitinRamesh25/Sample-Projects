import QtQuick 2.12
import QtQuick.Window 2.12

import SimpleMaterial 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 320
        height: 480
        color: "black"

    //! [1] //! [2]

        Column {
            anchors.fill: parent

            SimpleMaterialItem {
                width: parent.width;
                height: parent.height / 3;
                color: "steelblue"
            }

            SimpleMaterialItem {
                width: parent.width;
                height: parent.height / 3;
                color: "darkorchid"
            }

             SimpleMaterialItem {
                width: parent.width;
                height: parent.height / 3;
                color: "springgreen"
            }
        }


    //! [2] //! [3]
        Rectangle {
            color: Qt.rgba(0, 0, 0, 0.8)
            radius: 10
            antialiasing: true
            border.width: 1
            border.color: "black"
            anchors.fill: label
            anchors.margins: -10
        }

        Text {
            id: label
            color: "white"
            wrapMode: Text.WordWrap
            text: "These three gradient boxes are colorized using a custom material."
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 20
        }
    }
    //! [3]

}
