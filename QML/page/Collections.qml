import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI

FluScrollablePage{

    title:"Collections"

    Component.onCompleted: {
        const columns = [
                          {
                              title: '书籍',
                              dataIndex: 'name',
                              width:100
                          },
                          {
                              title: '作者',
                              dataIndex: 'author',
                              width:100
                          },
                          {
                              title: '出版社·',
                              dataIndex: 'press',
                              width:270
                          },
                          {
                              title: '操作',
                              dataIndex: 'action',
                              width:150
                          },
                      ];
        table_view.columns = columns
        loadData(1,10)
    }

    FluTableView{
        id:table_view
        Layout.fillWidth: true
        Layout.topMargin: 20
        pageCurrent:1
        pageCount:10
        itemCount: 1000
        onRequestPage:
            (page,count)=> {
                loadData(page,count)
            }
    }


    Component{
        id:com_action
        Item{
            Row{
                anchors.centerIn: parent
                spacing: 10
                FluFilledButton{
                    text:"打开"
                    horizontalPadding: 6
                    onClicked:{
                        showSuccess(JSON.stringify(dataObject)) //这里两个也都要改
                    }
                }
                FluFilledButton{
                    text:"取消收藏"
                    horizontalPadding: 6
                    onClicked:{
                        showError(JSON.stringify(dataObject))
                    }
                }

            }
        }
    }

    //给出一个showSuccess函数的定义，其他的都是类似的，一共有showSuccess,showInfo,showError,showWarning四种
    //    function showSuccess(text,duration=1000,moremsg){
    //            mcontrol.create(mcontrol.const_success,text,duration,moremsg ? moremsg : "");
    //        }

    function loadData(page,count){
        const dataSource = []
        for(var i=0;i<count;i++){
            dataSource.push({
                                name: "xx".arg(((page-1)*count+i)),
                                author: "xx",
                                press: "xxx",
                                action:com_action
                            })
        }
        table_view.dataSource = dataSource
    }
}
