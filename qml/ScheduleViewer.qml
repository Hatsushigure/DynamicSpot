import QtQuick
import DynamicSpot

Item {
	property string iconFileName
	property alias titleText: titleLabel.text
	property alias subtitleText: subtitleLabel.text
	property color textColor

	id: root
	implicitHeight: Math.max(icon1.height, container.implicitHeight)
	implicitWidth: icon1.width + container.implicitWidth
	onIconFileNameChanged: {
		if (iconFileName.search(".svg") == iconFileName.length - 4) {
			icon1.visible = true
			icon2.visible = false
			icon1.source = iconFileName
		}
		else {
			icon2.visible = true
			icon1.visible = false
			icon2.source = iconFileName
		}

	}

	HeSvgItem {
		id: icon1
		aspectRatioMode: Qt.KeepAspectRatio
		anchors.left: root.left
		anchors.verticalCenter: root.verticalCenter
		width: 96; height: width
	}

	Image {
		id: icon2
		anchors.left: root.left
		anchors.verticalCenter: root.verticalCenter
		width: 96; height: width
		asynchronous: true
		mipmap: true
	}

	Grid {
		id: container
		anchors.right: root.right
		anchors.verticalCenter: root.verticalCenter
		rows: 2; columns: 1
		horizontalItemAlignment: Grid.AlignHCenter
		verticalItemAlignment: Grid.AlignVCenter

		Text {
			id: titleLabel
			color: textColor
			font.bold: true
			font.pointSize: 24
		}

		Text {
			id: subtitleLabel
			color: textColor
			font.pointSize: 16
		}
	}
}
