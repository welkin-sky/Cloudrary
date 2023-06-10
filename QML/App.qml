import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

Window {
    id:app
    height: 600
    width: 1000
    Component.onCompleted: {
        FluApp.init(app)
        FluTheme.frameless = true
        FluApp.routes={
            "/":"qrc:/QML/Main.qml"
        }
        FluApp.initialRoute = "/"
        FluApp.run()
    }
}
