import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
Window {
    visible: true
    width: 310
    height: 150
    maximumHeight: height
    minimumHeight: height
    maximumWidth: width
    minimumWidth: width
    title: qsTr("Hello World")
    GridLayout{
        id: grid
        rows: 3
        columns: 2
        TextField{
            Layout.column: 1
            Layout.row: 1
            id: textFieldFile

        }
        TextField{
            Layout.column: 1
            Layout.row: 2
            text: "127.0.0.1"
            id: textFieldIP

        }
        TextField{
            Layout.column: 1
            Layout.row: 3
            id: textFieldPORT

        }
        Button{
            Layout.column: 2
            Layout.row: 1
            id: buttonBrowse
            text: "Browse..."
            onClicked: fileDialog.open()

        }
        Button{
            Layout.column: 2
            Layout.row: 2
            id: buttonSTART
            text: "Start!"
            onClicked: workerController.startConnection(textFieldIP.text,textFieldPORT.text)
        }

    }
    FileDialog{
        id: fileDialog
        title: "Choose file to send..."
        //folder: shortcuts.home
        onAccepted: {
           textFieldFile.text = fileDialog.fileUrl
        }
    }

}
