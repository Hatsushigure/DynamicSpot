import QtQuick
import "." as App

Item {
	property color textColor
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
		anchors.centerIn: root
		padding: 6
		spacing: 8
		rows: 1; columns: 2
		verticalItemAlignment: Grid.AlignVCenter

		App.TimeBanner {
			id: timeBanner
			objectName: "timeBanner"
			height: containerHeight + radius
			textColor: root.textColor
			color: backgroundColor
		}

		App.CountDown {
			id: countDown
			objectName: "countDown"
			height: containerHeight + radius
			textColor: root.textColor
			color: backgroundColor
		}
	}
}
