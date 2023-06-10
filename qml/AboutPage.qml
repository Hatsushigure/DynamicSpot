import QtQuick
import QtQuick.Controls.Material as Controls
import QtQuick.Layouts
import DynamicSpot

Rectangle {
	color: "lightgray"
	implicitWidth: grid1.implicitWidth; implicitHeight: grid1.implicitHeight

	GridLayout {
		id: grid1
		anchors.fill: parent
		columns: 1; rows: 4
		rowSpacing: 16

		Rectangle {
			Layout.leftMargin: 16; Layout.topMargin: 16; Layout.rightMargin: 16
			Layout.preferredWidth: grid2.implicitWidth; Layout.preferredHeight: grid2.implicitHeight
			Layout.fillWidth: true
			color: "white"
			border.width: 1; border.color: "gray"
			radius: 16

			GridLayout {
				id: grid2
				anchors.fill: parent
				rows:2; columns: 1
				rowSpacing: 8

				GridLayout {
					Layout.fillWidth: true
					Layout.topMargin: 8; Layout.leftMargin: 8; Layout.rightMargin: 8
					rows:6; columns: 4
					rowSpacing: 4; columnSpacing: 4
					flow: GridLayout.TopToBottom

					HeSvgItem {
						aspectRatioMode: Qt.KeepAspectRatio
						Layout.preferredWidth: 80; Layout.preferredHeight: 80
						Layout.rowSpan: 6
						source: ":/DynamicSpot/images/icons/dynamicspot-logo-256.svg"
					}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Text {text: "DynamicSpot"; font.pointSize: 16}
					Text {text: "v0.3.0"}
					Text {text: "MIT Licence"; color: "gray"}
					Text {text: "https://github.com/Hatsushigure/DynamicSpot"; color: "gray"}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Controls.RoundButton {
						text: "查看 README"
						radius: 4
						Layout.rowSpan: 6
						onClicked: Qt.openUrlExternally("https://github.com/Hatsushigure/DynamicSpot/blob/main/README.md")
					}
				}
				GridLayout {
					Layout.fillWidth: true
					Layout.leftMargin: 8; Layout.bottomMargin: 8; Layout.rightMargin: 8
					rows:4; columns: 2
					rowSpacing: 4; columnSpacing: 4
					flow: GridLayout.TopToBottom

					Image {
						Layout.preferredWidth: 80; Layout.preferredHeight: 80
						Layout.rowSpan: 4
						source: "qrc:/DynamicSpot/images/icons/avatar/avatar - 256.png"
						asynchronous: true
						mipmap: true
					}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Text {text: "初時雨"; font.pointSize: 12}
					Text {text: "本软件的唯一作者, 所有的代码都是这一个人敲的"; color: "gray"}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
				}
			}
		}
		Rectangle {
			Layout.leftMargin: 16; Layout.rightMargin: 16
			Layout.preferredWidth: grid3.implicitWidth; Layout.preferredHeight: grid3.implicitHeight
			Layout.fillWidth: true
			color: "white"
			border.width: 1; border.color: "gray"
			radius: 16

			GridLayout {
				id: grid3
				anchors.fill: parent
				rows:2; columns: 1
				rowSpacing: 8

				GridLayout {
					Layout.fillWidth: true
					Layout.leftMargin: 8; Layout.topMargin: 8; Layout.rightMargin: 8
					rows: 5; columns: 2
					rowSpacing: 4; columnSpacing: 4
					flow: GridLayout.TopToBottom

					HeSvgItem {
						aspectRatioMode: Qt.KeepAspectRatio
						Layout.preferredWidth: 80; Layout.preferredHeight: 80
						Layout.rowSpan: 5
						source: ":/DynamicSpot/images/icons/qt-logo.svg"
					}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Text {text: "Qt"; font.pointSize: 12}
					Text {text: "6.5.1"; color: "gray"}
					Text {text: "https://qt.io"; color: "gray"}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
				}
				GridLayout {
					Layout.fillWidth: true
					Layout.leftMargin: 8; Layout.bottomMargin: 8; Layout.rightMargin: 8
					rows: 5; columns: 4
					rowSpacing: 4; columnSpacing: 4
					flow: GridLayout.TopToBottom

					HeSvgItem {
						aspectRatioMode: Qt.KeepAspectRatio
						Layout.preferredWidth: 80; Layout.preferredHeight: 80
						Layout.rowSpan: 5
						source: ":/DynamicSpot/images/icons/icons8-logo-256.svg"
					}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Text {text: "Icons8"; font.pointSize: 12}
					Text {text: "感谢由 Icons8 提供的超多好看的图标!"; color: "gray"}
					Text {text: "https://icons8.com"; color: "gray"}
					Item {Layout.fillWidth: true; Layout.fillHeight: true}
					Controls.RoundButton {
						Layout.rowSpan: 5
						text: "打开网站"
						radius: 4
						onClicked: Qt.openUrlExternally("https://icons8.com")
					}
				}
			}
		}
		Rectangle {
			Layout.leftMargin: 16; Layout.rightMargin: 16
			Layout.preferredWidth: grid4.implicitWidth; Layout.preferredHeight: grid4.implicitHeight
			Layout.fillWidth: true
			color: "white"
			border.width: 1; border.color: "gray"
			radius: 16

			GridLayout {
				id: grid4
				anchors.fill: parent
				rows:1; columns: 1

				GridLayout {
					Layout.margins: 8
					rows: 3; columns: 5
					rowSpacing: 4; columnSpacing: 4

					Text {text: "其他信息"; font.bold: true; font.pointSize: 16; Layout.columnSpan: 5}
					Item {Layout.fillWidth: true; Layout.fillHeight: true; Layout.rowSpan: 2}
					Controls.RoundButton {
						Layout.alignment: Qt.AlignHCenter
						text: "查看许可证"
						radius: 4
						onClicked: {Qt.openUrlExternally("https://github.com/Hatsushigure/DynamicSpot/blob/main/LICENCE")}
					}
					Controls.RoundButton {
						Layout.alignment: Qt.AlignHCenter
						text: "查看源代码"
						radius: 4
						onClicked: Qt.openUrlExternally("https://github.com/Hatsushigure/DynamicSpot")
					}
					Controls.RoundButton {
						Layout.alignment: Qt.AlignHCenter
						text: "联系作者"
						radius: 4
						onClicked: Qt.openUrlExternally("mailto:Hatsushigure_c@163.com")
					}
					Item {Layout.fillWidth: true; Layout.fillHeight: true; Layout.rowSpan: 2}
					Controls.RoundButton {
						Layout.alignment: Qt.AlignHCenter
						text: "Github 个人首页"
						radius: 4
						onClicked: Qt.openUrlExternally("https://github.com/Hatsushigure")
					}
					Controls.RoundButton {
						Layout.alignment: Qt.AlignHCenter
						text: "初時雨の小窝"
						radius: 4
						onClicked: Qt.openUrlExternally("https://hatsushigure.github.io")
					}
				}
			}
		}
		Item {Layout.fillWidth: true; Layout.fillHeight: true}
		Text {text: "Build with Qt 6.5.1. Copyright(c) Hatsushigure, all rights reserved."; color: "gray"; Layout.alignment: Qt.AlignHCenter}
	}
}
