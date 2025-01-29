import QtQuick
import DynamicSpot

Item {
	property string iconFileName
	property alias titleText: titleLabel.text
	property alias subtitleText: subtitleLabel.text
	property color textColor

	id: root
	implicitHeight: Math.max(eventIcon.height, container.implicitHeight)
	implicitWidth: eventIcon.width + container.implicitWidth

	Image {
		id: eventIcon
		anchors.left: root.left
		anchors.verticalCenter: root.verticalCenter
		width: 96; height: width
		asynchronous: true	// FIXME
		source: iconFileName
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
