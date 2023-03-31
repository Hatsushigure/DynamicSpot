import QtQuick
import "." as App

Item {
	id: root
	anchors.fill: parent

	states: [
		State {
			name: "aprilFool"
			PropertyChanges {
				target: rotateAnima
				running: true
			}
		}
	]

	transitions: Transition {
		from: "*"; to: "aprilFool"

		PropertyAction {target: rotateAnima}
	}

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

		RotationAnimation {
			id: rotateAnima
			from: 0; to: 360
			duration: 1000
			target: container
			onFinished: {
				if (rotateAnima.duration > 250)
					rotateAnima.duration *= 0.9
				rotateAnima.start()
			}
		}
	}
}
