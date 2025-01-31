import QtQuick
import QtQuick.Controls.Material
import "." as App

Window {
	id: theWindow
	minimumWidth: aboutPage.implicitWidth
	title: "DynamicSpot 设置"
	height: 400
	visible: true
	ScrollView {
		id: scrollView
		anchors.fill: parent
		contentWidth: width;
		onHeightChanged: aboutPage.height = Math.max(scrollView.height, aboutPage.implicitHeight)
		App.AboutPage {
			id: aboutPage
			width: scrollView.width
		}
	}
}
