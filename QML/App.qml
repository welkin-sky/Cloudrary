import QtQuick
import QtQuick.Controls
import FluentUI

FluWindow {
    id:app
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
