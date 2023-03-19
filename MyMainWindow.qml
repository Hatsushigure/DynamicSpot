import QtQuick
import "." as App

Item {
	id: root
	anchors.fill: parent

	Row {
		id: container
		objectName: "container"
		anchors.centerIn: root
		padding: 6
		spacing: 8

		Item {
			width: timeBanner.width
			height: Math.max(timeBanner.height, countDown.height)

			App.TimeBanner {
				id: timeBanner
				objectName: "timeBanner"
				anchors.centerIn: parent
				height: containerHeight + radius
			}
		}

		Item {
			width: countDown.width
			height: Math.max(timeBanner.height, countDown.height)

			App.CountDown {
				id: countDown
				objectName: "countDown"
				anchors.centerIn: parent
				height: containerHeight + radius
			}
		}
	}
}
