import QtQuick 2.12
import QtQuick.Window 2.12

import CustomItems 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    CustomBox{
        id: box1
        width: 300
        height: 100
        color: "yellow"
        alternateColor: "green"
    }
    CustomBox{
        id: box2
        anchors.top: box1.bottom
        width: 300
        height: 100
        color: "orange"
        alternateColor: "red"
    }

}
