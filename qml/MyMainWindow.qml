import QtQuick
import "." as App

Item {
	property color textColor: "cyan"
	property color backgroundColor: "#80000000"

	id: root
	anchors.fill: parent

	Behavior on textColor {
		ColorAnimation {duration: 500}
	}
	Behavior on backgroundColor {
		ColorAnimation {duration: 500}
	}

	Grid {
		id: container
		objectName: "container"
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		padding: 6
		spacing: 8
		rows: 1; columns: 2
		verticalItemAlignment: Grid.AlignVCenter

		App.TimeBanner {
			id: timeBanner
			objectName: "timeBanner"
			textColor: root.textColor
			color: backgroundColor
		}

		App.CountDown {
			id: countDown
			objectName: "countDown"
			textColor: root.textColor
			color: backgroundColor
		}
	}
}
