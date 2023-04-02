import QtQuick

Rectangle {
	property color textColor
	property alias containerHeight: container.height
	property alias shortText: shortLabel.text
	property alias fullText: fullLabel.text

	id: root
	width: Math.max(container.width, container.height) + radius
	radius: Math.max(container.height, container.width)
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
				NumberAnimation {target: shortLabel; duration: 250; property: "opacity"}
				NumberAnimation {target: root; duration: 250; property: "radius"; easing.type: Easing.OutExpo}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				NumberAnimation {target: fullLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showFull"
			to: "showShort"

			SequentialAnimation {
				NumberAnimation {target: fullLabel; duration: 250; property: "opacity"}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutExpo; duration: 750; properties: "width, height"}
				NumberAnimation {target: root; duration: 250; property: "radius"; easing.type: Easing.InExpo}
				NumberAnimation {target: shortLabel; duration: 250; property: "opacity"}
			}
		}
	]

	Item {
		id: container
		anchors.centerIn: parent
		width: shortLabel.implicitWidth; height: shortLabel.implicitHeight

		Text {
			id: shortLabel
			color: root.textColor
			textFormat: Text.MarkdownText
			text: "<span style=\"color: red; font-weight: bold\">" + 99 + "</span>"
			font.pointSize: 26
		}
		Text {
			id: fullLabel
			color: root.textColor
			textFormat: Text.MarkdownText
			text: "距离高考仅剩 <span style=\"color: red; font-weight: bold\">" + 99 + "</span> 天"
			font.pointSize: 26
		}
	}

	Timer {
		id: stateChangeTimer
		interval: (Math.random() % 5 + 5) * 1000 * 60
		running: true
		repeat: true
		onTriggered: {
			interval = (Math.random() % 5 + 5) * 1000 * 60
			root.state = (root.state === "showShort" ? "showFull" : "showShort")
		}
	}
}
