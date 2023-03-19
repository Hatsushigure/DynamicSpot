import QtQuick

Rectangle {
	property alias containerHeight: container.height
	property color textColor
	property int daysLeft: getDaysLeft()

	id: root
	width: Math.max(container.width, container.height) + radius
	radius: Math.max(container.height, container.width)
	color: "#4d000000"
	state: "showShort"
	states: [
		State {
			name: "showShort"

			PropertyChanges {
				target: fullLabel
				opacity: 0
			}
			PropertyChanges {
				target: shortLabel;
				opacity: 1
			}
			PropertyChanges {
				target: container
				width: shortLabel.implicitWidth
				height: shortLabel.implicitHeight
			}
			PropertyChanges {
				target: root
				radius: Math.max(container.height, container.width)
			}
		},
		State {
			name: "showFull"

			PropertyChanges {
				target: fullLabel
				opacity: 1
			}
			PropertyChanges {
				target: shortLabel
				opacity: 0
			}
			PropertyChanges {
				target: container
				width: fullLabel.implicitWidth
				height: fullLabel.implicitHeight
			}
			PropertyChanges {
				target: root
				radius: 12
			}
		}
	]
	transitions: [
		Transition {
			from: "showShort"
			to: "showFull"

			SequentialAnimation {
				NumberAnimation {target: shortLabel; duration: 300; property: "opacity"}
				NumberAnimation {target: root; duration: 300; property: "radius"}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 600; properties: "width, height"}
				NumberAnimation {target: fullLabel; duration: 300; property: "opacity"}
			}
		},
		Transition {
			from: "showFull"
			to: "showShort"

			SequentialAnimation {
				NumberAnimation {target: fullLabel; duration: 300; property: "opacity"}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 500; properties: "width, height"}
				NumberAnimation {target: root; duration: 300; property: "radius"}
				NumberAnimation {target: shortLabel; duration: 300; property: "opacity"}
			}
		}
	]

	Behavior on textColor {
		PropertyAnimation {target: root; property: "textColor"; duration: 500}
	}

	Item {
		id: container
		anchors.centerIn: parent
		width: shortLabel.implicitWidth; height: shortLabel.implicitHeight

		Text {
			id: shortLabel
			color: root.textColor
			textFormat: Text.MarkdownText
			text: "<span style=\"color: red; font-weight: bold\">" + daysLeft + "</span>"
			font.pointSize: 24
		}
		Text {
			id: fullLabel
			color: root.textColor
			textFormat: Text.MarkdownText
			text: "距离高考仅剩 <span style=\"color: red; font-weight: bold\">" + daysLeft + "</span> 天"
			font.pointSize: 24
		}
	}

	Timer {
		id: stateChangeTimer
		interval: (Math.random() % 10 + 10) * 1000
		running: true
		repeat: true
		onTriggered: {
			interval = (Math.random() % 10 + 10) * 1000
			root.state = (root.state === "showShort" ? "showFull" : "showShort")
		}
	}

	function getDaysLeft() {
		var begin = new Date()
		var end = new Date()
		end.setFullYear(2023)
		end.setMonth(5)
		end.setDate(7)
		return (end - begin) / (1000 * 60 * 60 * 24)
	}
}
