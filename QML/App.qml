import QtQuick
import QtQuick.Controls
import FluentUI

Window {
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
