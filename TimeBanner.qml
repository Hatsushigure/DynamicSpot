import QtQuick

Rectangle {
	property alias containerHeight: container.height
	property alias timeText: timeLabel.text
	property alias sloganText: sloganLabel.text
	property color textColor

	id: root
	width: container.width + radius
	radius: 12
	color: "#4d000000"
	state: "showTime"
	states: [
		State {
			name: "showTime"

			PropertyChanges {
				target: sloganLabel
				opacity: 0
			}
			PropertyChanges {
				target: timeLabel;
				opacity: 1
			}
			PropertyChanges {
				target: container
				width: timeLabel.implicitWidth
				height: timeLabel.implicitHeight
			}
		},
		State {
			name: "showSlogan"

			PropertyChanges {
				target: sloganLabel
				opacity: 1
			}
			PropertyChanges {
				target: timeLabel
				opacity: 0
			}
			PropertyChanges {
				target: container
				width: sloganLabel.implicitWidth
				height: sloganLabel.implicitHeight
			}
		}
	]
	transitions: [
		Transition {
			from: "showTime"
			to: "showSlogan"

			SequentialAnimation {
				PropertyAnimation {target: timeLabel; duration: 250; property: "opacity"}
				PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showSlogan"
			to: "showTime"

			SequentialAnimation {
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
				PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				PropertyAnimation {target: timeLabel; duration: 250; property: "opacity"}
			}
		}
	]

	Behavior on textColor {
		PropertyAnimation {target: root; property: "textColor"; duration: 500}
	}

	Item {
		id: container
		anchors.centerIn: root
		width: timeLabel.implicitWidth; height: timeLabel.implicitHeight

		Text {
			id: timeLabel
			anchors.centerIn: container
			textFormat: Text.MarkdownText
			color: root.textColor
			text: "00:00:00"
			font.pointSize: 26
		}

		Text {
			id: sloganLabel
			anchors.centerIn: container
			textFormat: Text.MarkdownText
			color: root.textColor
			text: "平凡者做完，优秀者做好，卓越者做到极致"
			font.pointSize: 26
		}
	}

	Timer {
		id: changeTimeTimer
		interval: 500
		running: true
		repeat: true
		onTriggered: root.timeText = Qt.formatTime(new Date(), "HH:mm:ss")
	}

	Timer {
		id: showSloganTimer
		interval: 60 * 1000
		onTriggered: {
			root.state = "showTime"
			showTimeTimer.interval = (Math.random() % 10 + 10) * 1000 * 60
			showTimeTimer.start()
		}
	}

	Timer {
		id: showTimeTimer
		interval: (Math.random() % 10 + 10) * 1000 * 60
		running: true
		onTriggered: {
			root.state = "showSlogan"
			showSloganTimer.start()
		}
	}
}
