import QtQuick
import FluentUI

FluObject{

    property var navigationView

    id:footer_items

    FluPaneItemSeparator{}

    //设置
    FluPaneItem{
        title:lang.settings
        icon:FluentIcons.Settings
        onTap:{
            navigationView.push("qrc:/QML/page/Settings.qml")
        }
    }

}
