import QtQuick
import FluentUI

//导航栏具体页面
//TODO：现有书库，收藏书单，搜索图书，设置界面
//设置界面的跳转在ItemsFooter.qml文件中

FluObject{

    property var navigationView

    //前往主页
    FluPaneItem{
        title:lang.home
        icon:FluentIcons.Home
        onTap:{
            navigationView.push("qrc:/QML/page/Home.qml")
        }
    }

    //前往我的书库
    FluPaneItemExpander{
        title:lang.books_already_input
        icon:FluentIcons.TreeFolderFolderOpen
        FluPaneItem{
            title:"我的图书"
            image:"qrc:/resource/image/control/Button.png"
            flag:1
            desc:"你所有导入的书都会被呈现在这里"
            onTap:{
                navigationView.push("qrc:/QML/page/Books.qml")
            }
        }
        FluPaneItem{
            title:"我的收藏"
            image:"qrc:/resource/image/control/Button.png"
            flag:1
            desc:"你所有导入的书都会被呈现在这里"
            onTap:{
                navigationView.push("qrc:/QML/page/Collection.qml")
            }
        }
        //FluPaneItem{
        //    title:"我的书签"
        //   image:"qrc:/resource/image/control/Slider.png"
        //    getEntrance:true
        //    desc:"A control that lets the user select from a rangeof values by moving a Thumb control along atrack."
        //    onTap:{
        //        navigationView.push("qrc:/QML/page/Bookmark.qml")
        //    }
        //}
<<<<<<< HEAD
        FluPaneItem{
            title:"我的图书计划"
            image:"qrc:/resource/image/control/Checkbox.png"
            flag:1
            desc:"A control that a user can select or clear."
            onTap:{
                navigationView.push("qrc:/QML/page/Plan.qml")
            }
        }     
    }
//在首页显示窗口的快速入口
    function fasterEntance(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem && item.flag){
                arr.push(item)
            }
        }
        return arr
    }

    function getSearchData(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem){
                arr.push({title:item.title,key:item.key})
            }
        }
        return arr
    }

    function startPageByItem(data){
        navigationView.startPageByItem(data)
    }

}
