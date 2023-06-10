import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import FluentUI
import "./global"

FluWindow {                         //主页面
    title: "Cloudrary"
    width: 1000
    height: 640
    closeDestory:false
    minimumWidth: 520
    minimumHeight: 460
    launchMode: FluWindow.SingleTask
    visible: true
    FluNavigationView2{             //导航栏
            id:nav_view
            anchors.fill: parent
            items: ItemsOriginal
            footerItems:ItemsFooter
            z:11
            displayMode:MainEvent.displayMode
            logo: "qrc:/resource/image/cloudrary_icon.png"
            title:"Cloudrary"
            autoSuggestBox:FluAutoSuggestBox{
                width: 280
                anchors.centerIn: parent
                iconSource: FluentIcons.Search
                items: ItemsOriginal.getSearchData()
                placeholderText: lang.search
                onItemClicked:
                    (data)=>{
                        ItemsOriginal.startPageByItem(data)
                    }
            }
            actionItem:Item{
                height: 40
                width: 148
                RowLayout{
                    anchors.centerIn: parent
                    spacing: 5
                    FluText{
                        text:lang.dark_mode
                    }
                    FluToggleSwitch{
                        checked: FluTheme.dark
                        onClicked: {
                            if(FluTheme.dark){
                                FluTheme.darkMode = FluDarkMode.Light
                            }else{
                                FluTheme.darkMode = FluDarkMode.Dark
                            }
                        }
                    }
                }
            }
            Component.onCompleted: {
                ItemsOriginal.navigationView = nav_view
                ItemsFooter.navigationView = nav_view
            }
        }

}